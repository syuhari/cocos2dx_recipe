//
//  Recipe34.cpp
//  RecipeBook
//
//  Created by Akihiro Matsuura on 5/22/13.
//  Copyright 2013 Syuhari, Inc. All rights reserved.
//

#include "Recipe34.h"
#include "CCScale9Sprite.h"
#include "CCControlButton.h"

USING_NS_CC_EXT;
USING_NS_CC;

CCScene* Recipe34::scene()
{
    CCScene *scene = CCScene::create();
    Recipe34 *layer = Recipe34::create();
    scene->addChild(layer);
    return scene;
}

bool Recipe34::init()
{
    if ( !RecipeBase::init() )
    {
        return false;
    }

    CCSize size = CCDirector::sharedDirector()->getWinSize();
    
    CCScrollView* pScrollView = CCScrollView::create(size);
    this->addChild(pScrollView);
    
    CCSprite* pSprite = CCSprite::create("HelloWorld.png");
    pScrollView->setContainer(pSprite);
    pScrollView->setContentSize(pSprite->getContentSize());    
    pScrollView->setDelegate(this);
    
    return true;
}

void Recipe34::scrollViewDidScroll(CCScrollView* view) {
    CCLOG("did scroll");
}

void Recipe34::scrollViewDidZoom(CCScrollView* view) {
    CCLOG("did zoom");
}