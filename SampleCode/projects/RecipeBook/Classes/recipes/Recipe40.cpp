//
//  Recipe40.cpp
//  RecipeBook
//
//  Created by Akihiro Matsuura on 5/22/13.
//  Copyright 2013 Syuhari, Inc. All rights reserved.
//

#include "Recipe40.h"

USING_NS_CC;

CCScene* Recipe40::scene()
{
    CCScene *scene = CCScene::create();
    Recipe40 *layer = Recipe40::create();
    scene->addChild(layer);
    return scene;
}

bool Recipe40::init()
{
    if ( !RecipeBase::init() )
    {
        return false;
    }
    
    CCSize size = CCDirector::sharedDirector()->getWinSize();
    
    CCSprite* para1 = CCSprite::create("HelloWorld.png");
    CCSprite* para2 = CCSprite::create("Default.png");
    CCSprite* para3 = CCSprite::create("CloseNormal.png");
    CCSprite* para4 = CCSprite::create("recipe40_uhhoi.png");
    /*
     para1->setAnchorPoint(ccp(0,1));
     para2->setAnchorPoint(ccp(0,1));
     para3->setAnchorPoint(ccp(0,0.6f));
     para4->setAnchorPoint(ccp(0,0));
     */
    CCPoint topOffset = ccp(0, size.height);
    CCPoint midOffset = ccp(0, size.height/2);
    CCPoint downOffset= CCPointZero;
    
    CCParallaxNode* paraNode = CCParallaxNode::create();
    paraNode->addChild(para1, 1, ccp(0.5f, 0), topOffset);
    paraNode->addChild(para2, 2, ccp(1.0f, 0), topOffset);
    paraNode->addChild(para3, 3, ccp(2.0f, 0), midOffset);
    paraNode->addChild(para4, 4, ccp(3.0f, 0), downOffset);
    paraNode->setPosition(ccp(size.width/2, size.height/2));
    this->addChild(paraNode);
    
    CCMoveBy* move1 = CCMoveBy::create(5.0f, ccp(-size.width/2, 0));
    CCMoveBy* move2 = CCMoveBy::create(5.0f, ccp(size.width/2, 0));
    CCSequence* seq = (CCSequence*)CCSequence::create(move1, move2, NULL);
    CCRepeatForever* repeat = CCRepeatForever::create(seq);
    paraNode->runAction(repeat);
    
    return true;
}
