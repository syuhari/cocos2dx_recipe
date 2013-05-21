//
//  Recipe26.cpp
//  RecipeBook
//
//  Created by Akihiro Matsuura on 5/22/13.
//  Copyright 2013 Syuhari, Inc. All rights reserved.
//

#include "Recipe26.h"

USING_NS_CC;

CCScene* Recipe26::scene()
{
    CCScene *scene = CCScene::create();
    Recipe26 *layer = Recipe26::create();
    scene->addChild(layer);
    return scene;
}

bool Recipe26::init()
{
    if ( !RecipeBase::init() )
    {
        return false;
    }
    
    CCSize size = CCDirector::sharedDirector()->getVisibleSize();
    
    CCSprite* pSprite = CCSprite::create("test.png");
    pSprite->setPosition( ccp(size.width/2, size.height/2) );
    
    CCSprite* pMask = CCSprite::create("mask_star.png");
    pMask->setPosition(ccp(size.width/2, size.height/2));
    
    CCClippingNode* pClip = CCClippingNode::create();
    pClip->setStencil(pMask);
    pClip->setAlphaThreshold(0.0f);
    pClip->addChild(pSprite);
    
    this->addChild(pClip);
    
    return true;
}