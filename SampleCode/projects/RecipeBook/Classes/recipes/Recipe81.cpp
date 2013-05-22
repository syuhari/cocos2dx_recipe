//
//  Recipe81.cpp
//  RecipeBook
//
//  Created by Akihiro Matsuura on 5/22/13.
//  Copyright 2013 Syuhari, Inc. All rights reserved.
//

#include "Recipe81.h"

USING_NS_CC;

CCScene* Recipe81::scene()
{
    CCScene *scene = CCScene::create();
    Recipe81 *layer = Recipe81::create();
    scene->addChild(layer);
    return scene;
}

bool Recipe81::init()
{
    if ( !RecipeBase::init() )
    {
        return false;
    }
        
    CCTextureCache::sharedTextureCache()->addImageAsync("uhhoi.png", this, callfuncO_selector(Recipe81::loadedTexture));
    
    return true;
}

void Recipe81::loadedTexture(CCTexture2D* pTexture)
{
    CCSpriteFrameCache* frameCache = CCSpriteFrameCache::sharedSpriteFrameCache();
    frameCache->addSpriteFramesWithFile("uhhoi.plist", pTexture);
    
    CCSize size = CCDirector::sharedDirector()->getWinSize();
    CCSprite* sprite = CCSprite::createWithSpriteFrameName("uhhoi_1.png");
    sprite->setPosition(ccp(size.width/2, size.height/2));
    this->addChild(sprite);
    
}

