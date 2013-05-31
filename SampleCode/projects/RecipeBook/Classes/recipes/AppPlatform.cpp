//
//  AppPlatform.cpp
//  RecipeBook
//
//  Created by FURUKI Eiji on 13/05/31.
//
//

#include "AppPlatform.h"
#include <jni.h>
#include "cocoa/CCString.h"
#include "platform/android/jni/JniHelper.h"

#define  CLASS_NAME "jp/syuhari/RecipeBook/RecipeBook"

using namespace std;
using namespace cocos2d;

// Recipe60 アプリーケーションバージョンの取得
const char* AppPlatform::getAppVersion()
{
    JniMethodInfo t;
    const char* ret = NULL;
    if (JniHelper::getStaticMethodInfo(t, CLASS_NAME, "getAppVersion", "()Ljava/lang/String;")) {
        
        jstring jstr = (jstring)t.env->CallStaticObjectMethod(t.classID, t.methodID);
        
        std::string sstr = JniHelper::jstring2string(jstr);
        CCString* cstr = CCString::create(sstr.c_str());
        t.env->DeleteLocalRef(t.classID);
        t.env->DeleteLocalRef(jstr);
        ret = cstr->getCString();
    }
    return ret;
}


extern "C" {
    // Keyboard イベントの通知
    JNIEXPORT void JNICALL Java_jp_syuhari_RecipeBook_RecipeBook_nativeMyKeyDown(JNIEnv * env, jobject thiz, jint keyCode) {
        __android_log_print(ANDROID_LOG_DEBUG,"KeyDown", "keydown in cocos2dx %d", keyCode);
        
        AppKeyDelegate *delegate = AppPlatform::sharedInstance()->getAppKeyDelegate();
        if (delegate != NULL) {
            delegate->onAppKeyEvent(keyCode);
        }
    }
}

AppPlatform* AppPlatform::instance = NULL;

AppPlatform* AppPlatform::sharedInstance()
{
    if (instance == NULL)
    {
        instance = new AppPlatform();
        instance->m_appkeydelegate = NULL;
    }
    return instance;
}
