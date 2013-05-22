
#include "SSPlayer.h"
#include "SSPlayerData.h"
#include <cstring>
#include <string>

using namespace cocos2d;


/**
 * SSDataHandle
 */

class SSDataHandle
{
public:
	SSDataHandle(const SSData* data)
		: m_data(data)
	{}

	const SSData* getData() const
	{
		return m_data;
	}

	int indexOfPart(const char* partName) const
	{
		for (int i = 0; i < m_data->numParts; i++)
		{
			if (std::strcmp(partName, m_data->partData[i].name) == 0)
			{
				return i;
			}
		}
		return -1;
	}

private:
	const SSData*	m_data;
};



/**
 * SSImageList
 */

SSImageList::SSImageList()
{
}

SSImageList::SSImageList(const char* imageFiles[], const char* imageDir)
{
	init(imageFiles, imageDir);
}

SSImageList::~SSImageList()
{
	clear();
}

void SSImageList::init(const char* imageFiles[], const char* imageDir)
{
	CCAssert(imageFiles != NULL, "zero is imageFiles pointer");

	clear();

	CCTextureCache* texCache = CCTextureCache::sharedTextureCache();
	for (size_t i = 0; imageFiles[i] != 0; i++)
	{
        std::string path;
        if (imageDir) path.append(imageDir);
        path.append(imageFiles[i]);
        
		CCTexture2D* tex = texCache->addImage(path.c_str());
        if (tex == NULL)
        {
            CCLOG("image load failed: %s", path.c_str());
            CC_ASSERT(0);
        }
		m_imageList.addObject(tex);
	}
}

void SSImageList::clear()
{
	CCTextureCache* texCache = CCTextureCache::sharedTextureCache();
	for (size_t i = 0, count = m_imageList.count(); i < count; i++)
	{
		CCTexture2D* tex = static_cast<CCTexture2D*>( m_imageList.objectAtIndex(i) );
		texCache->removeTexture(tex);
	}

	m_imageList.removeAllObjects();
}

CCTexture2D* SSImageList::getTexture(size_t index)
{
	if (index >= m_imageList.count()) return NULL;

	CCTexture2D* tex = static_cast<CCTexture2D*>( m_imageList.objectAtIndex(index) );
	return tex;
}



/**
 * SSPartState
 */

class SSPartState : public cocos2d::CCObject
{
public:
	SSPartState();
	virtual ~SSPartState();

	float getPositionX() const;
	float getPositionY() const;

private:
	friend class SSPlayer;

	float	m_x;
	float	m_y;
};

SSPartState::SSPartState()
	: m_x(0), m_y(0)
{
	this->autorelease();
}

SSPartState::~SSPartState()
{
}

float SSPartState::getPositionX() const
{
	return m_x;
}

float SSPartState::getPositionY() const
{
	return m_y;
}



/**
 * SSPlayer
 */

SSPlayer::SSPlayer(void)
	: m_ssDataHandle(0)
	, m_imageList(0)
{
}

SSPlayer* SSPlayer::create()
{
	SSPlayer* player = new SSPlayer();
	if (player && player->init())
	{
		player->autorelease();
		return player;
	}
	CC_SAFE_DELETE(player);
	return NULL;
}
	
SSPlayer* SSPlayer::create(const SSData* ssData, SSImageList* imageList)
{
	SSPlayer* player = create();
	if (player)
	{
		player->setAnimation(ssData, imageList);
	}
	return player;
}

SSPlayer::~SSPlayer(void)
{
	this->unscheduleUpdate();
	clearAnimation();
	releaseParts();
}

bool SSPlayer::init()
{
    if ( !CCSprite::init() )
    {
        return false;
    }

	return true;
}

void SSPlayer::allocParts(int numParts)
{
	if (m_partStates.count() != numParts)
	{
		// 既存パーツ解放 
		releaseParts();

		// パーツ数だけCCSpriteとSSPartStateを作成する 
		for (int i = 0; i < numParts; i++)
		{
			CCSprite* pSprite = CCSprite::create();
			this->addChild(pSprite);

			SSPartState* state = new SSPartState();
			m_partStates.addObject(state);
		}
	}
}

void SSPlayer::releaseParts()
{
	// パーツの子CCSpriteを全て削除 
	this->removeAllChildrenWithCleanup(true);
	// パーツステートオブジェクトを全て削除 
	m_partStates.removeAllObjects();
}

bool SSPlayer::hasAnimation() const
{
	return m_ssDataHandle != 0;
}

void SSPlayer::clearAnimation()
{
	if (!hasAnimation()) return;

	CC_SAFE_DELETE(m_ssDataHandle);
	m_imageList = 0;
}

/** アニメーションを設定 */
void SSPlayer::setAnimation(const SSData* ssData, SSImageList* imageList)
{
	// パーツアロケート 
	allocParts(ssData->numParts);

	// アニメーションパラメータ初期化 
	clearAnimation();
	m_ssDataHandle = new SSDataHandle(ssData);
	m_imageList = imageList;

	m_playingFrame = 0.0f;
	m_step = 1.0f;
	m_loop = 0;
	m_loopCount = 0;

	setFrame(0);

	this->scheduleUpdate();
}

