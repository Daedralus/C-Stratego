#include "header.h"
#include "BaseEngine.h"
#include "DisplayableObject.h"
#include "CollisionDetection.h"
#include "Psybd2Engine.h"
#include "Psybd2ObjectA.h"

Psybd2ObjectB::Psybd2ObjectB(BaseEngine* pEngine)
	: DisplayableObject(pEngine, 100, 50, false)
{
		bObject = NULL;
	m_dX = m_iCurrentScreenX = m_iDrawWidth;
	m_dY = m_iCurrentScreenY = m_iDrawHeight;
	m_dSX = 3.5;
	m_dSY = 3.5;
	setVisible(true);
	//std::cout << "X: " << m_dX << "\n" << "Y: " << m_dY << "\n";	
}

void Psybd2ObjectB::virtDraw() {
	getEngine()->drawForegroundRectangle(
		m_iCurrentScreenX - m_iDrawWidth / 2 + 1,
		m_iCurrentScreenY - m_iDrawHeight / 2 + 1,
		m_iCurrentScreenX + m_iDrawWidth / 2 - 1,
		m_iCurrentScreenY + m_iDrawHeight / 2 - 1,
		0x00ffff);
}

void Psybd2ObjectB::virtDoUpdate(int iCurrentTime) {
	if (getEngine()->isPaused())
		return; // Do nothing if paused

	// Alter position for speed
	m_dX += m_dSX;
	m_dY += m_dSY;

	// Check for bounce off the edge
	if ((m_dX + m_iStartDrawPosX) < 0)
	{
		m_dX = -m_iStartDrawPosX;
		if (m_dSX < 0)
			m_dSX = -m_dSX;
	}
	if ((m_dX + m_iStartDrawPosX + m_iDrawWidth) > (getEngine()->getWindowWidth() - 1))
	{
		m_dX = getEngine()->getWindowWidth() - 1 - m_iStartDrawPosX - m_iDrawWidth;
		if (m_dSX > 0)
			m_dSX = -m_dSX;
	}
	if ((m_dY + m_iStartDrawPosY) < 0)
	{
		m_dY = -m_iStartDrawPosY;
		if (m_dSY < 0)
			m_dSY = -m_dSY;
	}
	if ((m_dY + m_iStartDrawPosY + m_iDrawHeight) > (getEngine()->getWindowHeight() - 1))
	{

		m_dY = getEngine()->getWindowHeight() - 1 - m_iStartDrawPosY - m_iDrawHeight;
		if (m_dSY > 0)
			m_dSY = -m_dSY;
	}

	if (bObject != NULL) {
		if (CollisionDetection::checkRectangles(
			this->getXCentre() - 100,
			this->getXCentre() + 100,
			this->getYCentre() - 100,
			this->getYCentre() + 100,
			bObject->getXCentre(),
			bObject->getXCentre(),
			bObject->getYCentre(),
			bObject->getYCentre()))
		{
			if (m_dSX > 0)
				m_dSX = -m_dSX;
		}
	}

	m_iCurrentScreenX = (int)(m_dX + 0.5);
	m_iCurrentScreenY = (int)(m_dY + 0.5);
	redrawDisplay();
}

void Psybd2ObjectB::setCollisionObject(DisplayableObject* pObject) {
	bObject = pObject;
}