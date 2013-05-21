//
//  Recipe31.cpp
//  RecipeBook
//
//  Created by Akihiro Matsuura on 5/22/13.
//  Copyright 2013 Syuhari, Inc. All rights reserved.
//

#include "Recipe31.h"

USING_NS_CC;

CCScene* Recipe31::scene()
{
    CCScene *scene = CCScene::create();
    Recipe31 *layer = Recipe31::create();
    scene->addChild(layer);
    return scene;
}

bool Recipe31::init()
{
    if ( !RecipeBase::init() )
    {
        return false;
    }

    CCSize size = CCDirector::sharedDirector()->getWinSize();
    
    // switch
    CCSprite* maskSprite  = CCSprite::create("switch-mask.png");
    CCSprite* onSprite    = CCSprite::create("switch-on.png");
    CCSprite* offSprite   = CCSprite::create("switch-off.png");
    CCSprite* thumbSprite = CCSprite::create("switch-thumb.png");
    CCLabelTTF* onLabel   = CCLabelTTF::create("On", "Arial-BoldMT", 16);
    CCLabelTTF* offLabel  = CCLabelTTF::create("Off", "Arial-BoldMT", 16);
    CCControlSwitch* pSwitch = CCControlSwitch::create(maskSprite, onSprite, offSprite, thumbSprite, onLabel, offLabel);
    pSwitch->setPosition(ccp(50+pSwitch->getContentSize().width/2, size.height/4*3)); //-pSwitch->getContentSize().height/2));
    this->addChild(pSwitch);
    pSwitch->addTargetWithActionForControlEvents(this, cccontrol_selector(Recipe31::switchCallBack), CCControlEventValueChanged);
    
    CCLabelTTF* labelSwitch = CCLabelTTF::create("CCControlSwitch", "Arial", 20);
    labelSwitch->setPosition(ccp(50+labelSwitch->getContentSize().width/2,
                                 pSwitch->getPositionY()+pSwitch->getContentSize().height/2+labelSwitch->getContentSize().height));
    this->addChild(labelSwitch);
    
    // slider
    CCControlSlider* pSlider = CCControlSlider::create("sliderTrack.png", "sliderProgress.png", "sliderThumb.png");
    pSlider->setMinimumValue(0.0f);
    pSlider->setMaximumValue(100.0f);
    pSlider->setValue(50.0f);
    pSlider->setPosition(ccp(50+pSlider->getContentSize().width/2, size.height/4));
    this->addChild(pSlider);
    pSlider->addTargetWithActionForControlEvents(this, cccontrol_selector(Recipe31::sliderCallBack), CCControlEventValueChanged);
    
    CCLabelTTF* labelSlider = CCLabelTTF::create("CCControlSlider", "Arial", 20);
    labelSlider->setPosition(ccp(50+labelSlider->getContentSize().width/2,
                                 pSlider->getPositionY()+pSlider->getContentSize().height/2+labelSlider->getContentSize().height));
    this->addChild(labelSlider);
    
    // stepper
    CCSprite* minusSprite = CCSprite::create("stepper-minus.png");
    CCSprite* plusSprite  = CCSprite::create("stepper-plus.png");
    CCControlStepper* pStepper = CCControlStepper::create(minusSprite, plusSprite);
    pStepper->setMinimumValue(0.0f);
    pStepper->setMaximumValue(10.0f);
    pStepper->setValue(5.0f);
    pStepper->setPosition(ccp(50+pStepper->getContentSize().width/2, size.height/2)); //-pStepper->getContentSize().height/2));
    this->addChild(pStepper);
    pStepper->addTargetWithActionForControlEvents(this, cccontrol_selector(Recipe31::stepperCallBack), CCControlEventValueChanged);
    
    CCLabelTTF* labelStepper = CCLabelTTF::create("CCControlStepper", "Arial", 20);
    labelStepper->setPosition(ccp(50+labelStepper->getContentSize().width/2,
                                  pStepper->getPositionY()+pStepper->getContentSize().height/2+labelStepper->getContentSize().height));
    this->addChild(labelStepper);
    
    
    // potentiometer
    CCLabelTTF* labelMeter = CCLabelTTF::create("CCControlPotentiometer", "Arial", 20);
    labelMeter->setPosition(ccp(size.width-labelMeter->getContentSize().width/2,
                                labelSwitch->getPositionY()));
    CCControlPotentiometer* pMeter = CCControlPotentiometer::create("potentiometerTrack.png", "potentiometerProgress.png", "potentiometerButton.png");
    pMeter->setPosition(ccp(400 - pMeter->getContentSize().width, labelMeter->getPositionY()-pMeter->getContentSize().height/2-labelMeter->getContentSize().height/2));
    this->addChild(pMeter);
    pMeter->addTargetWithActionForControlEvents(this, cccontrol_selector(Recipe31::potentiometerCallBack), CCControlEventValueChanged);
    
    
    this->addChild(labelMeter);
    
    // color picker
    CCLabelTTF* labelColor = CCLabelTTF::create("CCControlColourPicker", "Arial", 20);
    labelColor->setPosition(ccp(labelMeter->getPositionX(),
                                labelColor->getContentSize().height));
    this->addChild(labelColor);
    
    CCControlColourPicker *colorPicker = CCControlColourPicker::create();
    colorPicker->setColor(ccc3(37, 46, 252));
    colorPicker->setPosition(ccp(size.width-colorPicker->getContentSize().width/2,
                                 labelColor->getPositionY()+labelColor->getContentSize().height/2+colorPicker->getContentSize().height/2));
    this->addChild(colorPicker);
    colorPicker->addTargetWithActionForControlEvents(this, cccontrol_selector(Recipe31::colorCallBack), CCControlEventValueChanged);
    
    
    
    return true;
}

void Recipe31::switchCallBack(CCObject* pSender, CCControlEvent controlEvent)
{
    CCControlSwitch* pSwitch = (CCControlSwitch*)pSender;
    if (pSwitch->isOn()) {
        CCLOG("value = ON");
    } else {
        CCLOG("value = OFF");
    }
}

void Recipe31::sliderCallBack(CCObject* pSender, CCControlEvent controlEvent)
{
    CCControlSlider* pSlider = (CCControlSlider*)pSender;
    CCLOG("slider value = %f", pSlider->getValue());
}

void Recipe31::stepperCallBack(CCObject* pSender, CCControlEvent controlEvent)
{
    CCControlStepper* pStepper = (CCControlStepper*)pSender;
    CCLOG("stepper value = %f", pStepper->getValue());
}

void Recipe31::colorCallBack(CCObject* pSender, CCControlEvent controlEvent)
{
    CCControlColourPicker* pColor = (CCControlColourPicker*)pSender;
    CCLOG("color value = #%02X%02X%02X",pColor->getColor().r, pColor->getColor().g, pColor->getColor().b);
}

void Recipe31::potentiometerCallBack(CCObject* pSender, CCControlEvent controlEvent)
{
    CCControlPotentiometer* pMeter = (CCControlPotentiometer*)pSender;
    CCLOG("potentiometer value = %f", pMeter->getValue());
}