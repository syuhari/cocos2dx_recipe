//
//  Recipe03to16.cpp
//  RecipeBook
//
//  Created by Kenji Saito on 5/25/13.
//  Copyright 2013 Syuhari, Inc. All rights reserved.
//

#include "Recipe03to16.h"
#include "HelloWorldScene.h"

USING_NS_CC;

CCScene* Recipe03to16::scene()
{
    CCScene *scene = CCScene::create();
    Recipe03to16 *layer = Recipe03to16::create();
    scene->addChild(layer);
    return scene;
}

bool Recipe03to16::init()
{
    // ▼ レシピ03で追加 //////////
    // レシピ06で変更
    //if (!CCLayer::init())
    //if (!CCLayerColor::initWithColor(ccc4(170,220,120,255)))
    if (!CCLayerGradient::initWithColor(ccc4(70,145,15,255), ccc4(170,220,120,255) ,ccp(0.0f, 1.0f)))
    {
        return false;
    }
    
    // 画面の幅を取得
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    // 画像ファイルとrectを指定してスプライトを作成
    CCSprite *player = CCSprite::create("monkey01.png", CCRectMake(0, 0, 100, 135) );
    // スプライトの位置を設定
    player->setPosition(ccp(player->getContentSize().width*3/2, winSize.height/2));
    // 後で識別できるようにタグを設定
    player->setTag(1);
    // スプライトをレイヤに追加
    this->addChild(player);
    // ▲ レシピ03で追加 \\\\\\\\\\
    
    
    // ▼ レシピ10で追加 //////////
    // 閉じるボタン
    // ２つの画像ファイルとコールバックを指定してCCMenuItemImageを作成
    CCMenuItemImage *pCloseItem = CCMenuItemImage::create(
                                        "button_close.png",
                                        "button_close_pressed.png",
                                        this,
                                        menu_selector(Recipe03to16::menuCloseCallback));
    // 表示位置を指定
    pCloseItem->setPosition(ccp(winSize.width - pCloseItem->getContentSize().width / 2 ,
                                pCloseItem->getContentSize().height / 2));
    // CCMenuItemImage から CCMenuを作成
    CCMenu* pMenu = CCMenu::create(pCloseItem, NULL);
    // CCMenuとしての位置は(0,0)を指定
    pMenu->setPosition(CCPointZero);
    // CCMenuをレイヤに追加
    this->addChild(pMenu);
    
    // タップ時の画像を用意せずタップ時に色合いを変えるボタン
    // 同じ画像のスプライトを２つ作成
    CCSprite* item1 = CCSprite::create("button_close.png");
    CCSprite* item2 = CCSprite::create("button_close.png");
    // タップ時に表示するスプライトに灰色を指定
    item2->setColor(ccc3(102,102,102));
    // ２つのスプライトとコールバックを指定してCCMenuItemSpriteを作成
    CCMenuItemSprite* pCloseItem2 = CCMenuItemSprite::create(
                                        item1, item2, this, menu_selector(Recipe03to16::menuCloseCallback));
    pCloseItem2->setPosition(ccp(winSize.width - pCloseItem->getContentSize().width * 3 / 2 ,
                                 pCloseItem->getContentSize().height / 2));
    // CCMenuItemSprite から CCMenuを作成
    CCMenu* pMenu2 = CCMenu::create(pCloseItem2, NULL);
    pMenu2->setPosition(CCPointZero);
    // CCMenuをレイヤに追加
    this->addChild(pMenu2);
    // ▲ レシピ10で追加 \\\\\\\\\\
    
    
    // ▼ レシピ11で追加 //////////
    // トグルボタン
    // Offの状態を示すCCMenuItemSpriteを作成
    // Offの通常時
    CCSprite* itemOff1 = CCSprite::create("button_check_off.png");
    // Offのタップ時は色合いを変える
    CCSprite* itemOff2 = CCSprite::create("button_check_off.png");
    itemOff2->setColor(ccc3(102,102,102));
    CCMenuItemSprite* menuItemOff = CCMenuItemSprite::create(itemOff1, itemOff2, NULL);
    
    // Onの状態を示すCCMenuItemSpriteを作成
    // Onの通常時
    CCSprite* itemOn1 = CCSprite::create("button_check_on.png");
    // Onのタップ時は色合いを変える
    CCSprite* itemOn2 = CCSprite::create("button_check_on.png");
    itemOn2->setColor(ccc3(102,102,102));
    CCMenuItemSprite* menuItemOn = CCMenuItemSprite::create(itemOn1, itemOn2, NULL);
    
    // OnとOffのCCMenuItemとコールバックを指定してCCMenuItemToggleを作成
    CCMenuItemToggle* toggleItem = CCMenuItemToggle::createWithTarget(
                                        this,
                                        menu_selector(Recipe03to16::changeMode),
                                        menuItemOff,
                                        menuItemOn, NULL );
    // 表示位置を指定
    toggleItem->setPosition(ccp(toggleItem->getContentSize().width / 2 ,
                                winSize.height - toggleItem->getContentSize().height / 2));
    // CCMenuItemToggle から CCMenuを作成
    CCMenu* toggleMenu = CCMenu::create(toggleItem, NULL);
    // CCMenuとしての位置は(0,0)を指定
    toggleMenu->setPosition(CCPointZero);
    toggleMenu->setTag(3);
    // CCMenuをレイヤに追加
    this->addChild(toggleMenu);
    // ▲ レシピ11で追加 \\\\\\\\\\
    
    
    // ▼ レシピ12で追加 //////////
    // SCORE 文字列
    CCLabelTTF* scoreLabel = CCLabelTTF::create("SCORE", "arial", 48);
    scoreLabel->setPosition(ccp(winSize.width/2, winSize.height - scoreLabel->getContentSize().height/2));
    scoreLabel->setTag(10);
    this->addChild(scoreLabel);
    
    // スコアポイント
    CCLabelTTF* pointsLabel = CCLabelTTF::create("0", "arial", 48);
    pointsLabel->setPosition(ccp(scoreLabel->getPositionX() + scoreLabel->getContentSize().width,
                                 winSize.height - pointsLabel->getContentSize().height/2));
    pointsLabel->setTag(11);
    this->addChild(pointsLabel);
    // ▲ レシピ12で追加 \\\\\\\\\\
    
    
    // レシピ04で追加
    // 3秒に一度、gameLogic()を実行させる
    this->schedule(schedule_selector(Recipe03to16::gameLogic), 3.0);
    
    // レシピ08で追加
    // 毎フレームでupdate()を実行させる
    this->scheduleUpdate();
    // レシピ09補足：上記は以下と同じ結果
    //this->schedule(schedule_selector(Recipe03to16::update));
    
    
    // ▼ レシピ07で追加 //////////
    // マルチタッチモード
    this->setTouchMode(kCCTouchesAllAtOnce);
    // シングルタッチモード
    // this->setTouchMode(kCCTouchesOneByOne);
    
    // タッチを有効にする
    this->setTouchEnabled(true);
    // ▲ レシピ07で追加 \\\\\\\\\\
    
    return true;
}


