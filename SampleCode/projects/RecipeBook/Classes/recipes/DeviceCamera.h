//
//  DeviceCamera.h
//  RecipeBook
//
//  Created by FURUKI Eiji on 13/05/31.
//
//

#ifndef __RecipeBook__DeviceCamera__
#define __RecipeBook__DeviceCamera__

#include "cocos2d.h"

class DeviceCameraDelegate
{
public:
    virtual void onDeviceCameraDidFinishPick(cocos2d::CCTexture2D *texture){};
};

class DeviceCamera
{
    static DeviceCamera* instance;
public:
    static DeviceCamera* sharedInstance();
    
    // カメラを起動し写真を撮る
    void launchCamera();
    // SDKから撮った写真をテクスチャにして設定する
    void didTakePhoto(cocos2d::CCTexture2D *texture);
    
    CC_SYNTHESIZE(DeviceCameraDelegate*, m_delegate, Delegate);
};

#endif /* defined(__RecipeBook__DeviceCamera__) */
