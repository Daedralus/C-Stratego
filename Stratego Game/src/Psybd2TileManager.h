#pragma once
#include "header.h"
#include "TileManager.h"
class Psybd2TileManager :
	public TileManager
{
public:
	Psybd2TileManager();
	virtual void virtDrawTileAt(
		BaseEngine* pEngine,
		DrawingSurface* pSurface,
		int iMapX, int iMapY,
		int iStartPositionScreenX, int iStartPositionScreenY) const override;
protected:
	Psybd2TileManager* tile;
};

