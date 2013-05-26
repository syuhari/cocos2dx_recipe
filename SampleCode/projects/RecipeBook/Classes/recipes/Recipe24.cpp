//
//  Recipe24.cpp
//  RecipeBook
//
//  Created by Kenji Saito on 5/25/13.
//  Copyright 2013 Syuhari, Inc. All rights reserved.
//

#include "Recipe24.h"

USING_NS_CC;

CCScene* Recipe24::scene()
{
    CCScene *scene = CCScene::create();
    Recipe24 *layer = Recipe24::create();
    scene->addChild(layer);
    return scene;
}

bool Recipe24::init()
{
    if ( !RecipeBase::init() )
    {
        return false;
    }
    
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    
    int fontSize = CCEGLView::sharedOpenGLView()->getDesignResolutionSize().height/320.0f * 16;
    std::string text = "各種のフォーマットでログ出力します。";
    CCLabelTTF *label = CCLabelTTF::create(text.c_str(), "Helvetica", fontSize);
    label->setPosition(ccp(visibleSize.width/2, visibleSize.height/2));
    this->addChild(label);
    
    CCLog("--- Recipe 24 ------");
    this->method1();
    
    return true;
}

void Recipe24::method1()
{
    // ログを出力する
    CCLog("Characters: %c %c", 'a', 65);
    CCLog("Decimals: %d %ld", 1977, 650000L);
    CCLog("Preceding with blanks: %10d", 1977);
    CCLog("Preceding with zeros: %010d", 1977);
    CCLog("Some different radixes: %d %x %o %#x %#o", 100, 100, 100, 100, 100);
    CCLog("floats: %4.2f %+.0e %E", 3.1416, 3.1416, 3.1416);
    CCLog("%s", "A string");
}