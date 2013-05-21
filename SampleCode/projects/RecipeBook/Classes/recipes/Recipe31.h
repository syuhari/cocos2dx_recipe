//
//  Recipe31.h
//  RecipeBook
//
//  Created by Akihiro Matsuura on 5/22/13.
//  Copyright 2013 Syuhari, Inc. All rights reserved.
//

#ifndef _RecipeBook_Recipe31_H_
#define _RecipeBook_Recipe31_H_

#include "cocos2d.h"
#include "RecipeBase.h"

#include "cocos-ext.h"
USING_NS_CC_EXT;

class Recipe31 : public RecipeBase
{
public:
    virtual bool init();
    static cocos2d::CCScene* scene();
    CREATE_FUNC(Recipe31);
    
    // 各パーツのコールバック
    void switchCallBack(CCObject* pSender, CCControlEvent controlEvent);
    void sliderCallBack(CCObject* pSender, CCControlEvent controlEvent);
    void stepperCallBack(CCObject* pSender, CCControlEvent controlEvent);
    void colorCallBack(CCObject* pSender, CCControlEvent controlEvent);
    void potentiometerCallBack(CCObject* pSender, CCControlEvent controlEvent);
};

#endif // _RecipeBook_Recipe31_H_
