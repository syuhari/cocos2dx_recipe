//
//  Recipe46.cpp
//  RecipeBook
//
//  Created by FURUKI Eiji on 13/05/25.
//
//

#include "Recipe46.h"

USING_NS_CC;

Recipe46::Recipe46() : m_count(0)
{
}

CCScene* Recipe46::scene()
{
    CCScene *scene = CCScene::create();
    Recipe46 *layer = Recipe46::create();
    scene->addChild(layer);
    return scene;
}

bool Recipe46::init()
{
    if ( !RecipeBase::init() )
    {
        return false;
    }
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();
    CCDrawNode *node = CCDrawNode::create();
    node->setPosition(ccp(origin.x + visibleSize.width/2,
                          origin.y + visibleSize.height/2));
    addChild(node, 1, 1);

    schedule(schedule_selector(Recipe46::updateDraw), 1);
    return true;
}

void Recipe46::updateDraw()
{
    CCDrawNode *node = (CCDrawNode *)getChildByTag(1);
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    float radius = visibleSize.height/2;
    if (m_count == 0)
    {
        node->drawDot(ccp(0, 0),                // 中心
                      radius,                   // 半径
                      ccc4FFromccc3B(ccBLUE));  // 色
        m_count++;
    }
    else if (m_count == 1)
    {
        node->drawSegment(ccp(-radius, 0),      // 始点
                          ccp(radius, 0),       // 終点
                          2,                    // 線の太さ
                          ccc4FFromccc3B(ccRED));
        m_count++;
    }
    else if (m_count == 2)
    {
        static CCPoint triangle[3] = {
            ccp(0, 0),
            ccp(sinf(45.f*M_PI/180.f)*radius, cosf(45.f*M_PI/180.f)*radius),
            ccp(0, radius)
        };
        node->drawPolygon(triangle,                     // 座標データ
                          3,                            // 角数
                          ccc4FFromccc3B(ccGREEN),      // 色
                          1,                            // 枠線の太さ
                          ccc4FFromccc3B(ccBLACK));     // 枠線の色
        m_count++;
    }
    else if (m_count == 3)
    {
        node->clear();
        m_count = 0;
    }
}
