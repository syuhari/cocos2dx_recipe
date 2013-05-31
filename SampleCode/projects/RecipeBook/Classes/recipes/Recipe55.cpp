//
//  Recipe55.cpp
//  RecipeBook
//
//  Created by FURUKI Eiji on 13/05/30.
//
//

#include "curl/curl.h"
#include "Recipe55.h"
#include "AppMacro.h"
#include <errno.h>

USING_NS_CC;

static pthread_t s_recipe55_thread;
static std::string s_writablePath;

Recipe55::Recipe55() 
{
}

CCScene* Recipe55::scene()
{
    CCScene *scene = CCScene::create();
    Recipe55 *layer = Recipe55::create();
    scene->addChild(layer);
    return scene;
}

bool Recipe55::init()
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
    
    // 進捗のリセット
    this->progressData = 0;
    // ダウンロード進捗表示の開始（1秒ごと）
    this->schedule(schedule_selector(Recipe55::recipe55_update_progress), 0.5f);
    // ダウンロード実行
    recipe55_downloadHugeFile();
    return true;
}

static int recipe55_progress(void *clientp, double dltotal,
                             double dlnow, double ultotal, double ulnow)
{
    // CURLOPT_PROGRESSDATA で設定したポインタに進捗状況を設定
    unsigned *progress = (unsigned *)clientp;
    *progress = (dlnow/dltotal)*100;
    return 0;
}


static void *recipe55_workthread(void *data)
{
    CURL *curl;
    curl = curl_easy_init();
    if (curl)
    {
        std::string path = s_writablePath + "recipe55_download.dat";
        FILE *fp = fopen(path.c_str(), "wb");
        if (fp != NULL) {
            curl_easy_setopt(curl, CURLOPT_URL, "http://fullfool.com/ccrecipe/hugeData");
            curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp);
            // 進捗状況の変化を受け取る関数を設定
            curl_easy_setopt(curl, CURLOPT_PROGRESSFUNCTION, recipe55_progress);
            // 上記関数に渡すポインタを設定（ここではunsigned intのポインタ）
            curl_easy_setopt(curl, CURLOPT_PROGRESSDATA, data);
            // 進捗状況の通知を有効にする
            curl_easy_setopt(curl, CURLOPT_NOPROGRESS, 0L);
            CURLcode res = curl_easy_perform(curl);
            if (res == 0) {
                CCLOG("curl done");
            }
            curl_easy_cleanup(curl);
            fclose(fp);
        }else{
            CCLOG("%s:%s", strerror(errno), path.c_str());
        }
    }
    return NULL;
}

void Recipe55::recipe55_downloadHugeFile()
{
    s_writablePath = CCFileUtils::sharedFileUtils()->getWritablePath();
    pthread_create(&s_recipe55_thread, NULL, recipe55_workthread, &(this->progressData));
    pthread_detach(s_recipe55_thread);
}

void Recipe55::recipe55_update_progress()
{
    // 進捗を表示するラベルに進捗データを表示
    CCLabelTTF* label = (CCLabelTTF*)this->getChildByTag(10);
    CCString* str = CCString::createWithFormat("progress %d %%",
                                               this->progressData);
    label->setString(str->getCString());
}

