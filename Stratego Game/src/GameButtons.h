#pragma once
#include "header.h"
#include "Game.h"
#include "DisplayableObject.h"

class GameButtons : 
	public DisplayableObject
{

public:
	GameButtons(BaseEngine* pEngine);

	virtual ~GameButtons(void);

	void virtDraw() override;

private:
	Game* m_pMainEngine;

	// We use one of these to interpolate the position based on a starting and ending position and time.

	// Current position and heading direction on the map
	double m_dSX;
	double m_dSY;
	double m_dX;
	double m_dY;
	DisplayableObject* bObject;
};

