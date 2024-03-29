﻿#ifndef __GAME_DEFAULT_CONSTANT_H__
#define __GAME_DEFAULT_CONSTANT_H__

// SYSTEM SETTING
#define INFO_FILE				_T("info")
//#define EXTENSION_PICTURE		_T(".png")
#define EXTENSION_PICTURE		_T("")
#define EXTENSION_SOUND			_T(".wav")

#define MARK_OFSET				(~0)

#define FPS						60
#define FRAME_TIME				(1000.0 / FPS)
#define FRAME_TIME_FOR_RENDER	(1000.0 / 10)

// GAME SPEED
#define JUMP_SPEED				280.0F
#define JUMP_SPEED_DEAD			200.0F
#define GRAVITY					(-600.0F)
#define DEFAULT_MOVE_SPEED		60.0F
#define MOVE_SPEED_LEFT			(-DEFAULT_MOVE_SPEED)
#define MOVE_SPEED_RIGHT		( DEFAULT_MOVE_SPEED)
#define CLIMB_DISTANCE			T6Vec3(42.0f, 0.0f, 0.0f)

#define TRUE_SPEED(speed,time)	(speed * (time / 1000.0F))
#define SPEED_NO			T6Vec3(0.0f,	0.0f,	0.0f)
#define SPEED_X(A)			T6Vec3(A,		0.0f,	0.0f)
#define SPEED_Y(A)			T6Vec3(0.0f,	A,		0.0f)	
#define SPEED_XY(A, B)		T6Vec3(A,		B,		0.0f)

// GAME INITIALIZE
#define DEFAULT_LIFE			3
#define DEFAULT_SCORE			0
#define DEFAULT_STARTPOINT(X,Y)	T6Vec3((1.5F * SIZE_TILE_W) + X, RESOLUTION_HEIGHT + Y, DEFAULT_DEPTH)

#define WDPOS_CENTER		(T6Vec3(RESOLUTION_WIDTH / 2.0F,	RESOLUTION_HEIGHT / 2.0F,	DEFAULT_DEPTH))
#define WDPOS_NOTIFY		(T6Vec3(RESOLUTION_WIDTH / 2.0F,	RESOLUTION_HEIGHT / 4.0F,	DEFAULT_DEPTH))
#define WDPOS_BOTTOM_CENTER (T6Vec3(RESOLUTION_WIDTH / 2.0F,	RESOLUTION_HEIGHT,			DEFAULT_DEPTH))
#define WDPOS_BOTTOM_RIGHT	(T6Vec3(RESOLUTION_WIDTH,			RESOLUTION_HEIGHT,			DEFAULT_DEPTH))
#define WDPOS_BOTTOM_LEFT	(T6Vec3(0.0F,						RESOLUTION_HEIGHT,			DEFAULT_DEPTH))
#define WDPOS_TOP_LEFT		(T6Vec3(0.0F,						0.0F,						DEFAULT_DEPTH))
#define WDPOS_CENTER_(A)	(T6Vec3(RESOLUTION_WIDTH / 2.0F,	100 + 80 * A,				DEFAULT_DEPTH))
#define POSITION_ZERO		(T6Vec3(0.0F, 0.0F, 0.0F))
// GAME SETTING
#define ALLY_MOBS				0
#define ALLY_PLAYER				1

#define BULLET_BASIC_MOVE_SPEED	150

#define BULLET_M_MOVE_SPEED		200

#define BULLET_F_MOVE_SPEED		100
#define BULLET_F_ROUND_RANGE	15
#define BULLET_F_ROUND_SPEED	ANGLE_CLOCKWISE(1500)

#define BULLET_DAMAGE_BASIC		1
#define BULLET_DAMAGE_S			2
#define BULLET_DAMAGE_F			2
#define BULLET_DAMAGE_M			2
#define BULLET_DAMAGE_L			3
#define BULLET_DAMAGE_MASSIVE	999

#define BULLET_MAX_MOBS		10
#define BULLET_MAX_BASIC	4
#define BULLET_MAX_S		10
#define BULLET_MAX_F		4
#define BULLET_MAX_M		4
#define BULLET_MAX_L		4
#define BULLET_MAX_RED_BOOM	6
#define BULLET_MAX_RED_SPREAD_BOOM	4
#define BULLET_MAX_FIRE_CIRCLE	7

#define BULLET_SIZE_BASIC		Size(3.0, 3.0)
#define BULLET_SIZE_S			Size(8.0, 8.0)
#define BULLET_SIZE_F			Size(8.0, 8.0)
#define BULLET_SIZE_M			Size(8.0, 8.0)
#define BULLET_SIZE_L			Size(16.0, 4.0)
#define BULLET_SIZE_RED_BOOM	Size(8.0, 8.0)

