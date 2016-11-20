#include "ExplodeBridge.h"
#include "GameDefaultConstant.h"


Pretties** ExplodeBridge::destroyedBridgePretties_ = nullptr;

ExplodeBridge::ExplodeBridge(Object* baseObject, T6Vec3 position, T6Rect boundRange, ExplodeBridgeOrder order)
	: Pretties(EXPLODE_BRIDGE_RESOURCE_LINK, 0,
	EXPLODE_BRIDGE_RESOURCE_ROWS,
	EXPLODE_BRIDGE_FRAME_NUM, position,
	RESOURCE_MS)
	, AnimatedPretties(EXPLODE_BRIDGE_RESOURCE_LINK, 0,
	EXPLODE_BRIDGE_RESOURCE_ROWS, position,
	EXPLODE_BRIDGE_FRAME_NUM)
	, Tile(boundRange.left, boundRange.right, boundRange.top, boundRange.bottom,
	0/*==CharacterStatus::ON_GROUND*/, TileType::TOP_ONLY)
{
	if (destroyedBridgePretties_ == nullptr)
		ExplodeBridge::initializeBridgeStaticResource();

	position_ = position;
	this->order_ = order;
	this->baseObjectForUpdate_ = baseObject;
	this->currentBridgeStatus_ = ExplodeBrideStatus::BRIDGE_WAIT;
	this->destroyTimeRemaining_ = 0;
}


ExplodeBridge::~ExplodeBridge()
{
}


void ExplodeBridge::initializeBridgeStaticResource()
{
	destroyedBridgePretties_ = new Pretties*[Side::NUM_OF_SIDE];

	FOR_e(Side::NUM_OF_SIDE)
		destroyedBridgePretties_[i] = new Pretties(tstring(LINK_BRIDGE_DESTROYED) + EXTENSION_PICTURE,
		i + 1, 1, Side::NUM_OF_SIDE,
		WDPOS_TOP_LEFT, RESOURCE_MT, (DrawCenter)i);
}


ExplodeBridge* ExplodeBridge::createBridge(Object* baseObject, Tile* leftside_BrideHead, Tile* rightside_BrideHead,
	vector<Tile*>* tileList, ExplodeBridgeOrder order)
{
	T6Vec3 position(leftside_BrideHead->getRect().right,
		leftside_BrideHead->getRect().bottom, leftside_BrideHead->getPosition().z);

	T6Rect boundRange;
	boundRange.left = (LONG)position.x;
	boundRange.bottom = (LONG)position.y;
	boundRange.right = (LONG)boundRange.left + (LONG)EXPLODE_BRIDGE_LONG;
	boundRange.top = (LONG)boundRange.bottom + (LONG)EXPLODE_BRIDGE_THICKNESS;

	ExplodeBridge* bridgePart = new ExplodeBridge(baseObject, position, boundRange, ExplodeBridgeOrder::BRIDGE_MIDDLE);

	bridgePart->bridgehead_LinkedTile_ = new Tile*[Side::NUM_OF_SIDE];
	bridgePart->bridgehead_LinkedTile_[Side::SIDE_LEFT] = leftside_BrideHead;

	if (bridgePart->getRect().right < rightside_BrideHead->getRect().left)
	{
		bridgePart->bridgehead_LinkedTile_[Side::SIDE_RIGHT] = ExplodeBridge::createBridge(nullptr, bridgePart, rightside_BrideHead,
			tileList, ExplodeBridgeOrder::BRIDGE_MIDDLE);
		bridgePart->linkedPretties_.push_back(new Pretties(EXPLODE_BRIDGE_RESOURCE_LINK,
			order + EXPLODE_BRIDGE_FRAME_NUM + 1,
			EXPLODE_BRIDGE_RESOURCE_ROWS,
			EXPLODE_BRIDGE_FRAME_NUM,
			bridgePart->getPosition(),
			RESOURCE_MT,
			DrawCenter::TOPLEFT));
	}
	else
	{
		bridgePart->bridgehead_LinkedTile_[Side::SIDE_RIGHT] = rightside_BrideHead;
		bridgePart->order_ = ExplodeBridgeOrder::NUM_OF_ORDER;
		bridgePart->linkedPretties_.push_back(new Pretties(EXPLODE_BRIDGE_RESOURCE_LINK,
			ExplodeBridgeOrder::BRIDGEHEAD_RIGHT + EXPLODE_BRIDGE_FRAME_NUM + 1,
			EXPLODE_BRIDGE_RESOURCE_ROWS,
			EXPLODE_BRIDGE_FRAME_NUM,
			bridgePart->getPosition(),
			RESOURCE_MT,
			DrawCenter::TOPLEFT));
	}

	tileList->push_back(bridgePart);
	return bridgePart;
}


