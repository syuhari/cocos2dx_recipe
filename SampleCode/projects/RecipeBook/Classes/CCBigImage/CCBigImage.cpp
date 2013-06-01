//
//  CCBigImage.cpp
//
//  Created by Akihiro Matsuura on 12/09/27.
//
//

#include "CCBigImage.h"
#include "platform/CCThread.h"
#include "cocoa/CCNS.h"

UnloadableSpriteNode* UnloadableSpriteNode::nodeWithImageForRect(string anImage, CCRect aRect)
{
    UnloadableSpriteNode* pRet = new UnloadableSpriteNode();
    if (pRet->initWithImageForRect(anImage, aRect))
    {
        pRet->autorelease();
        return pRet;
    }
    CC_SAFE_DELETE(pRet);
    return NULL;
}

bool UnloadableSpriteNode::initWithImageForRect(string anImage, CCRect aRect)
{
    drawing = false;
    loading = false;
    _imageName = anImage;
    _activeRect = aRect;
    setAnchorPoint(ccp(0,0));
    setPosition(aRect.origin);
	return true;
}

#pragma mark CocosNode


// small visit for only one sprite
void UnloadableSpriteNode::visit()
{
	// quick return if not visible
	if (!this->isVisible()) return;
	
    if (!this->_sprite) return;
    
    drawing = true;
    kmGLPushMatrix();
	
    this->transform();
    if (this->_sprite!=NULL) {
        this->_sprite->visit();
	}
    kmGLPopMatrix();
    drawing = false;
}

CCRect UnloadableSpriteNode::boundingBox()
{
	return _activeRect;
}

UnloadableSpriteNode::~UnloadableSpriteNode()
{
	if (this->_sprite) {
        while (drawing) {
            // 描画中のためウェイト
            usleep(30*1000);
        }
        this->_sprite->release();
        this->_sprite = NULL;
    }
}

#pragma mark Load/Unload

void UnloadableSpriteNode::loadedTexture(CCObject* obj)
{
    CCTexture2D* aTex = (CCTexture2D*)obj;
    if (aTex==NULL || aTex->retainCount()<=0) {
        loading = false;
        return;
    }
	aTex->setAntiAliasTexParameters();
	
	//create sprite, position it and at to self
    drawing = true;
    
    this->_sprite = new CCSprite;
    this->_sprite->initWithTexture(aTex);

	this->_sprite->setAnchorPoint(ccp(0,0));
	this->_sprite->setPosition(ccp(0,0));
    
	// fill our activeRect fully with sprite (stretch if needed)
	this->_sprite->setScaleX(this->_activeRect.size.width / this->_sprite->getContentSize().width);
	this->_sprite->setScaleY(this->_activeRect.size.height / this->_sprite->getContentSize().height);
    
    loading = false;
    drawing = false;
}

void UnloadableSpriteNode::unload()
{
    if (this->_sprite) {
        while (drawing) {
            // 描画中のためウェイト
            usleep(30*1000);
        }
        this->_sprite->release();
        this->_sprite = NULL;
    }
}


void UnloadableSpriteNode::load(CCTextureCache* textureCache)
{
	if (this->_sprite || loading) {
		return; //< already loaded or now loading
	}
    
    // load image in other thread
    loading = true;
    textureCache->addImageAsync(_imageName.c_str(), this, callfuncO_selector(UnloadableSpriteNode::loadedTexture));
}

void CCBigImage::setPosition(const CCPoint &newPosition)
{
	float significantPositionDelta = MIN(this->_screenLoadRectExtension.width,
										   this->_screenLoadRectExtension.height) / 2.0f;
	
	if ( ccpLength(ccpSub(newPosition, this->getPosition())) > significantPositionDelta ) {
		this->_significantPositionChange = true;
    }
    
    CCNode::setPosition(newPosition);
}

#pragma mark Init / Creation

CCBigImage* CCBigImage::nodeWithTilesFileTilesExtensionTilesZ(string filename, string extension, int tilesZ)
{
    CCBigImage* pRet = new CCBigImage();
    if (pRet->initWithTilesFileTilesExtensionTilesZ(filename, extension, tilesZ))
    {
        pRet->autorelease();
        return pRet;
    }
    CC_SAFE_DELETE(pRet);
    return NULL;
}

