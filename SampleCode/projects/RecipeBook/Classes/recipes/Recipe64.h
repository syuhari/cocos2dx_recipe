//
//  Recipe64.h
//  RecipeBook
//
//  Created by FURUKI Eiji on 13/05/31.
//
//

#ifndef __RecipeBook__Recipe64__
#define __RecipeBook__Recipe64__

#include "cocos2d.h"
#include "RecipeBase.h"
#include "DeviceCamera.h"

class Recipe64 : public RecipeBase, public DeviceCameraDelegate
{
private:
public:
    Recipe64();
    virtual bool init();
    static cocos2d::CCScene* scene();
    CREATE_FUNC(Recipe64);
    
    virtual void onEnter();
    virtual void ccTouchesBegan(cocos2d::CCSet* touches, cocos2d::CCEvent* event);
    virtual void onDeviceCameraDidFinishPick(cocos2d::CCTexture2D *texture);
};

#endif /* defined(__RecipeBook__Recipe64__) */
