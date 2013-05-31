//
//  Recipe77.h
//  RecipeBook
//
//  Created by FURUKI Eiji on 13/05/31.
//
//

#ifndef __RecipeBook__Recipe77__
#define __RecipeBook__Recipe77__

#include "cocos2d.h"
#include "RecipeBase.h"

class Recipe77 : public RecipeBase
{
private:
public:
    Recipe77();
    virtual bool init();
    static cocos2d::CCScene* scene();
    CREATE_FUNC(Recipe77);
    
    virtual void onEnter();
    virtual void onExit();
};

#endif /* defined(__RecipeBook__Recipe77__) */
