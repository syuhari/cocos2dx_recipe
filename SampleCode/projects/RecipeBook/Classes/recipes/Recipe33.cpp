//
//  Recipe33.cpp
//  RecipeBook
//
//  Created by Akihiro Matsuura on 5/22/13.
//  Copyright 2013 Syuhari, Inc. All rights reserved.
//

#include "Recipe33.h"
#include "CCScale9Sprite.h"
#include "CCControlButton.h"

USING_NS_CC_EXT;
USING_NS_CC;

CCScene* Recipe33::scene()
{
    CCScene *scene = CCScene::create();
    Recipe33 *layer = Recipe33::create();
    scene->addChild(layer);
    return scene;
}

bool Recipe33::init()
{
    if ( !RecipeBase::init() )
    {
        return false;
    }

    CCSize size = CCDirector::sharedDirector()->getWinSize();
    
    // 画像の実際の大きさ
    CCRect spriteRect = CCRectMake(0, 0, 80, 80);
    // 9つに区切るときの内側の大きさ
    CCRect capInsents = CCRectMake(12, 12, 56, 56);
    CCScale9Sprite* backgroundSprite = CCScale9Sprite::create("button9.png", spriteRect, capInsents);
    
    CCLabelTTF* label = CCLabelTTF::create("ボタン1", "Arial", 30);
    CCControlButton* button = CCControlButton::create(label, backgroundSprite);
    button->setPreferredSize(CCSizeMake(200, 60));
    button->setPosition(ccp(50+button->getContentSize().width/2, size.height/2+button->getContentSize().height));
    this->addChild(button);
    button->addTargetWithActionForControlEvents(this, cccontrol_selector(Recipe33::menuCloseCallback), CCControlEventTouchUpInside);
    
    CCScale9Sprite* backgroundSprite2 = CCScale9Sprite::create("button9.png", spriteRect, capInsents);
    CCLabelTTF* label2 = CCLabelTTF::create("ボタン2", "Arial", 30);
    CCControlButton* button2 = CCControlButton::create(label2, backgroundSprite2);
    button2->setPreferredSize(CCSizeMake(150, 100));
    button2->setPosition(ccp(50+button2->getContentSize().width/2, size.height/2-button2->getContentSize().height/2));
    this->addChild(button2);
    
    CCScale9Sprite* backgroundSprite3 = CCScale9Sprite::create("button9.png", spriteRect, capInsents);
    CCLabelTTF* label3 = CCLabelTTF::create("ボタン3", "Arial", 30);
    CCControlButton* button3 = CCControlButton::create(label3, backgroundSprite3);
    button3->setPreferredSize(CCSizeMake(150, 150));
    button3->setPosition(ccp(size.width/2+button3->getContentSize().width, button->getPositionY()-button2->getContentSize().height/2));
    this->addChild(button3);
    
    return true;
}

void Recipe33::menuCloseCallback(CCObject* pSender)
{
    CCLOG("touch up inside!!");
}