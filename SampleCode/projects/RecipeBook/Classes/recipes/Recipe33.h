//
//  Recipe33.h
//  RecipeBook
//
//  Created by Akihiro Matsuura on 5/22/13.
//  Copyright 2013 Syuhari, Inc. All rights reserved.
//

#ifndef _RecipeBook_Recipe33_H_
#define _RecipeBook_Recipe33_H_

#include "cocos2d.h"
#include "RecipeBase.h"

class Recipe33 : public RecipeBase
{
public:
    virtual bool init();
    static cocos2d::CCScene* scene();
    CREATE_FUNC(Recipe33);
    
    // ボタンのコールバック
    void menuCloseCallback(CCObject* pSender);
};

#endif // _RecipeBook_Recipe33_H_
