//
//  Recipe39.cpp
//  RecipeBook
//
//  Created by Akihiro Matsuura on 5/22/13.
//  Copyright 2013 Syuhari, Inc. All rights reserved.
//

#include "Recipe39.h"

USING_NS_CC;

CCScene* Recipe39::scene()
{
    CCScene *scene = CCScene::create();
    Recipe39 *layer = Recipe39::create();
    scene->addChild(layer);
    return scene;
}

bool Recipe39::init()
{
    if ( !RecipeBase::init() )
    {
        return false;
    }
    
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    
    int fontSize = CCEGLView::sharedOpenGLView()->getDesignResolutionSize().height/320.0f * 16;
    std::string text = "指でなぞったラインを描画します";
    CCLabelTTF *label = CCLabelTTF::create(text.c_str(), "Helvetica", fontSize);
    label->setPosition(ccp(visibleSize.width/2, visibleSize.height-label->getContentSize().height/2));
    this->addChild(label);
    
    return true;
}
