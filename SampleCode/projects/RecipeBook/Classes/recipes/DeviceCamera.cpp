//
//  DeviceCamera.cpp
//  RecipeBook
//
//  Created by FURUKI Eiji on 13/05/31.
//
//

#include <jni.h>
#include "DeviceCamera.h"
#include "platform/android/jni/JniHelper.h"

#define  CLASS_NAME "jp/syuhari/RecipeBook/RecipeBook"

using namespace std;
using namespace cocos2d;

void launchCameraJNI()
{
    JniMethodInfo t;
    const char* ret = NULL;
    if (JniHelper::getStaticMethodInfo(t, CLASS_NAME, "launchCamera", "()V"))
    {
        t.env->CallStaticVoidMethod(t.classID, t.methodID);
        t.env->DeleteLocalRef(t.classID);
    }
}

extern "C" {
    JNIEXPORT void JNICALL Java_jp_syuhari_RecipeBook_RecipeBook_nativeDidTakenPhoto(JNIEnv*  env, jobject thiz, int size, jbyteArray pixels)
    {
        unsigned char* data = new unsigned char[size];
        env->GetByteArrayRegion(pixels, 0, size, (jbyte*)data);
        
        // 画像をCCTexture2Dにしてデリゲートで通知する
        cocos2d::CCImage *ccImage = new cocos2d::CCImage();
        if (ccImage->initWithImageData((void*)data, size))
        {
            cocos2d::CCTexture2D *ccTexture = new cocos2d::CCTexture2D();
            if (ccTexture->initWithImage(ccImage))
            {
                DeviceCamera* cam = DeviceCamera::sharedInstance();
                cam->didTakePhoto(ccTexture);
            }
            CC_SAFE_RELEASE(ccTexture);
        }
        CC_SAFE_RELEASE(ccImage);
        delete [] data;
    }
}

DeviceCamera* DeviceCamera::instance = NULL;

DeviceCamera* DeviceCamera::sharedInstance()
{
    if (instance == NULL)
    {
        instance = new DeviceCamera();
    }
    return instance;
}

void DeviceCamera::launchCamera()
{
    launchCameraJNI();
}

void DeviceCamera::didTakePhoto(cocos2d::CCTexture2D *texture)
{
    if (m_delegate)
    {
        m_delegate->onDeviceCameraDidFinishPick(texture);
    }
}
