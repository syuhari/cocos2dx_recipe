//
//  Recipe45.cpp
//  RecipeBook
//
//  Created by FURUKI Eiji on 13/05/30.
//
//

#include "Recipe45.h"
#include "cocos-ext.h"
#include "MyTableViewCell.h"

USING_NS_CC;
USING_NS_CC_EXT;

Recipe45::Recipe45()
{
}

CCScene* Recipe45::scene()
{
    CCScene *scene = CCScene::create();
    Recipe45 *layer = Recipe45::create();
    scene->addChild(layer);
    return scene;
}

bool Recipe45::init()
{
    if ( !RecipeBase::init() )
    {
        return false;
    }
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();
    
    CCTableView* tableView = CCTableView::create(this,
                                                 CCSizeMake(visibleSize.width, visibleSize.height));
    // 表示方向（縦）
    tableView->setDirection(kCCScrollViewDirectionVertical);
    // 表示順（上から）
    tableView->setVerticalFillOrder(kCCTableViewFillTopDown);
    tableView->setPosition(ccp(origin.x, origin.y));
    tableView->setDelegate(this);
    addChild(tableView);
    // テーブルビューのデータを読み込み
    tableView->reloadData();
    return true;
}

void Recipe45::tableCellTouched(CCTableView* table,
                                  CCTableViewCell* cell)
{
    CCLOG("cell touched at index: %i", cell->getIdx());
}

CCSize Recipe45::cellSizeForTable(CCTableView *table)
{
    return MyTableViewCell::cellSize();
}

void Recipe45::tableCellHighlight(CCTableView* table,
                                    CCTableViewCell* cell)
{
    CCLOG("cell tableCellHighlight at index: %i", cell->getIdx());
}
void Recipe45::tableCellUnhighlight(CCTableView* table,
                                      CCTableViewCell* cell)
{
    CCLOG("cell tableCellUnhighlight at index: %i", cell->getIdx());
    
}
void Recipe45::tableCellWillRecycle(CCTableView* table,
                                      CCTableViewCell* cell)
{
    CCLOG("cell tableCellWillRecycle at index: %i", cell->getIdx());
    
}

CCTableViewCell* Recipe45::tableCellAtIndex(CCTableView *table,
                                              unsigned int idx)
{
    MyTableViewCell *cell = (MyTableViewCell*)table->dequeueCell();
    if (!cell)
    {
        cell = MyTableViewCell::create();
    }
    CCString *text = CCString::createWithFormat(
                                                "Cocos2d-x開発のレシピ %d", idx);
    CCString *detail = CCString::createWithFormat(
                                                  "Cocos2d-x開発のレシピ %d", idx);
    cell->setTextString(text->getCString());
    cell->setDetailString(detail->getCString());
    
    CCString *path = CCString::createWithFormat(
                                                "nini_eat_%d.png", idx%5+1);
    cell->setImagePath(path->getCString());
    return cell;
}

unsigned int Recipe45::numberOfCellsInTableView(CCTableView *table)
{
    return 20;
}

