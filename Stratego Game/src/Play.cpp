#include "header.h"
#include "Play.h"
#include "BaseEngine.h"
#include "DisplayableObject.h"
#include "ImageObject.h"

void Play::virtSetupBackgroundBuffer() {
	SimpleImage menu = ImageManager::loadImage("menu.jpeg", true);
	menu.renderImage(getBackgroundSurface(), 0, 0, 0, 0,
		menu.getWidth(), menu.getHeight());
}

int Play::virtInitialiseObjects() {
	drawableObjectsChanged();

	// Destroy any existing objects
	destroyOldObjects(true);

	// Creates an array one element larger than the number of objects that you want.
	createObjectArray(3);

	// You MUST set the array entry after the last one that you create to NULL, so that the system knows when to stop.
	storeObjectInArray(0, new ImageObject(1000, 400, this, "fuji.jpg", false, false));
	storeObjectInArray(1, new ImageObject(1000, 600, this, "earth.jpg", false, false));
	setAllObjectsVisible(true);
	return 0;
}

void Play::virtKeyDown(int iKeyCode) {

}

void Play::virtMouseDown(int iButton, int iX, int iY) {
	// TODO: Add your implementation code here.
	if (iButton == SDL_BUTTON_LEFT)
	{
		
	}
}