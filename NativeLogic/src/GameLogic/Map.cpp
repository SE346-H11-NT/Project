#include "Map.h"
#include "GameState.h"

#if MEMORY_LEAK_DEBUG == 1
#include <vld.h>
#endif


Object* Map::player_ = nullptr;
Map* Map::instance_ = nullptr;


Map::Map()
{
	this->stage_ = 1;

	this->boss_ = nullptr;
	this->mapObjects_ = nullptr;
	this->spawPos_ = POSITION_ZERO;
}


Map::Map(int stage)
{
	mapSize_ = 0;

	this->stage_ = stage;

	loadInfo();
	loadPretties();
	loadAnimatedPretties();
	loadTile();
	loadMobs();
	loadSignatureObjects();

	// Concatenate all map object's reference to split into 4tree.
	vector<Object*> mapObjects;
	mapObjects.insert(mapObjects.end(), pretties_.begin(), pretties_.end());

	mapObjects_ = new QuadTree(new T6Rect(Default::createT6Rect(0, mapSize_, mapSize_, 0)));
	mapObjects_->assign(mapObjects);
}


Map::~Map()
{
	SAFE_RELEASE(mapObjects_);

	FOR(pretties_.size())		SAFE_RELEASE(pretties_.at(i));		pretties_.clear();
	FOR(gameObjects_.size())	SAFE_RELEASE(gameObjects_.at(i));	gameObjects_.clear();
}


void Map::loadPretties()
{
	// Get resource info.
	tstring linkRS(LINK_PRETTIES_RS + Default::tostr(stage_));
	fstream data(linkRS + INFO_FILE);

	int columns, rows, prettiesWidth, prettiesHeight;
	if (data.is_open()) {
		data >> columns >> rows >> prettiesWidth >> prettiesHeight;
	}
	else {
		WARNING_BOX("Cannot open file\n" << linkRS);
		return;
	}

	data.close();

	// Read pretties map.
	tstring linkIF = tstring(LINK_PRETTIES_IF + Default::tostr(stage_));
	data.open(linkIF.c_str());

	if (data.is_open()) {
		int sizeMapWidth, nPretties;
		data >> nPretties;
		data >> sizeMapWidth;

		int value;
		FOR(nPretties) {
			data >> value;
			pretties_.push_back(new Pretties((linkRS + EXTENSION_PICTURE).c_str(), value, rows, columns,
				POSITION(i, sizeMapWidth, prettiesWidth, prettiesHeight)));
		}
	}
	else {
		WARNING_BOX("Cannot open file\n" << linkIF);
		return;
	}
	data.close();
}


void Map::loadTile()
{
	fstream data;
	tstring linkIF(LINK_TILE_IF + Default::tostr(stage_));
	data.open(linkIF);

	index_t tileMark = ~0;

	if (data.is_open()) {

		while (!data.eof())
		{
			long l, r, t, b;
			int characterTouch, tileType;
			data >> l >> r >> t >> b >> characterTouch >> tileType;
			tiles_.push_back(new Tile(l, r, t, b, characterTouch, (TileType)tileType));
		}

		data.close();
	}
	else {
		WARNING_BOX("Cannot open file\n" << linkIF);
		return;
	}
}


void Map::loadAnimatedPretties()
{
	tstring linkRS(LINK_A_PRETTIES_RS + Default::tostr(stage_));
	fstream data(linkRS + INFO_FILE);

	int rows, columns, tileSizeW, tileSizeH;
	if (data.is_open()) {

		data >> columns >> rows >> tileSizeW >> tileSizeH;
		data.close();

	}
	else {
		WARNING_BOX("Cannot open file\n" << linkRS);
		return;
	}

	tstring linkIF(LINK_A_PRETTIES_IF + Default::tostr(stage_));
	data.open(linkIF);

	index_t tileMark = ~0;
	index_t index;

	if (data.is_open()) {

		int nTileWidth, nTiles;
		data >> nTiles >> nTileWidth;

		int i = 0;
		while (!data.eof()) {

			data >> index;
			if (index == MARK_OFSET) {
				data >> tileMark;
			}
			else {
				pretties_.push_back(new AnimatedPretties(linkRS + EXTENSION_PICTURE, tileMark,
					rows, POSITION(index, nTileWidth, tileSizeW, tileSizeH), columns));
				i++;
			}

		}
		data.close();
	}
	else {
		WARNING_BOX("Cannot open file\n" << linkRS);
		return;
	}
}


