//
//  Recipe87.cpp
//  RecipeBook
//
//  Created by Akihiro Matsuura on 5/22/13.
//  Copyright 2013 Syuhari, Inc. All rights reserved.
//

#include "Recipe87.h"

#include "SSPlayer.h"
#include "SSPlayerData.h"

extern SSData robo_02_motion1_partsData;
extern const char* robo_02_motion1_images[];

USING_NS_CC;

CCScene* Recipe87::scene()
{
    CCScene *scene = CCScene::create();
    Recipe87 *layer = Recipe87::create();
    scene->addChild(layer);
    return scene;
}

bool Recipe87::init()
{
    if ( !RecipeBase::init() )
    {
        return false;
    }
    
    CCSize size = CCDirector::sharedDirector()->getVisibleSize();
    
    // roboアニメ
	SSImageList* roboImageList = new SSImageList(robo_02_motion1_images);
	SSPlayer* roboPlayer = SSPlayer::create(&robo_02_motion1_partsData, roboImageList);
	this->addChild(roboPlayer);
	roboPlayer->setPositionX(size.width/2);
	roboPlayer->setScale(0.5f);
    
    return true;
}

