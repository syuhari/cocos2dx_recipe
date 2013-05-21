//
//  Recipe32.h
//  RecipeBook
//
//  Created by Akihiro Matsuura on 5/22/13.
//  Copyright 2013 Syuhari, Inc. All rights reserved.
//

#ifndef _RecipeBook_Recipe32_H_
#define _RecipeBook_Recipe32_H_

#include "cocos2d.h"
#include "RecipeBase.h"
#include "cocos-ext.h"
USING_NS_CC_EXT;

class Recipe32 : public RecipeBase, public CCEditBoxDelegate
{
private:
    void editBoxEditingDidBegin(CCEditBox* editBox);
    void editBoxEditingDidEnd(CCEditBox* editBox);
    void editBoxTextChanged(CCEditBox* editBox, const std::string& text);
    void editBoxReturn(CCEditBox* editBox);
public:
    virtual bool init();
    static cocos2d::CCScene* scene();
    CREATE_FUNC(Recipe32);
};

#endif // _RecipeBook_Recipe32_H_
