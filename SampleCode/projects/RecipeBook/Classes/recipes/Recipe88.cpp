//
//  Recipe88.cpp
//  RecipeBook
//
//  Created by Akihiro Matsuura on 5/22/13.
//  Copyright 2013 Syuhari, Inc. All rights reserved.
//

#include "Recipe88.h"

USING_NS_CC;

CCScene* Recipe88::scene()
{
    CCScene *scene = CCScene::create();
    Recipe88 *layer = Recipe88::create();
    scene->addChild(layer);
    return scene;
}

bool Recipe88::init()
{
    if ( !RecipeBase::init() )
    {
        return false;
    }
    
    CCSize size = CCDirector::sharedDirector()->getWinSize();
    
    CCLabelBMFont* pLabel = CCLabelBMFont::create("Cocos2d-x", "my_font.fnt");
    pLabel->setPosition(ccp(size.width/2, size.height/2));
    this->addChild(pLabel);
    
    return true;
}
