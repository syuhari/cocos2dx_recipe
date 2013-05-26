//
//  DictationManager.cpp
//  RecipeBook
//
//  Created by Kenji Saito on 5/25/13.
//  Copyright 2013 Syuhari, Inc. All rights reserved.
//

#include "DictationManager.h"

USING_NS_CC;

// _instanceの初期化
DictationManager* DictationManager::_instance = NULL;

// 依頼側クラスに呼び出してもらい、依頼側クラスのインスタンスを保持する
void DictationManager::setDelegate(DictationManagerDelegate* delegate)
{
    this->_delegate = delegate;
}

// 音声認識を開始する
void DictationManager::startListening()
{
    // ３秒後に処理を完了したようにシミュレート
    usleep(3*1000*1000); // wait 3sec
    this->onResults(0, NULL);
}

// 音声認識の結果を受ける
void DictationManager::onResults(int error, CCArray *results)
{
    if (this->_delegate)
    {
        if (error)
        {
            // エラーの場合、依頼側にエラーを通知
            this->_delegate->onError(error);
        }
        else
        {
            // 依頼側に結果を通知
            this->_delegate->onResults(results);
        }
    }
}

// 自クラスのインスタンスを返す
DictationManager* DictationManager::sharedObject()
{
    if (_instance == NULL)
    {
        _instance = new DictationManager();
    }
    return _instance;
}