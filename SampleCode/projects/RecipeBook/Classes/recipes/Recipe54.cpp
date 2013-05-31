//
//  Recipe54.cpp
//  RecipeBook
//
//  Created by FURUKI Eiji on 13/05/30.
//
//

#include "AppMacro.h"
#include "Recipe54.h"

#include "curl/curl.h"
#include "HttpRequest.h"
#include "HttpClient.h"

USING_NS_CC;
USING_NS_CC_EXT;

Recipe54::Recipe54()
{
}

CCScene* Recipe54::scene()
{
    CCScene *scene = CCScene::create();
    Recipe54 *layer = Recipe54::create();
    scene->addChild(layer);
    return scene;
}

bool Recipe54::init()
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

void Recipe54::onEnter()
{
    RecipeBase::onEnter();
    std::vector<char> responseData;
    if (getTextFromUrl(
                       "http://www.cocos2d-x.org/projects/cocos2d-x/news.atom",
                       &responseData))
    {
        std::string str = std::string(responseData.begin(), responseData.end());
        CCLOG("%s", str.c_str());
        
        recipe54_httprequest();
    }
}

static size_t onCurlWriteData(char *ptr, size_t size,
                              size_t nmemb, void *userdata)
{
    // 受信データをバッファに保存する
    std::vector<char> *buff = (std::vector<char>*)userdata;
    size_t sizes = size * nmemb;
    buff->insert(buff->end(), (char*)ptr, (char*)ptr+sizes);
    return sizes;
}

bool Recipe54::getTextFromUrl(const char* url,
                                std::vector<char> *response)
{
    CURL *curl;
    CURLcode res = CURLE_FAILED_INIT;
    
    curl = curl_easy_init();
    if (curl)
    {
        curl_easy_setopt(curl, CURLOPT_URL, url);
        // 受信データ保存関数を指定する
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION,onCurlWriteData);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, response);
        res = curl_easy_perform(curl);
        curl_easy_cleanup(curl);
    }
    if (res == CURLE_OK && response->size())
    {
        return true;
    }
    return false;
}


void Recipe54::recipe54_httprequest()
{
    CCHttpRequest* request = new CCHttpRequest();
    request->setUrl("http://example.com");
    request->setRequestType(CCHttpRequest::kHttpGet);
    request->setResponseCallback(this, callfuncND_selector(Recipe54::onHttpRequestCompleted));
    request->setTag("GET example.com");
    CCHttpClient::getInstance()->send(request);
    request->release();
    
    CCHttpRequest* request2 = new CCHttpRequest();
    request2->setUrl("http://example.net");
    request2->setRequestType(CCHttpRequest::kHttpGet);
    request2->setResponseCallback(this, callfuncND_selector(Recipe54::onHttpRequestCompleted));
    request2->setTag("GET example.net");
    CCHttpClient::getInstance()->send(request2);
    request2->release();
}

void Recipe54::onHttpRequestCompleted(cocos2d::CCNode *sender, void *data)
{
    CCHttpResponse *response = (CCHttpResponse*)data;
    CCHttpRequest* request = response->getHttpRequest();
    
    CCLOG("http request completed");
    CCLOG("url         :%s", request->getUrl());
    CCLOG("tag         :%s", request->getTag());
    CCLOG("status code :%d", response->getResponseCode());
    
    if (!response->isSucceed())
    {
        CCLOG("error buffer: %s", response->getErrorBuffer());
    }
    
    // dump data
    std::vector<char> *buffer = response->getResponseData();
    printf("Http Test, dump data: ");
    for (unsigned int i = 0; i < buffer->size(); i++)
    {
        printf("%c", (*buffer)[i]);
    }
    printf("\n");
    
    CCLabelTTF *label = (CCLabelTTF*)this->getChildByTag(10);
    label->setString("ダウンロード処理が完了しました。\nログとソースを確認してください");
}