void Map::loadMobs()
{
	tstring linkIF(LINK_MOBS_IF + Default::tostr(stage_));
	fstream data(linkIF);

	if (data.is_open())
	{
		int mobType;
		while (!data.eof())
		{
			data >> mobType;
			T6Vec3 pos(0.0F, 0.0F, DEFAULT_DEPTH);
			Size visible;
			int intPropertie;


			switch ((MobTypes)mobType)
			{
			case MobTypes::RUNNING_MAN:
				data >> pos.x >> pos.y >> intPropertie;
				gameObjects_.push_back(
					new RunningMan(pos, 
									T6Vec3(RUNNING_MAN_MOVE_SPEED_ABSOLUTE_VALUE * GET_SIGN(player_->getPosition().x - pos.x)
									, 0.0f, 0.0f), intPropertie));
				break;

			case MobTypes::SNIPER:
				data >> pos.x >> pos.y;
				gameObjects_.push_back(new Sniper(pos, player_));
				break;

			case MobTypes::HIDDEN_SNIPER:
				data >> pos.x >> pos.y >> visible.width >> visible.height >> intPropertie;
				gameObjects_.push_back(new HiddenSniper(pos, player_, visible, intPropertie));
				break;

			case MobTypes::STAND_CANON:
				data >> pos.x >> pos.y;
				gameObjects_.push_back(new StandCanon(pos, player_));
				break;

			case MobTypes::CANON:
				data >> pos.x >> pos.y;
				gameObjects_.push_back(new Canon(pos, player_));
				break;

			case MobTypes::DIVE_SHOOTER:
				data >> pos.x >> pos.y;
				gameObjects_.push_back(new DiveShooter(pos, player_));
				break;

			case MobTypes::STAND_SHOOTER:
				data >> pos.x >> pos.y;
				gameObjects_.push_back(new StandShooter(pos));
				break;

			case MobTypes::TANK:
				data >> pos.x >> pos.y;
				gameObjects_.push_back(new Tank(pos, player_));
				break;

			default:
				break;
			}
		}
	}
	else {
		WARNING_BOX("Cannot open file\n" << linkIF);
		return;
	}
}


void Map::update()
{
#if DEBUG == DEBUG_MAP_UPDATE_TIME
	clock_t time = clock();
#endif

	FOR(Map::getInstance().gameObjects_.size())
	{
		Map::getInstance().gameObjects_.at(i)->update();
		if (Map::getInstance().gameObjects_.at(i)->isTerminated())
		{
			Map::getInstance().gameObjects_.erase(Map::getInstance().gameObjects_.begin() + i);
			i--;
		}
	}

	FOR(Map::getInstance().tiles_.size())
		Map::getInstance().tiles_.at(i)->update();

	getInstance().boss_->update();

	if (getInstance().boss_->isDead())
	{
		SOUND_CODE(FreeSound::stop(getSoundtrackLink()));
		if (getInstance().boss_->getTimeCounter() > TIME_TO_NEXT_STAGE)
		{
			toNextMap();
		}
	}

#if DEBUG == DEBUG_MAP_UPDATE_TIME
	time = clock() - time;
	OutputDebugString(Default::tostr(time).c_str());
	OutputDebugString(_T("\n"));
#endif
}


