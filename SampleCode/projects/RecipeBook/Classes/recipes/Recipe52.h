//
//  Recipe52.h
//  RecipeBook
//
//  Created by FURUKI Eiji on 13/05/31.
//
//

#ifndef __RecipeBook__Recipe52__
#define __RecipeBook__Recipe52__

#include "cocos2d.h"
#include "RecipeBase.h"
#include "sqlite3.h"

class Recipe52 : public RecipeBase
{
private:
    int sqliteOpen(sqlite3 **database);
    void sqliteCreateTable();
    const char* sqliteGetValueForKey(const char * key);
    void sqliteSetValueForKey(const char * key, const char* value);
    
public:
    Recipe52();
    virtual bool init();
    static cocos2d::CCScene* scene();
    CREATE_FUNC(Recipe52);
    
    virtual void onEnter();
};

#endif /* defined(__RecipeBook__Recipe52__) */