// designated initializer
bool CCBigImage::initWithTilesFileTilesExtensionTilesZ(string filename, string extension, int tilesZ)
{
    CCDirector::sharedDirector()->setDepthTest(false);

    _loadedRect = CCRectZero;
    _screenLoadRectExtension = CCSizeZero;
    _textureCache = CCTextureCache::sharedTextureCache();
    _allStop = false;
    drawing = false;
    
    string path = CCFileUtils::sharedFileUtils()->fullPathForFilename(filename.c_str());
    this->prepareTilesWithFileExtensionZ(path , extension, tilesZ);
	
	return true;
}

// loads info about all tiles,sets self.contentSize & screenLoadRectExtension
// creates & adds tiles for dynamic usage if batchNode
void CCBigImage::prepareTilesWithFileExtensionZ(string plistFile, string extension, int tilesZ)
{
	// load plist with image & tiles info
    CCDictionary *dict = CCDictionary::createWithContentsOfFile(plistFile.c_str());
    if ( !dict )
    {
        CCLOGERROR("CCBigImage#prepareTilesWithFile:extension:z: can not load dictionary from file: %s", plistFile.c_str());
        return;
    }
	
	// load image size
    CCDictionary *sourceDict = (CCDictionary*)dict->objectForKey(std::string("Source"));
    CCSize size = CCSizeFromString(valueForKey("Size", sourceDict));
    
    this->setContentSize(size);
	
	// load tiles
    CCArray* array = (CCArray*)dict->objectForKey(std::string("Tiles"));
	
	_dynamicChildren = CCArray::createWithCapacity(array->count());
    _dynamicChildren->retain();
    
	// set screenLoadRectExtension = size of first tile
	if (array->count())
	{
        CCDictionary *dict_ = (CCDictionary*)array->objectAtIndex(0);
        _screenLoadRectExtension = CCRectFromString(valueForKey("Rect", dict_)).size;
	}
	
	//read data and create nodes and add them
    for (int i=0; i<array->count(); i++)
    {
        CCDictionary* tileDict = (CCDictionary*)array->objectAtIndex(i);

        // All properties of Dictionary
        const char *spriteName = valueForKey("Name", tileDict);
		
		CCRect tileRect = CCRectFromString(valueForKey("Rect", tileDict));
        
		// convert rect origin from top-left to bottom-left
		tileRect.origin.y = this->getContentSize().height - tileRect.origin.y - tileRect.size.height;
		
		// Use forced tile extension or original if tilesExtension isn't set
		if (!extension.empty())
		{
			// Change extension
            string filename = string(spriteName);
            int index = filename.find('.');
            string name = filename.substr(0, index);
			spriteName = (name+"."+extension).c_str();
		}

		// Create & Add Tile (Dynamic Sprite Mode)
		UnloadableSpriteNode* tile = UnloadableSpriteNode::nodeWithImageForRect(spriteName, tileRect);
		this->addChild(tile, tilesZ);
		_dynamicChildren->addObject(tile);
		
    } //< for dict in arr
    
    dict->release();
	
}

CCBigImage::~CCBigImage()
{
    //this->stopTilesLoadingThread();
    while (drawing) {
        // 描画中のためウェイト
        usleep(30*1000);
    }
    
    CCSpriteFrameCache::sharedSpriteFrameCache()->removeUnusedSpriteFrames();
    _textureCache->removeUnusedTextures();
    
    _dynamicChildren->release();
	_dynamicChildren = NULL;
}


#pragma mark CCNode LifeCycle

void CCBigImage::onEnter()
{
    CCNode::onEnter();
	this->startTilesLoadingThread();
}

void CCBigImage::onExit()
{
	// turn off dynamic thread
	this->stopTilesLoadingThread();
    
    CCNode::onExit();
}

void CCBigImage::visit()
{
    if (_tilesLoadThreadCancel) return;
	this->updateLoadRect();
	
    drawing = true;
	CCNode::visit();
	drawing = false;
    
	// remove unused textures periodically
    static int i = CCBIGIMAGE_TEXTURE_UNLOAD_PERIOD;
    if (--i <= 0) {
        i = CCBIGIMAGE_TEXTURE_UNLOAD_PERIOD;
        if (_tilesLoadThreadIsSleeping) {
            _textureCache->removeUnusedTextures();
        }
    }
}

