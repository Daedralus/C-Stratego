#pragma once
#include "header.h"
#include "BaseEngine.h"
#include "MyTileManager.h"

class MyDemoA :
	public BaseEngine
{
public: 
	MyDemoA();
	~MyDemoA();
	void virtSetupBackgroundBuffer();
	void virtMouseDown(int iButton, int iX, int iY);
	void virtKeyDown(int iKeyCode);
	int virtInitialiseObjects();


protected:
	MyTileManager tm;

};

