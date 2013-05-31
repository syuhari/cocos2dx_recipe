//
//  Recipe67.cpp
//  RecipeBook
//
//  Created by FURUKI Eiji on 13/05/31.
//
//

#include "Recipe67.h"
#include "AppMacro.h"
#include "AppPlatform.h"
#include "VisibleRect.h"

USING_NS_CC;

Recipe67::Recipe67()
{
}

CCScene* Recipe67::scene()
{
    CCScene *scene = CCScene::create();
    Recipe67 *layer = Recipe67::create();
    scene->addChild(layer);
    return scene;
}

bool Recipe67::init()
{
    if ( !RecipeBase::init() )
    {
        return false;
    }
    CCPoint center = VisibleRect::center();
    CCLabelTTF *label = CCLabelTTF::create("Menu/Backキーを押してください", "Helvetica", FONT_SIZE(16));
    label->setPosition(center);
    addChild(label, 10, 10);

    CCLabelTTF *label2 = CCLabelTTF::create("その他のハードキーを押してください", "Helvetica", FONT_SIZE(16));
    label2->setPosition(ccp(center.x, center.y/2));
    addChild(label2, 11, 11);
    
    return true;
}

void Recipe67::onEnter()
{
    RecipeBase::onEnter();

    this->setKeypadEnabled(true);
    
    AppPlatform::sharedInstance()->setAppKeyDelegate(this);    
}

void Recipe67::onExit()
{
    RecipeBase::onExit();
    AppPlatform::sharedInstance()->setAppKeyDelegate(NULL);
}

void Recipe67::keyBackClicked()
{
    CCLabelTTF *label = (CCLabelTTF*)this->getChildByTag(10);
    label->setString("Back がクリックされました");
}

void Recipe67::keyMenuClicked()
{
    CCLabelTTF *label = (CCLabelTTF*)this->getChildByTag(10);
    label->setString("Menu がクリックされました");
}

void Recipe67::onAppKeyEvent(int keycode)
{
    CCString *msg = CCString::createWithFormat("キーコード(%d)がクリックされました", keycode);
    CCLabelTTF *label = (CCLabelTTF*)this->getChildByTag(11);
    label->setString(msg->getCString());
}

