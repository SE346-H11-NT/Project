#ifndef _CAMERA_H_
#define _CAMERA_H_

#include "DefaultConstant.h"
#include "GraphicAlgorithms2D/MathDefaultConstant.h"

#define CAMERA_X (1)
#define CAMERA_Y (-1)
#define CAMERA_MOVE_SPEED	50

enum CameraState
{
	CAMERA_NORMAL = 0,
	CAMERA_AUTO,
	CAMERA_STOP,
	NUM_OF_CAMERA_STATE
};

class Camera
{
public:
	static void update(T6Vec3 pos, DWORD deltaTime, int cameraAxis = CAMERA_X);
	static T6Matrix4 getTransform();
	static T6Vec3 getPosition();

	static T6Rect getViewPort();

	static Camera* getInstance();

	static void activateMove(T6Vec3 distance, CameraState endState = CameraState::CAMERA_STOP);

	static void setPosition(T6Vec3 pos);

	static CameraState getState();

private:
	Camera();
	~Camera();

	static void normalUpdate(T6Vec3 pos, int cameraAxis);
	static void autoUpdate(DWORD deltaTime);
	
	static void	computeViewPort();

private:
	T6Matrix4 transform_;
	T6Vec3 position_;
	T6Vec3 moveDistance_;
	CameraState state_;
	CameraState nextState_;
	T6Rect view_;
	static Camera* instance_;
};

#endif