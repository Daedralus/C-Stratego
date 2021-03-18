#pragma once
#include "header.h"
#include "BaseEngine.h"
#include "DisplayableObject.h"
class MyObjectA :
	public DisplayableObject
{
public:
	MyObjectA(BaseEngine* pEngine);
	~MyObjectA();
	void virtDraw();
	void virtDoUpdate(int iCurrentTime);
};

