//
//  GB2ShapeCache-x.cpp
//  
//  Loads physics sprites created with http://www.PhysicsEditor.de
//  To be used with cocos2d-x
//
//  Generic Shape Cache for box2d
//
//  Created by Thomas Broquist
//
//      http://www.PhysicsEditor.de
//      http://texturepacker.com
//      http://www.code-and-web.de
//  
//  All rights reserved.
//
//  Permission is hereby granted, free of charge, to any person obtaining a copy
//  of this software and associated documentation files (the "Software"), to deal
//  in the Software without restriction, including without limitation the rights
//  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
//  copies of the Software, and to permit persons to whom the Software is
//  furnished to do so, subject to the following conditions:
//  
//  The above copyright notice and this permission notice shall be included in
//  all copies or substantial portions of the Software.
//  
//  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
//  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
//  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
//  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
//  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
//  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
//  THE SOFTWARE.
//

#include "GB2ShapeCache-x.h"
#include "Box2D.h"
#include "cocoa/CCNS.h"

USING_NS_CC;

/**
 * Internal class to hold the fixtures
 */
class FixtureDef {
public:
    FixtureDef()
    : next(NULL) {}
    
    ~FixtureDef() {
        delete next;
        delete fixture.shape;
    }
    
    FixtureDef *next;
    b2FixtureDef fixture;
    int callbackData;
};

class BodyDef {
public:
  BodyDef()
	: fixtures(NULL) {}
	
	~BodyDef() {
		if (fixtures)
			delete fixtures;
	}
	
	FixtureDef *fixtures;
	CCPoint anchorPoint;
};

static GB2ShapeCache *_sharedGB2ShapeCache = NULL;

GB2ShapeCache* GB2ShapeCache::sharedGB2ShapeCache(void) {
	if (!_sharedGB2ShapeCache) {
		_sharedGB2ShapeCache = new GB2ShapeCache();
        _sharedGB2ShapeCache->init();
	}
	
	return _sharedGB2ShapeCache;
}

bool GB2ShapeCache::init() {
	return true;
}

void GB2ShapeCache::reset() {
	std::map<std::string, BodyDef *>::iterator iter;
	for (iter = shapeObjects.begin() ; iter != shapeObjects.end() ; ++iter) {
		delete iter->second;
	}
	shapeObjects.clear();
}

void GB2ShapeCache::addFixturesToBody(b2Body *body, const std::string &shape) {
	std::map<std::string, BodyDef *>::iterator pos = shapeObjects.find(shape);
	assert(pos != shapeObjects.end());
	
	BodyDef *so = (*pos).second;

	FixtureDef *fix = so->fixtures;
    while (fix) {
        body->CreateFixture(&fix->fixture);
        fix = fix->next;
    }
}

cocos2d::CCPoint GB2ShapeCache::anchorPointForShape(const std::string &shape) {
	std::map<std::string, BodyDef *>::iterator pos = shapeObjects.find(shape);
	assert(pos != shapeObjects.end());
	
	BodyDef *bd = (*pos).second;
	return bd->anchorPoint;
}

//typedef CCDictionary<std::string, CCObject*> ObjectDict;
typedef CCDictionary ObjectDict;

