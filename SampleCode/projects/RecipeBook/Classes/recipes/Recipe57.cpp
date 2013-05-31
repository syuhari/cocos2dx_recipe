//
//  Recipe57.cpp
//  RecipeBook
//
//  Created by FURUKI Eiji on 13/05/30.
//
//

#include "Recipe57.h"
#include "AppMacro.h"

USING_NS_CC;

Recipe57::Recipe57()
{
}

CCScene* Recipe57::scene()
{
    CCScene *scene = CCScene::create();
    Recipe57 *layer = Recipe57::create();
    scene->addChild(layer);
    return scene;
}

bool Recipe57::init()
{
    if ( !RecipeBase::init() )
    {
        return false;
    }
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();
    
    CCLabelTTF *label = CCLabelTTF::create("plist解析処理", "Helvetica", FONT_SIZE(16));
    label->setPosition(ccp(origin.x + visibleSize.width/2,
                           origin.y + visibleSize.height/2));
    addChild(label, 10, 10);
    
    return true;
}

void Recipe57::onEnter()
{
    RecipeBase::onEnter();
    // plistファイルからDictionaryを生成する
    CCDictionary* plist = CCDictionary::createWithContentsOfFile("Property.plist");
    // テキスト値を取得する
    CCString* pText = (CCString*)plist->objectForKey("text");
    CCLOG("pText:%s", pText->getCString());
    // bool値を取得する
    CCString* pBool = (CCString*)plist->objectForKey("bool");
    CCLOG("pBool:%s", pBool->getCString());
    // dictionary値を取得する
    CCDictionary* pDict = (CCDictionary*)plist->objectForKey("dict");
    // array値を取得する
    CCArray* pArrayInDict = (CCArray*)pDict->objectForKey("array_in_dict");
    
    CCObject* pObj = NULL;
    CCARRAY_FOREACH(pArrayInDict, pObj)
    {
        // 数値を取得する
        CCString* pStr = (CCString*)pObj;
        CCLOG("pStr:%s", pStr->getCString());
    }

    CCLabelTTF *label = (CCLabelTTF*)this->getChildByTag(10);
    label->setString("plistのパース処理が完了しました。\nログとソースを確認してください");
}
