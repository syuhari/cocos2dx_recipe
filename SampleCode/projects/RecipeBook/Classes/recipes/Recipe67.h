//
//  Recipe67.h
//  RecipeBook
//
//  Created by FURUKI Eiji on 13/05/31.
//
//

#ifndef __RecipeBook__Recipe67__
#define __RecipeBook__Recipe67__

#include "cocos2d.h"
#include "RecipeBase.h"
#include "AppPlatform.h"

class Recipe67 : public RecipeBase, public AppKeyDelegate
{
private:
public:
    Recipe67();
    virtual bool init();
    static cocos2d::CCScene* scene();
    CREATE_FUNC(Recipe67);
    
    virtual void onEnter();
    virtual void onExit();
    virtual void keyBackClicked();
    virtual void keyMenuClicked();
    virtual void onAppKeyEvent(int keycode);
};

#endif /* defined(__RecipeBook__Recipe67__) */
