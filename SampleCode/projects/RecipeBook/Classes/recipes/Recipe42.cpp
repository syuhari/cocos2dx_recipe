//
//  Recipe42.cpp
//  RecipeBook
//
//  Created by Akihiro Matsuura on 5/22/13.
//  Copyright 2013 Syuhari, Inc. All rights reserved.
//

#include "Recipe42.h"

USING_NS_CC;

CCScene* Recipe42::scene()
{
    CCScene *scene = CCScene::create();
    Recipe42 *layer = Recipe42::create();
    scene->addChild(layer);
    return scene;
}

bool Recipe42::init()
{
    if ( !RecipeBase::init() )
    {
        return false;
    }
    
    CCSize size = CCDirector::sharedDirector()->getWinSize();
    
    CCSprite* pSprite = CCSprite::create("circle.png");
    CCProgressTimer* pTimer = CCProgressTimer::create(pSprite);
    pTimer->setType(kCCProgressTimerTypeRadial);
    pTimer->setPosition(ccp(size.width/2, size.height/4*3));
    pTimer->setPercentage(0.0f);
    pTimer->setTag(1);
    this->addChild(pTimer);
    
    CCSprite* pSprite2 = CCSprite::create("bar.png");
    CCProgressTimer* pTimer2 = CCProgressTimer::create(pSprite2);
    pTimer2->setPercentage(0.0f);
    pTimer2->setPosition(ccp(size.width/2, size.height/4));
    pTimer2->setType(kCCProgressTimerTypeBar);
    pTimer2->setMidpoint(ccp(0,0));
    pTimer2->setBarChangeRate(ccp(1,0));
    pTimer2->setTag(2);
    this->addChild(pTimer2);
    
    this->scheduleUpdate();
    
    return true;
}

void Recipe42::update(float delta) {
    CCProgressTimer* pTimer = (CCProgressTimer*)this->getChildByTag(1);
    float percent = pTimer->getPercentage();
    percent += 10.0f * delta;
    pTimer->setPercentage(percent);
    
    CCProgressTimer* pTimer2 = (CCProgressTimer*)this->getChildByTag(2);
    float percent2 = pTimer2->getPercentage();
    percent2 += 10.0f * delta;
    pTimer2->setPercentage(percent2);
    
    if (percent>100.0f) {
        this->unscheduleUpdate();
    }
}