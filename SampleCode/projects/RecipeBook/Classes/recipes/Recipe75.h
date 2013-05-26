//
//  Recipe75.h
//  RecipeBook
//
//  Created by Kenji Saito on 5/25/13.
//  Copyright 2013 Syuhari, Inc. All rights reserved.
//

#ifndef _RecipeBook_Recipe75_H_
#define _RecipeBook_Recipe75_H_

#include "cocos2d.h"
#include "RecipeBase.h"
#include "DictationManager.h"

USING_NS_CC;

class Recipe75 : public RecipeBase, DictationManagerDelegate
{
public:
    virtual bool init();
    static cocos2d::CCScene* scene();
    CREATE_FUNC(Recipe75);
    
    // デリゲートメソッドをオーバーライドします
    virtual void onResults(CCArray* results);
    virtual void onError(int errorCode);
    
    // 処理を依頼するメソッド
    void keyMenuTapped();
    
    bool ccTouchBegan(CCTouch* pTouch, CCEvent* pEvent);
};

#endif // _RecipeBook_Recipe75_H_
