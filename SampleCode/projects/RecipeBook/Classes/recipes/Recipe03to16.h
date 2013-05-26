//
//  Recipe03to16.h
//  RecipeBook
//
//  Created by Kenji Saito on 5/25/13.
//  Copyright 2013 Syuhari, Inc. All rights reserved.
//

#ifndef _RecipeBook_Recipe03to16_H_
#define _RecipeBook_Recipe03to16_H_

#include "cocos2d.h"

// レシピ06で変更
//class Recipe03to16 : public cocos2d::CCLayer
//class Recipe03to16 : public cocos2d::CCLayerColor
class Recipe03to16 : public cocos2d::CCLayerGradient
{
protected:
    // レシピ12で追加
    int m_points;
    
    // レシピ13で追加
    int m_actionType;

public:
    virtual bool init();
    static cocos2d::CCScene* scene();
    void menuCloseCallback(CCObject* pSender);
    CREATE_FUNC(Recipe03to16);
    
    
    // レシピ04で追加
    void addFood();
    void gameLogic();
    
    // レシピ05で追加
    void spriteMoveFinished(CCNode* sender);
    
    // レシピ07で追加
    void ccTouchesBegan(cocos2d::CCSet* touches, cocos2d::CCEvent* event);
    
    // レシピ08で追加
    void update(float dt);
    
    // レシピ09で追加
    void eat();
    
    // レシピ11で追加
    void changeMode(CCObject* sender);
};

#endif // _RecipeBook_Recipe03to16_H_
