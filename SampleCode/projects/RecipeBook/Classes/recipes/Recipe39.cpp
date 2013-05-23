//
//  Recipe39.cpp
//  RecipeBook
//
//  Created by Akihiro Matsuura on 5/22/13.
//  Copyright 2013 Syuhari, Inc. All rights reserved.
//

#include "Recipe39.h"

USING_NS_CC;

#define MOTION_STREAK_TAG 10

CCScene* Recipe39::scene()
{
    CCScene *scene = CCScene::create();
    Recipe39 *layer = Recipe39::create();
    scene->addChild(layer);
    return scene;
}

bool Recipe39::init()
{
    if ( !RecipeBase::init() )
    {
        return false;
    }
    
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    
    int fontSize = CCEGLView::sharedOpenGLView()->getDesignResolutionSize().height/320.0f * 18;
    CCLabelTTF *label = CCLabelTTF::create("指でなぞったラインを CCMotionStreak で描画します", "Helvetica", fontSize);
    label->setPosition(ccp(visibleSize.width/2, visibleSize.height-label->getContentSize().height/2));
    this->addChild(label);
    
    this->setTouchEnabled(true);
    this->setTouchMode(kCCTouchesOneByOne);
    
    return true;
}

bool Recipe39::ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
    this->removeChildByTag(MOTION_STREAK_TAG, true);
    
    CCPoint point = this->convertTouchToNodeSpace(pTouch);
    CCMotionStreak* pStreak = CCMotionStreak::create(0.5f, 1.0f, 10.0f, ccc3(255, 255, 0), "line.png");
    pStreak->setPosition(point);
    this->addChild(pStreak, 5, MOTION_STREAK_TAG);
    return true;
}

void Recipe39::ccTouchMoved(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
    CCPoint point = this->convertTouchToNodeSpace(pTouch);
    CCMotionStreak* pStreak = (CCMotionStreak*)this->getChildByTag(MOTION_STREAK_TAG);
    pStreak->setPosition(point);
}
