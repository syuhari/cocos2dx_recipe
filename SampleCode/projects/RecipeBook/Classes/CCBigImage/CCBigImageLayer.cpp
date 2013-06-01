//
//  CCBigImageLayer.cpp
//
//  Created by Akihiro Matsuura on 12/09/27.
//
//

#include "CCBigImageLayer.h"

#define MIN_SCALE 0.3
#define INIT_SCALE 0.5

#define BOUNCE_SCALE 0.03           // バウンススケール（最小スケールからさらにどれだけ小さくするか）
#define BOUNCE_SLIDE 0.05            // バウンススライド（上下左右にどれだけバウンスするか）
#define BOUNCE_SPEED 0.7            // バウンスして戻る時間（秒で指定）
#define MAX_SCALE 2.0f              // マップの最大拡大率
// マップスクロール
#define MAP_SLIDE_MOVE_SPEED 1.0
#define MAP_SLIDE_SCROLL_SPEED 1.0
#define MAP_SLIDE_PIX_PER_SEC 1000.0f

using namespace cocos2d;

enum nodeTags {
	kBigNode,
};

bool CCBigImageLayer::init() {
    if (CCLayer::init() ) {
        this->setTouchEnabled(true);
        this->setDelegate(NULL);
        CCDirector::sharedDirector()->getTouchDispatcher()->setDispatchEvents(true);
        
        return true;
    } else {
        return false;
    }
}

void CCBigImageLayer::loadBigImage(string plist) {
    // Create DynamicTiledNode with screen bounds additional preload zone size
    CCBigImage *node = CCBigImage::nodeWithTilesFileTilesExtensionTilesZ(plist, "", 0);
    
    // size of bigImage.png in points
    this->setContentSize(node->getContentSize());
    
    // calc min scale
    float w_scale = CCDirector::sharedDirector()->getWinSize().width / node->getContentSize().width;
    float h_scale = CCDirector::sharedDirector()->getWinSize().height / node->getContentSize().height;
    min_scale = MAX(w_scale, h_scale);
    min_scale = MAX(min_scale, MIN_SCALE);
    
    max_scale = this->getMapMaxScale();
    
    // Add node as child.
    node->setScale(MIN(INIT_SCALE, min_scale));
    this->addChild(node, 0, kBigNode);
    
    this->updateForScreenReshape();
}

CCBigImage* CCBigImageLayer::getBigImage() {
	CCBigImage *node = (CCBigImage*)this->getChildByTag(kBigNode);
    return node;
}


CCBigImageLayer::~CCBigImageLayer() {
    if (delegate) {
        delegate = NULL;
    }
}

void CCBigImageLayer::updateForScreenReshape()
{
	CCSize s = CCDirector::sharedDirector()->getWinSize();
	CCNode *node = this->getChildByTag(kBigNode);
	node->setAnchorPoint(ccp(0.5f, 0.5f));
	node->setPosition(ccp(0.5f * s.width, 0.5f * s.height));
}


#pragma mark Scrolling

void CCBigImageLayer::ccTouchesBegan(CCSet* touches, CCEvent* event) {
    isPinch = false;
    if (touches->count() == 2) {
        isPinch = true;
		// Get points of both touches
        CCSetIterator it = touches->begin();
        CCTouch* tOne = (CCTouch*)(*it);
        CCTouch* tTwo = (CCTouch*)(*++it);
        CCPoint firstTouch = tOne->getLocationInView();
		CCPoint secondTouch = tTwo->getLocationInView();
        
		// Find the distance between those two points
		initialDistance = sqrt(pow(firstTouch.x - secondTouch.x, 2.0f) + pow(firstTouch.y - secondTouch.y, 2.0f));
	} else {
        CCTouch* touch = (CCTouch*)touches->anyObject();
        startPoint = touch->getLocationInView();
        CCTime::gettimeofdayCocos2d(&beginTime, NULL);
    }
    
    if (delegate) {
        delegate->onTouched(this);
    }
}

