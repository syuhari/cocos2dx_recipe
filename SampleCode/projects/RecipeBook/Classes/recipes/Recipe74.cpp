//
//  Recipe74.cpp
//  RecipeBook
//
//  Created by Akihiro Matsuura on 5/22/13.
//  Copyright 2013 Syuhari, Inc. All rights reserved.
//

#include "Recipe74.h"

#define kTileMapTag 10

USING_NS_CC;

CCScene* Recipe74::scene()
{
    CCScene *scene = CCScene::create();
    Recipe74 *layer = Recipe74::create();
    scene->addChild(layer);
    return scene;
}

bool Recipe74::init()
{
    if ( !RecipeBase::init() )
    {
        return false;
    }
        
    CCTMXTiledMap* pTileMap = CCTMXTiledMap::create("desert.tmx");
    this->addChild(pTileMap);
    pTileMap->setTag(kTileMapTag);
    
    //CCLOG("map size = %f, %f", pTileMap->getContentSize().width, pTileMap->getContentSize().height);
    
    this->setTouchEnabled(true);
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, 0, false);
    
    return true;
}

CCPoint Recipe74::getTilePosition(CCPoint point) {
    CCTMXTiledMap* pTileMap = (CCTMXTiledMap*)this->getChildByTag(kTileMapTag);
    CCPoint tilePoint = ccpSub(point, pTileMap->getPosition());
    
    float fTileWidth = pTileMap->getTileSize().width;
    float fTileHeight = pTileMap->getTileSize().height;
    float fTileRows = pTileMap->getMapSize().height;
    
    tilePoint.x = (int)(tilePoint.x / fTileWidth);
    tilePoint.y = (int)((fTileRows * fTileHeight - tilePoint.y)/fTileHeight);
    
    return tilePoint;
}

bool Recipe74::ccTouchBegan(CCTouch *touch, CCEvent *pEvent) {
    m_pStartPoint = this->convertToWorldSpace(this->convertTouchToNodeSpace(touch));
    this->scheduleUpdate();
    
    CCPoint tilePoint = this->getTilePosition(m_pStartPoint);
    CCTMXTiledMap* pTileMap = (CCTMXTiledMap*)this->getChildByTag(kTileMapTag);
    CCTMXLayer* pGroundLayer = pTileMap->layerNamed("Ground");
    int iGid = pGroundLayer->tileGIDAt(tilePoint);
    CCLOG("iGid = %d", iGid);
    if (iGid!=0) {
        CCDictionary* dProperties = pTileMap->propertiesForGID(iGid);
        if (dProperties!=NULL) {
            const CCString* pProperty = dProperties->valueForKey("isTree");
            if (pProperty->boolValue()) {
                CCLOG("is tree!!");
            }
        }
        
    }
    
    return true;
}

void Recipe74::ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent) {
    CCPoint touchPoint = this->convertToWorldSpace(this->convertTouchToNodeSpace(pTouch));
    m_pDelta = ccpSub(m_pStartPoint, touchPoint);
}

void Recipe74::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent) {
    this->unscheduleUpdate();
}

void Recipe74::ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent) {
    this->unscheduleUpdate();
}

void Recipe74::update(float delta) {
    CCSize size = CCDirector::sharedDirector()->getWinSize();
    
    CCTMXTiledMap* pTileMap = (CCTMXTiledMap*)this->getChildByTag(kTileMapTag);
    CCPoint point = pTileMap->getPosition();
    
    CCPoint pDelta = ccp(m_pDelta.x*delta*5.0f, m_pDelta.y*delta*5.0f);
    
    point = ccpAdd(point, pDelta);
    point.x = MAX(point.x, size.width-pTileMap->getContentSize().width);
    point.x = MIN(point.x, 0);
    point.y = MAX(point.y, size.height-pTileMap->getContentSize().height);
    point.y = MIN(point.y, 0);
    
    pTileMap->setPosition(point);
}
