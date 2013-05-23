//
//  Recipe39_3.cpp
//  RecipeBook
//
//  Created by Akihiro Matsuura on 5/22/13.
//  Copyright 2013 Syuhari, Inc. All rights reserved.
//

#include "Recipe39_3.h"

USING_NS_CC;

#define MOTION_STREAK_TAG 10

CCScene* Recipe39_3::scene()
{
    CCScene *scene = CCScene::create();
    Recipe39_3 *layer = Recipe39_3::create();
    scene->addChild(layer);
    return scene;
}

bool Recipe39_3::init()
{
    if ( !RecipeBase::init() )
    {
        return false;
    }
    
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    
    int fontSize = CCEGLView::sharedOpenGLView()->getDesignResolutionSize().height/320.0f * 18;
    CCLabelTTF *label = CCLabelTTF::create("指でなぞったラインを CCRenderTexture で描画します", "Helvetica", fontSize);
    label->setPosition(ccp(visibleSize.width/2, visibleSize.height-label->getContentSize().height/2));
    this->addChild(label);
    
    this->setTouchEnabled(true);
    this->setTouchMode(kCCTouchesOneByOne);
    
    pBrush = CCSprite::create("brush.png");
    pBrush->retain();
    
    return true;
}

bool Recipe39_3::ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
    points.clear();
    
    CCPoint location = pTouch->getLocation();
    points.push_back(location);
    prevLocation = location;
    
    CCSize size = CCDirector::sharedDirector()->getVisibleSize();
    pTarget = CCRenderTexture::create(size.width, size.height, kCCTexture2DPixelFormat_RGBA8888);
    pTarget->retain();
    pTarget->setPosition(ccp(size.width/2, size.height/2));
    this->addChild(pTarget);
    
    return true;
}

void Recipe39_3::ccTouchMoved(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
    CCPoint start = pTouch->getLocation();
    CCPoint end   = pTouch->getPreviousLocation();
    
    pTarget->begin();
    float distance = ccpDistance(start, end);
    for (int i=0; i<distance; i++)
    {
        float diff_x = end.x - start.x;
        float diff_y = end.y - start.y;
        float delta = (float)i / distance;
        CCPoint point = ccp(start.x + (diff_x*delta), start.y + (diff_y*delta));
        pBrush->setPosition(point);
        pBrush->visit();
    }
    pTarget->end();
    
    float distance2 = ccpDistance(start, prevLocation);
    if (distance2 > 15.0f)
    {
        points.push_back(start);
        prevLocation = start;
    }
}

void Recipe39_3::ccTouchEnded(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
    CCSize size = CCDirector::sharedDirector()->getVisibleSize();
    
    if (points.size()>1)
    {
        CCRect rect = this->getTextureRect();
        
        CCImage* pImage = pTarget->newCCImage();
        CCTexture2D* pTexture = CCTextureCache::sharedTextureCache()->addUIImage(pImage, NULL);
        CC_SAFE_DELETE(pImage);
        
        CCSprite* pSprite = CCSprite::createWithTexture(pTexture, rect);
        pSprite->setPosition(ccp(rect.origin.x + rect.size.width/2,  size.height - (rect.origin.y + rect.size.height/2)));
        this->addChild(pSprite);
    }
    
    this->removeChild(pTarget, true);
    pTarget->release();
}

void Recipe39_3::ccTouchCancelled(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
    this->removeChild(pTarget, true);
    pTarget->release();
}

CCRect Recipe39_3::getTextureRect()
{
    CCSize size = CCDirector::sharedDirector()->getVisibleSize();
    float minX = size.width;
    float maxX = 0;
    float minY = size.height;
    float maxY = 0;
    
    for (int i=0; i<points.size()-1; i++)
    {
        minX = MIN(minX, points[i].x);
        minX = MIN(minX, points[i+1].x);
        
        maxX = MAX(maxX, points[i].x);
        maxX = MAX(maxX, points[i+1].x);
        
        minY = MIN(minY, points[i].y);
        minY = MIN(minY, points[i+1].y);
        
        maxY = MAX(maxY, points[i].y);
        maxY = MAX(maxY, points[i+1].y);
    }
    
    float margin = pBrush->getContentSize().width * pBrush->getScale() / 2.0f;
    float width  = maxX - minX + margin * 2;
    float height = maxY - minY + margin * 2;
    
    float x = minX - margin;
    float y = size.height - maxY - margin;
    
    // 画面外に出ないように補正
    x = MAX(0.0f, x);
    y = MAX(0.0f, y);
    if (minX + width > size.width)
    {
        width = size.width - x;
    }
    if (minY + height > size.height)
    {
        height = size.height - y;
    }
    
    return CCRectMake(x, y, width, height);
}
