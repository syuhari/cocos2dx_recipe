//
//  Recipe28.cpp
//  RecipeBook
//
//  Created by Akihiro Matsuura on 5/22/13.
//  Copyright 2013 Syuhari, Inc. All rights reserved.
//

#include "Recipe28.h"

#define FLIP_DURATION 1.0f  // カードめくる時間
#define CARD_FACE_TAG 1     // カード裏面のタグ
#define CARD_BACK_TAG 2     // カード表面のタグ

USING_NS_CC;

CCScene* Recipe28::scene()
{
    CCScene *scene = CCScene::create();
    Recipe28 *layer = Recipe28::create();
    scene->addChild(layer);
    return scene;
}

bool Recipe28::init()
{
    if ( !RecipeBase::init() )
    {
        return false;
    }
    
    CCDirector::sharedDirector()->setDepthTest(false);
    
    this->flipCard();

    
    return true;
}

// 裏面カードを表示して半分までひっくり返すアクション
void Recipe28::flipCard() {
    CCSize size = CCDirector::sharedDirector()->getWinSize();
    
    // 裏面カード
    CCSprite* card = CCSprite::create("card.png");
    card->setPosition(ccp(size.width/2, size.height/2));
    this->addChild(card, CARD_FACE_TAG, CARD_FACE_TAG);
    card->setVisible(false);
    
    // 表面カード
    CCSprite* card2 = CCSprite::create("card_face.png");
    card2->setPosition(card->getPosition());
    this->addChild(card2, CARD_BACK_TAG, CARD_BACK_TAG);
    
    // カードめくるアクション
    CCOrbitCamera* turn = CCOrbitCamera::create(FLIP_DURATION/2.0f, 1, 0, 0.0f, 90.0f, 0, 0);
    CCHide* hide = CCHide::create();
    CCCallFunc* func = CCCallFunc::create(this, callfunc_selector(Recipe28::flipCard2));
    card2->runAction(CCSequence::create(turn, hide, func, NULL));
}

void Recipe28::flipCard2() {
    CCSprite* card = (CCSprite*)this->getChildByTag(CARD_FACE_TAG);
    CCShow* show = CCShow::create();
    CCOrbitCamera* turn = CCOrbitCamera::create(FLIP_DURATION/2.0f, 1, 0, 270.0f, 90.0f, 0, 0);
    card->runAction(CCSequence::create(show, turn, NULL));
}