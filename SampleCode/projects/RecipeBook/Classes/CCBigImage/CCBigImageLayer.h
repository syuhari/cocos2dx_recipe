//
//  CCBigImageLayer.h
//
//  Created by Akihiro Matsuura on 12/09/27.
//
//

#ifndef __CCBigImageLayer__
#define __CCBigImageLayer__

#include "platform/platform.h"
#include "cocos2d.h"
#include "CCBigImage.h"

using namespace cocos2d;

class CCBigImageLayer;

class CCBigImageLayerDelegate {
public:
    virtual void onTouched(CCBigImageLayer* layer){};
};

class CCBigImageLayer : public cocos2d::CCLayer
{
private:
    bool isPinch;
	cc_timeval beginTime;
    CCPoint startPoint;
    float initialDistance;
    void updateForScreenReshape();
    void fixPosition();
    float getMapMaxScale();
public:
    bool isBounce;
    float min_scale;
    float max_scale;
    CC_SYNTHESIZE(int, mapNo, MapNo);
    CC_SYNTHESIZE(CCBigImageLayerDelegate*, delegate, Delegate);
    virtual ~CCBigImageLayer();
    bool init();
    void loadBigImage(string plist);
    CCBigImage* getBigImage();
    virtual void stopBigImage();

    virtual void ccTouchesBegan(CCSet *pTouches, CCEvent *pEvent);
	virtual void ccTouchesMoved(CCSet *pTouches, CCEvent *pEvent);
	virtual void ccTouchesEnded(CCSet *pTouches, CCEvent *pEvent);
	virtual void ccTouchesCancelled(CCSet *pTouches, CCEvent *pEvent);
    
    CREATE_FUNC(CCBigImageLayer);
};

#endif
