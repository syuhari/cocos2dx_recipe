//
//  MyTableViewCell.h
//  RecipeBook
//
//  Created by FURUKI Eiji on 13/05/30.
//
//

#ifndef __RecipeBook__MyTableViewCell__
#define __RecipeBook__MyTableViewCell__

#include "cocos2d.h"
#include "cocos-ext.h"

NS_CC_EXT_BEGIN

class MyTableViewCell : public CCTableViewCell
{
protected:
    CC_SYNTHESIZE_RETAIN(CCLabelTTF*, m_textLabel, TextLabel);
    CC_SYNTHESIZE_RETAIN(CCLabelTTF*, m_detailLabel, DetailLabel);
    CC_SYNTHESIZE_RETAIN(CCSprite*, m_imageSprite, ImageSprite);
    virtual void needsLayout();
public:
    MyTableViewCell();
    virtual ~MyTableViewCell();
    
    // 生成メソッド
    virtual bool init();
    virtual bool initWithLabel(CCLabelTTF* textLabel, CCLabelTTF* detailLabel, CCSprite *imageSprite);
    static MyTableViewCell* create(CCLabelTTF* textLabel, CCLabelTTF* detailLabel, CCSprite *imageSprite);
    static MyTableViewCell* create(const char *text, const char *fontName, float fontSize,
                                   const char *detail, float detailFontSize,
                                   const char* imagePath=NULL);
    CREATE_FUNC(MyTableViewCell);
    
    static CCSize cellSize();
    // プロパティ
    void setImagePath(const char* path);
    CC_PROPERTY(const char*, m_textString, TextString);
    CC_PROPERTY(const char*, m_detailString, DetailString);
};

NS_CC_EXT_END

#endif /* defined(__RecipeBook__MyTableViewCell__) */
