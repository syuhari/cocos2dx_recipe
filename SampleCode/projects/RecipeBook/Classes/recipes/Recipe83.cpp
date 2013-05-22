//
//  Recipe83.cpp
//  RecipeBook
//
//  Created by Akihiro Matsuura on 5/22/13.
//  Copyright 2013 Syuhari, Inc. All rights reserved.
//

#include "Recipe83.h"

USING_NS_CC;

CCScene* Recipe83::scene()
{
    CCScene *scene = CCScene::create();
    Recipe83 *layer = Recipe83::create();
    scene->addChild(layer);
    return scene;
}

bool Recipe83::init()
{
    if ( !RecipeBase::init() )
    {
        return false;
    }
        
    // 雪のパーティクル
    //CCParticleSnow* pParticle = CCParticleSnow::createWithTotalParticles(1000);
    
    // 雨
    //CCParticleRain* pParticle = CCParticleRain::createWithTotalParticles(1000);
    
    // 煙
    //CCParticleSmoke* pParticle = CCParticleSmoke::createWithTotalParticles(1000);
    
    // 炎
    CCParticleFire* pParticle = CCParticleFire::createWithTotalParticles(1000);
    ccColor4F color = pParticle->getStartColor();
    color.r = 0.0f;
    color.g = 0.1f;
    pParticle->setStartColor(color);
    
    // 花火
    //CCParticleFireworks* pParticle = CCParticleFireworks::createWithTotalParticles(1000);
    
    // 花
    //CCParticleFlower* pParticle = CCParticleFlower::createWithTotalParticles(100);
    
    // 銀河
    //CCParticleGalaxy* pParticle = CCParticleGalaxy::createWithTotalParticles(1000);
    
    // 流星
    //CCParticleMeteor* pParticle = CCParticleMeteor::createWithTotalParticles(1000);
    
    //CCParticleSpiral* pParticle = CCParticleSpiral::createWithTotalParticles(1000);
    
    //CCParticleSun* pParticle = CCParticleSun::createWithTotalParticles(1000);
    
    //CCParticleExplosion* pParticle = CCParticleExplosion::createWithTotalParticles(1000);
    
    
    
    // plist からパーティクルを読み込む
    //CCParticleSystemQuad* pParticle = CCParticleSystemQuad::create("my_particle.plist");
    
    
    this->addChild(pParticle);
    
    return true;
}

