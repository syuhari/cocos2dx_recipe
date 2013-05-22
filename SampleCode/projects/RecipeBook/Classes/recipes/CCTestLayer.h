//
//  CCTestLayer.h
//  TestBuilder
//
//  Created by 松浦 晃洋 on 1/23/13.
//
//

#ifndef __TestBuilder__CCTestLayer__
#define __TestBuilder__CCTestLayer__

#include "cocos2d.h"
#include "cocos-ext.h"

class CCTestLayer : public cocos2d::CCLayer, public cocos2d::extension::CCBSelectorResolver
{
    virtual cocos2d::SEL_MenuHandler onResolveCCBCCMenuItemSelector(CCObject * pTarget, cocos2d::CCString * pSelectorName);
	virtual cocos2d::extension::SEL_CCControlHandler onResolveCCBCCControlSelector(cocos2d::CCObject * pTarget, cocos2d::CCString * pSelectorName);
    void menuTapped(CCObject *pSender, cocos2d::extension::CCControlEvent pCCControlEvent);
public:
    //CREATE_FUNC(CCTestLayer);
};

class TestBuilderLoader : public cocos2d::extension::CCLayerLoader {
public:
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(TestBuilderLoader, loader);
protected:
    //CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(CCTestLayer);
};
#endif /* defined(__TestBuilder__CCTestLayer__) */