// ▼ レシピ04で追加 //////////
void Recipe03to16::addFood()
{
    // ハンバーガーのスプライトを作成してレイヤへ追加
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    CCSprite* food = CCSprite::create("hamburger.png", CCRectMake(0, 0, 36, 30) );
    int height = rand() % (int)winSize.height;
    food->setPosition(ccp(winSize.width + food->getContentSize().width/2, height));
    // 後で識別できるようにタグを設定
    food->setTag(2);
    this->addChild(food);
    
    // アクションの継続時間
    float duration = 2.0f;
    // アクションの作成
    CCMoveTo* actionMove = CCMoveTo::create(duration,
                                ccp(food->getContentSize().width*3/2, food->getPositionY()));
    
    // レシピ05で追加
    // spriteMoveFinished()メソッドを呼び出すCCCallFuncNアクションを作成
    CCCallFuncN* actionMoveDone =
            CCCallFuncN::create( this, callfuncN_selector(Recipe03to16::spriteMoveFinished));
    
    // アクションの実行
    //food->runAction(actionMove);
    // レシピ05で変更
    // actionMoveアクションの後に、actionMoveDoneを実行させる
    food->runAction(CCSequence::create(actionMove, actionMoveDone, NULL));
    
    
    // ▼ レシピ13で追加 //////////
    CCActionInterval* action1;
    CCActionInterval* action2;
    // ベジェ曲線移動の際に利用
    ccBezierConfig bezier;
    bezier.controlPoint_1 = ccp(winSize.width, winSize.height);
    bezier.controlPoint_2 = ccp(winSize.width/2, -winSize.height);
    bezier.endPosition = ccp(0, winSize.height);
    
    // アクションの種類を切り替えて実行
    switch (this->m_actionType) {
        case 1:
            // 拡大：４倍に拡大
            action1 = CCScaleTo::create(duration, 4.0f);
            food->runAction(action1);
            break;
        case 2:
            // 回転：360度回転
            action1 = CCRotateBy::create(duration, 360);
            food->runAction(action1);
            action2 = CCRepeatForever::create(action1);
            break;
        case 3:
            // 拡大と回転の組み合わせ
            action1 = CCScaleTo::create(duration, 4.0f);
            action2 = CCRotateBy::create(duration, 360);
            //food->runAction(action1);
            //food->runAction(action2);
            food->runAction(CCSpawn::create(action1, action2, NULL));
            break;
        case 4:
            // 永久繰り返し
            action1 = CCRotateBy::create(0.5f, -360);
            // 0.5秒で1回転を永久に繰り返す（削除されるまで）
            action2 = CCRepeatForever::create(action1);
            food->runAction(action2);
            break;
        case 5:
            // ジャンプ：高さ100、回数5
            action1 = CCJumpBy::create(duration, ccp(0, 0), 100, 5);
            food->runAction(action1);
            break;
        case 6:
            // シーケンス実行：４倍に拡大した後、３回ジャンプ
            action1 = CCScaleTo::create(duration/2.0f, 4.0f);
            action2 = CCJumpBy::create(duration/2.0f, ccp(0, 0), 100, 3);
            food->runAction(CCSequence::create(action1, action2, NULL));
            break;
        case 7:
            // フェードイン／アウト
            // 半分の時間でフェードイン
            action1 = CCFadeIn::create(duration/2.0f);
            // フェードインの反転
            action2 = action1->reverse();
            // フェードインの反転は以下と同じ
            //action2 = CCFadeOut::create(duration/2.0f);
            // action1、action2 の順に実行
            food->runAction(CCSequence::create(action1, action2, NULL));
            break;
        case 8:
            // 水平移動のアクションを停止
            food->stopAllActions();
            // ベジェ曲線に沿って移動
            action1 = CCBezierTo::create(duration, bezier);
            food->runAction(CCSequence::create(action1, actionMoveDone, NULL));
            break;
            
            
        // ▼ レシピ14で追加 //////////
        case 9:
            // 水平移動のアクションを停止
            food->stopAllActions();
            // EaseInOutアクションを作成
            action1 = CCEaseInOut::create((CCActionInterval *)actionMove, 3.0f);
            food->runAction(CCSequence::create(action1, actionMoveDone, NULL));
            break;
        case 10:
            // 水平移動のアクションを停止
            food->stopAllActions();
            // CCEaseBounceOutアクションを作成
            action1 = CCEaseBounceOut::create((CCActionInterval *)actionMove);
            food->runAction(CCSequence::create(action1, actionMoveDone, NULL));
            break;
        case 11:
            // 水平移動のアクションを停止
            food->stopAllActions();
            // CCEaseBounceOutアクションを作成
            action1 = CCEaseBounceOut::create((CCActionInterval *)actionMove);
            food->runAction(CCSequence::create(action1, actionMoveDone, NULL));
            // ジャンプ：高さ100、回数5
            action2 = CCJumpBy::create(duration, ccp(0, 0), 100, 5);
            // ジャンプも同時に実行
            food->runAction(action2);
            break;
        // ▲ レシピ14で追加 \\\\\\\\\\
            
            
        default:
            // 水平移動
            break;
    }
    CCLOG("m_actionType :%d", this->m_actionType);
    // actionTypeをインクリメント（8の次は0へ戻る）
    //this->m_actionType = (this->m_actionType + 1)%9;
    // レシピ14で変更
    // actionTypeをインクリメント（11の次は0へ戻る）
    this->m_actionType = (this->m_actionType + 1)%12;
    // ▲ レシピ13で追加 \\\\\\\\\\
    
}
// ▲ レシピ04で追加 \\\\\\\\\\


