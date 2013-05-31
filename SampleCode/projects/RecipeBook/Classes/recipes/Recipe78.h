//
//  Recipe78.h
//  RecipeBook
//
//  Created by FURUKI Eiji on 13/05/31.
//
//

#ifndef __RecipeBook__Recipe78__
#define __RecipeBook__Recipe78__

#include "cocos2d.h"
#include "RecipeBase.h"

class Recipe78 : public RecipeBase
{
private:
public:
    Recipe78();
    virtual bool init();
    static cocos2d::CCScene* scene();
    CREATE_FUNC(Recipe78);
    
    virtual void onEnter();
    virtual void onExit();
    virtual void didAccelerate(cocos2d::CCAcceleration* pAccl);
};

#endif /* defined(__RecipeBook__Recipe78__) */
