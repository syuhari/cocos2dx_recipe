//
//  Recipe22.h
//  RecipeBook
//
//  Created by Kenji Saito on 5/25/13.
//  Copyright 2013 Syuhari, Inc. All rights reserved.
//

#ifndef _RecipeBook_Recipe22_H_
#define _RecipeBook_Recipe22_H_

#include "cocos2d.h"
#include "RecipeBase.h"

class Recipe22 : public RecipeBase
{
public:
    virtual bool init();
    static cocos2d::CCScene* scene();
    CREATE_FUNC(Recipe22);
    
    void method1();
};

#endif // _RecipeBook_Recipe22_H_
