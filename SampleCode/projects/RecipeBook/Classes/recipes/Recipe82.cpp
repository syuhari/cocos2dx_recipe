//
//  Recipe82.cpp
//  RecipeBook
//
//  Created by Akihiro Matsuura on 5/22/13.
//  Copyright 2013 Syuhari, Inc. All rights reserved.
//

#include "Recipe82.h"

USING_NS_CC;

CCScene* Recipe82::scene()
{
    CCScene *scene = CCScene::create();
    Recipe82 *layer = Recipe82::create();
    scene->addChild(layer);
    return scene;
}

bool Recipe82::init()
{
    if ( !RecipeBase::init() )
    {
        return false;
    }
        
    CCTexture2D::PVRImagesHavePremultipliedAlpha(true);
    
    CCSpriteFrameCache* frameCache = CCSpriteFrameCache::sharedSpriteFrameCache();
    CCSize size = CCDirector::sharedDirector()->getWinSize();
    frameCache->addSpriteFramesWithFile("uhhoi_pvr.plist");
    
    CCSprite* sprite = CCSprite::createWithSpriteFrameName("uhhoi_1.png");
    sprite->setPosition(ccp(size.width/2, size.height/2));
    this->addChild(sprite);
        
    return true;
}

