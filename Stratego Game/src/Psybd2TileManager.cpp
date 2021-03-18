#include "header.h"
#include "Psybd2TileManager.h"
#include "TileManager.h"

Psybd2TileManager::Psybd2TileManager()
	: TileManager(75, 25, 10, 1)
{
}

void Psybd2TileManager::virtDrawTileAt(BaseEngine* pEngine,
	DrawingSurface* pSurface,
	int iMapX, int iMapY,
	int iStartPositionScreenX,
	int iStartPositionScreenY) const 
{
	int iMapValue = getMapValue(iMapX, iMapY); // which was set to result of rand()
	unsigned int iColour = (unsigned int)((iMapValue & 0xf00) << 12) // red
		+ (unsigned int)((iMapValue & 0xf0) << 8) // green
		+ (unsigned int)((iMapValue & 0xf) << 4); // blue
	pSurface->drawRectangle(
		iStartPositionScreenX, // Left
		iStartPositionScreenY, // Top
		iStartPositionScreenX + getTileWidth() - 1, // Right
		iStartPositionScreenY + getTileHeight() - 1, // Bottom
		iColour);
}