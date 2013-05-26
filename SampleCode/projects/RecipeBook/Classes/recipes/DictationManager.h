//
//  DictationManager.h
//  RecipeBook
//
//  Created by Kenji Saito on 5/25/13.
//  Copyright 2013 Syuhari, Inc. All rights reserved.
//

#ifndef _RecipeBook_DictationManager_H_
#define _RecipeBook_DictationManager_H_

#include "cocos2d.h"
#include "RecipeBase.h"

USING_NS_CC;

// 依頼側に実装してもらうデリゲートメソッドを定義したクラス
class DictationManagerDelegate
{
public:
    // virtualとして、実装が空のメソッドを定義
    virtual void onResults(CCArray* results) {};
    virtual void onError(int errorCode) {};
};


// 処理側本体のクラス
class DictationManager
{
private:
    // 依頼側クラスのインスタンスを保持する変数
    DictationManagerDelegate* _delegate;
    // 自クラスのインスタンスを保持する変数
    static DictationManager* _instance;
    
public:
    // 依頼側クラスのインスタンスをセットするメソッド
    void setDelegate(DictationManagerDelegate* delegate);
    // 音声認識を開始するメソッド
    void startListening();
    // 音声認識の結果を受けるメソッド
    void onResults(int error, CCArray* results);
    // 自クラスのインスタンスを返す
    static DictationManager* sharedObject();
};

#endif // _RecipeBook_DictationManager_H_
