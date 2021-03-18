#pragma once
#include "header.h"
#include "BaseEngine.h"
#include "DisplayableObject.h"
#include "CollisionDetection.h"
#include "Psybd2Engine.h"
#include "Psybd2ObjectB.h"
 
class Psybd2ObjectA :
	public DisplayableObject
{
private:
	double m_dSX;
	double m_dSY;
	double m_dX;
	double m_dY;
	DisplayableObject* bObject;

public:
	Psybd2ObjectA(BaseEngine* pEngine);
	void virtDraw() override;
	void virtDoUpdate(int iCurrentTime) override;
	void setCollisionObject(DisplayableObject* pObject);
	void updateBar();
};

