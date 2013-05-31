//
//  RecipeBase.h
//  RecipeBook
//
//  Created by Akihiro Matsuura on 5/22/13.
//  Copyright 2013 Syuhari, Inc. All rights reserved.
//

#ifndef _RecipeBook_RecipeBase_H_
#define _RecipeBook_RecipeBase_H_

#include "cocos2d.h"

class RecipeBase : public cocos2d::CCLayer
{
protected:
    virtual void doStep1(){}
    virtual void doStep2(){}
    virtual void doStep3(){}
    
public:
    RecipeBase();
    virtual bool init();
    static cocos2d::CCScene* scene();
    virtual void onEnter();
    void menuCloseCallback(CCObject* pSender);
    CREATE_FUNC(RecipeBase);
    CC_SYNTHESIZE(int, m_stepNo, StepNo);
};

#endif // _RecipeBook_RecipeBase_H_
