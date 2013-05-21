//
//  Recipe42.h
//  RecipeBook
//
//  Created by Akihiro Matsuura on 5/22/13.
//  Copyright 2013 Syuhari, Inc. All rights reserved.
//

#ifndef _RecipeBook_Recipe42_H_
#define _RecipeBook_Recipe42_H_

#include "cocos2d.h"
#include "RecipeBase.h"

class Recipe42 : public RecipeBase
{
public:
    virtual bool init();
    static cocos2d::CCScene* scene();
    CREATE_FUNC(Recipe42);
    
    void update(float delta);
};

#endif // _RecipeBook_Recipe42_H_
