#ifndef GameState_h__
#define GameState_h__

#include "Camera.h"
#include "T6_Keyboard.h"

#include "Selector.h"
#include "FreeSound.h"
#include "GameDefaultConstant.h"
#include "Character.h"
#include "Map.h"
#include "Timer.h"
#include "FreeText.h"
#include "ScoreManager.h"

#pragma region Game State

class GameState
{
public:
	virtual void update() = 0;
	virtual void draw() = 0;
	virtual void enter() = 0;

	static void initialize(T6_Keyboard* controler);

	static void release();

	static void switchState(GameState* newState);

	virtual void cameraUpdate() = 0;

	static void stateUpdate();

	static void stateDraw();

protected:
	static T6_Keyboard* controler_;
	static Character*	player_;
	static GameState*	gameState_;
};
#pragma endregion

#pragma region Main Menu
#define MAIN_MENU_SELECTION_START	_T("Start Game")
#define MAIN_MENU_SELECTION_CREDIT	_T("About Me")
#define MAIN_MENU_RESOURCE_BILL		(tstring(_T("Resource//Miscellaneous//BillAndLance")) + EXTENSION_PICTURE)
#define MAIN_MENU_RESOURCE_CONTRA_LOGO	(tstring(_T("Resource//Miscellaneous//ContraLogo")) + EXTENSION_PICTURE)
#define MAIN_MENU_RESOURCE_KONAMI_LOGO	(tstring(_T("Resource//Miscellaneous//KonamiLogo")) + EXTENSION_PICTURE)
#define MAIN_MENU_LISENCE	_T("TM and (c) 2014\nUIT student's project\nMade by\nFrederick Tran of SE07")
#define MAIN_MENU_SELECT_ORDER	_T("Play Select")
#define MAIN_MENU_LISENCE_POS	T6Vec3(RESOLUTION_WIDTH / 2.0F, 48.0F, 0.0F)
#define MAIN_MENU_SELECTION_POS		T6Vec3(56.0F, 80.0F, 0.0F)
#define MAIN_MENU_SELECT_TIME	/*0*/ 5000

#define DRAWPOS_BILL_AND_LANCE	T6Vec3(139.0F, 120.0F, 0.0F)
#define DRAWPOS_CONTRA_LOGO		T6Vec3(32.0F, 191.0F, 0.0F)
#define DRAWPOS_KONAMI_LOGO		T6Vec3(81.0F, 222.0F, 0.0F)
#define DRAWPOS_SELECT_ORDER	T6Vec3(40.0F, 96.0F, 0.0F)

#define SOUND_MAINMENU_BACKGOUND	_T("Resource//Soundtrack//MainMenu.wav")

class MainMenu : public GameState
{
public:
	virtual void update();

	virtual void draw();

	virtual void enter();

	static MainMenu* get();

private:
	MainMenu();
	~MainMenu();

	virtual void cameraUpdate();

private:
	Selector* selector_;
	T6_Texture* billAndLance_;
	T6_Texture* contraLogo_;
	T6_Texture* konamiLogo_;
	bool	isPlayedSound_;
	const tchar* selectedOne_;
	DWORD	timeCounter_;
	static MainMenu* instance_;
};
#pragma endregion

#pragma region Starting State
#define STARTING_STRING_POS_SCORE	T6Vec3(16.0F, 208.0F, 0.0F)
#define STARTING_STRING_POS_REST	T6Vec3(16.0F, 192.0F, 0.0F)
#define STARTING_STRING_POS_HIGH_S	T6Vec3(80.0F, 168.0F, 0.0F)
#define STARTING_STRING_1P			_T("1P")
#define STARTING_STRING_REST		_T("Rest")
#define STARTING_STRING_HIGH_S		_T("Hi")
#define STARTING_STRING_STAGE		_T("Stage ")
#define STARTING_POS_REST			T6Vec3(64.0F, 192.0F, 0.0F)
#define STARTING_POS_SCORE			T6Vec3(88.0F, 208.0F, 0.0F)
#define STARTING_POS_HIGH_S			T6Vec3(120.0F, 168.0F, 0.0F)
#define STARTING_POS_STAGE_INDEX	T6Vec3(95.0F, 112.0F, 0.0F)
#define STARTING_POS_STAGE_NAME		T6Vec3(96.0F, 96.0F, 0.0F)
#define STARTING_FLASH_TIME			300
#define STARTING_STATE_TIME			/*0*/ 5000

class StartingState : public GameState
{
public:
	virtual void update();

	virtual void draw();

	virtual void enter();

	static StartingState* get();

private:
	StartingState();
	~StartingState();

	virtual void cameraUpdate();

private:
	static StartingState* instance_;
	
	bool isFlashOn_;
	DWORD timeCounter_;
	DWORD timeCounterToNextState_;
};
#pragma endregion

#pragma region Playing State
class PlayingState : public GameState
{
public:
	virtual void update();

	virtual void draw();

	virtual void enter();

	static PlayingState* get();

private:
	PlayingState();
	~PlayingState();

	virtual void cameraUpdate();

private:
	static PlayingState* instance_;

};
#pragma endregion

#pragma region Dead State
#define DEAD_STATE_SELECTOR_CONTINUE	_T("Continue")
#define DEAD_STATE_SELECTOR_END			_T("End")
#define DEAD_STATE_STRING_GAMEOVER		_T("Game Over")

#define DEAD_STATE_STRING_POS_SCORE		STARTING_STRING_POS_SCORE
#define DEAD_STATE_STRING_POS_HIGH_S	STARTING_STRING_POS_HIGH_S
#define DEAD_STATE_STRING_POS_GAMEOVER	STARTING_POS_STAGE_INDEX
#define DEAD_STATE_STRING_1P			STARTING_STRING_1P
#define DEAD_STATE_STRING_HIGH_S		STARTING_STRING_HIGH_S
#define DEAD_STATE_POS_SCORE			STARTING_POS_SCORE
#define DEAD_STATE_POS_HIGH_S			STARTING_POS_HIGH_S
#define DEAD_STATE_POS_SELECTOR			T6Vec3(112.0F, 96.0F, 0.0F)
#define DEAD_STATE_FLASH_TIME			STARTING_FLASH_TIME
#define DEAD_STATE_APPEAR_TIMES			3

class DeadScene : public GameState
{
public:
	virtual void update();

	virtual void draw();

	virtual void enter();


	static DeadScene* get();

private:
	DeadScene();
	~DeadScene();

	virtual void cameraUpdate();

private:
	static DeadScene* instance_;

	bool isFlashOn_;
	DWORD timeCounter_;
	Selector* selector_;
	int	deadTimesRemaining_;
};
#pragma endregion

#endif // GameState_h__
