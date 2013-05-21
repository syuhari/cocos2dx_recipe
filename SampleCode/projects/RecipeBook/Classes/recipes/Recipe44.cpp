//
//  Recipe44.cpp
//  RecipeBook
//
//  Created by Akihiro Matsuura on 5/22/13.
//  Copyright 2013 Syuhari, Inc. All rights reserved.
//

#include "Recipe44.h"

USING_NS_CC;

CCScene* Recipe44::scene()
{
    CCScene *scene = CCScene::create();
    Recipe44 *layer = Recipe44::create();
    scene->addChild(layer);
    return scene;
}

bool Recipe44::init()
{
    if ( !RecipeBase::init() )
    {
        return false;
    }
    
    this->makeSprite();
    this->makeSpriteFromTexture();
    
    return true;
}

void Recipe44::makeSprite() {
    CCSize size = CCDirector::sharedDirector()->getWinSize();
    
    // 元画像のテクスチャを作成
    CCTexture2D *pTexture = CCTextureCache::sharedTextureCache()->addImage("tsunaget.png");
    // 元画像のサイズを取得
    CCRect rect = CCRectZero;
    rect.size = pTexture->getContentSize();
    
    // 左半分のスプライトを生成
    CCRect leftRect = CCRectMake(rect.origin.x, rect.origin.y, rect.size.width/2.0f, rect.size.height);
    CCSprite* spriteL = CCSprite::createWithTexture(pTexture, leftRect);
    
    CCPoint pointL = ccp(spriteL->getContentSize().width/2, size.height/4*3);
    spriteL->setPosition(pointL);
    this->addChild(spriteL);
    
    // 右半分のスプライトを生成
    CCRect rightRect = CCRectMake(rect.origin.x+rect.size.width/2, rect.origin.y, rect.size.width/2.0f, rect.size.height);
    CCSprite* spriteR = CCSprite::createWithTexture(pTexture, rightRect);
    CCPoint pointR = ccp(size.width-spriteR->getContentSize().width/2, size.height/4*3);
    spriteR->setPosition(pointR);
    this->addChild(spriteR);
}

void Recipe44::makeSpriteFromTexture() {
    CCSize size = CCDirector::sharedDirector()->getWinSize();
    
    // テクスチャアトラスからテクスチャを生成
    CCSpriteFrameCache* cache = CCSpriteFrameCache::sharedSpriteFrameCache();
    cache->addSpriteFramesWithFile("texture.plist");
    
    CCSprite* sprite = CCSprite::createWithSpriteFrameName("btn_awaset_1.png");
    CCTexture2D* pTexture = sprite->getTexture();
    
    CCRect rect = sprite->getTextureRect();
    
    // 左半分のスプライトを生成
    CCRect leftRect = CCRectMake(rect.origin.x, rect.origin.y, rect.size.width/2.0f, rect.size.height);
    CCSprite* spriteL = CCSprite::createWithTexture(pTexture, leftRect);
    spriteL->setTextureRect(leftRect, sprite->isTextureRectRotated(), rect.size);
    
    CCPoint pointL = ccp(spriteL->getContentSize().width/2, size.height/4);
    spriteL->setPosition(pointL);
    this->addChild(spriteL);
    
    // 右半分のスプライトを生成
    CCRect rightRect = CCRectMake(rect.origin.x, rect.origin.y, rect.size.width/2.0f, rect.size.height);
    if (sprite->isTextureRectRotated()) {
        // テクスチャが回転されている場合はY軸をずらす
        rightRect.origin.y += rect.size.width/2;
    } else {
        rightRect.origin.x += rect.size.width/2;
    }
    CCSprite* spriteR = CCSprite::createWithTexture(pTexture, rightRect);
    spriteR->setTextureRect(rightRect, sprite->isTextureRectRotated(), rect.size);
    
    CCPoint pointR = ccp(size.width-spriteR->getContentSize().width/2, size.height/4);
    spriteR->setPosition(pointR);
    this->addChild(spriteR);
}