void CCBigImageLayer::ccTouchesMoved(CCSet* touches, CCEvent* event) {
    CCBigImage* node = (CCBigImage*)this->getChildByTag(kBigNode);

    if (touches->count()==1) {
        CCTouch* touch = (CCTouch*)touches->anyObject();
        
        CCSize winSize = CCDirector::sharedDirector()->getWinSize();
        CCRect boundaryRect = CCRectMake(0, 0, winSize.width, winSize.height);
        
        // scrolling is allowed only with non-zero boundaryRect
        if (boundaryRect.size.width>0 && boundaryRect.size.height>0)
        {
            // get touch move delta
            CCPoint point = touch->getLocation();
            CCPoint prevPoint = touch->getPreviousLocation();
            
            CCPoint delta = ccpSub(point, prevPoint);
            CCPoint newPosition = ccpAdd(node->getPosition(), delta);
            
            CCSize size = node->getContentSize();
            size.width *= node->getScale();
            size.height *= node->getScale();
            
            float bounce_x = winSize.width * BOUNCE_SLIDE;
            float bounce_y = winSize.height* BOUNCE_SLIDE;
            
            isBounce = false;
            if (newPosition.x+size.width/2 < winSize.width-bounce_x) {
                newPosition.x = winSize.width - size.width/2 - bounce_x;
                isBounce = true;
            } else if (newPosition.x-size.width/2 > 0.0f+bounce_x) {
                newPosition.x = size.width/2 + bounce_x;
                isBounce = true;
            }
            
            if (newPosition.y+size.height/2 < winSize.height-bounce_y) {
                newPosition.y = winSize.height - size.height/2 - bounce_y;
                isBounce = true;
            } else if (newPosition.y-size.height/2 > 0.0f+bounce_y) {
                newPosition.y = size.height/2 + bounce_y;
                isBounce = true;
            }
            
            node->setPosition(newPosition);
        }
    }
    else if (touches->count() == 2) {
        isPinch = true;
        CCSetIterator it = touches->begin();
        CCTouch* tOne = (CCTouch*)(*it);
        CCTouch* tTwo = (CCTouch*)(*++it);
        CCPoint firstTouch = tOne->getLocationInView();
		CCPoint secondTouch = tTwo->getLocationInView();
		float currentDistance = sqrt(pow(firstTouch.x - secondTouch.x, 2.0f) + pow(firstTouch.y - secondTouch.y, 2.0f));
        
        float zoomFactor = node->getScale();
        float prevScale = node->getScale();

		if (initialDistance == 0) {
			initialDistance = currentDistance;
            // set to 0 in case the two touches weren't at the same time
		} else if (currentDistance - initialDistance > 0) {
			// zoom in
			if (node->getScale() < max_scale) {
				zoomFactor += zoomFactor *0.05f;
                if (zoomFactor>max_scale) {
                    zoomFactor = max_scale;
                }
				node->setScale(zoomFactor);
			}
            
			initialDistance = currentDistance;
		} else if (currentDistance - initialDistance < 0) {
			// zoom out
			if (node->getScale() > min_scale-BOUNCE_SCALE) {
				zoomFactor -= zoomFactor *0.05f;
                if (zoomFactor<min_scale-BOUNCE_SCALE) {
                    zoomFactor = min_scale-BOUNCE_SCALE;
                }
				node->setScale(zoomFactor);
			}
            
			initialDistance = currentDistance;
        }
        
        // update center position
        firstTouch =  CCDirector::sharedDirector()->convertToGL(firstTouch);
        secondTouch =  CCDirector::sharedDirector()->convertToGL(secondTouch);
        CCPoint curPosLayer = ccpMidpoint(firstTouch, secondTouch);

        if (node->getScale() != prevScale)
        {
            CCPoint realCurPosLayer = node->convertToNodeSpace(curPosLayer);
            float deltaX = (realCurPosLayer.x - node->getAnchorPoint().x * node->getContentSize().width) * (node->getScale() - prevScale);
            float deltaY = (realCurPosLayer.y - node->getAnchorPoint().y * node->getContentSize().height)* (node->getScale() - prevScale);
            node->setPosition(ccp(node->getPositionX() - deltaX, node->getPositionY() - deltaY));
        }
	}
}

float CCBigImageLayer::getMapMaxScale() {
    return MAX_SCALE;
}