// ▼ レシピ04で追加 //////////
void Recipe03to16::gameLogic()
{
    this->addFood();
}
// ▲ レシピ04で追加 \\\\\\\\\\


// ▼ レシピ05で追加 //////////
void Recipe03to16::spriteMoveFinished(CCNode* sender)
{
    // 終了したアクションのスプライトを取得（本メソッドの呼び出し元を取得）
    CCSprite *sprite = (CCSprite *)sender;
    bool isCleanUp = true;
    // スプライトをレイヤから削除して破棄する
    this->removeChild(sprite, isCleanUp);
    
    //sprite->setVisible(false);
    //sprite->setOpacity(0);
}
// ▲ レシピ05で追加 \\\\\\\\\\


// ▼ レシピ07で追加 //////////
void Recipe03to16::ccTouchesBegan(cocos2d::CCSet* touches, cocos2d::CCEvent* event)
{
    // タッチされた座標を取得
    CCTouch *touch = (CCTouch *)touches->anyObject();
    CCPoint location = touch->getLocationInView();
    location = CCDirector::sharedDirector()->convertToGL(location);
    
    // ウッホイ君を取得（tag=1で識別）
    CCSprite *player = (CCSprite *)this->getChildByTag(1);
    
    // ウッホイ君をタッチされた座標まで移動させる
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    // 継続時間は移動距離に比例させる
    float length = sqrtf(powf(location.x - player->getPositionX(), 2.0f) + powf(location.y - player->getPositionY(), 2.0f));
    float duration = length / winSize.width * 1.5f;
    CCMoveTo* actionMove = CCMoveTo::create(duration, location);
    player->runAction(actionMove);
}
// ▲ レシピ07で追加 \\\\\\\\\\


