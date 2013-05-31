//
//  Recipe57.h
//  RecipeBook
//
//  Created by FURUKI Eiji on 13/05/30.
//
//

#ifndef __RecipeBook__Recipe57__
#define __RecipeBook__Recipe57__

#include "cocos2d.h"
#include "RecipeBase.h"

class Recipe57 : public RecipeBase
{
private:
public:
    Recipe57();
    virtual bool init();
    static cocos2d::CCScene* scene();
    CREATE_FUNC(Recipe57);
    
    virtual void onEnter();
};

#endif /* defined(__RecipeBook__Recipe57__) */
