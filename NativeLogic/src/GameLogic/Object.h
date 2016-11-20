#ifndef __OBJECT_H__
#define __OBJECT_H__

#include <time.h>

#include "GameDefaultConstant.h"
#include "Timer.h"

#include "T6_Sprite.h"
#include "T6_MergedTexture.h"
#include "T6_ColormapTexture.h"
#include "DefaultMethods.h"
#include "Camera.h"

#define PROPERTIES_IMMORTAL 0
#define PROPERTIES_EVATION 1
#define PROPERTIES_VISIBLE 2

#define RESOURCE_MT	1	// Merged Texture
#define RESOURCE_MS	2	// Merged Sprite

typedef bool (*PropertiesFunction)(void);

#define KEY_NO				(0)			// Default false key
#define KEY_MOVEABLE		(1 << 0)	// Moveable or Static
#define KEY_PLAYER			(1 << 1)	// Player or Mobs
#define KEY_DESTROYABLE		(1 << 2)	// Be able shooted or not
#define KEY_WATER_COLLIS	(1 << 3)	// Collis with Water or not

#define CHECK_KEY(key, propertiesKey)	((key & propertiesKey) != 0)

class Object
{
	// OVERRIDED RE-CALL FUNCTION *must be call in the override function.
protected:
	virtual void			setBasicProperties();
	// ================================
public:
	virtual void			update() = 0;
	virtual void			draw()		= 0;
	virtual bool			affect(Object* obj, DWORD key) = 0;
	virtual bool			isTerminated() = 0;
	virtual					~Object();

			bool			isImmortal();
			bool			isTouchable();
			bool			isShootable();

			void			activate(int propertie);
			void			deactivate(int propertie);

			void			switchStatusTo(unsigned int newStatus);
			void			setScale(T6Vec2 newScale);

	virtual T6Vec3		getPosition();
			void			fixPosition(T6Vec3 fixDistance);
			void			setPosition(T6Vec3 newPos);
	virtual T6Rect			getRect();
			T6_Texture*		getCurrentSprite();
	virtual	T6Vec3*	getVelo();
			T6Vec2		getScale();
			bool			checkIfCurrentSpriteIs(int spriteIndex);

protected:
	static	bool propertiesYes();
	static	bool propertiesNo();
			void loadObjectResource(int numOfSprite, tstring spriteLink);
			void loadObjectResource(const tchar* path, int rows, int columns, int prettiesResourceType = RESOURCE_MT);

protected:
			T6_Texture**	sprites_;
			int				resourceType_;
			size_t			nSprite_;
			int				status_;
			T6Vec3		position_;
			T6Vec2		scale_;
			T6Rect*			objectDefRect_;

	PropertiesFunction		currentImmortalStatus_;
	PropertiesFunction		currentTouchableStatus_;
	PropertiesFunction		currentShootableStatus_;
};

#endif