void Map::draw()
{
#if DEBUG == DEBUG_MAP_DRAW_TIME
	clock_t time = clock();
#endif

	Map::getInstance().mapObjects_->draw(Camera::getViewPort());
	FOR(Map::getInstance().gameObjects_.size())
		Map::getInstance().gameObjects_.at(i)->draw();

	FOR(Map::getInstance().tiles_.size())
		Map::getInstance().tiles_.at(i)->draw();

	getInstance().boss_->draw();

#if DEBUG == DEBUG_MAP_DRAW_TIME
	time = clock() - time;
	OutputDebugString(Default::tostr(time).c_str());
	OutputDebugString(_T("\n"));
#endif
}


Map& Map::getInstance()
{
	if (Map::instance_ == nullptr) {
		Map::instance_ = new Map();
		return *Map::instance_;
	}

	return *Map::instance_;
}


void Map::toNextMap()
{
	int stage;
	if (Map::instance_ == nullptr)
		stage = 1;
	else
		stage = Map::instance_->stage_ + 1;

	SAFE_RELEASE(Map::instance_);
	Map::instance_ = new Map(stage);
	GameState::switchState(StartingState::get());
}


void Map::loadSignatureObjects()
{
	fstream data;
	tstring linkIF(LINK_SIGNATURE_IF + Default::tostr(stage_));
	data.open(linkIF);

	string objectMark;

	if (data.is_open()) {

		T6Vec3 pos = GAMEPOS_TOP_LEFT;
		data >> objectMark >> pos.x >> pos.y;

		SAFE_RELEASE(boss_);
		if (objectMark == BOSS_WALL)
			boss_ = new CrossHair(pos, player_);
		else if (objectMark == BOSS_ALIEN)
			boss_ = new Mouth(pos, player_);
		else if (objectMark == BOSS_DROID)
			boss_ = new Droid(pos);

		while (!data.eof())
		{
			data >> objectMark;

			if (objectMark == SIGNATURE_EXPLODE_BRIDGE)
				loadExplodeBridge(data);
			else if (objectMark == SIGNATURE_BULLET_BAG)
				loadBulletBag(data);
			else if (objectMark == SIGNATURE_FLOATING_BAG)
				loadFloatingBag(data);
			else if (objectMark == SIGNATURE_FALLING_STONE)
				loadFallingStone(data);
			else if (objectMark == SIGNATURE_FIRE)
				loadFire(data);
			else if (objectMark == SIGNATURE_FLOATING_ROCK)
				loadFloatingRock(data);
			else if (objectMark == SIGNATURE_BLUE_BOOM)
				loadBlueBoom(data);
		}
		data.close();
	}
	else {
		WARNING_BOX("Cannot open file\n" + linkIF);
		return;
	}
}


void Map::loadExplodeBridge(fstream& data)
{
	int left, right;
	data >> left >> right;

	ExplodeBridge::createBridge(Map::player_, tiles_[left], tiles_[right], &tiles_);
}


void Map::assignPlayer(Object* player)
{
	player_ = player;
}


void Map::generateFalcon(T6Vec3 position, BulletFalconType type)
{
	getInstance().gameObjects_.push_back(new BulletFalcon(position, type));
}


void Map::affectedByGameObjects(Object* obj, DWORD key)
{
	FOR(getInstance().gameObjects_.size())
		if (getInstance().gameObjects_.at(i)->affect(obj, key))
		{
			SAFE_RELEASE(getInstance().gameObjects_.at(i));
			getInstance().gameObjects_.erase(getInstance().gameObjects_.begin() + i);
		}

	getInstance().boss_->affect(obj, key);
}


void Map::affectedByTiles(Object* obj, bool isWaterCollis, int collisLevel)
{
	DWORD key = KEY_MOVEABLE;
	if (isWaterCollis)
		key = KEY_MOVEABLE | KEY_WATER_COLLIS;

	FOR(getInstance().tiles_.size())
		getInstance().tiles_.at(i)->affect(obj, key, (TileType)collisLevel);
}


void Map::loadBulletBag(fstream& data)
{
	T6Vec3 position = GAMEPOS_TOP_LEFT;
	int falconType;

	data >> position.x >> position.y;
	data >> falconType;

	gameObjects_.push_back(new BulletBag(position, (BulletFalconType)falconType));
}


