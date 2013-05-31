//
//  Recipe45.h
//  RecipeBook
//
//  Created by FURUKI Eiji on 13/05/30.
//
//

#ifndef __RecipeBook__Recipe45__
#define __RecipeBook__Recipe45__

#include "cocos2d.h"
#include "cocos-ext.h"
#include "RecipeBase.h"

NS_CC_EXT_BEGIN

class Recipe45 : public RecipeBase, public CCTableViewDataSource, public CCTableViewDelegate
{
private:
public:
    Recipe45();
    virtual bool init();
    static CCScene* scene();
    CREATE_FUNC(Recipe45);

    virtual void scrollViewDidScroll(CCScrollView* view) {}
    virtual void scrollViewDidZoom(CCScrollView* view) {}
    virtual void tableCellTouched(CCTableView* table, CCTableViewCell* cell);
    virtual void tableCellHighlight(CCTableView* table, CCTableViewCell* cell);
    virtual void tableCellUnhighlight(CCTableView* table, CCTableViewCell* cell);
    virtual void tableCellWillRecycle(CCTableView* table, CCTableViewCell* cell);
    virtual cocos2d::CCSize cellSizeForTable(CCTableView *table);
    virtual cocos2d::extension::CCTableViewCell* tableCellAtIndex(CCTableView *table, unsigned int idx);
    virtual unsigned int numberOfCellsInTableView(CCTableView *table);
};

NS_CC_EXT_END

#endif /* defined(__RecipeBook__Recipe45__) */
