//
//  AppPlatform.h
//  RecipeBook
//
//  Created by FURUKI Eiji on 13/05/31.
//
//

#ifndef __RecipeBook__AppPlatform__
#define __RecipeBook__AppPlatform__

#include "cocos2d.h"

// Recipe67 キーイベント
class AppKeyDelegate
{
public:
    virtual void onAppKeyEvent(int keycode){};
};

class AppPlatform
{
private:
    static AppPlatform *instance;
public:
    static AppPlatform* sharedInstance();

    // Recipe60 アプリーケーションバージョンの取得
    static const char* getAppVersion();

    // Recipe67 キーイベント
    CC_SYNTHESIZE(AppKeyDelegate*, m_appkeydelegate, AppKeyDelegate);
};

#endif /* defined(__RecipeBook__AppPlatform__) */
