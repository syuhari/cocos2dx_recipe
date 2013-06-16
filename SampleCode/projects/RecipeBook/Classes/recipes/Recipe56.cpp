//
//  Recipe56.cpp
//  RecipeBook
//
//  Created by FURUKI Eiji on 13/06/16.
//
//

#include "Recipe56.h"
#include "AppMacro.h"
#include "Recipe54.h"
#include "picojson.h"

USING_NS_CC;

Recipe56::Recipe56()
{
}

CCScene* Recipe56::scene()
{
    CCScene *scene = CCScene::create();
    Recipe56 *layer = Recipe56::create();
    scene->addChild(layer);
    return scene;
}

bool Recipe56::init()
{
    if ( !RecipeBase::init() )
    {
        return false;
    }
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();
    
    CCLabelTTF *label = CCLabelTTF::create("json解析処理", "Helvetica", FONT_SIZE(16));
    label->setPosition(ccp(origin.x + visibleSize.width/2,
                           origin.y + visibleSize.height/2));
    addChild(label, 10, 10);
    
    return true;
}

void Recipe56::onEnter()
{
    RecipeBase::onEnter();

    CCFileUtils* fileUtils = CCFileUtils::sharedFileUtils();
    std::string fullpath = fileUtils->fullPathForFilename("tweet_sample.json");
    unsigned long size;
    unsigned char* data = fileUtils->getFileData(fullpath.c_str(), "rb", &size);
    if (data != NULL)
    {
        std::string err;
        // パースを実行し、picojson::valueにパース結果を格納する
        picojson::value v;
        picojson::parse(v, data, data+size, &err);
        delete [] data;
        if (err.empty())
        {
            // JSONのルートのobject(std::map<std::string, value>) を取得する
            picojson::object &root = v.get<picojson::object>();
            // 検索結果一覧を取得する
            picojson::array &results = root["results"].get<picojson::array>();
            picojson::array::iterator it;
            for (it = results.begin(); it != results.end(); it++)
            {
                // Tweetのテキストとユーザを取得する
                picojson::object& tweet = it->get<picojson::object>();
                std::string& from_user = tweet["from_user"].get<std::string>();
                std::string& text = tweet["text"].get<std::string>();
                CCLOG("%s:%s", from_user.c_str(), text.c_str());
            }
        }
    }
    
    CCLabelTTF *label = (CCLabelTTF*)this->getChildByTag(10);
    label->setString("tweet データのパース処理が完了しました。\nログとソースを確認してください");
}