#if CC_BIGIMAGE_DEBUG_DRAW
void CCBigImage::draw()
{
    CCNode::draw();
	
	CCSize s = this->getContentSize();
	CCPoint vertices[4]={
		ccp(0,0),ccp(s.width,0),
		ccp(s.width,s.height),ccp(0,s.height),
	};
	ccDrawPoly(vertices, 4, true);
}
#endif


#pragma mark Dynamic Tiles Stuff

void CCBigImage::startTilesLoadingThread()
{
	// do nothing if thread exist
	if (this->_tilesLoadThread || _allStop) {
		return;
	}
    
	// create new thread if it doesn't exist
    _tilesLoadThreadCancel = false;
    pthread_create(&_tilesLoadThread, NULL, &CCBigImage::updateTilesInThread, this);
    pthread_detach(_tilesLoadThread);
    
	_tilesLoadThreadIsSleeping = false;
}

void CCBigImage::stopTilesLoadingThread()
{
    _tilesLoadThreadCancel = true;
    _allStop = true;
	_tilesLoadThread = NULL;
}

void CCBigImage::updateLoadRect()
{
	// get screen rect
	CCRect screenRect = CCRectZero;
	screenRect.size = CCDirector::sharedDirector()->getWinSize();

	screenRect = CCRectApplyAffineTransform(screenRect, this->worldToNodeTransform());
    
	// get level's must-be-loaded-part rect
	_loadedRect = CCRectMake(screenRect.origin.x - _screenLoadRectExtension.width,
							 screenRect.origin.y - _screenLoadRectExtension.height,
							 screenRect.size.width + 3.0f * _screenLoadRectExtension.width,
							 screenRect.size.height + 3.0f * _screenLoadRectExtension.height);
	
	// avoid tiles blinking
	if (_significantPositionChange)
	{
		this->updateTiles();
		_significantPositionChange = false;
	}
}


// new update tiles for threaded use
void *CCBigImage::updateTilesInThread(void *ptr)
{
    CCThread thread;
    thread.createAutoreleasePool();
    
    CCBigImage* bigImage = (CCBigImage*)ptr;
    
	while(!bigImage->_tilesLoadThreadCancel)
	{
        CCThread thread;
        thread.createAutoreleasePool();
        
		// flag for removeUnusedTextures only when sleeping - to disable deadLocks
		bigImage->_tilesLoadThreadIsSleeping = false;
		
        if (bigImage->_tilesLoadThreadCancel) return NULL;
        if (bigImage->_dynamicChildren==NULL) return NULL;
        int count = bigImage->_dynamicChildren->count();
		for (int i=0; i<count; i++)
        {
            if (bigImage->_tilesLoadThreadCancel || bigImage->_dynamicChildren==NULL) break;
            UnloadableSpriteNode *child = (UnloadableSpriteNode*)(bigImage->_dynamicChildren->objectAtIndex(i));
			if (!child->boundingBox().intersectsRect(bigImage->_loadedRect)) {
				child->unload();
            } else {
				child->load(bigImage->_textureCache);;
            } //< 0 == size.width must be faster than CGRectIsEmpty
		}
        
		// flag removeUnusedTextures only when sleeping - to disable deadLocks
		bigImage->_tilesLoadThreadIsSleeping = true;
		
		// 60 FPS run, update at 30 fps should be ok
        usleep(30*1000);
	}
    
    return NULL;
}

void CCBigImage::updateTiles()
{
	//load loadedRect tiles and unload tiles that are not in loadedRect
    for (int i=0; i<_dynamicChildren->count(); i++)
    {
        UnloadableSpriteNode *child = (UnloadableSpriteNode*)_dynamicChildren->objectAtIndex(i);
		if (!_loadedRect.intersectsRect(child->boundingBox())) {
			child->unload();
		} else {
			child->load(_textureCache);
        }
        //< 0 == size.width must be faster than CGRectIsEmpty
    }
}
