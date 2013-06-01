//
//  Recipe25.cpp
//  RecipeBook
//
//  Created by Akihiro Matsuura on 5/22/13.
//  Copyright 2013 Syuhari, Inc. All rights reserved.
//

#include "Recipe25.h"
#include "CCBigImageLayer.h"

USING_NS_CC;

CCScene* Recipe25::scene()
{
    CCScene *scene = CCScene::create();
    Recipe25 *layer = Recipe25::create();
    scene->addChild(layer);
    return scene;
}

bool Recipe25::init()
{
    if ( !RecipeBase::init() )
    {
        return false;
    }
    
    CCBigImageLayer* layer = CCBigImageLayer::create();
    layer->setTag(1);
    this->addChild(layer);
    
    return true;
}

void Recipe25::onEnterTransitionDidFinish()
{
    CCBigImageLayer* layer = (CCBigImageLayer*)this->getChildByTag(1);
    layer->loadBigImage("bigImage.plist");
}