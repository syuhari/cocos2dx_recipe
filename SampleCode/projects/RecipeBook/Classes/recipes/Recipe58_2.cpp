//
//  Recipe58_2.cpp
//  RecipeBook
//
//  Created by FURUKI Eiji on 13/05/31.
//
//

#include "Recipe58_2.h"
#include "AppMacro.h"

USING_NS_CC;

Recipe58_2::Recipe58_2()
{
}

CCScene* Recipe58_2::scene()
{
    CCScene *scene = CCScene::create();
    Recipe58_2 *layer = Recipe58_2::create();
    scene->addChild(layer);
    return scene;
}

bool Recipe58_2::init()
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
    
    return true;
}

void Recipe58_2::onEnter()
{
    RecipeBase::onEnter();
    std::string xml =
    "<CATALOG>"
    "<APP>"
    "<TITLE>おやこでリズムタップ</TITLE>"
    "<COMPANY>SMARTEDUCATION,LTD</COMPANY>"
    "<URL>http://rhythmtap.smarteducation.jp</URL>"
    "<YEAR>2013</YEAR>"
    "</APP>"
    "</CATALOG>";

    CCSAXParser parser;
    parser.init("UTF-8");
    parser.setDelegator(this);
    parser.parse(xml.c_str(), xml.length());

    CCLabelTTF *label = (CCLabelTTF*)this->getChildByTag(10);
    label->setString("XMLのパース処理が完了しました。\nログとソースを確認してください");
}

void Recipe58_2::startElement(void *ctx, const char *name, const char **atts)
{
    // テキストバッファの初期化
    currentSAXtext = "";
}

void Recipe58_2::endElement(void *ctx, const char *name)
{
    if (currentSAXtext.length())
    {
        if (strcmp(name, "TITLE")==0)
        {
            // TITLE データ
            CCString* pTitle =
            CCString::create(currentSAXtext.c_str());
            CCLOG("title=%s", pTitle->getCString());
        }
        else if (strcmp(name, "URL")==0)
        {
            // URL データ
            CCString* pUrl = CCString::create(currentSAXtext.c_str());
            CCLOG("url=%s", pUrl->getCString());
        }
    }
}

void Recipe58_2::textHandler(void *ctx, const char *ch, int len)
{
    // テキストバッファへ追加
    currentSAXtext += std::string(ch,0,len);
}