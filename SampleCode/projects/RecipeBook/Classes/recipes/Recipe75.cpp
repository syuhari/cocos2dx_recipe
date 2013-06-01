//
//  Recipe75.cpp
//  RecipeBook
//
//  Created by Kenji Saito on 5/25/13.
//  Copyright 2013 Syuhari, Inc. All rights reserved.
//

#include "Recipe75.h"

USING_NS_CC;

CCScene* Recipe75::scene()
{
    CCScene *scene = CCScene::create();
    Recipe75 *layer = Recipe75::create();
    scene->addChild(layer);
    return scene;
}

bool Recipe75::init()
{
    if ( !RecipeBase::init() )
    {
        return false;
    }
    
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    
    int fontSize = CCEGLView::sharedOpenGLView()->getDesignResolutionSize().height/320.0f * 16;
    std::string text = "画面タッチでDictationManagerに処理を依頼し、\n処理が終わったらデリゲートメソッドを呼び出してもらいます。\nデリゲートメソッドが実行されるとログを出力します。\n（処理の実装はダミーで、処理の依頼を受けてから\n一律3秒後にデリゲートを呼び出しています）";
    CCLabelTTF *label = CCLabelTTF::create(text.c_str(), "Helvetica", fontSize);
    label->setPosition(ccp(visibleSize.width/2, visibleSize.height/2));
    this->addChild(label);
    
    // タッチを有効にする
    this->setTouchMode(kCCTouchesOneByOne);
    this->setTouchEnabled(true);
    
    CCLog("--- Recipe 75 ------");
    
    return true;
}

// 音声認識結果の通知を受けるデリゲートメソッド
void Recipe75::onResults(CCArray* results)
{
    CCLog("Recipe75::onResults called");
}

// 音声認識エラーの通知を受けるデリゲートメソッド
void Recipe75::onError(int errorCode)
{
    CCLog("Recipe75::onError called");
}

// ここでは、画面タッチされたら、処理を依頼するメソッドを呼ぶ
bool Recipe75::ccTouchBegan(CCTouch* pTouch, CCEvent* pEvent)
{
    this->keyMenuTapped();
    return true;
}

// 処理を依頼するメソッド
void Recipe75::keyMenuTapped()
{
    // 処理側に自インスタンスを設定する
    DictationManager::sharedObject()->setDelegate(this);
    
    CCLog("Call startListening()");
    // 処理を呼び出す
    //（処理が終わると、デリゲートメソッドがコールバックされる）
    DictationManager::sharedObject()->startListening();
}