//
//  Recipe60.h
//  RecipeBook
//
//  Created by FURUKI Eiji on 13/05/31.
//
//

#ifndef __RecipeBook__Recipe60__
#define __RecipeBook__Recipe60__

#include "cocos2d.h"
#include "RecipeBase.h"

class Recipe60 : public RecipeBase
{
private:    
public:
    Recipe60();
    virtual bool init();
    static cocos2d::CCScene* scene();
    CREATE_FUNC(Recipe60);
    
    virtual void onEnter();
};

#endif /* defined(__RecipeBook__Recipe60__) */
