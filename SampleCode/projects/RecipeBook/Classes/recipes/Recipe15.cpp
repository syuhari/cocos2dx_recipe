//
//  Recipe15.cpp
//  RecipeBook
//
//  Created by Kenji Saito on 5/25/13.
//  Copyright 2013 Syuhari, Inc. All rights reserved.
//

#include "Recipe15.h"

USING_NS_CC;

CCScene* Recipe15::scene()
{
    CCScene *scene = CCScene::create();
    Recipe15 *layer = Recipe15::create();
    scene->addChild(layer);
    return scene;
}

bool Recipe15::init()
{
    if ( !RecipeBase::init() )
    {
        return false;
    }
    
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    
    int fontSize = CCEGLView::sharedOpenGLView()->getDesignResolutionSize().height/320.0f * 16;
    std::string text = "CCCallFuncを使用して呼び出されたメソッドにより、\nログ出力されます。";
    CCLabelTTF *label = CCLabelTTF::create(text.c_str(), "Helvetica", fontSize);
    label->setPosition(ccp(visibleSize.width/2, visibleSize.height/2));
    this->addChild(label);
    
    CCLog("--- Recipe 15 ------");
    this->method1();
    
    return true;
}

void Recipe15::method1()
{
    // CCCallFuncをシーケンスしたアクション作成
    CCSequence* action1 = CCSequence::create(
                                // CCCallFunc
                                CCCallFunc::create(this, callfunc_selector(Recipe15::callback1)),
                                // CCCallFuncN
                                CCCallFuncN::create(this, callfuncN_selector(Recipe15::callback2)),
                                // CCCallFuncND
                                CCCallFuncND::create(this, callfuncND_selector(Recipe15::callback3),
                                                     (void*)123), // 任意のデータのポインタを渡す
                                // CCCallFuncO
                                CCCallFuncO::create(this, callfuncO_selector(Recipe15::callback4),
                                                    (CCObject*)CCString::create("text")), // CCObjectを渡す
                                NULL);
    // スプライトの作成
    CCSprite *player = CCSprite::create("monkey01.png");
    this->addChild(player);
    // 作成したスプライトでアクションを実行
    player->runAction(action1);
}

// CCCallFuncから呼び出される
void Recipe15::callback1()
{
    CCLog("callback1");
}

// CCCallFuncNから呼び出される
void Recipe15::callback2(CCNode* sender)
{
    CCLog("callback2");
    // スプライトを取得
    CCSprite* player = (CCSprite *)sender;
    player->setVisible(false);
}

// CCCallFuncNDから呼び出される
void Recipe15::callback3(CCNode* sender, void* data)
{
    CCLog("callback3");
    // スプライトを取得
    CCSprite* player = (CCSprite *)sender;
    player->setVisible(false);
    // データを取得
    int num = (int)data;
    CCLog("num: %d", num);
}

// CCCallFuncOから呼び出される
void Recipe15::callback4(CCObject* object)
{
    CCLog("callback4");
    // オブジェクトを取得
    CCString* str = (CCString *)object;
    CCLog("str: %s", str->getCString());
}