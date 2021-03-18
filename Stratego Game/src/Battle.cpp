#include "header.h"
#include "Battle.h"
#include "BaseEngine.h"
#include "CoordinateMapping.h"
#include "MappableImageObject.h"
#include "ImageObject.h"

// This forces a screen redraw every pass through the loop.
void Battle::virtMainLoopDoBeforeUpdate()
{
	int iOffset = getModifiedTime() / 10;

	rotator.setRotation((double)iOffset / -100.0);
	shifter1.setXShift((double)iOffset);
	shifter2.setYShift((double)iOffset / 2.0);

	this->redrawDisplay();

}

int Battle::virtInitialiseObjects()
{
	// Destroy any existing objects
	destroyOldObjects(true);

	// Add three draggable shapes. Just using the base class objects for this demo but you can subclass them
	createObjectArray(5);
	storeObjectInArray(3, new ImageObject(500, 500, this, "sword.jpg", false, false));

	// Understand what this one does first before looking at the others...
	MappableImageObject* ob = new MappableImageObject(this, 50, 50, this, "sword.jpg", false);
	ob->setTransparencyColour(ob->getPixelColour(0, 0));
	storeObjectInArray(0, ob);

	ob = new MappableImageObject(this, 250, 250, this, "Scimitar.png", false);
	ob->setTransparencyColour(ob->getPixelColour(0, 0));
	storeObjectInArray(1, ob);

	// Check out what happen in virtMainLoopDoBeforeUpdate() to see how the coordinate mapping objects are modified constantly
	ob = new MappableImageObject(&rotator, 450, 450, this, "Scimitar.png", false);
	ob->setTransparencyColour(ob->getPixelColour(0, 0));
	storeObjectInArray(2, ob);

	/*ob = new MappableImageObject(&shifter1, 250, 450, this, "demo.png", false);
	ob->setTransparencyColour(ob->getPixelColour(0, 0));
	storeObjectInArray(3, ob);*/

	//ob = new MappableImageObject(&shifter2, 450, 250, this, "demo.png", false);
	//ob->setTransparencyColour(ob->getPixelColour(0, 0));
	//storeObjectInArray(4, ob);
	setAllObjectsVisible(true);
	return 0;
}

bool Battle::mapCoordinates(double& x, double& y, const SimpleImage& image)
{
	int iOffset = getModifiedTime() / 2;

	if (x < 0) return false;
	if (y < 0) return false;
	if (x >= (image.getWidth() - 0.5)) return false;
	if (y >= (image.getHeight() - 0.5)) return false;

	// Demo 1 - shift x
//	x = ((int)(x + 0.5) + iOffset) % image.getWidth();

	// Demo 2 - shift y
//	y = ((int)(y + 0.5) + iOffset) % image.getHeight();

	// Demo 3 - simple rotation

	// Shift offset to the centre of the image, so we can rotate around centre
	x -= image.getWidth() / 2;
	y -= image.getHeight() / 2;

	// Rotate it
	//double dAngle = (double)iOffset / 100;
	double dAngle = atan(y / (x + 0.0001));
	
	if (x < 0)
		dAngle += M_PI;
	double hyp = ::sqrt(x * x + y * y);
	dAngle += (double)iOffset / 100;
	if (hyp > 60) {
		int fuck = 0;
	}
	x = hyp * ::cos(dAngle);
	y = hyp * ::sin(dAngle);

	if (x > 48) {
		int fuck = 0;
	}
	// Shift offset back to the corner
	x += image.getWidth() / 2;
	y += image.getHeight() / 2;

	

	if (x < 0) return false;
	if (y < 0) return false;
	if (x >= (image.getWidth() - 0.5)) return false;
	if (y >= (image.getHeight() - 0.5)) return false;

	return true;
}