void CCBigImageLayer::ccTouchesEnded(CCSet* touches, CCEvent* event) {
    CCBigImage* node = (CCBigImage*)this->getChildByTag(kBigNode);
    
    if (!isPinch) {
        CCTouch* touch = (CCTouch*)touches->anyObject();
        CCPoint touchLocation = touch->getLocationInView();

		cc_timeval endTime;
		CCTime::gettimeofdayCocos2d(&endTime, NULL);
		float delta = ccpDistance(touchLocation, startPoint);
        float microSeconds = CCTime::timersubCocos2d(&beginTime, &endTime);
		float speed = delta/(microSeconds);
		if (speed >= MAP_SLIDE_MOVE_SPEED) { //速度
			CCPoint deltaPos = ccpSub(touchLocation, startPoint);
            
            CCSize winSize = CCDirector::sharedDirector()->getWinSize();
            CCSize size = node->getContentSize();
            size.width *= node->getScale();
            size.height *= node->getScale();
            CCPoint fixPoint = node->getPosition();
            fixPoint.x += deltaPos.x * MAP_SLIDE_SCROLL_SPEED;
            fixPoint.y -= deltaPos.y * MAP_SLIDE_SCROLL_SPEED;
            
            float bounce_x = winSize.width * BOUNCE_SLIDE;
            float bounce_y = winSize.height* BOUNCE_SLIDE;
            
            if (fixPoint.x+size.width/2 < winSize.width-bounce_x) {
                fixPoint.x = winSize.width - size.width/2 - bounce_x;
            } else if (fixPoint.x-size.width/2 > 0.0f+bounce_x) {
                fixPoint.x = size.width/2 + bounce_x;
            }
            
            if (fixPoint.y+size.height/2 < winSize.height-bounce_y) {
                fixPoint.y = winSize.height - size.height/2 - bounce_y;
            } else if (fixPoint.y-size.height/2 > 0.0f+bounce_y) {
                fixPoint.y = size.height/2 + bounce_y;
            }
            
            node->stopAllActions();
            
            float diff = ccpDistance(node->getPosition(), fixPoint);
            float duration = diff/MAP_SLIDE_PIX_PER_SEC;
            
            CCCallFunc* func = CCCallFunc::create(this, callfunc_selector(CCBigImageLayer::fixPosition));
            CCEaseOut* fadeOut = CCEaseOut::create(CCMoveTo::create(duration, fixPoint),3);
            node->runAction(CCSequence::create(fadeOut, func, NULL));
		}else {
            this->fixPosition();
		}
    } else {
        this->fixPosition();
    }
}

void CCBigImageLayer::ccTouchesCancelled(CCSet* touches, CCEvent* event) {
    this->fixPosition();
}

void CCBigImageLayer::fixPosition()
{
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    CCRect boundaryRect = CCRectMake(0, 0, winSize.width, winSize.height);
	
    if (boundaryRect.size.width<=0 && boundaryRect.size.height<=0) {
		return;
    }
    
    CCBigImage* node = (CCBigImage*)this->getChildByTag(kBigNode);
    CCSize size = node->getContentSize();
    size.width *= node->getScale();
    size.height *= node->getScale();
    CCPoint fixPoint = node->getPosition();
    
    if (node->getPositionX()+size.width/2 < winSize.width) {
        fixPoint.x = winSize.width - size.width/2;
    } else if (node->getPositionX()-size.width/2 > 0.0f) {
        fixPoint.x = size.width/2;
    }
    
    if (node->getPositionY()+size.height/2 < winSize.height) {
        fixPoint.y = winSize.height - size.height/2;
    } else if (node->getPositionY()-size.height/2 > 0.0f) {
        fixPoint.y = size.height/2;
    }

    
    if (node->getScale() < min_scale) {
        node->stopAllActions();
        CCScaleTo* scale = CCScaleTo::create(BOUNCE_SPEED, min_scale);
        CCMoveTo* move = CCMoveTo::create(BOUNCE_SPEED, ccp(winSize.width/2, winSize.height/2));
        CCEaseOut* bounce = CCEaseOut::create(move,3);
        node->runAction(CCSpawn::create(scale, bounce, NULL));
    } else if (fixPoint.x!=node->getPositionX() || fixPoint.y!=node->getPositionY()) {
        CCMoveTo* move = CCMoveTo::create(BOUNCE_SPEED, fixPoint);
        CCEaseOut* bounce = CCEaseOut::create(move,3);
        node->runAction(bounce);
    }
}

void CCBigImageLayer::stopBigImage() {
    CCBigImage* node = (CCBigImage*)this->getChildByTag(kBigNode);
    node->stopTilesLoadingThread();
}