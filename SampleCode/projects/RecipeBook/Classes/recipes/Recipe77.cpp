//
//  Recipe77.cpp
//  RecipeBook
//
//  Created by FURUKI Eiji on 13/05/31.
//
//

#include "Recipe77.h"
#include "AppMacro.h"
#include "VisibleRect.h"

USING_NS_CC;

const char* LocalizedString(const char* searchKey, const char* comment)
{
    using namespace std;
    const char* ret = comment;
    
    static map<string, string> localizable;
    if(localizable.empty()){
        // 言語ディレクトリを検索対象にする
        CCFileUtils* fileUtils = CCFileUtils::sharedFileUtils();
        ccLanguageType lang = CCApplication::sharedApplication()->getCurrentLanguage();
        if (lang == kLanguageEnglish)
        {
            fileUtils->addSearchPath("en.lproj");
        }
        else if (lang == kLanguageJapanese)
        {
            fileUtils->addSearchPath("ja.lproj");
        }
        // 言語ファイルを開く
        unsigned long size;
        string fullpath = fileUtils->fullPathForFilename("Localizable.strings");
        unsigned char* data = fileUtils->getFileData(fullpath.c_str(), "rb", &size);
        if (data == NULL)
        {
            return ret;
        }
        // Localizable.string のパース
        istringstream is((char*)data);
        delete [] data;
        string line;
        while (std::getline(is, line))
        {
            string::size_type sep = line.find('=');
            if (sep != string::npos)
            {
                string key = line.substr(0,sep-1);
                string val = line.substr(sep+1);
                // スペース、セミコロンなどをトリミングする
                key.erase(0, key.find_first_not_of(" \""));
                key.erase(key.find_last_not_of(" \"")+1);
                val.erase(0, val.find_first_not_of(" \""));
                val.erase(val.find_last_not_of(" \";")+1);
                localizable.insert(pair<string, string>(key,val));
            }
        }
    }
    
    // キー値の検索
    map<string,string>::iterator ite = localizable.find(searchKey);
    if (ite != localizable.end())
    {
        ret = CCString::create((ite->second).c_str())->getCString();
    }
    return ret;
}

Recipe77::Recipe77()
{
}

CCScene* Recipe77::scene()
{
    CCScene *scene = CCScene::create();
    Recipe77 *layer = Recipe77::create();
    scene->addChild(layer);
    return scene;
}

bool Recipe77::init()
{
    if ( !RecipeBase::init() )
    {
        return false;
    }
    CCPoint center = VisibleRect::center();
    CCLabelTTF *label = CCLabelTTF::create("", "Helvetica", FONT_SIZE(16));
    label->setPosition(center);
    addChild(label, 10, 10);
    return true;
}

void Recipe77::onEnter()
{
    RecipeBase::onEnter();

    CCLabelTTF *label = (CCLabelTTF*)this->getChildByTag(10);
    label->setString(LocalizedString("hello_label", "Hello"));
    CCLOG("%s", LocalizedString("hello_log", "Hello"));
}

void Recipe77::onExit()
{
    RecipeBase::onExit();
}

