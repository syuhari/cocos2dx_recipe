//
//  CCBigImage.h
//
//  Created by Akihiro Matsuura on 12/09/27.
//
//

#ifndef __CCBigImage__
#define __CCBigImage__

#include "cocos2d.h"
using namespace cocos2d;
using namespace std;

// How many times visit should be called to call removeUnusedTexture
#define CCBIGIMAGE_TEXTURE_UNLOAD_PERIOD 30

class CCAsyncObject : CCObject
{
public:
	SEL_CallFunc	selector;
	CCObject*       target;
	string          data;
};

class CCBigImage : public CCNode
{
private:
    bool drawing;
    CCTextureCache* _textureCache;
	// Area within all tiles must be loaded
	CCRect _loadedRect;
	
	// Array of UnloadableSprites that holds image tiles
	CCArray* _dynamicChildren;

	// Dynamic Tiles Loading Mechanism
    pthread_t _tilesLoadThread;
    
	bool _tilesLoadThreadIsSleeping; //< status of loading tiles thread to know when to unload textures
	bool _significantPositionChange; //< if YES - tiles load will be forced
    
    void startTilesLoadingThread();
    
    void prepareTilesWithFileExtensionZ(string plistFile, string extension, int tilesZ);
    void updateLoadRect();
    void updateTiles();
    
    static void *updateTilesInThread(void *ptr);
    bool _tilesLoadThreadCancel;
    bool _allStop;
    
	/** Private method, return the string found by key in dict.
     @return "" if not found; return the string if found.
     */
	inline const char * valueForKey(const char *key, CCDictionary *dict)
	{
		if (dict)
		{
			CCString *pString = (CCString*)dict->objectForKey(std::string(key));
			return pString ? pString->m_sString.c_str() : "";
		}
		return "";
	}
public:
    // How much more tiles we should load beyond the visible area
    /** Returns size that describes in what distance beyond each side of the screen tiles should be loaded
     * to avoid holes when levels scrolls fast.
     * By default it's equal to first tile's size.
     */
	CC_SYNTHESIZE(CCSize, _screenLoadRectExtension, screenLoadRectExtension);
    
    /** Returns new CCBigImage. @see initWithTilesFile:tilesExtension:tilesZ: */
    static CCBigImage* nodeWithTilesFileTilesExtensionTilesZ(string filename, string extension, int tilesZ);
    
    /** Inits CCBigImage. Designated initializer.
     *
     * @param filename plist filename from Tile-Cutter.
     *
     * @param extension file extension, that will be used for all tiles instead of their
     * extensions that are in plist file. Pass nil to kep original extension from plist file.
     *
     * @param tilesZ zOrder, that will be used for all tiles. Usefull when you have
     * other nodes added as children to CCBigImage.
     */
    bool initWithTilesFileTilesExtensionTilesZ(string filename, string extension, int tilesZ);
    
    virtual ~CCBigImage();
    
    virtual void setPosition(const CCPoint &var);
    virtual void onEnter();
    virtual void onExit();
    virtual void visit();
    
    void stopTilesLoadingThread();

#if CC_BIGIMAGE_DEBUG_DRAW
    virtual void draw();
#endif
};


/* Unloadable Sprite - holds one dynamic tile for CCBigImage
 *
 * Limitations: scale, rotation not supported
 */
class UnloadableSpriteNode : public CCNode
{
private:
    bool drawing;
    bool loading;
	// name of texture file for sprite
    string _imageName;
    // position and size of the tile
	CCRect _activeRect;
    
    void loadedTexture(CCObject* obj);
public:
	// sprite used to render content if tile is loaded
    CC_SYNTHESIZE(CCSprite*, _sprite, Sprite);

    static UnloadableSpriteNode* nodeWithImageForRect(string anImage, CCRect aRect);
    bool initWithImageForRect(string anImage, CCRect aRect);
    
    CCRect boundingBox();
    
    void load(CCTextureCache* textureCache);
    void unload();
    virtual ~UnloadableSpriteNode();
    
    virtual void visit();
};

#endif /* defined(__CCBigImage__) */
