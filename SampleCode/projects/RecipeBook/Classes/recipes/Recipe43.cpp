//
//  Recipe43.cpp
//  RecipeBook
//
//  Created by Akihiro Matsuura on 5/22/13.
//  Copyright 2013 Syuhari, Inc. All rights reserved.
//

#include "Recipe43.h"

USING_NS_CC;

CCScene* Recipe43::scene()
{
    CCScene *scene = CCScene::create();
    Recipe43 *layer = Recipe43::create();
    scene->addChild(layer);
    return scene;
}

bool Recipe43::init()
{
    if ( !RecipeBase::init() )
    {
        return false;
    }
    
    CCSize size = CCDirector::sharedDirector()->getWinSize();
    
    CCLabelTTF* pLabel = CCLabelTTF::create("Cocos2d-x\n開発のレシピ", "Thonburi", 34);
    pLabel->setPosition(ccp(size.width/2, size.height/2) );
    this->addChild(pLabel);
    
    CCLabelTTF* pSec = CCLabelTTF::create("0秒", "Thonburi", 34);
    pSec->setPosition(ccp(size.width/2, size.height/4));
    this->addChild(pSec);
    pSec->setTag(10);
    
    m_iSec = 0;
    this->schedule(schedule_selector(Recipe43::updatePerSec), 1.0f);

    return true;
}

void Recipe43::updatePerSec() {
    m_iSec++;
    CCLabelTTF* pLabel = (CCLabelTTF*)this->getChildByTag(10);
    pLabel->setString(CCString::createWithFormat("%d秒", m_iSec)->getCString());
}
