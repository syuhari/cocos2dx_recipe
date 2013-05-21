//
//  Recipe34.h
//  RecipeBook
//
//  Created by Akihiro Matsuura on 5/22/13.
//  Copyright 2013 Syuhari, Inc. All rights reserved.
//

#ifndef _RecipeBook_Recipe34_H_
#define _RecipeBook_Recipe34_H_

#include "cocos2d.h"
#include "RecipeBase.h"
#include "cocos-ext.h"
USING_NS_CC_EXT;

class Recipe34 : public RecipeBase, public CCScrollViewDelegate
{
public:
    void scrollViewDidScroll(CCScrollView* view);
	void scrollViewDidZoom(CCScrollView* view);
public:
    virtual bool init();
    static cocos2d::CCScene* scene();
    CREATE_FUNC(Recipe34);
};

#endif // _RecipeBook_Recipe34_H_
