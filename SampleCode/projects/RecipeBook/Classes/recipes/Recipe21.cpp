//
//  Recipe21.cpp
//  RecipeBook
//
//  Created by Kenji Saito on 5/25/13.
//  Copyright 2013 Syuhari, Inc. All rights reserved.
//

#include "Recipe21.h"

USING_NS_CC;

CCScene* Recipe21::scene()
{
    CCScene *scene = CCScene::create();
    Recipe21 *layer = Recipe21::create();
    scene->addChild(layer);
    return scene;
}

bool Recipe21::init()
{
    if ( !RecipeBase::init() )
    {
        return false;
    }
    
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    
    int fontSize = CCEGLView::sharedOpenGLView()->getDesignResolutionSize().height/320.0f * 16;
    std::string text = "0からの連番でタグ付けしたスプライトを配列に入れ、\n配列をループしてスプライト毎にタグをログ出力します。";
    CCLabelTTF *label = CCLabelTTF::create(text.c_str(), "Helvetica", fontSize);
    label->setPosition(ccp(visibleSize.width/2, visibleSize.height/2));
    this->addChild(label);
    
    CCLog("--- Recipe 21 ------");
    this->method1();
    
    return true;
}

void Recipe21::method1()
{
    CCArray* array = CCArray::create();
    CCObject* it = NULL;
    
    for (int i=0; i<10; i++)
    {
        CCSprite* sprite = CCSprite::create();
        sprite->setTag(i);
        array->addObject(sprite);
    }
    
    // arrayの要素をループする
    CCARRAY_FOREACH(array, it)
    {
        CCSprite* sprite = dynamic_cast<CCSprite*>(it);
        CCLog("tag: %d", sprite->getTag());
    }
    
    for (int j = 0; j < array->count(); j++)
    {
        CCObject* obj = array->objectAtIndex(j);
        CCSprite* sprite = dynamic_cast<CCSprite*>(obj);
        CCLog("tag: %d", sprite->getTag());
    }
}