void ExplodeBridge::releaseExplodeBridgeResource()
{
	FOR_e(Side::NUM_OF_SIDE)	SAFE_RELEASE(destroyedBridgePretties_[i]);

	SAFE_RELEASE(destroyedBridgePretties_);
}


void ExplodeBridge::draw()
{
	if (currentBridgeStatus_ < ExplodeBrideStatus::BRIDGE_DETONATE)
	{
		Tile::draw();
		AnimatedPretties::draw();
	}
}


void ExplodeBridge::update()
{
	switch (currentBridgeStatus_)
	{
	case ExplodeBrideStatus::BRIDGE_WAIT:
		if (baseObjectForUpdate_ != nullptr)
			if (baseObjectForUpdate_->getPosition().x >= position_.x)
				detonate();
		break;

	case ExplodeBrideStatus::BRIDGE_EXPLODE:
		if (destroyTimeRemaining_ <= Timer::getRoundTime())
		{
			currentBridgeStatus_ = ExplodeBrideStatus::BRIDGE_DETONATE;
			deactivate(PROPERTIES_VISIBLE);
			T6Vec3 leftPos(position_);
			T6Vec3 rightPos(bridgehead_LinkedTile_[Side::SIDE_RIGHT]->getRect().left, 
								bridgehead_LinkedTile_[Side::SIDE_RIGHT]->getRect().bottom,
								bridgehead_LinkedTile_[Side::SIDE_RIGHT]->getPosition().z);

			leftPos.y += (float)(*sprites_)->getFrameSize().height;
			rightPos.y += (float)(*sprites_)->getFrameSize().height;

			bridgehead_LinkedTile_[Side::SIDE_LEFT]->pushAPretties(ExplodeBridge::destroyedBridgePretties_[SIDE_LEFT]->clone(leftPos));
			bridgehead_LinkedTile_[Side::SIDE_RIGHT]->pushAPretties(ExplodeBridge::destroyedBridgePretties_[SIDE_RIGHT]->clone(rightPos));
			destroyTimeRemaining_ = (DWORD)(EffectManager::getExplodeTime() * (EXPLODE_NUM_FOR_DESTROY_ANIMATION + EXPLODE_BRIDGE_FRAME_NUM));
		}
		else
			destroyTimeRemaining_ -= Timer::getRoundTime();
		break;

	case ExplodeBrideStatus::BRIDGE_DETONATE:
		if (destroyTimeRemaining_ <= Timer::getRoundTime())
		{
			bridgehead_LinkedTile_[Side::SIDE_RIGHT]->activate();
			currentBridgeStatus_ = ExplodeBrideStatus::BRIDGE_DISSAPEAR;
		}
		else
			destroyTimeRemaining_ -= Timer::getRoundTime();
		break;

	case ExplodeBrideStatus::BRIDGE_DISSAPEAR:
		break;
	default:
		break;
	}
}


void ExplodeBridge::detonate()
{
	currentBridgeStatus_ = ExplodeBrideStatus::BRIDGE_EXPLODE;
	srand((unsigned int)time(0));
	FOR(EXPLODE_NUM_FOR_DESTROY_ANIMATION)
		EffectManager::addExplode(T6Vec3(position_.x + EXPLODE_BRIDGE_RANDOM_IN_WIDTH,
		position_.y + EXPLODE_BRIDGE_RANDOM_IN_HEIGHT,
		DEFAULT_DEPTH), (DWORD)(i * EffectManager::getExplodeTime()));

	destroyTimeRemaining_ = (DWORD)(EffectManager::getExplodeTime());
}


void ExplodeBridge::activate()
{
	detonate();
}

bool ExplodeBridge::affect(Object* obj, DWORD key)
{
	Tile::affect(obj, key);
	bridgehead_LinkedTile_[Side::SIDE_RIGHT]->affect(obj, key);
	return false;
}

bool ExplodeBridge::isTerminated()
{
	return (currentBridgeStatus_ = ExplodeBrideStatus::BRIDGE_DISSAPEAR);
}