// ▼ レシピ08で追加 //////////
void Recipe03to16::update(float dt)
{
    // ウッホイ君のスプライトを取得（tag=1で識別）
    CCSprite* player = (CCSprite *)this->getChildByTag(1);
    CCRect playerRect = CCRectMake(
                            player->getPosition().x - (player->getContentSize().width/4),
                            player->getPosition().y - (player->getContentSize().height/4),
                            player->getContentSize().width/2,
                            player->getContentSize().height/2);
    
    // ハンバーガーのスプライトを取得（tag=2で識別）
    CCSprite* food = (CCSprite *)this->getChildByTag(2);
    if (food == NULL) return; // foodが作成されていなければ処理を抜ける
    CCRect foodRect = CCRectMake(
                            food->getPosition().x - (food->getContentSize().width/2),
                            food->getPosition().y - (food->getContentSize().height/2),
                            food->getContentSize().width,
                            food->getContentSize().height);
    
    // 衝突判定
    //if (playerRect.intersectsRect(foodRect))
    // レシピ13で変更
    if (playerRect.intersectsRect(foodRect) && player->isVisible())
    {
        // ハンバーガーを削除
        this->removeChild(food, true);
        
        // レシピ09で追加
        // ウッホイ君のイメージ変更
        player->setTexture(CCTextureCache::sharedTextureCache()->addImage("monkey02.png"));
        // 0.1秒後にRecipe03to16::eat()を１度だけ実行させる
        this->scheduleOnce(schedule_selector(Recipe03to16::eat), 0.1f);
    }
}
// ▲ レシピ08で追加 \\\\\\\\\\


