//
//  Recipe78.cpp
//  RecipeBook
//
//  Created by FURUKI Eiji on 13/05/31.
//
//

#include "Recipe78.h"
#include "AppMacro.h"
#include "VisibleRect.h"

USING_NS_CC;

Recipe78::Recipe78()
{
}

CCScene* Recipe78::scene()
{
    CCScene *scene = CCScene::create();
    Recipe78 *layer = Recipe78::create();
    scene->addChild(layer);
    return scene;
}

bool Recipe78::init()
{
    if ( !RecipeBase::init() )
    {
        return false;
    }
    CCPoint center = VisibleRect::center();
    CCSprite* pSprite = CCSprite::create("Default.png");
    pSprite->setPosition(center);
    addChild(pSprite, 9, 9);

    CCLabelTTF *label = CCLabelTTF::create("", "Helvetica", FONT_SIZE(16));
    label->setPosition(center);
    addChild(label, 10, 10);
    return true;
}

void Recipe78::onEnter()
{
    RecipeBase::onEnter();
    
    // 加速度センサーの監視を有効にする
    setAccelerometerEnabled(true);
    // 値の取得間隔は1秒ごと
//    setAccelerometerInterval(1.f);
}

void Recipe78::onExit()
{
    RecipeBase::onExit();
}

void Recipe78::didAccelerate(CCAcceleration* pAccl)
{
    CCString* str = CCString::createWithFormat("Acceleration x:%f, y:%f, z:%f",
                                               pAccl->x, pAccl->y, pAccl->z);
    CCLabelTTF *label = (CCLabelTTF*)this->getChildByTag(10);
    label->setString(str->getCString());

    // 加速度センサーの値に応じてカメラの視点を移動する
    this->getCamera()->setEyeXYZ(pAccl->x * 0.00000063429789, // sin(M_PI/180)/480
                                 pAccl->y * 0.00000095144683, // sin(M_PI/180)/320
                                 0.0000001);
}
