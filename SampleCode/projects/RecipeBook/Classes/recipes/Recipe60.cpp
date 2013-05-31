//
//  Recipe60.cpp
//  RecipeBook
//
//  Created by FURUKI Eiji on 13/05/31.
//
//

#include "Recipe60.h"
#include "AppMacro.h"
#include "AppPlatform.h"

USING_NS_CC;

Recipe60::Recipe60()
{
}

CCScene* Recipe60::scene()
{
    CCScene *scene = CCScene::create();
    Recipe60 *layer = Recipe60::create();
    scene->addChild(layer);
    return scene;
}

bool Recipe60::init()
{
    if ( !RecipeBase::init() )
    {
        return false;
    }
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();
    
    CCLabelTTF *label = CCLabelTTF::create("", "Helvetica", FONT_SIZE(16));
    label->setPosition(ccp(origin.x + visibleSize.width/2,
                           origin.y + visibleSize.height/2));
    addChild(label, 10, 10);
    
    return true;
}

void Recipe60::onEnter()
{
    RecipeBase::onEnter();
    
    // iOS、Andoridのリリースバージョンを取得する
    const char* version = AppPlatform::getAppVersion();
    CCString *msg = CCString::createWithFormat("version : %s", version);
    CCLOG("%s", msg->getCString());
    
    CCLabelTTF *label = (CCLabelTTF*)this->getChildByTag(10);
    label->setString( msg->getCString());
}

