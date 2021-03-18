#pragma once
#include "header.h"
#include "TileManager.h"
class GameTiles :
	public TileManager
{
public:
	GameTiles();
	virtual void virtDrawTileAt(
		BaseEngine* pEngine,
		DrawingSurface* pSurface,
		int iMapX, int iMapY,
		int iStartPositionScreenX, int iStartPositionScreenY) const override;
protected:
	GameTiles* tile;
};

