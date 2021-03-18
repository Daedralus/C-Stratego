#include "header.h"
#include "Menu.h"
#include "BaseEngine.h"
#include "DisplayableObject.h"
#include "ImageObject.h"
#include "Context.h"

void Menu::virtSetupBackgroundBuffer() {
	//fillBackground(0x000000);
	SimpleImage menu = ImageManager::loadImage("menu.jpeg", true);
	menu.renderImage(getBackgroundSurface(), 0, 0, 0, 0,
		1900, 1000);
		//menu.getWidth(), menu.getHeight());
}

int Menu::virtInitialiseObjects() {
	drawableObjectsChanged();

	// Destroy any existing objects
	destroyOldObjects(true);

	// Creates an array one element larger than the number of objects that you want.
	createObjectArray(3);

	// You MUST set the array entry after the last one that you create to NULL, so that the system knows when to stop.
	storeObjectInArray(0, new ImageObject(1000, 400, this, "play.png", false, false));
	storeObjectInArray(1, new ImageObject(1000, 600, this, "rules.png", false, false));
	setAllObjectsVisible(true);
	return 0;
}

void Menu::virtKeyDown(int iKeyCode) {
	switch (iKeyCode)
	{
	case SDLK_ESCAPE: // End program when escape is pressed
		setExitWithCode(0);
		break;
	case SDLK_SPACE: // SPACE Pauses
		this->context_->TransitionTo(new Play);
		break;
	}
}

void Menu::virtMouseDown(int iButton, int iX, int iY) {
	// TODO: Add your implementation code here.
	if (iButton == SDL_BUTTON_LEFT)
	{
		// Button Region
		if (iX >= 875 && iX <= 1125) {
			//Find specific button via y coords, do nothing otherwise		
			// Play
			if (iY >= 375 && iY <= 425) {
				//play state
				this->context_->TransitionTo(new Play);
			}
			if (iY >= 575 && iY <= 625) {
				//rules state
				redrawDisplay();
			}
		}
	}
}