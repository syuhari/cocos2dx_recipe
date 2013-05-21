//
//  Recipe37.cpp
//  RecipeBook
//
//  Created by Akihiro Matsuura on 5/22/13.
//  Copyright 2013 Syuhari, Inc. All rights reserved.
//

#include "Recipe37.h"
#include "TapSprite.h"

USING_NS_CC;

CCScene* Recipe37::scene()
{
    CCScene *scene = CCScene::create();
    Recipe37 *layer = Recipe37::create();
    scene->addChild(layer);
    return scene;
}

bool Recipe37::init()
{
    if ( !RecipeBase::init() )
    {
        return false;
    }
    
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();

    CCLabelTTF *label = CCLabelTTF::create("タップしてドラッグできます", "Helvetica", 20.0f);
    label->setPosition(ccp(visibleSize.width/2, visibleSize.height-label->getContentSize().height));
    this->addChild(label);
    
    TapSprite* sprite = (TapSprite*)TapSprite::create("Icon-57.png");
    sprite->setPosition(ccp(visibleSize.width/2, visibleSize.height/2));
    this->addChild(sprite);
    
    return true;
}
