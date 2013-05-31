//
//  Recipe64.cpp
//  RecipeBook
//
//  Created by FURUKI Eiji on 13/05/31.
//
//

#include "Recipe64.h"
#include "AppMacro.h"
#include "AppPlatform.h"
#include "VisibleRect.h"

USING_NS_CC;

Recipe64::Recipe64()
{
}

CCScene* Recipe64::scene()
{
    CCScene *scene = CCScene::create();
    Recipe64 *layer = Recipe64::create();
    scene->addChild(layer);
    return scene;
}

bool Recipe64::init()
{
    if ( !RecipeBase::init() )
    {
        return false;
    }
    CCLabelTTF *label = CCLabelTTF::create("画面をタップするとカメラを起動します", "Helvetica", FONT_SIZE(16));
    label->setPosition(VisibleRect::center());
    addChild(label, 10, 10);
    
    return true;
}

void Recipe64::onEnter()
{
    RecipeBase::onEnter();
    this->setTouchMode(kCCTouchesAllAtOnce);
    this->setTouchEnabled(true);
}

void Recipe64::ccTouchesBegan(CCSet* touches, CCEvent* event)
{
    // カメラを起動する
    DeviceCamera* camera = DeviceCamera::sharedInstance();
    camera->setDelegate(this);
    camera->launchCamera();
}

void Recipe64::onDeviceCameraDidFinishPick(CCTexture2D *texture)
{
    // カメラ画像のテクスチャをレイヤに追加して、シャッフルして元に戻す
    CCNode* node = CCNode::create();
    CCSprite *bg = CCSprite::createWithTexture(texture);
    bg->setPosition(VisibleRect::center());
    node->addChild(bg, 0);
    
    CCShuffleTiles* shuffle = CCShuffleTiles::create(2.f, CCSizeMake(32,32), 0);
    CCActionInterval* reverse = shuffle->reverse();
    CCActionInterval* act = CCSequence::create(shuffle, reverse,NULL);
    node->runAction(act);
    addChild(node);
}