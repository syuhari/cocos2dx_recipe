//
//  Recipe58_3.h
//  RecipeBook
//
//  Created by FURUKI Eiji on 13/05/31.
//
//

#ifndef __RecipeBook__Recipe58_3__
#define __RecipeBook__Recipe58_3__

#include "cocos2d.h"
#include "RecipeBase.h"

class Recipe58_3 : public RecipeBase
{
private:
public:
    Recipe58_3();
    virtual bool init();
    static cocos2d::CCScene* scene();
    CREATE_FUNC(Recipe58_3);
    
    virtual void onEnter();
};

#endif /* defined(__RecipeBook__Recipe58_3__) */
