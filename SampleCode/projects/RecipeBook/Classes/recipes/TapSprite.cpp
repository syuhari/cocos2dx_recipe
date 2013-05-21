//
//  TapSprite.cpp
//  Recipe37
//
//  Created by Akihiro Matsuura on 5/22/13.
//  Copyright 2013 Syuhari, Inc. All rights reserved.
//

#include "TapSprite.h"

NS_CC_BEGIN

TapSprite* TapSprite::create(const char *pszFileName)
{
    TapSprite *pobSprite = new TapSprite();
    if (pobSprite && pobSprite->initWithFile(pszFileName))
    {
        pobSprite->autorelease();
        return pobSprite;
    }
    CC_SAFE_DELETE(pobSprite);
    return NULL;
}

void TapSprite::onEnter()
{
    CCSprite::onEnter();
    CCTouchDispatcher* dispatcher = CCDirector::sharedDirector()->getTouchDispatcher();
    dispatcher->addTargetedDelegate(this, 0, true);
}

void TapSprite::onExit() {
    CCSprite::onExit();
    CCTouchDispatcher* dispatcher = CCDirector::sharedDirector()->getTouchDispatcher();
    dispatcher->removeDelegate(this);
}

bool TapSprite::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
    // タッチ開始処理
    // タッチ位置を取得
    CCPoint point = pTouch->getLocation();
    // スプライトの大きさ
    CCSize size = this->getTexture()->getContentSize();
    // スプライトの範囲
    CCRect rect = CCRectMake(this->getPositionX()-size.width/2, this->getPositionY()-size.height/2, size.width, size.height);
    // タッチ位置がスプライト内ならイベント処理するのでtrueを返す
    return rect.containsPoint(point);
}

void TapSprite::ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent)
{
    // タッチ移動処理
    CCPoint point = pTouch->getLocation();
    this->setPosition(point);
    
    CCLOG("TapSprite: touch moved");
}

void TapSprite::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent)
{
    // タッチ終了処理
    CCLOG("TapSprite: touch ended");
}

void TapSprite::ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent)
{
    // タッチキャンセル処理
    CCLOG("TapSprite: touch cancelled");
}

NS_CC_END