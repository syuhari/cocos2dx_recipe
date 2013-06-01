//
//  CCTestLayer.cpp
//  TestBuilder
//
//  Created by 松浦 晃洋 on 1/23/13.
//
//

#include "CCTestLayer.h"

USING_NS_CC;
USING_NS_CC_EXT;

SEL_MenuHandler CCTestLayer::onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName)
{
	CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "menuTapped", CCTestLayer::menuTapped);
	return NULL;
}

void CCTestLayer::menuTapped(CCObject *pSender, CCControlEvent pCCControlEvent) {
	CCLOG("button clicked");
}
