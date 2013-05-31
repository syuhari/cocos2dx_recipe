//
//  AppPlatform.mm
//  RecipeBook
//
//  Created by FURUKI Eiji on 13/05/31.
//
//

#include "AppPlatform.h"
#include "cocoa/CCString.h"

using namespace cocos2d;

// Recipe60 アプリーケーションバージョンの取得
const char* AppPlatform::getAppVersion()
{
    NSDictionary *info = [[NSBundle mainBundle] infoDictionary];
    NSString *version = [info objectForKey:@"CFBundleShortVersionString"];
    if (version) {
        CCString* ret = CCString::create([version UTF8String]);
        return ret->getCString();
    }
    return NULL;
}


AppPlatform* AppPlatform::instance = NULL;

AppPlatform* AppPlatform::sharedInstance()
{
    if (instance == NULL)
    {
        instance = new AppPlatform();
        instance->m_appkeydelegate = NULL;
    }
    return instance;
}
