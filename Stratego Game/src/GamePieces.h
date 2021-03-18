#pragma once
#include "header.h"
#include "DragableImageObject.h"
#include "DisplayableObject.h"
#include "Game.h"
#include "CollisionDetection.h"
#include "DisplayableObjectContainer.h"
#include <Windows.h>


class GamePiece :
	public DragableImageObject
{
public:

	GamePiece::GamePiece(Game* pEngine, std::string strURL, int xStart, int yStart, int level, int team)
		: DragableImageObject(xStart, yStart, pEngine, strURL, true, true)
	{
		oldX = xStart;
		oldY = yStart;
		power = level;
		color = team;
	}

	~GamePiece() {

	}


	/* Override if necessary - Mouse event - mouse button released. Must call notifyObjectsAboutMouse to tell base engine to notify objects, or this will not be called */
	virtual void virtMouseUp(int iButton, int iX, int iY)
	{
		
		//std::cout << "virtMouseUp " << std::to_string(iX) << " " << std::to_string(iY) << std::endl;
		if (m_bIsBeingDragged)
		{
			virtMouseMoved(iX, iY); // Do the drag to the position - redrawing it (calling move prevents needing to copy the code from above)

			//Snap to center of tile by getting its coords
			int newiX = getTileCenterX(iX);
			int newiY = getTileCenterY(iY);

			if ((oldX > 450 && oldX < 1450) && this->color != checkTurn()) {
				snapToPos(oldX, oldY);
				checkFinishDrag(oldX, oldY);
				if (this->color == 0) {
					MessageBox(0, "It is Blue's Turn!", "Error", 0);
				}
				else {
					MessageBox(0, "It is Red's Turn!", "Error", 0);
				}
				return;
			}
			// If out of bounds, in lake or over another unit
			if (newiX == -1 || newiY == -1)
			{
				//Snap piece to old position
				snapToPos(oldX, oldY);
				checkFinishDrag(oldX, oldY);
				return;
			} //Make sure not in lake
			else if (((newiX > 650 && newiX < 850) || (newiX > 1050 && newiX < 1250)) && (newiY > 400 && newiY < 600)) {
				snapToPos(oldX, oldY);
				checkFinishDrag(oldX, oldY);
				return;
			}
			//Block diagonal movement
			if ((oldX > 450 && oldX < 1450) && (oldX != newiX) && (oldY != newiY)) {
				snapToPos(oldX, oldY);
				checkFinishDrag(oldX, oldY);
				MessageBox(0, "Units cannot move diagonally!", "Error", 0);
				return;
			}

			//Ensure flag or bomb cannot be moved
			if ((oldX > 450 && oldX < 1450) && (this->power == 0 || this->power == 1000)) {
				snapToPos(oldX, oldY);
				checkFinishDrag(oldX, oldY);
				MessageBox(0, "Flag and bombs cannot be moved after placement! Please restart the game if you made a mistake while them", "Error", 0);
				return;
			}
			//Ensure units do not travel more than 1 tile except the scout
			if ((oldX > 450 && oldX < 1450) && (this->power != 2) && ((newiX > oldX+150 || newiX < oldX-150) || (newiY > oldY+100 || newiY < oldY-100)))
			{
				snapToPos(oldX, oldY);
				checkFinishDrag(oldX, oldY);
				MessageBox(0, "Only scouts may move more than 1 tile per turn!", "Error", 0);
				return;
			}
			
			//Added custom method to "snapToPos" DragableBaseClassObject
			snapToPos(newiX, newiY);
			checkFinishDrag(newiX, newiY);
			// Ensure tile isn't already used
			int placing = checkCollision();
			if ((oldX < 450 || oldX > 1450) && placing == -2) {
				this->setPosition(oldX, oldY);
				redrawDisplay();
				MessageBox(0, "You cannot place units on an already occupied tile!", "Error", 0);
				return;
			}
			placed = true;

			// 1 = won, 0 = empty tile/loss/tie, -1 = ally, pop back
			// Note that only -1 has special interaction but 1 and 0 are
			// kept just in case of feature additions
			victory = checkCollision();
			if (victory == -1) {
				this->setPosition(oldX, oldY);
				redrawDisplay();
			}
			else {
				if((oldX > 450 && oldX < 1450))
					changeTurn();
				oldX = newiX;
				oldY = newiY;
			}
			// Can set the new tile to be old once all conditions satisfied	
		}
	}

	int GamePiece::checkTurn() {
		Game p;
		int turn = p.getTurn();
		return turn;
	}

	void GamePiece::changeTurn() {
		Game p;
		p.changeTurn();
	}

	int GamePiece::getTileCenterX(int iX) {
		Game p;
		int y;
		y = p.getTileCenterX(iX);
		if (y == -1)
			return -1;
		return y;
	}
	int GamePiece::getTileCenterY(int iY) {
		Game p;
		int y;
		y = p.getTileCenterY(iY);
		if (y == -1)
			return -1;
		return y;
	}

	// Draw the object - override to implement the actual drawing of the correct object
	virtual void virtDraw()
	{
		if (isVisible())
		{
			image.renderImageWithMask(getEngine()->getForegroundSurface(), 0, 0, m_iCurrentScreenX + m_iStartDrawPosX, m_iCurrentScreenY + m_iStartDrawPosY, m_iDrawWidth, m_iDrawHeight);
		}
	}

	// Overridden, to call redrawRectangle rather than redrawScreen!
	virtual void doDragRedraw() override
	{
		redrawRectangle(); // It moved so do a redraw!
	}

	// Return the width of the loaded image
	int getImageWidth() { return m_iWidthInImage; }

	// Return the height of the loaded image
	int getImageHeight() { return m_iHeightInImage; }

	int checkCollision()
	{
		for (int i = 0; i < collisions.size(); i++) {
			// Check for collision among all other tiles. 
			// Note that if game is played properly, there can only be
			// one piece present at a tile and therefore the for can be exited.
			if (GamePiece::checkCollision(
				this->getXCentre() - 40,
				this->getXCentre() + 40,
				this->getYCentre() - 40,
				this->getYCentre() + 40,
				collisions[i]->getXCentre() - 40,
				collisions[i]->getXCentre() + 40,
				collisions[i]->getYCentre() - 40,
				collisions[i]->getYCentre() + 40)) {

				//Ensure new piece is not entering occupied slot
				if (!placed) {
					return -2;
				}
				std::cout << "BATTLE!";
				// Conditions: Ally, Bomb, Flag, Win, Tie, Loss
				// Remember "this" attacks, therefore miner vs bomb easier

				// Ally check
				if (collisions[i]->color == this->color) {
					return -1;
				}
				// Victory check
				if (this->power > 0 && collisions[i]->power == 0) {
					//collisions[i]->setVisible(false);
					collisions[i]->setPosition(700, 500);
					if (this->color == 1) {
						MessageBox(0, "Blue Wins!", "Victory!", 0);
					}
					else {
						MessageBox(0, "Red Wins!", "Victory!", 0);
					}
					return 0;
				}
				// Miner on bomb check
				if (this->power == 3 && collisions[i]->power == 1000) {
					collisions[i]->setVisible(false);
					collisions[i]->setPosition(-100, -100);
					return 0;
				}
				// Spy on Marshall check
				if (this->power == 1 && collisions[i]->power == 10) {
					collisions[i]->setVisible(false);
					collisions[i]->setPosition(-100, -100);
					return 0;
				}
				// Tie
				if (collisions[i]->power == this->power) {
					this->setVisible(false);
					collisions[i]->setVisible(false);
					collisions[i]->setPosition(-100, -100);
					this->setPosition(2000, 1500);
					return 0;
				}
				// Loss
				if (collisions[i]->power > this->power) {
					this->setVisible(false);
					this->setPosition(-100, -100);
					return 0;
				}
				// Win
				if (collisions[i]->power < this->power) {
					collisions[i]->setVisible(false);
					collisions[i]->setPosition(-100, -100);
					return 1;
				}
				return 0;
			}
		}

	}
	// CollisionDetection.h was not working as intended so swapped to this
	bool GamePiece::checkCollision(int x1l, int x1r, int y1t, int y1b, int x2l, int x2r, int y2t, int y2b) {

		if ((x1l == x2l) && (x1r == x2r) && (y1b == y2b) && (y1t == y2t))
			return true;
		else
			return false;
	}

	void GamePiece::setCollisionObject(GamePiece* pObject) {
		collisions.push_back(pObject);
		count++;
	}

	void GamePiece::forceKillUpdate() {
		keybd_event(VK_NUMLOCK,
			0x45,
			KEYEVENTF_EXTENDEDKEY | 0,
			0);

		// Simulate a key release
		keybd_event(VK_NUMLOCK,
			0x45,
			KEYEVENTF_EXTENDEDKEY | KEYEVENTF_KEYUP,
			0);
	}

private:
	GamePiece* piece;
	//Game* game;
protected:
	bool placed = false;
	int count = 0;
	int victory;
	std::vector<GamePiece*> collisions;
	int color;
	int power;
	int oldX;
	int oldY;
	bool m_bMoved = false;
	int m_iXInImage;
	int m_iYInImage;
	int m_iWidthInImage;
	int m_iHeightInImage;
	int m_iRotation;
};