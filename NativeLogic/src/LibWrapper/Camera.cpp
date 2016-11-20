#include "Camera.h"

#if MEMORY_LEAK_DEBUG == 1
#include <vld.h>
#endif

#include "GameDefaultConstant.h"

Camera* Camera::instance_ = 0;


Camera::Camera()
{
	position_ = POSITION_ZERO;
	moveDistance_ = POSITION_ZERO;
	NativeMatrix::indentity(&transform_);
	state_ = CAMERA_NORMAL;
}


Camera::~Camera()
{
	SAFE_RELEASE(instance_);
}


Camera* Camera::getInstance()
{
	if (instance_ == 0)
		instance_ = new Camera();
	return instance_;
}


void Camera::update(T6Vec3 pos, DWORD deltaTime, int cameraAxis)
{
	switch (Camera::getInstance()->state_)
	{
	case CAMERA_NORMAL:
		normalUpdate(pos, cameraAxis);
		break;
	case CAMERA_AUTO:
		autoUpdate(deltaTime);
		break;
	case CAMERA_STOP:
		break;
	default:
		break;
	}
}


T6Matrix4 Camera::getTransform()
{
	T6Matrix4 mtScale;
	NativeMatrix::scaling(&mtScale, 1, -1, 0);

	T6Matrix4 mtTrans;
	NativeMatrix::translation(&mtTrans, -(Camera::getInstance()->position_.x),
		-(Camera::getInstance()->position_.y + RESOLUTION_HEIGHT), 
		Camera::getInstance()->position_.z);

	Camera::getInstance()->transform_ = mtTrans * mtScale;
	return Camera::getInstance()->transform_;
}


T6Vec3 Camera::getPosition()
{
	return Camera::getInstance()->position_;
}


T6Rect Camera::getViewPort()
{
	return Camera::getInstance()->view_;
}


void Camera::activateMove(T6Vec3 distance, CameraState endState)
{
	Camera::getInstance()->moveDistance_ = distance;
	Camera::getInstance()->state_ = CameraState::CAMERA_AUTO;
	Camera::getInstance()->nextState_ = endState;
}

void Camera::normalUpdate(T6Vec3 pos, int cameraAxis)
{
	T6Vec3* position = &Camera::getInstance()->position_;

	switch (cameraAxis)
	{
	case CAMERA_X:
		if (pos.x > position->x + RESOLUTION_WIDTH / 2.0F)
			position->x = pos.x - RESOLUTION_WIDTH / 2.0F;
		break;
	case CAMERA_Y:
		if (pos.y > position->y + RESOLUTION_HEIGHT / 2.0F)
			position->y = pos.y - RESOLUTION_HEIGHT / 2.0F;
		break;
	default:
		break;
	}

	Camera::getInstance()->computeViewPort();
}

void Camera::autoUpdate(DWORD deltaTime)
{
	T6Vec3* position = &Camera::getInstance()->position_;
	T6Rect* view = &Camera::getInstance()->view_;
	T6Vec3* moveDistance = &Camera::getInstance()->moveDistance_;

	float moveStep = TRUE_SPEED(CAMERA_MOVE_SPEED, deltaTime) * GET_SIGN(moveDistance->x);

	if (VECTOR_VALUE_ABS(moveDistance->x) < moveStep)
	{
		position->x += moveDistance->x;
		moveDistance->x = 0.0F;
	}
	else
	{
		position->x += moveStep;
		moveDistance->x -= moveStep;
	}

	moveStep = TRUE_SPEED(CAMERA_MOVE_SPEED, deltaTime) * GET_SIGN(moveDistance->y);

	if (VECTOR_VALUE_ABS(moveDistance->y) < moveStep)
	{
		position->y += moveDistance->y;
		moveDistance->y = 0.0F;
	}
	else
	{
		position->y += moveStep;
		moveDistance->y -= moveStep;
	}

	if (*moveDistance == POSITION_ZERO)
		Camera::getInstance()->state_ = Camera::getInstance()->nextState_;

	Camera::getInstance()->computeViewPort();
}


void Camera::computeViewPort()
{
	T6Rect* view = &Camera::getInstance()->view_;

	view->left = (LONG)Camera::getInstance()->position_.x;
	view->bottom = (LONG)Camera::getInstance()->position_.y;
	view->right = (LONG)view->left + RESOLUTION_WIDTH;
	view->top = (LONG)view->bottom + RESOLUTION_HEIGHT;

	if (view->left < 0) {
		view->right -= view->left;
		view->left = 0;
	}

	if (view->bottom < 0) {
		view->top -= view->bottom;
		view->bottom = 0;
	}
}


void Camera::setPosition(T6Vec3 pos)
{
	Camera::getInstance()->position_ = pos;
	Camera::getInstance()->computeViewPort();
}


CameraState Camera::getState()
{
	return Camera::getInstance()->state_;
}