void SSPlayer::update(float dt)
{
//	CCLOG("%f", dt);

	if (!hasAnimation()) return;

	if (m_loop == 0 || m_loopCount < m_loop)
	{
		// フレームを進める 

		const int numFrames = m_ssDataHandle->getData()->numFrames;

		float s = dt / (1.0f / m_ssDataHandle->getData()->fps);
		m_playingFrame += s * m_step;

		int iPlayingFrame = static_cast<int>(m_playingFrame);
		int c = iPlayingFrame / numFrames;

		if (m_step >= 0)
		{
			// 順再生時
			if (iPlayingFrame >= numFrames)
			{
				m_loopCount += c;
				if (m_loop != 0 && m_loopCount >= m_loop)
				{
					// ループ終了。最終フレームで描画を止める
					m_playingFrame = numFrames - 1;
					// TODO:コールバック
				}
				else
				{
					m_playingFrame = iPlayingFrame % numFrames;
				}
			}
		}
		else
		{
			// 逆再生時
			if (iPlayingFrame < 0)
			{
				m_loopCount += 1 + -c;
				if (m_loop != 0 && m_loopCount >= m_loop)
				{
					// ループ終了。先頭フレームで描画を止める
					m_playingFrame = 0;
					// TODO:コールバック
				}
				else
				{
					m_playingFrame = iPlayingFrame % numFrames;
					if (m_playingFrame < 0.0f)
					{
						m_playingFrame += numFrames;
					}
				}
			}
		}
	}

	setFrame(getFrameNo());
}


int SSPlayer::getFrameNo() const
{
	return static_cast<int>(m_playingFrame);
}

void SSPlayer::setFrameNo(int frameNo)
{
	m_playingFrame = frameNo;
}

/** 再生スピードを取得 */
float SSPlayer::getStep() const
{
	return m_step;
}

/** 再生スピードを設定 1.0f:標準 */
void SSPlayer::setStep(float step)
{
	m_step = step;
}

/** 再生ループ回数の設定を取得 */
int SSPlayer::getLoop() const
{
	return m_loop;
}

/** 再生ループ回数の設定 */
void SSPlayer::setLoop(int loop)
{
	if (loop < 0) return;
	m_loop = loop;
}

/** 現在の再生回数を取得 */
int SSPlayer::getLoopCount() const
{
	return m_loopCount;
}

/** 現在の再生回数をクリア */
void SSPlayer::clearLoopCount()
{
	m_loopCount = 0;
}

/** 
* 指定パーツの情報をPartInfoに格納する 
* 成功時はtrue, パーツが見つからないときはfalseを返す 
*/
bool SSPlayer::getPartState(SSPlayer::PartState& result, const char* name)
{
	if (hasAnimation())
	{
		int index = m_ssDataHandle->indexOfPart(name);
		if (index >= 0 && index < static_cast<int>(m_partStates.count()))
		{
			const SSPartState* partState = static_cast<SSPartState*>( m_partStates.objectAtIndex(index) );
			result.x = partState->getPositionX();
			result.y = partState->getPositionY();
			return true;
		}
	}
	return false;
}


void SSPlayer::setFrame(int frameNo)
{
	setChildVisibleAll(false);

	const SSFrameData* frameData = &m_ssDataHandle->getData()->frameData[frameNo];
	size_t numParts = static_cast<size_t>(frameData->numParts);
	for (size_t i = 0; i < numParts; i++)
	{
		const SSPartFrameData* partData = &frameData->partFrameData[i];

		CCSprite* sprite = static_cast<CCSprite*>( m_pChildren->objectAtIndex(i) );
		SSPartState* partState = static_cast<SSPartState*>( m_partStates.objectAtIndex(partData->partNo) );

		size_t imageNo = m_ssDataHandle->getData()->partData[partData->partNo].imageNo;
		ss_u16 flags = partData->flags; 

		int sx = partData->souX;
		int sy = partData->souY;
		int sw = partData->souW;
		int sh = partData->souH;
		int dx = partData->dstX;
		int dy = partData->dstY;

		//int vdw = sw;
		//int vdh = sh;

		int ox = partData->orgX;
		int oy = partData->orgY;

		CCTexture2D* tex = m_imageList->getTexture(imageNo);
        if (tex == NULL) continue;
		sprite->setTexture(tex);
		sprite->setTextureRect(CCRect(sx, sy, sw, sh));

		sprite->setOpacity( partData->opacity );

		float ax = (float)ox / (float)sw;
		float ay = (float)oy / (float)sh;
		sprite->setAnchorPoint(ccp(ax, ay));

		sprite->setFlipX((flags & SS_PART_FLAG_FLIP_H) != 0);
		sprite->setFlipY((flags & SS_PART_FLAG_FLIP_V) != 0);
		sprite->setRotation(-partData->angle);
        sprite->setScaleX(partData->scaleX);
        sprite->setScaleY(partData->scaleY);
		sprite->setPosition(ccp(dx, 384 - dy));

		sprite->setVisible(true);

		partState->m_x = sprite->getPositionX();
		partState->m_y = sprite->getPositionY();
	}
}

void SSPlayer::setChildVisibleAll(bool visible)
{
    CCObject* child;
    CCARRAY_FOREACH(m_pChildren, child)
	{
		CCNode* node = static_cast<CCNode*>(child);
		node->setVisible(visible);
	}
}


