#ifndef __SS_PLAYER_DATA_H__
#define __SS_PLAYER_DATA_H__

#ifdef __cplusplus
extern "C" {
#endif

typedef unsigned char	ss_u8;
typedef signed char		ss_s8;
typedef short			ss_s16;
typedef unsigned short	ss_u16;

enum {
	SS_PART_FLAG_FLIP_H	= 1 << 0,
	SS_PART_FLAG_FLIP_V	= 1 << 1,
	NUM_SS_PART_FLAGS
};

typedef struct {
	ss_s16	partNo;
	ss_u16	flags;
	ss_s16	souX;
	ss_s16	souY;
	ss_s16	souW;
	ss_s16	souH;
	ss_s16	dstX;
	ss_s16	dstY;
	ss_s16	orgX;
	ss_s16	orgY;
	ss_s16	opacity;
    ss_s16  __reserved;
    float   angle;
	float	scaleX;
	float	scaleY;
} SSPartFrameData;


typedef struct {
	SSPartFrameData*	partFrameData;
	ss_s16				numParts;
} SSFrameData;


typedef struct {
	const char*		name;
	ss_s16			id;
	ss_s16			parentId;
	ss_s16			imageNo;
} SSPartData;


typedef struct {
	ss_s16			id;
	ss_s16			version;
	ss_s16			fps;
	ss_s16			numParts;
	SSPartData*		partData;
	ss_s16			numFrames;
	SSFrameData*	frameData;
} SSData;

#ifdef __cplusplus
}
#endif

#endif	// __SS_PLAYER_DATA_H__
