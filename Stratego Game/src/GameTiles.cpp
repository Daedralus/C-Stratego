#include "header.h"
#include "GameTiles.h"


GameTiles::GameTiles()
	: TileManager(100, 100, 10, 10)
{
}

void GameTiles::virtDrawTileAt(BaseEngine* pEngine,
	DrawingSurface* pSurface,
	int iMapX, int iMapY,
	int iStartPositionScreenX,
	int iStartPositionScreenY) const
{
	// Create tile borders by using mini-rectangles for each side.
	// Originally was using drawLine, but the borders were too thin.
	unsigned int iColour = 0x00f000;
	unsigned int black = 0x000000;

	// All
	/*pSurface->drawRectangle(iStartPositionScreenX,
		iStartPositionScreenY,
		iStartPositionScreenX + getTileWidth() - 1,
		iStartPositionScreenY + getTileHeight() -1,
		iColour);*/

	// Top Border
	pSurface->drawRectangle(iStartPositionScreenX, 
		iStartPositionScreenY, 
		iStartPositionScreenX + getTileWidth() - 1,
		iStartPositionScreenY + 3,
		iColour);

	// Bottom Border
	pSurface->drawRectangle(iStartPositionScreenX,
		iStartPositionScreenY + getTileHeight(),
		iStartPositionScreenX + getTileWidth() - 1,
		iStartPositionScreenY + getTileHeight() - 3,
		iColour);

	// Left Border
	pSurface->drawRectangle(iStartPositionScreenX,
		iStartPositionScreenY,
		iStartPositionScreenX + 3,
		iStartPositionScreenY + getTileHeight() - 1,
		iColour);

	// Right Border
	pSurface->drawRectangle(iStartPositionScreenX + getTileWidth(),
		iStartPositionScreenY,
		iStartPositionScreenX + getTileWidth() - 3,
		iStartPositionScreenY + getTileHeight() -1,
		iColour);
}