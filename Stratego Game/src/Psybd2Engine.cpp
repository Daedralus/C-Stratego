#include "header.h"
#include "ImageManager.h"
#include "Psybd2TileManager.h"
#include "MyObjectA.h"
#include "Psybd2Engine.h"
#include "BaseEngine.h"
#include "ImageObject.h"
#include "BouncingImageObject.h"
#include "DragableImageObject.h"
#include "Psybd2ObjectB.h"
#include "Psybd2ObjectA.h"
#include <Windows.h>
int count = 0;
char buffer[128];
static int bar = -2;
Psybd2Engine::Psybd2Engine() {

}

Psybd2Engine::~Psybd2Engine() {

}

void Psybd2Engine::virtSetupBackgroundBuffer()
{
	// TODO: Add your implementation code here.
		// TODO: Add your implementation code here.
	fillBackground(0x000000);

	SimpleImage image = ImageManager::loadImage("unc.jpg", true);
	image.renderImage(getBackgroundSurface(), 0, 0, 0, 0,
		image.getWidth(), image.getHeight());

	drawBackgroundTriangle(1150, 150, 1150, 50, 1250, 150, 0xFFFF000);
	drawBackgroundTriangle(1150, 150, 1050, 150, 1150, 250, 0xFFFF000);
	drawBackgroundTriangle(1050, 50, 1050, 150, 1150, 50, 0xFFFF000);
	drawBackgroundTriangle(1250, 250, 1150, 250, 1250, 150, 0xFFFF000);

	
	load.setMapValue(10, 1, rand());
	load.setTopLeftPositionOnScreen(550, 650);
	load.drawAllTiles(this, getBackgroundSurface());
}


void Psybd2Engine::virtDoUpdate()
{

}


void Psybd2Engine::virtKeyDown(int iKeyCode)
{
	// TODO: Add your implementation code here.
	switch (iKeyCode)
	{
	case SDLK_ESCAPE: // End program when escape is pressed
		setExitWithCode(0);
		break;
	case SDLK_SPACE: // SPACE Pauses
		if (isPaused())
			unpause();
		else
			pause();
		break;
	case SDLK_UP:
		count++;
		break;
	case SDLK_DOWN:
		count--;
		break;
	case SDLK_NUMLOCKCLEAR:
		if(bar >= 0 && bar < 10)
			load.setAndRedrawMapValueAt(bar, 0, 0xf0, this, getBackgroundSurface());
		break;
	}
}


int Psybd2Engine::virtInitialiseObjects()
{
	drawableObjectsChanged();
	// Destroy any existing objects
	destroyOldObjects(true);

	createObjectArray(11);

	storeObjectInArray(0, new DragableImageObject(100, 400, this, "evil72.jpg", false));
	storeObjectInArray(1, new ImageObject(100, 100, this, "evil72.jpg", false, false));
	storeObjectInArray(2, new DragableImageObject(200, 400, this, "scared72.jpg", false));
	storeObjectInArray(3, new ImageObject(400, 400, this, "scared72.jpg", false, false));
	storeObjectInArray(4, new DragableImageObject(300, 400, this, "majestic72.jpeg", false));
	storeObjectInArray(5, new ImageObject(500, 500, this, "majestic72.jpeg", false, false));
	storeObjectInArray(6, new DragableImageObject(400, 400, this, "derp72.jpeg", false));
	storeObjectInArray(7, new ImageObject(400, 400, this, "derp72.jpeg", false, false));
	//storeObjectInArray(8, new BouncingImageObject(this, "evil72.jpg"));

	Psybd2ObjectA* objA = new Psybd2ObjectA(this);
	Psybd2ObjectB* objB = new Psybd2ObjectB(this);

	objA->setCollisionObject(objB);
	objB->setCollisionObject(objA);

	storeObjectInArray(9, objA);
	storeObjectInArray(10, objB);
	return 0;
}


void Psybd2Engine::virtDrawStringsUnderneath()
{
	// TODO: Add your implementation code here.
	drawForegroundString(550, 10, "Berk's Coursework 3", 0x00ff00, NULL);
	redrawDisplay();

}


void Psybd2Engine::virtDrawStringsOnTop()
{
	// TODO: Add your implementation code here.
	sprintf(buffer, "Count %6d", count);
	drawForegroundString(150, 40, buffer, 0xff00ff, NULL);
	if (bar >= 9) {
		drawForegroundString(550, 620, "Load Complete", 0x00ff00, NULL);
		redrawDisplay();
	}
}


void Psybd2Engine::virtMouseDown(int iButton, int iX, int iY)
{
	// TODO: Add your implementation code here.
	if (iButton == SDL_BUTTON_LEFT)
	{
		if (load.isValidTilePosition(iX, iY)) // Clicked within tiles?
		{
			int mapX = load.getMapXForScreenX(iX); // Which column?
			int mapY = load.getMapYForScreenY(iY); // Which row?
			load.setAndRedrawMapValueAt(mapX, mapY, 0xf0, this, getBackgroundSurface());
			redrawDisplay(); // Force background to be redrawn to foreground
		}
	}
}


void Psybd2Engine::loader()
{
	
	// TODO: Add your implementation code here.
	bar++;

	// Simulate a key press
	keybd_event(VK_NUMLOCK,
		0x45,
		KEYEVENTF_EXTENDEDKEY | 0,
		0);

	// Simulate a key release
	keybd_event(VK_NUMLOCK,
		0x45,
		KEYEVENTF_EXTENDEDKEY | KEYEVENTF_KEYUP,
		0);
	//std::cout << "bar:" << bar << std::endl;
}