void GB2ShapeCache::addShapesWithFile(const std::string &plist) {
	const char *fullName = CCFileUtils::sharedFileUtils()->fullPathForFilename(plist.c_str()).c_str();
	//const char *fullName = CCFileUtils::sharedFileUtils()->fullPathFromRelativePath(plist.c_str());
	ObjectDict *dict = CCDictionary::createWithContentsOfFile(fullName);
	CCAssert(dict != NULL, "Shape-file not found"); // not triggered - cocos2dx delivers empty dict if non was found
    CCAssert(dict->count() != 0, "plist file empty or not existing");
	
	ObjectDict *metadataDict = (ObjectDict *)dict->objectForKey("metadata");
    int format = atoi(static_cast<CCString *>(metadataDict->objectForKey("format"))->getCString());
    ptmRatio = atof(static_cast<CCString *>(metadataDict->objectForKey("ptm_ratio"))->getCString());
	CCAssert(format == 1, "Format not supported");

	ObjectDict *bodyDict = (ObjectDict *)dict->objectForKey("bodies");
    CCLOG("%d", bodyDict->count());
    
    b2Vec2 vertices[b2_maxPolygonVertices];

	std::string bodyName;
    ObjectDict *bodyData;
    CCDictElement *pElement = NULL;
    CCDICT_FOREACH(bodyDict, pElement)
    {
        bodyName = pElement->getStrKey();
        bodyData = (ObjectDict *)pElement->getObject();

        CCLOG("%d", bodyData->count());
        
        CCString *anchorPoint = static_cast<CCString *>(bodyData->objectForKey("anchorpoint"));
		BodyDef *bodyDef = new BodyDef();
		bodyDef->anchorPoint = CCPointFromString(anchorPoint->getCString());
		
		CCArray *fixtureList = (CCArray *)(bodyData->objectForKey("fixtures"));
        FixtureDef **nextFixtureDef = &(bodyDef->fixtures);

        CCObject *pElement = NULL;
        CCARRAY_FOREACH(fixtureList, pElement)
        {
            b2FixtureDef basicData;
            ObjectDict *fixtureData = (ObjectDict *)pElement;
			
            basicData.filter.categoryBits = atoi(static_cast<CCString *>(fixtureData->objectForKey("filter_categoryBits"))->getCString());
            basicData.filter.maskBits = atoi(static_cast<CCString *>(fixtureData->objectForKey("filter_maskBits"))->getCString());
            basicData.filter.groupIndex = atoi(static_cast<CCString *>(fixtureData->objectForKey("filter_groupIndex"))->getCString());
            basicData.friction = atof(static_cast<CCString *>(fixtureData->objectForKey("friction"))->getCString());
            basicData.density = atof(static_cast<CCString *>(fixtureData->objectForKey("density"))->getCString());
            basicData.restitution = atof(static_cast<CCString *>(fixtureData->objectForKey("restitution"))->getCString());
            basicData.isSensor = (bool)(atoi(static_cast<CCString *>(fixtureData->objectForKey("isSensor"))->getCString()));

			CCString *cb = static_cast<CCString *>(fixtureData->objectForKey("userdataCbValue"));
			
            int callbackData = 0;
			
			if (cb)
				callbackData = atoi(cb->getCString());
            
			std::string fixtureType = static_cast<CCString *>(fixtureData->objectForKey("fixture_type"))->getCString();
			
			if (fixtureType == "POLYGON") {
				CCArray *polygonsArray = (CCArray *)(fixtureData->objectForKey("polygons"));

                CCObject *pElement = NULL;
                CCARRAY_FOREACH(polygonsArray, pElement)
                {
                    FixtureDef *fix = new FixtureDef();
                    fix->fixture = basicData; // copy basic data
                    fix->callbackData = callbackData;
					
                    b2PolygonShape *polyshape = new b2PolygonShape();
                    int vindex = 0;
                    
					CCArray *polygonArray = (CCArray *)pElement;

                    assert(polygonArray->count() <= b2_maxPolygonVertices);

                    CCObject *pElement = NULL;
                    CCARRAY_FOREACH(polygonArray, pElement)
                    {
                        CCString *str = (CCString *)pElement;
                        CCPoint offset = CCPointFromString(str->getCString());
                        vertices[vindex].x = (offset.x / ptmRatio) ; 
                        vertices[vindex].y = (offset.y / ptmRatio) ; 
                        vindex++;
                    }
                    
                    polyshape->Set(vertices, vindex);
                    fix->fixture.shape = polyshape;
                    
                    // create a list
                    *nextFixtureDef = fix;
                    nextFixtureDef = &(fix->next);
				}
				
			} else if (fixtureType == "CIRCLE") {
				FixtureDef *fix = new FixtureDef();
                fix->fixture = basicData; // copy basic data
                fix->callbackData = callbackData;
                
                ObjectDict *circleData = (ObjectDict *)fixtureData->objectForKey("circle");
                
                b2CircleShape *circleShape = new b2CircleShape();
				
                circleShape->m_radius = atof(static_cast<CCString *>(circleData->objectForKey("radius"))->getCString()) / ptmRatio;
				CCPoint p = CCPointFromString(static_cast<CCString *>(circleData->objectForKey("position"))->getCString());
                circleShape->m_p = b2Vec2(p.x / ptmRatio, p.y / ptmRatio);
                fix->fixture.shape = circleShape;
				
                // create a list
                *nextFixtureDef = fix;
                nextFixtureDef = &(fix->next);

			} else {
				CCAssert(0, "Unknown fixtureType");
			}
			
			// add the body element to the hash
			shapeObjects[bodyName] = bodyDef;
		}
	}
}