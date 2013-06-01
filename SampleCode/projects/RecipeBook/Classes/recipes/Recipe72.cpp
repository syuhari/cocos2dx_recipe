//
//  Recipe72.cpp
//  RecipeBook
//
//  Created by Akihiro Matsuura on 5/22/13.
//  Copyright 2013 Syuhari, Inc. All rights reserved.
//

#include "Recipe72.h"

USING_NS_CC;

CCScene* Recipe72::scene()
{
    CCScene *scene = CCScene::create();
    Recipe72 *layer = Recipe72::create();
    scene->addChild(layer);
    return scene;
}

bool Recipe72::init()
{
    if ( !RecipeBase::init() )
    {
        return false;
    }
        
    CCLabelTTF* pLabel = CCLabelTTF::create("Hello World", "Thonburi", 34);
    pLabel->setColor(ccBLACK);
    
    // ask director the window size
    CCSize size = CCDirector::sharedDirector()->getWinSize();
    
    // position the label on the center of the screen
    pLabel->setPosition( ccp(size.width / 2, size.height - 20) );
    
    // add the label as a child to this layer
    this->addChild(pLabel, 1);
    
    // add "HelloWorld" splash screen"
    CCSprite* pSprite = CCSprite::create("HelloWorld.png");
    
    // position the sprite on the center of the screen
    pSprite->setPosition( ccp(size.width/2, size.height/2) );
    
    // add the sprite as a child to this layer
    this->addChild(pSprite, 0);
    
    /*
     float x=0, y=0, z=0;
     this->getCamera()->getCenterXYZ(&x, &y, &z);
     this->getCamera()->setCenterXYZ(x, y+0.0000001, z);
     */
    /*
     float x=0, y=0, z=0;
     this->getCamera()->getEyeXYZ(&x, &y, &z);
     this->getCamera()->setEyeXYZ(x, y, 200);
     */
    //this->scheduleUpdate();
    
    //CCDirector::sharedDirector()->setDepthTest(false);
    
    CCCamera* pCamera = this->getCamera();
    pCamera->setEyeXYZ(10.0f, 20.0f, 20.0f);
    pCamera->setCenterXYZ(0, 0, 0);
    pCamera->setUpXYZ(0.0f, 1.0f, 0.0f);
    
    return true;
}

