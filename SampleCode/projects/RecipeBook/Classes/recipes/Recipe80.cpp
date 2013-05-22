//
//  Recipe80.cpp
//  RecipeBook
//
//  Created by Akihiro Matsuura on 5/22/13.
//  Copyright 2013 Syuhari, Inc. All rights reserved.
//

#include "Recipe80.h"

USING_NS_CC;

CCScene* Recipe80::scene()
{
    CCScene *scene = CCScene::create();
    Recipe80 *layer = Recipe80::create();
    scene->addChild(layer);
    return scene;
}

bool Recipe80::init()
{
    if ( !RecipeBase::init() )
    {
        return false;
    }
        
    CCSpriteFrameCache* frameCache = CCSpriteFrameCache::sharedSpriteFrameCache();
    CCSize size = CCDirector::sharedDirector()->getWinSize();
    frameCache->addSpriteFramesWithFile("uhhoi.plist");
    
    CCSprite* sprite = CCSprite::createWithSpriteFrameName("uhhoi_1.png");
    sprite->setPosition(ccp(size.width/2, size.height/2));
    this->addChild(sprite);
    
    CCArray* frames = CCArray::createWithCapacity(3);
    frames->addObject(frameCache->spriteFrameByName("uhhoi_2.png"));
    frames->addObject(frameCache->spriteFrameByName("uhhoi_2.png"));
    frames->addObject(frameCache->spriteFrameByName("uhhoi_3.png"));
    CCAnimation* animation = CCAnimation::createWithSpriteFrames(frames, 0.1f);
    CCAnimate* animate = CCAnimate::create(animation);
    sprite->runAction(CCRepeatForever::create(animate));
        
    return true;
}

