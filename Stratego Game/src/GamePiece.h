//#pragma once
//#include "header.h"
//#include "DragableImageObject.h"
//#include "DisplayableObject.h"
//#include "Game.h"
//#include "CollisionDetection.h"
//#include "DisplayableObjectContainer.h"
//#include <Windows.h>
//
//
//class GamePiece :
//	public DragableImageObject
//{
//public:
//
//	GamePiece::GamePiece(Game* pEngine, std::string strURL,int xStart, int yStart, int level, int team)
//		: DragableImageObject(xStart, yStart, pEngine, strURL, true, true)
//	{
//		oldX = xStart;
//		oldY = yStart;
//		power = level;
//		color = team;
//	}
//
//	~GamePiece() {
//
//	}
//
//
//	/* Override if necessary - Mouse event - mouse button released. Must call notifyObjectsAboutMouse to tell base engine to notify objects, or this will not be called */
//	virtual void virtMouseUp(int iButton, int iX, int iY)
//	{
//		//std::cout << "virtMouseUp " << std::to_string(iX) << " " << std::to_string(iY) << std::endl;
//		if (m_bIsBeingDragged)
//		{
//			virtMouseMoved(iX, iY); // Do the drag to the position - redrawing it (calling move prevents needing to copy the code from above)
//						
//			//Snap to center of tile by getting its coords
//			int newiX = getTileCenterX(iX);
//			int newiY = getTileCenterY(iY);
//			// If out of bounds, in lake or over another unit
//			if (newiX == -1 || newiY == -1)
//			{
//				//Snap piece to lake so that player fixes position for now
//				snapToPos(oldX, oldY);
//				checkFinishDrag(oldX, oldY);
//			} else if (((newiX > 650 && newiX < 850) || (newiX > 1050 && newiX < 1250)) && (newiY > 400 && newiY < 600)) {
//				snapToPos(oldX, oldY);
//				checkFinishDrag(oldX, oldY);
//			} else {
//				//Added custom method to DragableBaseClassObject
//				snapToPos(newiX, newiY);
//				checkFinishDrag(newiX, newiY);
//			}		
//			// 1 = won, 0 = empty tile/loss/tie, -1 = ally, pop back
//			victory = checkCollision();
//			if (victory == -1) {
//				this->setPosition(oldX, oldY);
//				redrawDisplay();
//			}
//			else {
//				oldX = newiX;
//				oldY = newiY;
//			}
//			// Can set the new tile to be old once all conditions satisfied	
//		}
//	}
//
//	int GamePiece::getTileCenterX(int iX) {
//		Game p;
//		int y;
//		y = p.getTileCenterX(iX);
//		if (y == -1)
//			return -1;
//		return y;
//	}
//	int GamePiece::getTileCenterY(int iY) {
//		Game p;
//		int y;
//		y = p.getTileCenterY(iY);
//		if (y == -1)
//			return -1;
//		return y;
//	}
//
//	// Draw the object - override to implement the actual drawing of the correct object
//	virtual void virtDraw()
//	{
//		if (isVisible())
//		{
//			image.renderImageWithMask(getEngine()->getForegroundSurface(), 0, 0, m_iCurrentScreenX + m_iStartDrawPosX, m_iCurrentScreenY + m_iStartDrawPosY, m_iDrawWidth, m_iDrawHeight);
//		}
//	}
//
//	// Overridden, to call redrawRectangle rather than redrawScreen!
//	virtual void doDragRedraw() override
//	{
//		redrawRectangle(); // It moved so do a redraw!
//	}
//
//	// Return the width of the loaded image
//	int getImageWidth() { return m_iWidthInImage; }
//
//	// Return the height of the loaded image
//	int getImageHeight() { return m_iHeightInImage; }
//
//	int checkCollision()
//	{
//		if (getEngine()->isPaused())
//			return 0;
//		for (int i = 0; i < collisions.size(); i++) {
//			// Check for collision among all other tiles. 
//			// Note that if game is played properly, there can only be
//			// one piece present at a tile and therefore the for can be exited.
//			if (GamePiece::checkCollision(
//				this->getXCentre() - 40,
//				this->getXCentre() + 40,
//				this->getYCentre() - 40,
//				this->getYCentre() + 40,
//				collisions[i]->getXCentre() - 40,
//				collisions[i]->getXCentre() + 40,
//				collisions[i]->getYCentre() - 40,
//				collisions[i]->getYCentre() + 40)) {
//				
//				std::cout << "BATTLE!";	
//				// Conditions: Ally, Bomb, Flag, Win, Tie, Loss
//				// Remember "this" attacks, therefore miner vs bomb easier
//
//				// Ally check
//				if (collisions[i]->color == this->color) {	
//					return -1;
//				}
//				// Miner on bomb check
//				if (this->power == 3 && collisions[i]->power == 1000) {
//					collisions[i]->setVisible(false);
//					collisions[i]->setPosition(0,0);
//				}
//				// Spy on Marshall check
//				if (this->power == 1 && collisions[i]->power == 10) {
//					collisions[i]->setVisible(false);
//					collisions[i]->setPosition(0, 0);
//				}
//				if (collisions[i]->power == this->power) {
//					this->setVisible(false);
//					collisions[i]->setVisible(false);
//					collisions[i]->setPosition(0, 0);
//					this->setPosition(0, 0);
//					return 0;
//				}
//				if (collisions[i]->power > this->power) {
//					this->setVisible(false);
//					this->setPosition(0, 0);
//					return 0;
//				}
//				if (collisions[i]->power < this->power) {
//					collisions[i]->setVisible(false);
//					collisions[i]->setPosition(0, 0);
//					return 1;
//				}
//				return 0;
//			}
//		}
//		
//	}
//	// CollisionDetection.h was not working as intended so swapped to this
//	bool GamePiece::checkCollision(int x1l, int x1r, int y1t, int y1b, int x2l, int x2r, int y2t, int y2b) {
//		
//		if ((x1l == x2l) && (x1r == x2r) && (y1b == y2b) && (y1t == y2t))
//			return true;
//		else
//			return false;
//	}
//
//	void GamePiece::setCollisionObject(GamePiece* pObject) {
//		collisions.push_back(pObject);
//		count++;
//	}
//
//	void GamePiece::forceKillUpdate() {
//		keybd_event(VK_NUMLOCK,
//			0x45,
//			KEYEVENTF_EXTENDEDKEY | 0,
//			0);
//
//		// Simulate a key release
//		keybd_event(VK_NUMLOCK,
//			0x45,
//			KEYEVENTF_EXTENDEDKEY | KEYEVENTF_KEYUP,
//			0);
//	}
//
//private:
//	GamePiece* piece;
//	//Game* game;
//protected:
//	int count = 0;
//	int victory;
//	std::vector<GamePiece*> collisions;
//	int color;
//	int power;
//	int oldX;
//	int oldY;
//	bool m_bMoved = false;
//	int m_iXInImage;
//	int m_iYInImage;
//	int m_iWidthInImage;
//	int m_iHeightInImage;
//	int m_iRotation;
//};
//
