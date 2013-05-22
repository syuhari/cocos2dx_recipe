//
//  Recipe86.cpp
//  RecipeBook
//
//  Created by Akihiro Matsuura on 5/22/13.
//  Copyright 2013 Syuhari, Inc. All rights reserved.
//

#include "Recipe86.h"
#include "CCBReader.h"
#include "CCNodeLoaderLibrary.h"
#include "CCTestLayer.h"

USING_NS_CC;
USING_NS_CC_EXT;

CCScene* Recipe86::scene()
{
    CCNodeLoaderLibrary * ccNodeLoaderLibrary = CCNodeLoaderLibrary::newDefaultCCNodeLoaderLibrary();
    ccNodeLoaderLibrary->registerCCNodeLoader("CCTestLayer", TestBuilderLoader::loader());
    CCBReader * ccbReader = new CCBReader(ccNodeLoaderLibrary);
    CCNode* node = ccbReader->readNodeGraphFromFile("CCTestLayer.ccbi");
    CCScene * scene = CCScene::create();
    if(node != NULL) {
        scene->addChild(node);
    }
    ccbReader->release();
    
    return scene;
}