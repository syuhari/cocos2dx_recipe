//
//  Recipe84.h
//  RecipeBook
//
//  Created by Akihiro Matsuura on 5/22/13.
//  Copyright 2013 Syuhari, Inc. All rights reserved.
//

#ifndef _RecipeBook_Recipe84_H_
#define _RecipeBook_Recipe84_H_

#include "cocos2d.h"
#include "Box2D.h"
#include "RecipeBase.h"

class Recipe84 : public RecipeBase {
public:
    ~Recipe84();
    Recipe84();
    static cocos2d::CCScene* scene();
    void initPhysics();
    void addNewSpriteAtPosition(cocos2d::CCPoint p);

    virtual void draw();
    virtual void ccTouchesEnded(cocos2d::CCSet* touches, cocos2d::CCEvent* event);
    void update(float dt);
    
private:
    b2World* world;
    cocos2d::CCTexture2D* m_pSpriteTexture; // weak ref
};

#endif // _RecipeBook_Recipe84_H_
