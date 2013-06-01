//
//  Recipe76.h
//  RecipeBook
//
//  Created by FURUKI Eiji on 13/05/31.
//
//

#ifndef __RecipeBook__Recipe76__
#define __RecipeBook__Recipe76__

#include "cocos2d.h"
#include "RecipeBase.h"

class Recipe76 : public RecipeBase
{
private:
    bool createDirectory(const char *path);
    void unzipFileToDir(const char *zipFullPath, const char* toDir);

protected:
    virtual void doStep1();
    virtual void doStep2();
    virtual void doStep3();

public:
    Recipe76();
    virtual bool init();
    static cocos2d::CCScene* scene(int step);
    CREATE_FUNC(Recipe76);

    //virtual void onEnter();
    //virtual void onExit();
};

#endif /* defined(__RecipeBook__Recipe76__) */
