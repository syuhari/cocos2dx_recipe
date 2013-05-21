//
//  Recipe19.cpp
//  RecipeBook
//
//  Created by Akihiro Matsuura on 5/22/13.
//  Copyright 2013 Syuhari, Inc. All rights reserved.
//

#include "Recipe19.h"

USING_NS_CC;

CCScene* Recipe19::scene()
{
    CCScene *scene = CCScene::create();
    Recipe19 *layer = Recipe19::create();
    scene->addChild(layer);
    return scene;
}

bool Recipe19::init()
{
    if ( !RecipeBase::init() )
    {
        return false;
    }
    
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    
    int fontSize = CCEGLView::sharedOpenGLView()->getDesignResolutionSize().height/320.0f * 16;
    std::string text = "左下の最下行、右側に表示されているのが残りメモリです。\n本プロジェクトのcocos2dx/CCDirector.cppに組み込んで有ります";
    CCLabelTTF *label = CCLabelTTF::create(text.c_str(), "Helvetica", fontSize);
    label->setPosition(ccp(visibleSize.width/2, visibleSize.height/2));
    this->addChild(label);
    
    return true;
}