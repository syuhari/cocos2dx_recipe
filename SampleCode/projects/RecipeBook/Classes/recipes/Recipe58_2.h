//
//  Recipe58_2.h
//  RecipeBook
//
//  Created by FURUKI Eiji on 13/05/31.
//
//

#ifndef __RecipeBook__Recipe58_2__
#define __RecipeBook__Recipe58_2__

#include "cocos2d.h"
#include "RecipeBase.h"

class Recipe58_2 : public RecipeBase, public cocos2d::CCSAXDelegator
{
private:
    // XML解析中のテキストバッファ
    std::string currentSAXtext;
public:
    Recipe58_2();
    virtual bool init();
    static cocos2d::CCScene* scene();
    CREATE_FUNC(Recipe58_2);
    
    virtual void onEnter();
    
    virtual void startElement(void *ctx, const char *name, const char **atts);
    virtual void endElement(void *ctx, const char *name);
    virtual void textHandler(void *ctx, const char *ch, int len);
    
    
};


#endif /* defined(__RecipeBook__Recipe58_2__) */
