//
//  Recipe58_3.cpp
//  RecipeBook
//
//  Created by FURUKI Eiji on 13/05/31.
//
//

#include "Recipe58_3.h"
#include "AppMacro.h"
#include "support/tinyxml2/tinyxml2.h"
using namespace tinyxml2;

USING_NS_CC;

Recipe58_3::Recipe58_3()
{
}

CCScene* Recipe58_3::scene()
{
    CCScene *scene = CCScene::create();
    Recipe58_3 *layer = Recipe58_3::create();
    scene->addChild(layer);
    return scene;
}

bool Recipe58_3::init()
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

void Recipe58_3::onEnter()
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
    
    XMLDocument doc;
    // XMLをパースする
    if( doc.Parse(xml.c_str()) == XML_NO_ERROR)
    {
        // 必要な要素を取得する
        const XMLElement* catalog = doc.FirstChildElement();
        const XMLElement* apps = catalog->FirstChildElement();
        for( ;apps; apps = apps->NextSiblingElement() )
        {
            // TITLE データ
            const XMLElement* title = apps->FirstChildElement("TITLE");
            CCString* pTitle = CCString::create(title->GetText());
            // URL データ
            const XMLElement* url = apps->FirstChildElement("URL");
            CCString* pUrl = CCString::create(url->GetText());
            CCLOG("%s, url:%s", pTitle->getCString(), pUrl->getCString());
        }
    }
    CCLabelTTF *label = (CCLabelTTF*)this->getChildByTag(10);
    label->setString("XMLのパース処理が完了しました。\nログとソースを確認してください");
}
