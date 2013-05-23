//
//  Recipe39_3.h
//  RecipeBook
//
//  Created by Akihiro Matsuura on 5/22/13.
//  Copyright 2013 Syuhari, Inc. All rights reserved.
//

#ifndef _RecipeBook_Recipe39_3_H_
#define _RecipeBook_Recipe39_3_H_

#include "cocos2d.h"
#include "RecipeBase.h"

class Recipe39_3 : public RecipeBase
{
private:
    std::vector<cocos2d::CCPoint> points;
    cocos2d::CCPoint prevLocation;
    cocos2d::CCRenderTexture *pTarget;
    cocos2d::CCSprite *pBrush;
    
    cocos2d::CCRect getTextureRect();
public:
    virtual bool init();
    static cocos2d::CCScene* scene();
    CREATE_FUNC(Recipe39_3);
    
    virtual bool ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
    virtual void ccTouchMoved(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
    virtual void ccTouchEnded(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
    virtual void ccTouchCancelled(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
};

#endif // _RecipeBook_Recipe39_3_H_
