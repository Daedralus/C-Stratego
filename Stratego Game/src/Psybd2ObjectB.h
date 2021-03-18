#pragma once
#include "header.h"
#include "BaseEngine.h"
#include "DisplayableObject.h"
#include "CollisionDetection.h"
#include "Psybd2Engine.h"
#include "Psybd2ObjectA.h"

class Psybd2ObjectB :
	public DisplayableObject
{
private:
	double m_dSX;
	double m_dSY;
	double m_dX;
	double m_dY;
	DisplayableObject* bObject;

public:
	Psybd2ObjectB(BaseEngine* pEngine);
	void virtDraw() override;	
	void virtDoUpdate(int iCurrentTime) override;
	void setCollisionObject(DisplayableObject* pObject);
};

