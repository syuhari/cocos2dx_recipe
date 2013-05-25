//
//  Recipe46.h
//  RecipeBook
//
//  Created by FURUKI Eiji on 13/05/25.
//
//

#ifndef __RecipeBook__Recipe46__
#define __RecipeBook__Recipe46__

#include "cocos2d.h"
#include "RecipeBase.h"

class Recipe46 : public RecipeBase
{
private:
    int m_count;
public:
    Recipe46();
    virtual bool init();
    static cocos2d::CCScene* scene();
    CREATE_FUNC(Recipe46);

    void updateDraw();
};

#endif /* defined(__RecipeBook__Recipe46__) */
