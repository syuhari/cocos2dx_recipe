//
//  TapSprite.h
//  Recipe37
//
//  Created by Akihiro Matsuura on 5/22/13.
//  Copyright 2013 Syuhari, Inc. All rights reserved.
//

#ifndef _Recipe37_TapSprite_H_
#define _Recipe37_TapSprite_H_

#include "cocos2d.h"

NS_CC_BEGIN

class TapSprite : public CCSprite, public CCTargetedTouchDelegate
{
public:
    static TapSprite* create(const char *pszFileName);
    virtual void onEnter();
    virtual void onExit();
    virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent);
};

NS_CC_END

#endif // _Recipe37_TapSprite_H_
