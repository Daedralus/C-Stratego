#pragma once
#include "header.h"
#include "BaseEngine.h"
#include "Psybd2TileManager.h"
#include "Psybd2ObjectA.h"
#include "Psybd2ObjectB.h"


class Psybd2Engine :
	public BaseEngine
{
public:
	Psybd2Engine();
	~Psybd2Engine();
	void virtSetupBackgroundBuffer();
	void virtDoUpdate();

protected: 
	Psybd2TileManager load;

public:
	void virtKeyDown(int iKeyCode);
	int virtInitialiseObjects() override;
	void virtDrawStringsUnderneath();

	void virtDrawStringsOnTop();
	void virtMouseDown(int iButton, int iX, int iY);
	void loader();

};

