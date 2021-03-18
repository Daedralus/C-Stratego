#include "header.h"
#include "GameButtons.h"
#include "DisplayableObject.h"
#include "BaseEngine.h"

GameButtons::GameButtons(BaseEngine* pEngine)
	: DisplayableObject(pEngine, 250, 50, false) 
{
	bObject = NULL;
	m_dX = m_iCurrentScreenX = m_iDrawWidth;
	m_dY = m_iCurrentScreenY = m_iDrawHeight;
	m_dSX = 0;
	m_dSY = 0;
	setVisible(true);
}

GameButtons::~GameButtons(void)
{
}

void GameButtons::virtDraw() {
	//Play
	getEngine()->drawForegroundRectangle(
		m_iCurrentScreenX / 2 - 125,
		m_iCurrentScreenY / 2 - 300,
		m_iCurrentScreenX / 2 + 125,
		m_iCurrentScreenY / 2 + 250,
		0x00ffff);
	//Rules
	getEngine()->drawForegroundRectangle(
		m_iCurrentScreenX / 2 - 125,
		m_iCurrentScreenY / 2 - 25,
		m_iCurrentScreenX / 2 + 125,
		m_iCurrentScreenY / 2 + 25,
		0x00ffff);
	//Load
	getEngine()->drawForegroundRectangle(
		m_iCurrentScreenX / 2 - 125,
		m_iCurrentScreenY / 2 + 250,
		m_iCurrentScreenX / 2 + 125,
		m_iCurrentScreenY / 2 + 300,
		0x00ffff);
}

