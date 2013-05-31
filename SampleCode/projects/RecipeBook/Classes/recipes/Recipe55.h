//
//  Recipe55.h
//  RecipeBook
//
//  Created by FURUKI Eiji on 13/05/30.
//
//

#ifndef __RecipeBook__Recipe55__
#define __RecipeBook__Recipe55__

#include "cocos2d.h"
#include "RecipeBase.h"

class Recipe55 : public RecipeBase
{
private:
    unsigned progressData;  // ダウンロードの進捗保持
public:
    Recipe55();
    virtual bool init();
    static cocos2d::CCScene* scene();
    CREATE_FUNC(Recipe55);

    void recipe55_downloadHugeFile();
    void recipe55_update_progress();
 
};

#endif /* defined(__RecipeBook__Recipe55__) */
