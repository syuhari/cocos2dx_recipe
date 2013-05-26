//
//  Recipe22.cpp
//  RecipeBook
//
//  Created by Kenji Saito on 5/25/13.
//  Copyright 2013 Syuhari, Inc. All rights reserved.
//

#include "Recipe22.h"

USING_NS_CC;

CCScene* Recipe22::scene()
{
    CCScene *scene = CCScene::create();
    Recipe22 *layer = Recipe22::create();
    scene->addChild(layer);
    return scene;
}

bool Recipe22::init()
{
    if ( !RecipeBase::init() )
    {
        return false;
    }
    
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    
    int fontSize = CCEGLView::sharedOpenGLView()->getDesignResolutionSize().height/320.0f * 16;
    std::string text = "CCString、CCIntegerのオブジェクトを辞書に入れ、\n辞書をループして内容をログ出力します。";
    CCLabelTTF *label = CCLabelTTF::create(text.c_str(), "Helvetica", fontSize);
    label->setPosition(ccp(visibleSize.width/2, visibleSize.height/2));
    this->addChild(label);
    
    CCLog("--- Recipe 22 ------");
    this->method1();
    
    return true;
}

void Recipe22::method1()
{
    CCDictionary* pDict = CCDictionary::create();
    CCDictElement* pElement = NULL;
    
    // 辞書にオブジェクトを挿入
    CCString* pValue1 = CCString::create("100");
    CCString* pValue2 = CCString::create("120");
    CCInteger* pValue3 = CCInteger::create(200);
    pDict->setObject(pValue1, "key1");
    pDict->setObject(pValue2, "key2");
    pDict->setObject(pValue3, "key3");
    
    // pDictの要素をループする
    CCDICT_FOREACH(pDict, pElement)
    {
        if (strcmp(pElement->getStrKey(), "key3") != 0) {
            CCString* string = (CCString *)pElement->getObject();
            CCLog("%s", string->getCString());
        } else {
            CCInteger* integer = (CCInteger *)pElement->getObject();
            CCLog("%d", integer->getValue());
        }
    }
}