void Map::loadFloatingBag(fstream& data)
{
	T6Vec3 position = GAMEPOS_TOP_LEFT;
	int falconType;
	T6Vec3 velocity;

	data >> position.x >> position.y;
	data >> falconType;
	data >> velocity.x >> velocity.y;

	gameObjects_.push_back(new FloatingBulletBag(position, (BulletFalconType)falconType, velocity));
}


void Map::loadInfo()
{
	ifstream data(tstring(LINK_MAP_IF) + Default::tostr(stage_));
	if (data.is_open())
	{
		string buffer;
		getline(data, buffer);
		mapName_ = tstring(buffer.begin(), buffer.end());

		data >> cameraType_;

		data >> buffer;
		soundtrackLink_ = tstring(buffer.begin(), buffer.end());
		data >> mapSize_;

		data >> spawPos_.x >> spawPos_.y;
	}
}


int Map::getCameraType()
{
	return getInstance().cameraType_;
}


void Map::loadFallingStone(fstream& data)
{
	T6Vec3 position = GAMEPOS_TOP_LEFT;

	data >> position.x >> position.y;
	gameObjects_.push_back(new FallingStone(position));
}


void Map::loadFire(fstream& data)
{
	T6Vec3 position = GAMEPOS_TOP_LEFT;
	T6Vec3 velocity = SPEED_NO;
	T6Rect	moveRange;
	memset(&moveRange, 0, sizeof(moveRange));

	data >> position.x >> position.y;
	data >> velocity.x >> velocity.y;
	data >> moveRange.left >> moveRange.right;

	gameObjects_.push_back(new Fire(position, velocity, moveRange));
}


void Map::loadBlueBoom(fstream& data)
{
	T6Vec3 position = GAMEPOS_TOP_LEFT;

	data >> position.x >> position.y;

	gameObjects_.push_back(new BlueBoomGenerator(position));
}

void Map::loadFloatingRock(fstream& data)
{
	T6Vec3 position = GAMEPOS_TOP_LEFT;
	T6Vec3 velocity = SPEED_NO;
	T6Rect	moveRange;
	memset(&moveRange, 0, sizeof(moveRange));

	data >> position.x >> position.y;
	data >> velocity.x >> velocity.y;
	data >> moveRange.left >> moveRange.right;

	FloatingRock* theRock = new FloatingRock(position, velocity, moveRange);

	gameObjects_.push_back(theRock);
	tiles_.push_back(theRock);
}

int Map::getStageIndex()
{
	return getInstance().stage_;
}

tstring Map::getStageName()
{
	return getInstance().mapName_;
}

tstring Map::getSoundtrackLink()
{
	return getInstance().soundtrackLink_;
}

int Map::getMapSize_()
{
	return getInstance().mapSize_;
}

void Map::addGameObject(Object* object)
{
	getInstance().gameObjects_.push_back(object);
}

void Map::reload()
{
	int stage = Map::getInstance().getStageIndex();
	SAFE_RELEASE(Map::instance_);
	Map::instance_ = new Map(stage);
}

T6Vec3 Map::getPlayerSpawPos()
{
	return getInstance().spawPos_;
}

void Map::reset()
{
	SAFE_RELEASE(Map::instance_);
}

T6Vec3 Map::computeRespawPos()
{
	T6Rect view = Camera::getViewPort();

	T6Rect range = view;
	if (getCameraType() == CAMERA_Y)
		range.top = range.bottom + (range.top - range.bottom) * 2 / 3;

	while (true)
	{
		range.left += SIZE_TILE_W;

		if (range.left > view.right)
		{
			range.left = 0;
		}

		range.right = range.left + SIZE_TILE_W;

		FOR(getInstance().tiles_.size())
			if (Default::checkIfBoundedNotEqual(&getInstance().tiles_.at(i)->getRect(), &range))
			{
				return T6Vec3((range.right + range.left) / 2, range.top, 0.0f);
			}
	}
}
