//
//  Recipe24.h
//  RecipeBook
//
//  Created by Kenji Saito on 5/25/13.
//  Copyright 2013 Syuhari, Inc. All rights reserved.
//

#ifndef _RecipeBook_Recipe24_H_
#define _RecipeBook_Recipe24_H_

#include "cocos2d.h"
#include "RecipeBase.h"

class Recipe24 : public RecipeBase
{
public:
    virtual bool init();
    static cocos2d::CCScene* scene();
    CREATE_FUNC(Recipe24);
    
    void method1();
};

#endif // _RecipeBook_Recipe24_H_
