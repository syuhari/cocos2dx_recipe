#ifndef __SS_PLAYER_H__
#define __SS_PLAYER_H__

#include "cocos2d.h"

#include "SSPlayerData.h"


/**
 * SSImageList
 */

class SSImageList
{
public:
	/** コンストラクタ */
	explicit SSImageList(const char* imageFiles[], const char* imageDir = NULL);

	/** コンストラクタ */
	SSImageList();

	/** デストラクタ */
	virtual ~SSImageList();

	/** 初期化 */
	void init(const char* imageFiles[], const char* imageDir = NULL);

	/** 指定インデックスのテクスチャを返す */
	cocos2d::CCTexture2D* getTexture(size_t index);

protected:
	/** コンテナクリア */
	void clear();

	cocos2d::CCArray	m_imageList;
};



/**
 * SSPlayer
 */

class SSPlayer : public cocos2d::CCSprite
{
public:
	/** SSPlayerを生成する */
	static SSPlayer* create();

	/** SSPlayerを生成し、アニメーションを設定する */
	static SSPlayer* create(const SSData* ssData, SSImageList* imageList);

	/** アニメーションを設定 */
	void setAnimation(const SSData* ssData, SSImageList* imageList);

	/** 再生フレームNoを取得 */
	int getFrameNo() const;
	/** 再生フレームNoを設定 */
	void setFrameNo(int frameNo);

	/** 再生スピードを取得 */
	float getStep() const;
	/** 再生スピードを設定 1.0f:標準 */
	void setStep(float step);

	/** 再生ループ回数の設定を取得 */
	int getLoop() const;
	/** 再生ループ回数の設定 */
	void setLoop(int loop);

	/** 現在の再生回数を取得 */
	int getLoopCount() const;
	/** 現在の再生回数をクリア */
	void clearLoopCount();


	/** パーツの情報 */
	struct PartState
	{
		float	x;
		float	y;
	};

	/** 
	 * 指定パーツの情報をPartInfoに格納する 
	 * 成功時はtrue, パーツが見つからないときはfalseを返す 
	 */
	bool getPartState(PartState& result, const char* name);


public:
	SSPlayer(void);
	virtual ~SSPlayer(void);
	virtual bool init();
	void update(float dt);

protected:
	void allocParts(int numParts);
	void releaseParts();

	void clearAnimation();
	bool hasAnimation() const;

	void setFrame(int frameNo);
	void setChildVisibleAll(bool visible);

protected:
	class SSDataHandle*	m_ssDataHandle;
	SSImageList*		m_imageList;

	cocos2d::CCArray	m_partStates;
	float				m_playingFrame;
	float				m_step;
	int					m_loop;
	int					m_loopCount;
};


#endif	// __SS_PLAYER_H__
