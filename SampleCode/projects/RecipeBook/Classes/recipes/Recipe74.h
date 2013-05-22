//
//  Recipe74.h
//  RecipeBook
//
//  Created by Akihiro Matsuura on 5/22/13.
//  Copyright 2013 Syuhari, Inc. All rights reserved.
//

#ifndef _RecipeBook_Recipe74_H_
#define _RecipeBook_Recipe74_H_

#include "cocos2d.h"
#include "RecipeBase.h"

class Recipe74 : public RecipeBase
{
private:
    cocos2d::CCPoint m_pStartPoint;
    cocos2d::CCPoint m_pDelta;
public:
    virtual bool init();
    static cocos2d::CCScene* scene();
    CREATE_FUNC(Recipe74);
    virtual bool ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
    virtual void ccTouchMoved(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
    virtual void ccTouchEnded(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
    virtual void ccTouchCancelled(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
    
    cocos2d::CCPoint getTilePosition(cocos2d::CCPoint point);
    
    virtual void update(float delta);
};

#endif // _RecipeBook_Recipe74_H_
