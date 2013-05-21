//
//  ModalLayer.cpp
//  Modal
//
//  Created by Akihiro Matsuura on 5/22/13.
//  Copyright 2013 Syuhari, Inc. All rights reserved.
//
//

#include "ModalLayer.h"

// モーダルレイヤの優先順位
#define kModalLayerPriority kCCMenuHandlerPriority-1
// モーダルレイア上のCCMenuの優先順位
#define kModalLayerMenuPriority kCCMenuHandlerPriority-2

using namespace cocos2d;

bool ModalLayer::init()
{
    if ( !CCLayer::init() )
    {
        return false;
    }
    
    this->setTouchPriority(kModalLayerPriority);
    this->setTouchEnabled(true);
    this->setTouchMode(kCCTouchesOneByOne);
    
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    
    CCSprite* frame = CCSprite::create("frame.png");
    frame->setPosition(ccp(visibleSize.width/2, visibleSize.height/2));
    this->addChild(frame);
    
    CCMenuItemImage *pCloseItem = CCMenuItemImage::create(
                                                          "tg_close_1.png",
                                                          "tg_close_2.png",
                                                          this,
                                                          menu_selector(ModalLayer::menuCloseCallback) );
    pCloseItem->setPosition(ccp(
                        visibleSize.width/2+frame->getContentSize().width/2-pCloseItem->getContentSize().width/2-10,
                        visibleSize.height/2+frame->getContentSize().height/2-pCloseItem->getContentSize().height/2-10));
    
    CCMenu* pMenu = CCMenu::create(pCloseItem, NULL);
    pMenu->setTouchPriority(kModalLayerMenuPriority);
    pMenu->setPosition( CCPointZero );
    this->addChild(pMenu);
        
    return true;
}

bool ModalLayer::ccTouchBegan(CCTouch* touch, CCEvent* event) {
    // can not touch on back layers    
    return true;
}

void ModalLayer::menuCloseCallback(CCObject* pSender)
{
    this->removeFromParentAndCleanup(true);
}
