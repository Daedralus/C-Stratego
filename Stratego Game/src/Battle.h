#pragma once
#include "header.h"
#include "BaseEngine.h"
#include "CoordinateMapping.h"
#include "DisplayableObject.h"

class Battle : public BaseEngine, public CoordinateMapping
{
public:
	Battle()
		: rotator(0.0), shifter1(0, 0), shifter2(0, 0)
	{
	
	}

	void Battle::virtMainLoopDoBeforeUpdate();

	int virtInitialiseObjects();

	bool mapCoordinates(double& x, double& y, const SimpleImage& image);


protected:
	CoordinateMappingRotate rotator;
	CoordinateMappingShiftXY shifter1;
	CoordinateMappingShiftXY shifter2;
};

