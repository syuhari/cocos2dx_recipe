//
//  Recipe19.cpp
//  RecipeBook
//
//  Created by Akihiro Matsuura on 5/22/13.
//  Copyright 2013 Syuhari, Inc. All rights reserved.
//

#include "RecipeBase.h"
#include "HelloWorldScene.h"

USING_NS_CC;

CCScene* RecipeBase::scene()
{
    CCScene *scene = CCScene::create();
    RecipeBase *layer = RecipeBase::create();
    scene->addChild(layer);
    return scene;
}

RecipeBase::RecipeBase() : m_stepNo(0)
{
    
}

bool RecipeBase::init()
{
    if ( !CCLayer::init() )
    {
        return false;
    }
        
    CCMenuItemImage *pCloseItem = CCMenuItemImage::create(
                                                          "CloseNormal.png",
                                                          "CloseSelected.png",
                                                          this,
                                                          menu_selector(RecipeBase::menuCloseCallback) );
    pCloseItem->setPosition( ccp(CCDirector::sharedDirector()->getWinSize().width - 20, 20) );
    CCMenu* pMenu = CCMenu::create(pCloseItem, NULL);
    pMenu->setPosition( CCPointZero );
    this->addChild(pMenu, 1);
    
    return true;
}

void RecipeBase::menuCloseCallback(CCObject* pSender)
{
    CCDirector::sharedDirector()->replaceScene(HelloWorld::scene());
}

void RecipeBase::onEnter()
{
    CCLayer::onEnter();
    if (m_stepNo == 1)  doStep1();
    else if (m_stepNo == 2)  doStep2();
    else if (m_stepNo == 3)  doStep3();
}
