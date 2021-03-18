#pragma once
#include "header.h"
#include "BaseEngine.h"
#include "GameTiles.h"
#include "DrawingFilters.h"
#include "AudioManager.h"
#include "State.h"
#include "CoordinateMapping.h"
#include <Windows.h>

class Game :
	public BaseEngine
{
public:
	void virtKeyDown(int iKeyCode);

	void virtDrawStringsOnTop();

	int getTurn();

	void changeTurn();

    //void Utilities(HWND h, UINT i, WPARAM w, LPARAM l);

	void virtSetupBackgroundBuffer();

	int virtInitialiseObjects();

	void virtMouseDown(int iButton, int iX, int iY);

    void forceResetScale();

    int getTileCenterX(int iX);
    int getTileCenterY(int iY);

	void GameBoard();
	void GamePieces();
    void KillList(int target);
    void Kill(int index);
	void Play();

	void Save(std::string fileName);

	void Load();
    
    Game();
    ~Game();
	int virtInitialise();
    void virtMouseWheel(int x, int y, int which, int timestamp);

protected:
    bool inGame = false;
    bool generated = false;
    DrawingSurface* pSurface;
	GameTiles tiles;
	AudioManager audio;
    //State *state;
	FilterPointsScaling m_filterScaling;
	FilterPointsTranslation m_filterTranslation;
    //int m_iCurrentItemIndex;

};