// ▼ レシピ09で追加 //////////
void Recipe03to16::eat()
{
    // ウッホイ君のイメージを戻す
    CCSprite* player = (CCSprite *)this->getChildByTag(1);
    player->setTexture(CCTextureCache::sharedTextureCache()->addImage("monkey01.png"));
    
    
    // ▼ レシピ16で追加 //////////
    // フレームアニメーション
    // コーディングしてCCAnimationを作成
    CCAnimation* animation = CCAnimation::create();
    for (int i = 3; i <= 5; i++)
    {
        char szName[100] = {0};
        sprintf(szName, "monkey%02d.png", i);
        // フレーム毎の画像を追加
        animation->addSpriteFrameWithFileName(szName);
    }
    // ３フレームで150ミリ秒継続
    animation->setDelayPerUnit(0.15f / 3.0f);
    // アニメーション終了後に元の画像に戻す
    animation->setRestoreOriginalFrame(true);
    // ３回繰り返す
    animation->setLoops(3);
    
    // plistからCCAnimationを作成
    CCAnimationCache* cache = CCAnimationCache::sharedAnimationCache();
    cache->addAnimationsWithFile("animations.plist");
    // plist内の"bite"という名前のアニメーションを生成
    //CCAnimation* animation2 = cache->animationByName("bite");
    
    // フレームアニメーションを実行
    CCAnimate* action = CCAnimate::create(animation);
    //CCAnimate* action = CCAnimate::create(animation2);
    player->runAction(action);
    // ▲ レシピ16で追加 \\\\\\\\\\
    
    
    // ▼ レシピ12で追加 //////////
    // スコアポイントを加算
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    this->m_points += player->getPositionX()/(winSize.width/4) + 1;
    // スコアポイントのラベルを取得
    CCLabelTTF* label = (CCLabelTTF *)this->getChildByTag(11);
    // intからCCStringに変換
    CCString* points = CCString::createWithFormat("%d", this->m_points);
    // スコアポイントの表示を更新
    label->setString(points->getCString());
    // ▲ レシピ12で追加 \\\\\\\\\\
    
}
// ▲ レシピ09で追加 \\\\\\\\\\


// ▼ レシピ11で追加 //////////
void Recipe03to16::changeMode(CCObject* sender)
{
    // トグルボタン内で選択中のアイテムのindexを取得
    // 0:Off, 1:On
    int selectedIndex = dynamic_cast<CCMenuItemToggle*>(sender)->getSelectedIndex();
    
    CCSprite* player = (CCSprite *)this->getChildByTag(1);
    // トグルボタンがOnの時にウッホイ君を非表示にして、Offの時は表示する
    player->setVisible(selectedIndex == 0);
}
// ▲ レシピ11で追加 \\\\\\\\\\


// レシピ02でのプロジェクト作成時にテンプレートに含まれているアプリを終了するメソッド
// レシピ10のボタンタップ時に呼び出される
void Recipe03to16::menuCloseCallback(CCObject* pSender)
{
    // このサンプルアプリでは、前のシーンに戻る
    CCDirector::sharedDirector()->replaceScene(HelloWorld::scene());
    
/*    // アプリを終了する
    CCDirector::sharedDirector()->end();
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
*/
}