// GAME TIME SETTING
#define TIME_SHOOT_DELAY	20
#define TIME_ROTATE_DELAY	1000
#define TIME_DEATH			2000
#define SEC_TO_MICROSEC(A)	(A * 1000.0F)
#define MICROSEC_TO_SEC(A)	(A / 1000.0F)

// CHARACTER SETTING
#define DISTANCE_FROM_HIP_TO_MUZZLE_STRAIGHT_Y	4
#define DISTANCE_FROM_HIP_TO_MUZZLE_DOWN45_Y	(-7)
#define DISTANCE_FROM_HIP_TO_MUZZLE_FALL_Y		23
#define	DISTANCE_FROM_HIP_TO_MUZZLE_LIE_Y		9
#define SWIM_SHOOT_POINT_FIX_DISTANCE			T6Vec2(0.0F, 5.0F)
#define SWIM_SHOOT_POINT_FIX_DISTANCE_VECTOR3	T6Vec3(SWIM_SHOOT_POINT_FIX_DISTANCE)

#define SHOOT_ANGLE_UP45		ANGLE_COUNTER_CLOCKWISE(30)
#define SHOOT_ANGLE_UP135		ANGLE_COUNTER_CLOCKWISE(150)
#define SHOOT_ANGLE_UP90		ANGLE_COUNTER_CLOCKWISE(90)
#define SHOOT_ANGLE_DOWN45		ANGLE_CLOCKWISE(30)
#define SHOOT_ANGLE_DOWN135		ANGLE_CLOCKWISE(150)
#define SHOOT_ANGLE_DOWN90		ANGLE_CLOCKWISE(90)

// GAME SCORE
#define SCORE_PICK_ITEM		1000
#define SCORE_CANON			500
#define SCORE_STAND_CANON	500
#define SCORE_RUNNING_MAN	100
#define SCORE_SNIPER		100

// GAME UPDATE SETTING
#define UPDATE_NONE				0	// 0000
#define UPDATE_X				1	// 0001
#define UPDATE_Y				2	// 0010
#define UPDATE_XY				3	// 0011
#define NUM_OF_UPDATE_TYPE		4

// GAME GRAPHIC INFO
#define WATER_WAVE_ROWS	1
#define WATER_WAVE_COLUMNS 1
#define WATER_WAVE_TOTAL_FRAMES	1

#define ANGLE_BASIC_SX(scaleX)	(scaleX < 0 ? ANGLE_COUNTER_CLOCKWISE(180) : ANGLE_COUNTER_CLOCKWISE(0))

// TILE AND PRETTIES
#define SIZE_PRETTIES_W		16
#define SIZE_PRETTIES_H		16
#define SIZE_TILE_W			32
#define SIZE_TILE_H			16
#define SIZE_TILE_STAND_S	6  

#define POSITION(index, nColumns, columnsSize, rowSize) T6Vec3((int)(index % nColumns) * (float)columnsSize, (int)(index / nColumns) * (float)rowSize, DEFAULT_DEPTH)

// CONTROLLER KEY
#define CK_UP					DIK_W
#define CK_DOWN					DIK_S
#define CK_LEFT					DIK_A
#define CK_RIGHT				DIK_D
#define CK_FIRE					DIK_J
#define CK_JUMP					DIK_K
#define CK_START				DIK_RETURN
#define CK_SELECT				DIK_RSHIFT

// RESOURCE PATHS
#define LINK_CHARACTER_HEAD		_T("Resource\\Character\\Head\\")
#define LINK_CHARACTER_LEG		_T("Resource\\Character\\Leg\\")
#define LINK_PRETTIES_RS		_T("Resource\\Map\\Image\\PR")
#define LINK_PRETTIES_IF		_T("Resource\\Map\\P")
#define LINK_A_PRETTIES_RS		_T("Resource\\Map\\Image\\APR")
#define LINK_A_PRETTIES_IF		_T("Resource\\Map\\AP")
#define LINK_TILE_RS			_T("Resource\\Map\\Image\\TR")
#define LINK_TILE_IF			_T("Resource\\Map\\T")
#define LINK_MOBS_IF			_T("Resource\\Map\\M")
#define LINK_SIGNATURE_IF		_T("Resource\\Map\\S")
#define LINK_MAP_IF				_T("Resource\\Map\\IF")

// Miscellaneous
#define LINK_BULLET_RS			_T("Resource\\Miscellaneous\\Bullets")  
#define LINK_WATER_WAVE			_T("Resource\\Miscellaneous\\WaterWave")
#define LINK_WATER_BLOW			_T("Resource\\Miscellaneous\\WaterBlow")

// Quadratic tree
#define NODE_MAX_OBJECT			20
#define NUM_OF_SUBNODE			4
#define NUM_OF_NODE_PER_ROW		2

// Simple Functions
#define ROUNDED_RANGE_INCREASE(value, step, limit) ((value + step) % limit)
#endif