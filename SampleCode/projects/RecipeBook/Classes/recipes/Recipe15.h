//
//  Recipe15.h
//  RecipeBook
//
//  Created by Kenji Saito on 5/25/13.
//  Copyright 2013 Syuhari, Inc. All rights reserved.
//

#ifndef _RecipeBook_Recipe15_H_
#define _RecipeBook_Recipe15_H_

#include "cocos2d.h"
#include "RecipeBase.h"

class Recipe15 : public RecipeBase
{
public:
    virtual bool init();
    static cocos2d::CCScene* scene();
    CREATE_FUNC(Recipe15);
    
    void method1();
    void callback1();
    void callback2(CCNode* sender);
    void callback3(CCNode* sender, void* data);
    void callback4(CCObject* object);
};

#endif // _RecipeBook_Recipe15_H_
