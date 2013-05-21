//
//  Recipe43.h
//  RecipeBook
//
//  Created by Akihiro Matsuura on 5/22/13.
//  Copyright 2013 Syuhari, Inc. All rights reserved.
//

#ifndef _RecipeBook_Recipe43_H_
#define _RecipeBook_Recipe43_H_

#include "cocos2d.h"
#include "RecipeBase.h"

class Recipe43 : public RecipeBase
{
private:
    int m_iSec;
public:
    virtual bool init();
    static cocos2d::CCScene* scene();
    CREATE_FUNC(Recipe43);
    
    void updatePerSec();
};

#endif // _RecipeBook_Recipe43_H_
