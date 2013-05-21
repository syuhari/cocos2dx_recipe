//
//  Recipe30.cpp
//  RecipeBook
//
//  Created by Akihiro Matsuura on 5/22/13.
//  Copyright 2013 Syuhari, Inc. All rights reserved.
//

#include "Recipe30.h"

USING_NS_CC;

CCScene* Recipe30::scene()
{
    CCScene *scene = CCScene::create();
    Recipe30 *layer = Recipe30::create();
    scene->addChild(layer);
    return scene;
}

bool Recipe30::init()
{
    if ( !RecipeBase::init() )
    {
        return false;
    }

    CCSize size = CCDirector::sharedDirector()->getWinSize();

    CCSpriteBatchNode* pBatchNode = CCSpriteBatchNode::create("uhhoi.png");
    this->addChild(pBatchNode);
    
    for (int i=0; i<300; i++) {
        CCSprite* sprite = CCSprite::createWithTexture(pBatchNode->getTexture());
        float x = CCRANDOM_0_1()*size.width;
        float y = CCRANDOM_0_1()*size.height;
        sprite->setPosition(ccp(x, y));
        pBatchNode->addChild(sprite);
        
        CCFadeOut* fade = CCFadeOut::create(CCRANDOM_0_1()*10.0f);
        sprite->runAction(fade);
    }

    
    return true;
}