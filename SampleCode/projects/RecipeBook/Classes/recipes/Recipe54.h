//
//  Recipe54.h
//  RecipeBook
//
//  Created by FURUKI Eiji on 13/05/30.
//
//

#ifndef __RecipeBook__Recipe54__
#define __RecipeBook__Recipe54__

#include "cocos2d.h"
#include "RecipeBase.h"

class Recipe54 : public RecipeBase
{
private:
public:
    Recipe54();
    virtual bool init();
    static cocos2d::CCScene* scene();
    CREATE_FUNC(Recipe54);

    virtual void onEnter();
    static bool getTextFromUrl(const char* url, std::vector<char> *response);
    void recipe54_httprequest();
    void onHttpRequestCompleted(cocos2d::CCNode *sender, void *data);

};

#endif /* defined(__RecipeBook__Recipe54__) */
