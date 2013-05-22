//
//  Recipe85.h
//  RecipeBook
//
//  Created by Akihiro Matsuura on 5/22/13.
//  Copyright 2013 Syuhari, Inc. All rights reserved.
//

#ifndef _RecipeBook_Recipe85_H_
#define _RecipeBook_Recipe85_H_

#include "cocos2d.h"
#include "Box2D.h"
#include "RecipeBase.h"
#include "LevelHelperLoader.h"

class Recipe85 : public RecipeBase {
public:
    ~Recipe85();
    Recipe85();
    static cocos2d::CCScene* scene();
    void initPhysics();
    void addNewSpriteAtPosition(cocos2d::CCPoint p);

    virtual void draw();
    void update(float dt);
    
private:
    b2World* world;
    LevelHelperLoader* m_pLHLoader;
};

#endif // _RecipeBook_Recipe85_H_
