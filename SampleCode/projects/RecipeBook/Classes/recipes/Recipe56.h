//
//  Recipe56.h
//  RecipeBook
//
//  Created by FURUKI Eiji on 13/06/16.
//
//

#ifndef __RecipeBook__Recipe56__
#define __RecipeBook__Recipe56__

#include "cocos2d.h"
#include "RecipeBase.h"

class Recipe56 : public RecipeBase
{
private:
public:
    Recipe56();
    virtual bool init();
    static cocos2d::CCScene* scene();
    CREATE_FUNC(Recipe56);
    
    virtual void onEnter();
};

#endif /* defined(__RecipeBook__Recipe56__) */
