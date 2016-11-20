#ifndef __MAP_H__
#define __MAP_H__

#include <fstream>
#include <vector>

#include "GameDefaultConstant.h"
#include "Pretties.h"
#include "AnimatedPretties.h"
#include "Tile.h"
#include "ExplodeBridge.h"
#include "BulletFalcon.h"
#include "BulletBag.h"
#include "FloatingBulletBag.h"
#include "FloatingRock.h"

#include "Mobs.h"

#include "Quadtree.h"
#include "Collision.h"

#include "RunningMan.h"
#include "StandCanon.h"
#include "Canon.h"
#include "HiddenSniper.h"
#include "Sniper.h"
#include "CrossHair.h"
#include "FallingStone.h"
#include "Fire.h"
#include "DiveShooter.h"
#include "Tentacle.h"
#include "Mouth.h"
#include "StandShooter.h"
#include "Tank.h"
#include "Droid.h"
#include "BlueBoomGenerator.h"

#include "T6_MergedTexture.h"
#include "DefaultMethods.h"
#include "DefaultConstant.h"

#define SIGNATURE_EXPLODE_BRIDGE	"EXPLODE_BRIDGE"
#define SIGNATURE_BULLET_BAG		"BULLET_BAG"
#define SIGNATURE_FLOATING_BAG		"FLOATING_BAG"
#define SIGNATURE_FALLING_STONE		"FALLING_STONE"
#define SIGNATURE_FIRE				"FIRE"
#define SIGNATURE_FLOATING_ROCK		"FLOATING_ROCK"
#define SIGNATURE_BLUE_BOOM			"BLUE_BOOM"

#define BOSS_WALL	"WALL"
#define BOSS_ALIEN	"ALIEN"
#define BOSS_DROID	"DROID"

class Sniper;

typedef TileType TouchLevel;

class Map
{
public:
	static void		update();
	static void		draw();
	static Map&		getInstance();
	static void		toNextMap();
	static int		getCameraType();
	static void		assignPlayer(Object* player);
	static void		generateFalcon(T6Vec3 position, BulletFalconType type);
	static int		getStageIndex();
	static tstring	getStageName();
	static tstring	getSoundtrackLink();
	static int		getMapSize_();
	static void		addGameObject(Object* object);
	static void		reload();
	static void		reset();
	static T6Vec3 computeRespawPos();

	static void		affectedByGameObjects(Object* obj, DWORD key);
	static void		affectedByTiles(Object* obj, bool isWaterCollis, int collisLevel);
	static T6Vec3	getPlayerSpawPos();

private:
	Map();
	Map(int stage);
	~Map();
	void	loadInfo();
	void	loadPretties();
	void	loadAnimatedPretties();
	void	loadTile();
	void	loadMobs();
	void	loadSignatureObjects();

	// Signature Object loading functions
	void	loadExplodeBridge(fstream& data);
	void	loadBulletBag(fstream& data);
	void	loadFloatingBag(fstream& data);
	void	loadFallingStone(fstream& data);
	void	loadFire(fstream& data);
	void	loadFloatingRock(fstream& data);
	void	loadBlueBoom(fstream& data);

private:
	static	Map*				instance_;
	static	Object*				player_;
	vector<Pretties*>			pretties_;
	vector<Tile*>				tiles_;
	vector<Object*>				gameObjects_;
	Boss*						boss_;
	QuadTree*					mapObjects_;
	int							mapSize_;
	int							stage_;
	int							cameraType_;
	tstring						mapName_;
	tstring						soundtrackLink_;
	T6Vec3					spawPos_;
};


#include "Sniper.h"

#endif