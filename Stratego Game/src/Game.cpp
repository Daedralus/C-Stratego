#include "header.h"
#include "Game.h"
#include "GameButtons.h"
#include "GameTiles.h"
#include "ImageObject.h"
#include "SDL_audio.h"
#include "State.h"
#include "Context.h"
#include "Menu.h"
#include "Play.h"
#include "GamePieces.h"
#include "DragableImageObject.h"
#include "CoordinateMapping.h"
#include "DisplayableObjectContainer.h"
#include <Windows.h>
#include <fstream>

std::vector<char> text;
std::vector<GamePiece*> pieces;
int update = -1;
int turn = 0;

Game::Game() : m_filterScaling(0, 0, this), m_filterTranslation(0, 0, &m_filterScaling)
{
	SDL_Init(SDL_INIT_EVERYTHING);
	audio.load("menu.wav");
	audio.play();
}

Game::~Game() {

}

int Game::virtInitialise()
{
	// These only need to be called once, so I didn't want to put them in functions which are called multiple times, even though I now need to override this method too
	getBackgroundSurface()->setDrawPointsFilter(&m_filterTranslation);
	getForegroundSurface()->setDrawPointsFilter(&m_filterTranslation);

	// Call base class version
	return BaseEngine::virtInitialise();
}

void Game::virtMouseWheel(int x, int y, int which, int timestamp)
{
	if (!inGame) {
		int iOldCentreX = convertClickedToVirtualPixelXPosition(this->getWindowWidth() / 2);
		int iOldCentreY = convertClickedToVirtualPixelYPosition(this->getWindowHeight() / 2);

		if (y < 0)
			m_filterScaling.compress();
		else if (y > 0)
			m_filterScaling.stretch();

		int iNewCentreX = convertClickedToVirtualPixelXPosition(this->getWindowWidth() / 2);
		int iNewCentreY = convertClickedToVirtualPixelYPosition(this->getWindowHeight() / 2);

		// Apply a translation to offset so it appears to have zoomed on the centre.
		m_filterTranslation.changeOffset(iNewCentreX - iOldCentreX, iNewCentreY - iOldCentreY);
		redrawDisplay(); 
	}
}

void Game::virtKeyDown(int iKeyCode) {
	// TODO: Add your implementation code here.
	switch (iKeyCode)
	{
	case SDLK_ESCAPE: // End program when escape is pressed
		setExitWithCode(0);
		break;
	case SDLK_SPACE: // SPACE Pauses
		if (!inGame) {
			m_filterScaling.setStretch(-1, -1);
			m_filterTranslation.setOffset(950, 500);
			m_filterScaling.stretch();
			m_filterTranslation.setOffset(0, 0);
		}	
		if (isPaused())
			unpause();
		else
			pause();
		break;
	case SDLK_LEFT:
		if (!inGame) {
			m_filterTranslation.changeOffset(-10, 0);
			redrawDisplay();
		}
		break;
	case SDLK_RIGHT:
		if (!inGame) {
			m_filterTranslation.changeOffset(10, 0);
			redrawDisplay();
		}
		break;
	case SDLK_UP:
		if (!inGame) {
			m_filterTranslation.changeOffset(0, -10);
			redrawDisplay();
		}
		break;
	case SDLK_DOWN:
		if (!inGame) {
			m_filterTranslation.changeOffset(0, 10);
			redrawDisplay();
		}
	case SDLK_NUMLOCKCLEAR:
		if (update == -1)
			break;
		Kill(update);
		update = -1;
		break;
	case SDLK_a:
		if (!inGame) {
			text.push_back('a');
			virtDrawStringsOnTop();
		}
		break;
	case SDLK_b:
		if (!inGame) {
			text.push_back('b');
			virtDrawStringsOnTop();
		}
		break;
	case SDLK_c:
		if (!inGame) {
			text.push_back('c');
			virtDrawStringsOnTop();
		}
		break;
	case SDLK_d:
		if (!inGame) {
			text.push_back('d');
			virtDrawStringsOnTop();
		}
		break;
	case SDLK_e:
		if (!inGame) {
			text.push_back('e');
			virtDrawStringsOnTop();
		}
		break;
	case SDLK_f:
		if (!inGame) {
			text.push_back('f');
			virtDrawStringsOnTop();
		}
		break;
	case SDLK_g:
		if (!inGame) {
			text.push_back('g');
			virtDrawStringsOnTop();
		}
		break;
	case SDLK_h:
		if (!inGame) {
			text.push_back('h');
			virtDrawStringsOnTop();
		}
		break;
	case SDLK_i:
		if (!inGame) {
			text.push_back('i');
			virtDrawStringsOnTop();
		}
		break;
	case SDLK_j:
		if (!inGame) {
			text.push_back('j');
			virtDrawStringsOnTop();
		}
		break;
	case SDLK_k:
		if (!inGame) {
			text.push_back('k');
			virtDrawStringsOnTop();
		}
		break;
	case SDLK_l:
		if (!inGame) {
			text.push_back('l');
			virtDrawStringsOnTop();
		}
		break;
	case SDLK_m:
		if (!inGame) {
			text.push_back('m');
			virtDrawStringsOnTop();
		}
		break;
	case SDLK_n:
		if (!inGame) {
			text.push_back('n');
			virtDrawStringsOnTop();
		}
		break;
	case SDLK_o:
		if (!inGame) {
			text.push_back('o');
			virtDrawStringsOnTop();
		}
		break;
	case SDLK_p:
		if (!inGame) {
			text.push_back('p');
			virtDrawStringsOnTop();
		}
		break;
	case SDLK_q:
		if (!inGame) {
			text.push_back('q');
			virtDrawStringsOnTop();
		}
		break;
	case SDLK_r:
		if (!inGame) {
			text.push_back('r');
			virtDrawStringsOnTop();
		}
		break;
	case SDLK_s:
		if (!inGame) {
			text.push_back('s');
			virtDrawStringsOnTop();
		}
		if (inGame) {
			Save("whatever");
		}
		break;
	case SDLK_t:
		if (!inGame) {
			text.push_back('t');
			virtDrawStringsOnTop();
		}
		break;
	case SDLK_u:
		if (!inGame) {
			text.push_back('u');
			virtDrawStringsOnTop();
		}
		break;
	case SDLK_v:
		if (!inGame) {
			text.push_back('v');
			virtDrawStringsOnTop();
		}
		break;
	case SDLK_w:
		if (!inGame) {
			text.push_back('w');
			virtDrawStringsOnTop();
		}
		break;
	case SDLK_x:
		if (!inGame) {
			text.push_back('x');
			virtDrawStringsOnTop();
		}
		break;
	case SDLK_y:
		if (!inGame) {
			text.push_back('y');
			virtDrawStringsOnTop();
		}
		break;
	case SDLK_z:
		if (!inGame) {
			text.push_back('z');
			virtDrawStringsOnTop();
		}
		break;
	case SDLK_BACKSPACE:
		if (!inGame) {
			text.pop_back();
			virtDrawStringsOnTop();
		}
	}	
}

void Game::virtDrawStringsOnTop() {
	lockBackgroundForDrawing();
	int size = text.size();
	std::string string(text.begin(), text.end());
	const char* input = string.c_str();
	if (size == 0)
		input = " ";
	drawForegroundString(900, 300, input, 0x00ff00, NULL);
	unlockBackgroundForDrawing();
	redrawDisplay();
}

int Game::getTurn() {
	return turn;
}

void Game::changeTurn() {
	if (turn == 0) {
		turn = 1;
		return;
	}
	if (turn == 1)
		turn = 0;
}

void Game::virtSetupBackgroundBuffer() {
	SimpleImage menu = ImageManager::loadImage("menu.jpeg", true);
	menu.renderImage(getBackgroundSurface(), 0, 0, 0, 0,
		menu.getWidth(), menu.getHeight());

}

int Game::virtInitialiseObjects() {
	// Record the fact that we are about to change the array - so it doesn't get used elsewhere without reloading it
	drawableObjectsChanged();
	// Destroy any existing objects
	destroyOldObjects(true);
	// Creates an array one element larger than the number of objects that you want.
	createObjectArray(4);
	// You MUST set the array entry after the last one that you create to NULL, so that the system knows when to stop.	
	// BUTTONS
	storeObjectInArray(0, new ImageObject(950, 400, this, "play2.png", false, false));
	storeObjectInArray(1, new ImageObject(950, 600, this, "rules.png", false, false));
	storeObjectInArray(2, new ImageObject(950, 800, this, "load.jpg", false, false));
	//storeObjectInArray(2, new ImageObject(950, 600, this, "rules.png", false, false));
	//storeObjectInArray(3, new ImageObject(950, 600, this, "rules.png", false, false));

	// Make everything invisible to start with
	setAllObjectsVisible(true);
	return 0;
}

void Game::virtMouseDown(int iButton, int iX, int iY)
{
	// TODO: Add your implementation code here.
	if (iButton == SDL_BUTTON_LEFT)
	{
		// Button Region - Will not be checked once in game.
		if (iX >= 875 && iX <= 1125 && !inGame) {
			//Find specific button via y coords, do nothing otherwise		
			// Play
			if (iY >= 375 && iY <= 425) {
				//play state
				// Simulate a key press
				forceResetScale();
				inGame = true;
				text.empty();
				text.resize(0);
				virtDrawStringsOnTop();
				destroyOldObjects(true);
				Play();			
			}
			//Rules
			if (iY >= 575 && iY <= 625) {
				//rules state
				int lines = 0;
				std::string line;
				LPCSTR text;
				std::string final;
				std::ifstream rules;
				std::vector<std::string> vect;
				rules.open("rules.txt");
				if (!rules) {
					std::cout << "Error, couldn't find file";
					return;
				}
				while (std::getline(rules, line)) {
					vect.push_back(line);
					lines++;
				}
				for (int j = 0; j < lines; j++) {
					final = final + "\n" + vect[j];
				}
				text = final.c_str();
				rules.close();
				std::cout << text << std::endl;
				MessageBox(0, text, "Rules", 0);
				redrawDisplay();
			}
			//Load
			if (iY >= 775 && iY <= 825) {
				forceResetScale();
				inGame = true;
				text.empty();
				text.resize(0);
				virtDrawStringsOnTop();
				destroyOldObjects(true);
				Load();
			}
		}
	}
}

void Game::forceResetScale() {
	m_filterScaling.setStretch(-1, -1);
	m_filterTranslation.setOffset(950, 500);
	m_filterScaling.stretch();
	m_filterTranslation.setOffset(0, 0);
}

// Snap Dragged Objects to Tile
int Game::getTileCenterX(int iX) {
	iX -= 450;
	int mapX = tiles.getMapXForScreenX(iX);
	// Ensure within tiles
	if (mapX > -1 && mapX < 10) {
		//Adjust to center of horizontal tile
		mapX = mapX * 100 + 460;
		//Adjust to center of vertical tile		
		return mapX;
	}
	return -1;
}
int Game::getTileCenterY(int iY) {
	int mapY = tiles.getMapXForScreenX(iY);
	//Adjust to center of horizontal tile
	
	if (mapY > -1 && mapY < 10) {
		mapY = mapY * 100 + 10;
		return mapY;
	}
	//Adjust to center of vertical tile		
	return -1;
}

// Function to handle game board creation
void Game::GameBoard() {
	//Handle Red Side
	tiles.setTopLeftPositionOnScreen(450, 0);
	tiles.drawSomeTiles(this, getBackgroundSurface(), 0, 0, 10, 4);
	//Handle Blue Side
	tiles.setTopLeftPositionOnScreen(450, 600);
	tiles.drawSomeTiles(this, getBackgroundSurface(), 0, 0, 10, 4);
	//Handle Passage 1
	tiles.setTopLeftPositionOnScreen(450, 400);
	tiles.drawSomeTiles(this, getBackgroundSurface(), 0, 0, 2, 2);
	//Handle Passage 2
	tiles.setTopLeftPositionOnScreen(850, 400);
	tiles.drawSomeTiles(this, getBackgroundSurface(), 0, 0, 2, 2);
	//Handle Passage 3
	tiles.setTopLeftPositionOnScreen(1250, 400);
	tiles.drawSomeTiles(this, getBackgroundSurface(), 0, 0, 2, 2);
	//Reset the top left to correct value
	tiles.setTopLeftPositionOnScreen(450, 0);
}

void Game::GamePieces() {
	//WELCOME TO THE HORRENDOUSLY LARGE ARRAY AND COLLISION SETUP!

	drawableObjectsChanged();
	// Destroy any existing objects
	destroyOldObjects(true);
	// Creates an array one element larger than the number of objects that you want.
	createObjectArray(200);
	// Main Loop for player count
	// Sub loops for each players pieces
	// Flag 1
	GamePiece* bf = new GamePiece(this, "bf.png", 0, 0, 0, 1);
	pieces.push_back(bf);
	bf->setVisible(true);
	storeObjectInArray(0, bf);
	// Spy 1
	GamePiece* bs = new GamePiece(this, "bs.png", 100, 0, 1, 1);
	bs->setVisible(true);
	pieces.push_back(bs);

	storeObjectInArray(1, bs);
	// Marshall 1
	GamePiece* b1 = new GamePiece(this, "b1.png", 200, 0, 10, 1);
	pieces.push_back(b1);

	storeObjectInArray(2, b1);
	// General 1 
	GamePiece* b2 = new GamePiece(this, "b2.png", 300, 0, 9, 1);
	pieces.push_back(b2);

	storeObjectInArray(3, b2);
	// Colonels 2
	GamePiece* b3a = new GamePiece(this, "b3.png", 0, 100, 8, 1);
	GamePiece* b3b = new GamePiece(this, "b3.png", 100, 100, 8, 1);
	pieces.push_back(b3a);
	pieces.push_back(b3b);

	storeObjectInArray(4, b3a);
	storeObjectInArray(5, b3b);
	// Majors 3
	GamePiece* b4a = new GamePiece(this, "b4.png", 200, 100, 7, 1);
	GamePiece* b4b = new GamePiece(this, "b4.png", 300, 100, 7, 1);
	GamePiece* b4c = new GamePiece(this, "b4.png", 0, 200, 7, 1);
	pieces.push_back(b4a);
	pieces.push_back(b4b);
	pieces.push_back(b4c);
	storeObjectInArray(6, b4a);
	storeObjectInArray(7, b4b);
	storeObjectInArray(8, b4c);
	// Captains 4
	GamePiece* b5a = new GamePiece(this, "b5.png", 100, 200, 6, 1);
	GamePiece* b5b = new GamePiece(this, "b5.png", 200, 200, 6, 1);
	GamePiece* b5c = new GamePiece(this, "b5.png", 300, 200, 6, 1);
	GamePiece* b5d = new GamePiece(this, "b5.png", 0, 300, 6, 1);
	pieces.push_back(b5a);
	pieces.push_back(b5b);
	pieces.push_back(b5c);
	pieces.push_back(b5d);

	storeObjectInArray(9, b5a);
	storeObjectInArray(10, b5b);
	storeObjectInArray(11, b5c);
	storeObjectInArray(12, b5d);
	// Lieutenants 4
	GamePiece* b6a = new GamePiece(this, "b6.png", 100, 300, 5, 1);
	GamePiece* b6b = new GamePiece(this, "b6.png", 200, 300, 5, 1);
	GamePiece* b6c = new GamePiece(this, "b6.png", 300, 300, 5, 1);
	GamePiece* b6d = new GamePiece(this, "b6.png", 0, 400, 5, 1);
	pieces.push_back(b6a);
	pieces.push_back(b6b);
	pieces.push_back(b6c);
	pieces.push_back(b6d);

	storeObjectInArray(13, b6a);
	storeObjectInArray(14, b6b);
	storeObjectInArray(15, b6c);
	storeObjectInArray(16, b6d);
	// Sergeants 4
	GamePiece* b7a = new GamePiece(this, "b7.png", 100, 400, 4, 1);
	GamePiece* b7b = new GamePiece(this, "b7.png", 200, 400, 4, 1);
	GamePiece* b7c = new GamePiece(this, "b7.png", 300, 400, 4, 1);
	GamePiece* b7d = new GamePiece(this, "b7.png", 0, 500, 4, 1);
	pieces.push_back(b7a);
	pieces.push_back(b7b);
	pieces.push_back(b7c);
	pieces.push_back(b7d);

	storeObjectInArray(17, b7a);
	storeObjectInArray(18, b7b);
	storeObjectInArray(19, b7c);
	storeObjectInArray(20, b7d);
	// Miners 5
	GamePiece* b8a = new GamePiece(this, "b8.png", 100, 500, 3, 1);
	GamePiece* b8b = new GamePiece(this, "b8.png", 200, 500, 3, 1);
	GamePiece* b8c = new GamePiece(this, "b8.png", 300, 500, 3, 1);
	GamePiece* b8d = new GamePiece(this, "b8.png", 0, 600, 3, 1);
	GamePiece* b8e = new GamePiece(this, "b8.png", 100, 600, 3, 1);
	pieces.push_back(b8a);
	pieces.push_back(b8b);
	pieces.push_back(b8c);
	pieces.push_back(b8d);
	pieces.push_back(b8e);

	storeObjectInArray(21, b8a);
	storeObjectInArray(22, b8b);
	storeObjectInArray(23, b8c);
	storeObjectInArray(24, b8d);
	storeObjectInArray(25, b8e);
	// Scouts 8
	GamePiece* b9a = new GamePiece(this, "b9.png", 200, 600, 2, 1);
	GamePiece* b9b = new GamePiece(this, "b9.png", 300, 600, 2, 1);
	GamePiece* b9c = new GamePiece(this, "b9.png", 0, 700, 2, 1);
	GamePiece* b9d = new GamePiece(this, "b9.png", 100, 700, 2, 1);
	GamePiece* b9e = new GamePiece(this, "b9.png", 200, 700, 2, 1);
	GamePiece* b9f = new GamePiece(this, "b9.png", 300, 700, 2, 1);
	GamePiece* b9g = new GamePiece(this, "b9.png", 0, 800, 2, 1);
	GamePiece* b9h = new GamePiece(this, "b9.png", 100, 800, 2, 1);
	pieces.push_back(b9a);
	pieces.push_back(b9b);
	pieces.push_back(b9c);
	pieces.push_back(b9d);
	pieces.push_back(b9e);
	pieces.push_back(b9f);
	pieces.push_back(b9g);
	pieces.push_back(b9h);

	storeObjectInArray(26, b9a);
	storeObjectInArray(27, b9c);
	storeObjectInArray(28, b9b);
	storeObjectInArray(29, b9d);
	storeObjectInArray(30, b9e);
	storeObjectInArray(31, b9f);
	storeObjectInArray(32, b9g);
	storeObjectInArray(33, b9h);
	// Bombs 6
	GamePiece* bba = new GamePiece(this, "bb.png", 200, 800, 1000, 1);
	GamePiece* bbb = new GamePiece(this, "bb.png", 300, 800, 1000, 1);
	GamePiece* bbc = new GamePiece(this, "bb.png", 0, 900, 1000, 1);
	GamePiece* bbd = new GamePiece(this, "bb.png", 100, 900, 1000, 1);
	GamePiece* bbe = new GamePiece(this, "bb.png", 200, 900, 1000, 1);
	GamePiece* bbf = new GamePiece(this, "bb.png", 300, 900, 1000, 1);
	pieces.push_back(bba);
	pieces.push_back(bbb);
	pieces.push_back(bbc);
	pieces.push_back(bbd);
	pieces.push_back(bbe);
	pieces.push_back(bbf);

	storeObjectInArray(34, bba);
	storeObjectInArray(35, bbb);
	storeObjectInArray(36, bbc);
	storeObjectInArray(37, bbd);
	storeObjectInArray(38, bbe);
	storeObjectInArray(39, bbf);


	// Flag 1
	GamePiece* rf = new GamePiece(this, "rf.png", 1500, 0, 0, 0);
	pieces.push_back(rf);

	storeObjectInArray(40, rf);
	// Spy 1
	GamePiece* rs = new GamePiece(this, "rs.png", 1600, 0, 1, 0);
	pieces.push_back(rs);
	storeObjectInArray(41, rs);
	// Marshall 1
	GamePiece* r1 = new GamePiece(this, "r1.png", 1700, 0, 10, 0);
	pieces.push_back(r1);

	storeObjectInArray(42, r1);
	// General 1 
	GamePiece* r2 = new GamePiece(this, "r2.png", 1800, 0, 9, 0);
	pieces.push_back(r2);

	storeObjectInArray(43, r2);
	// Colonels 2
	GamePiece* r3a = new GamePiece(this, "r3.png", 1500, 100, 8, 0);
	GamePiece* r3b = new GamePiece(this, "r3.png", 1600, 100, 8, 0);
	pieces.push_back(r3a);
	pieces.push_back(r3b);

	storeObjectInArray(44, r3a);
	storeObjectInArray(45, r3b);
	// Majors 3
	GamePiece* r4a = new GamePiece(this, "r4.png", 1700, 100, 7, 0);
	GamePiece* r4b = new GamePiece(this, "r4.png", 1800, 100, 7, 0);
	GamePiece* r4c = new GamePiece(this, "r4.png", 1500, 200, 7, 0);
	pieces.push_back(r4a);
	pieces.push_back(r4b);
	pieces.push_back(r4c);
	storeObjectInArray(46, r4a);
	storeObjectInArray(47, r4b);
	storeObjectInArray(48, r4c);
	// Captains 4
	GamePiece* r5a = new GamePiece(this, "r5.png", 1600, 200, 6, 0);
	GamePiece* r5b = new GamePiece(this, "r5.png", 1700, 200, 6, 0);
	GamePiece* r5c = new GamePiece(this, "r5.png", 1800, 200, 6, 0);
	GamePiece* r5d = new GamePiece(this, "r5.png", 1500, 300, 6, 0);
	pieces.push_back(r5a);
	pieces.push_back(r5b);
	pieces.push_back(r5c);
	pieces.push_back(r5d);
	storeObjectInArray(49, r5a);
	storeObjectInArray(50, r5b);
	storeObjectInArray(51, r5c);
	storeObjectInArray(52, r5d);
	// Lieutenants 4
	GamePiece* r6a = new GamePiece(this, "r6.png", 1600, 300, 5, 0);
	GamePiece* r6b = new GamePiece(this, "r6.png", 1700, 300, 5, 0);
	GamePiece* r6c = new GamePiece(this, "r6.png", 1800, 300, 5, 0);
	GamePiece* r6d = new GamePiece(this, "r6.png", 1500, 400, 5, 0);
	pieces.push_back(r6a);
	pieces.push_back(r6b);
	pieces.push_back(r6c);
	pieces.push_back(r6d);
	storeObjectInArray(53, r6a);
	storeObjectInArray(54, r6b);
	storeObjectInArray(55, r6c);
	storeObjectInArray(56, r6d);
	// Sergeants 4
	GamePiece* r7a = new GamePiece(this, "r7.png", 1600, 400, 4, 0);
	GamePiece* r7b = new GamePiece(this, "r7.png", 1700, 400, 4, 0);
	GamePiece* r7c = new GamePiece(this, "r7.png", 1800, 400, 4, 0);
	GamePiece* r7d = new GamePiece(this, "r7.png", 1500, 500, 4, 0);
	pieces.push_back(r7a);
	pieces.push_back(r7b);
	pieces.push_back(r7c);
	pieces.push_back(r7d);
	storeObjectInArray(57, r7a);
	storeObjectInArray(58, r7b);
	storeObjectInArray(59, r7c);
	storeObjectInArray(60, r7d);
	// Miners 5
	GamePiece* r8a = new GamePiece(this, "r8.png", 1600, 500, 3, 0);
	GamePiece* r8b = new GamePiece(this, "r8.png", 1700, 500, 3, 0);
	GamePiece* r8c = new GamePiece(this, "r8.png", 1800, 500, 3, 0);
	GamePiece* r8d = new GamePiece(this, "r8.png", 1500, 600, 3, 0);
	GamePiece* r8e = new GamePiece(this, "r8.png", 1600, 600, 3, 0);
	pieces.push_back(r8a);
	pieces.push_back(r8b);
	pieces.push_back(r8c);
	pieces.push_back(r8d);
	pieces.push_back(r8e);
	storeObjectInArray(61, r8a);
	storeObjectInArray(62, r8b);
	storeObjectInArray(63, r8c);
	storeObjectInArray(64, r8d);
	storeObjectInArray(65, r8e);
	// Scouts 8
	GamePiece* r9a = new GamePiece(this, "r9.png", 1700, 600, 2, 0);
	GamePiece* r9b = new GamePiece(this, "r9.png", 1800, 600, 2, 0);
	GamePiece* r9c = new GamePiece(this, "r9.png", 1500, 700, 2, 0);
	GamePiece* r9d = new GamePiece(this, "r9.png", 1600, 700, 2, 0);
	GamePiece* r9e = new GamePiece(this, "r9.png", 1700, 700, 2, 0);
	GamePiece* r9f = new GamePiece(this, "r9.png", 1800, 700, 2, 0);
	GamePiece* r9g = new GamePiece(this, "r9.png", 1500, 800, 2, 0);
	GamePiece* r9h = new GamePiece(this, "r9.png", 1600, 800, 2, 0);
	pieces.push_back(r9a);
	pieces.push_back(r9b);
	pieces.push_back(r9c);
	pieces.push_back(r9d);
	pieces.push_back(r9e);
	pieces.push_back(r9f);
	pieces.push_back(r9g);
	pieces.push_back(r9h);
	storeObjectInArray(66, r9a);
	storeObjectInArray(67, r9c);
	storeObjectInArray(68, r9b);
	storeObjectInArray(69, r9d);
	storeObjectInArray(70, r9e);
	storeObjectInArray(71, r9f);
	storeObjectInArray(72, r9g);
	storeObjectInArray(73, r9h);
	// Bombs 6
	GamePiece* rba = new GamePiece(this, "rb.png", 1700, 800, 1000, 0);
	GamePiece* rbb = new GamePiece(this, "rb.png", 1800, 800, 1000, 0);
	GamePiece* rbc = new GamePiece(this, "rb.png", 1500, 900, 1000, 0);
	GamePiece* rbd = new GamePiece(this, "rb.png", 1600, 900, 1000, 0);
	GamePiece* rbe = new GamePiece(this, "rb.png", 1700, 900, 1000, 0);
	GamePiece* rbf = new GamePiece(this, "rb.png", 1800, 900, 1000, 0);
	pieces.push_back(rba);
	pieces.push_back(rbb);
	pieces.push_back(rbc);
	pieces.push_back(rbd);
	pieces.push_back(rbe);
	pieces.push_back(rbf);
	storeObjectInArray(74, rba);
	storeObjectInArray(75, rbb);
	storeObjectInArray(76, rbc);
	storeObjectInArray(77, rbd);
	storeObjectInArray(78, rbe);
	storeObjectInArray(79, rbf);

	/*bf->setCollisionObject(bs);
	bf->setCollisionObject(b1);
	bf->setCollisionObject(b2);
	bs->setCollisionObject(bf);
	bs->setCollisionObject(b1);
	bs->setCollisionObject(b2);
	b1->setCollisionObject(bf);
	b1->setCollisionObject(bs);
	b1->setCollisionObject(r1);
	b1->setCollisionObject(b2);
	b2->setCollisionObject(r1);
	b2->setCollisionObject(bf);
	b2->setCollisionObject(b1);
	b2->setCollisionObject(bs);
	r1->setCollisionObject(b1);
	r1->setCollisionObject(b2);*/


	for (int i = 0; i < 80; i++) {
		GamePiece* temp = pieces[i];
		for (int j = 0; j < 80; j++) {
			if (i != j) {
				GamePiece* target = pieces[j];
				temp->setCollisionObject(target);
			}		
		}
	}
	// You MUST set the array entry after the last one that you create to NULL, so that the system knows when to stop.	
	// BUTTONS
	//storeObjectInArray(0, new ImageObject(950, 400, this, "play.png", false, false));
	//storeObjectInArray(1, new ImageObject(950, 600, this, "rules.png", false, false));
	// Make everything invisible to start with
	setAllObjectsVisible(true);

	//theMostDisgustingMethodEverWrittenPleaseCollapseAndNeverReOpen();
}

void Game::KillList(int target) {
	update = target;
}

void Game::Kill(int index) {
	DisplayableObject* killTarget = getDisplayableObject(index);
	removeDisplayableObject(killTarget);
}

void Game::Play() {
	
	lockBackgroundForDrawing();
	SimpleImage board = ImageManager::loadImage("board.png", true);
	board.renderImage(getBackgroundSurface(), 0, 0, 450, 0,
		board.getWidth(), board.getHeight());
	SimpleImage blue = ImageManager::loadImage("holders.png", true);
	blue.renderImage(getBackgroundSurface(), 0, 0, 0, 0,
		blue.getWidth(), blue.getHeight());
	SimpleImage red = ImageManager::loadImage("holders.png", true);
	red.renderImage(getBackgroundSurface(), 0, 0, 1450, 0,
		red.getWidth(), red.getHeight());
	unlockBackgroundForDrawing();
	GameBoard();
	GamePieces();
	redrawDisplay();
	generated = true;

}

void Game::Save(std::string fileName) {
	std::ofstream outfile("SaveFile.txt");
	std::ofstream turnfile("turn.txt");
	
	for (int i = 0; i < 80; i++) {
		GamePiece* temp = pieces[i];
		int x;
		int y;
		x = temp->getXCentre();
		y = temp->getYCentre();
		outfile << x << " " << y << std::endl;
	}
	turnfile << turn;
	outfile.close();
	MessageBox(0, "Game Saved Successfully", "Success!", 0);
}

// Another version of Game::Play() essentially but more of a singleton at the generation
void Game::Load() {
	std::ifstream turnfile;
	turnfile.open("turn.txt");
	if (!turnfile) {
		std::cout << "Error, couldn't find file\n";
		MessageBox(0, "No save files found, ensure to press 's' while in game to save!", "Load Error", 0);
	}
	while (turnfile >> turn);
	
	std::vector<int> xs;
	std::vector<int> ys;

	int lines = 0;
	std::string line;
	std::string x;
	std::string y;
	int xCoord;
	int yCoord;
	std::ifstream load;
	load.open("SaveFile.txt");
	if (!load) {
		std::cout << "Error, couldn't find file\n";
		MessageBox(0, "No save files found, ensure to press 's' while in game to save!", "Load Error", 0);
		return;
	}
	while (load >> x >> y) {
		xCoord = std::stoi(x);
		yCoord = std::stoi(y);
		xCoord -= 40;
		yCoord -= 40;
		xs.push_back(xCoord);
		ys.push_back(yCoord);
		std::cout << xs[lines] << " " << ys[lines] << std::endl;
		lines++;
	}
	load.close();

	lockBackgroundForDrawing();
	SimpleImage board = ImageManager::loadImage("board.png", true);
	board.renderImage(getBackgroundSurface(), 0, 0, 450, 0,
		board.getWidth(), board.getHeight());
	SimpleImage blue = ImageManager::loadImage("holders.png", true);
	blue.renderImage(getBackgroundSurface(), 0, 0, 0, 0,
		blue.getWidth(), blue.getHeight());
	SimpleImage red = ImageManager::loadImage("holders.png", true);
	red.renderImage(getBackgroundSurface(), 0, 0, 1450, 0,
		red.getWidth(), red.getHeight());
	unlockBackgroundForDrawing();
	GameBoard();
	

	//WELCOME TO THE HORRENDOUSLY LARGE ARRAY AND COLLISION SETUP V2!
	//THIS TIME FEATURING RE-CREATION ON LOADING!
	//Sincere apologies as to how terrible this code is, but this was cutting close to 
	//submission deadline with only a few hours left. Each piece still must be unique after all

	drawableObjectsChanged();
	// Destroy any existing objects
	destroyOldObjects(true);
	// Creates an array one element larger than the number of objects that you want.
	createObjectArray(200);

	// Flag 1
	GamePiece* bf = new GamePiece(this, "bf.png", xs[0], ys[0], 0, 1);
	pieces.push_back(bf);
	bf->setVisible(true);
	storeObjectInArray(0, bf);
	// Spy 1
	GamePiece* bs = new GamePiece(this, "bs.png", xs[1], ys[1], 1, 1);
	bs->setVisible(true);
	pieces.push_back(bs);

	storeObjectInArray(1, bs);
	// Marshall 1
	GamePiece* b1 = new GamePiece(this, "b1.png", xs[2], ys[2], 10, 1);
	pieces.push_back(b1);

	storeObjectInArray(2, b1);
	// General 1 
	GamePiece* b2 = new GamePiece(this, "b2.png", xs[3], ys[3], 9, 1);
	pieces.push_back(b2);

	storeObjectInArray(3, b2);
	// Colonels 2
	GamePiece* b3a = new GamePiece(this, "b3.png", xs[4], ys[4], 8, 1);
	GamePiece* b3b = new GamePiece(this, "b3.png", xs[5], ys[5], 8, 1);
	pieces.push_back(b3a);
	pieces.push_back(b3b);

	storeObjectInArray(4, b3a);
	storeObjectInArray(5, b3b);
	// Majors 3
	GamePiece* b4a = new GamePiece(this, "b4.png", xs[6], ys[6], 7, 1);
	GamePiece* b4b = new GamePiece(this, "b4.png", xs[7], ys[7], 7, 1);
	GamePiece* b4c = new GamePiece(this, "b4.png", xs[8], ys[8], 7, 1);
	pieces.push_back(b4a);
	pieces.push_back(b4b);
	pieces.push_back(b4c);
	storeObjectInArray(6, b4a);
	storeObjectInArray(7, b4b);
	storeObjectInArray(8, b4c);
	// Captains 4
	GamePiece* b5a = new GamePiece(this, "b5.png", xs[9], ys[9], 6, 1);
	GamePiece* b5b = new GamePiece(this, "b5.png", xs[10], ys[10], 6, 1);
	GamePiece* b5c = new GamePiece(this, "b5.png", xs[11], ys[11], 6, 1);
	GamePiece* b5d = new GamePiece(this, "b5.png", xs[12], ys[12], 6, 1);
	pieces.push_back(b5a);
	pieces.push_back(b5b);
	pieces.push_back(b5c);
	pieces.push_back(b5d);

	storeObjectInArray(9, b5a);
	storeObjectInArray(10, b5b);
	storeObjectInArray(11, b5c);
	storeObjectInArray(12, b5d);
	// Lieutenants 4
	GamePiece* b6a = new GamePiece(this, "b6.png", xs[13], ys[13], 5, 1);
	GamePiece* b6b = new GamePiece(this, "b6.png", xs[14], ys[14], 5, 1);
	GamePiece* b6c = new GamePiece(this, "b6.png", xs[15], ys[15], 5, 1);
	GamePiece* b6d = new GamePiece(this, "b6.png", xs[16], ys[16], 5, 1);
	pieces.push_back(b6a);
	pieces.push_back(b6b);
	pieces.push_back(b6c);
	pieces.push_back(b6d);

	storeObjectInArray(13, b6a);
	storeObjectInArray(14, b6b);
	storeObjectInArray(15, b6c);
	storeObjectInArray(16, b6d);
	// Sergeants 4
	GamePiece* b7a = new GamePiece(this, "b7.png", xs[17], ys[17], 4, 1);
	GamePiece* b7b = new GamePiece(this, "b7.png", xs[18], ys[18], 4, 1);
	GamePiece* b7c = new GamePiece(this, "b7.png", xs[19], ys[19], 4, 1);
	GamePiece* b7d = new GamePiece(this, "b7.png", xs[20], ys[20], 4, 1);
	pieces.push_back(b7a);
	pieces.push_back(b7b);
	pieces.push_back(b7c);
	pieces.push_back(b7d);

	storeObjectInArray(17, b7a);
	storeObjectInArray(18, b7b);
	storeObjectInArray(19, b7c);
	storeObjectInArray(20, b7d);
	// Miners 5
	GamePiece* b8a = new GamePiece(this, "b8.png", xs[21], ys[21], 3, 1);
	GamePiece* b8b = new GamePiece(this, "b8.png", xs[22], ys[22], 3, 1);
	GamePiece* b8c = new GamePiece(this, "b8.png", xs[23], ys[23], 3, 1);
	GamePiece* b8d = new GamePiece(this, "b8.png", xs[24], ys[24], 3, 1);
	GamePiece* b8e = new GamePiece(this, "b8.png", xs[25], ys[25], 3, 1);
	pieces.push_back(b8a);
	pieces.push_back(b8b);
	pieces.push_back(b8c);
	pieces.push_back(b8d);
	pieces.push_back(b8e);

	storeObjectInArray(21, b8a);
	storeObjectInArray(22, b8b);
	storeObjectInArray(23, b8c);
	storeObjectInArray(24, b8d);
	storeObjectInArray(25, b8e);
	// Scouts 8
	GamePiece* b9a = new GamePiece(this, "b9.png", xs[26], ys[26], 2, 1);
	GamePiece* b9b = new GamePiece(this, "b9.png", xs[27], ys[27], 2, 1);
	GamePiece* b9c = new GamePiece(this, "b9.png", xs[28], ys[28], 2, 1);
	GamePiece* b9d = new GamePiece(this, "b9.png", xs[29], ys[29], 2, 1);
	GamePiece* b9e = new GamePiece(this, "b9.png", xs[30], ys[30], 2, 1);
	GamePiece* b9f = new GamePiece(this, "b9.png", xs[31], ys[31], 2, 1);
	GamePiece* b9g = new GamePiece(this, "b9.png", xs[32], ys[32], 2, 1);
	GamePiece* b9h = new GamePiece(this, "b9.png", xs[33], ys[33], 2, 1);
	pieces.push_back(b9a);
	pieces.push_back(b9b);
	pieces.push_back(b9c);
	pieces.push_back(b9d);
	pieces.push_back(b9e);
	pieces.push_back(b9f);
	pieces.push_back(b9g);
	pieces.push_back(b9h);

	storeObjectInArray(26, b9a);
	storeObjectInArray(27, b9c);
	storeObjectInArray(28, b9b);
	storeObjectInArray(29, b9d);
	storeObjectInArray(30, b9e);
	storeObjectInArray(31, b9f);
	storeObjectInArray(32, b9g);
	storeObjectInArray(33, b9h);
	// Bombs 6
	GamePiece* bba = new GamePiece(this, "bb.png", xs[34], ys[34], 1000, 1);
	GamePiece* bbb = new GamePiece(this, "bb.png", xs[35], ys[35], 1000, 1);
	GamePiece* bbc = new GamePiece(this, "bb.png", xs[36], ys[36], 1000, 1);
	GamePiece* bbd = new GamePiece(this, "bb.png", xs[37], ys[37], 1000, 1);
	GamePiece* bbe = new GamePiece(this, "bb.png", xs[38], ys[38], 1000, 1);
	GamePiece* bbf = new GamePiece(this, "bb.png", xs[39], ys[39], 1000, 1);
	pieces.push_back(bba);
	pieces.push_back(bbb);
	pieces.push_back(bbc);
	pieces.push_back(bbd);
	pieces.push_back(bbe);
	pieces.push_back(bbf);

	storeObjectInArray(34, bba);
	storeObjectInArray(35, bbb);
	storeObjectInArray(36, bbc);
	storeObjectInArray(37, bbd);
	storeObjectInArray(38, bbe);
	storeObjectInArray(39, bbf);


	// Flag 1
	GamePiece* rf = new GamePiece(this, "rf.png", xs[40], ys[40], 0, 0);
	pieces.push_back(rf);

	storeObjectInArray(40, rf);
	// Spy 1
	GamePiece* rs = new GamePiece(this, "rs.png", xs[41], ys[41], 1, 0);
	pieces.push_back(rs);
	storeObjectInArray(41, rs);
	// Marshall 1
	GamePiece* r1 = new GamePiece(this, "r1.png", xs[42], ys[42], 10, 0);
	pieces.push_back(r1);

	storeObjectInArray(42, r1);
	// General 1 
	GamePiece* r2 = new GamePiece(this, "r2.png", xs[43], ys[43], 9, 0);
	pieces.push_back(r2);

	storeObjectInArray(43, r2);
	// Colonels 2
	GamePiece* r3a = new GamePiece(this, "r3.png", xs[44], ys[44], 8, 0);
	GamePiece* r3b = new GamePiece(this, "r3.png", xs[45], ys[45], 8, 0);
	pieces.push_back(r3a);
	pieces.push_back(r3b);

	storeObjectInArray(44, r3a);
	storeObjectInArray(45, r3b);
	// Majors 3
	GamePiece* r4a = new GamePiece(this, "r4.png", xs[46], ys[46], 7, 0);
	GamePiece* r4b = new GamePiece(this, "r4.png", xs[47], ys[47], 7, 0);
	GamePiece* r4c = new GamePiece(this, "r4.png", xs[48], ys[48], 7, 0);
	pieces.push_back(r4a);
	pieces.push_back(r4b);
	pieces.push_back(r4c);
	storeObjectInArray(46, r4a);
	storeObjectInArray(47, r4b);
	storeObjectInArray(48, r4c);
	// Captains 4
	GamePiece* r5a = new GamePiece(this, "r5.png", xs[49], ys[49], 6, 0);
	GamePiece* r5b = new GamePiece(this, "r5.png", xs[50], ys[50], 6, 0);
	GamePiece* r5c = new GamePiece(this, "r5.png", xs[51], ys[51], 6, 0);
	GamePiece* r5d = new GamePiece(this, "r5.png", xs[52], ys[52], 6, 0);
	pieces.push_back(r5a);
	pieces.push_back(r5b);
	pieces.push_back(r5c);
	pieces.push_back(r5d);
	storeObjectInArray(49, r5a);
	storeObjectInArray(50, r5b);
	storeObjectInArray(51, r5c);
	storeObjectInArray(52, r5d);
	// Lieutenants 4
	GamePiece* r6a = new GamePiece(this, "r6.png", xs[53], ys[53], 5, 0);
	GamePiece* r6b = new GamePiece(this, "r6.png", xs[54], ys[54], 5, 0);
	GamePiece* r6c = new GamePiece(this, "r6.png", xs[55], ys[55], 5, 0);
	GamePiece* r6d = new GamePiece(this, "r6.png", xs[56], ys[56], 5, 0);
	pieces.push_back(r6a);
	pieces.push_back(r6b);
	pieces.push_back(r6c);
	pieces.push_back(r6d);
	storeObjectInArray(53, r6a);
	storeObjectInArray(54, r6b);
	storeObjectInArray(55, r6c);
	storeObjectInArray(56, r6d);
	// Sergeants 4
	GamePiece* r7a = new GamePiece(this, "r7.png", xs[57], ys[57], 4, 0);
	GamePiece* r7b = new GamePiece(this, "r7.png", xs[58], ys[58], 4, 0);
	GamePiece* r7c = new GamePiece(this, "r7.png", xs[59], ys[59], 4, 0);
	GamePiece* r7d = new GamePiece(this, "r7.png", xs[60], ys[60], 4, 0);
	pieces.push_back(r7a);
	pieces.push_back(r7b);
	pieces.push_back(r7c);
	pieces.push_back(r7d);
	storeObjectInArray(57, r7a);
	storeObjectInArray(58, r7b);
	storeObjectInArray(59, r7c);
	storeObjectInArray(60, r7d);
	// Miners 5
	GamePiece* r8a = new GamePiece(this, "r8.png", xs[61], ys[61], 3, 0);
	GamePiece* r8b = new GamePiece(this, "r8.png", xs[62], ys[62], 3, 0);
	GamePiece* r8c = new GamePiece(this, "r8.png", xs[63], ys[63], 3, 0);
	GamePiece* r8d = new GamePiece(this, "r8.png", xs[64], ys[64], 3, 0);
	GamePiece* r8e = new GamePiece(this, "r8.png", xs[65], ys[65], 3, 0);
	pieces.push_back(r8a);
	pieces.push_back(r8b);
	pieces.push_back(r8c);
	pieces.push_back(r8d);
	pieces.push_back(r8e);
	storeObjectInArray(61, r8a);
	storeObjectInArray(62, r8b);
	storeObjectInArray(63, r8c);
	storeObjectInArray(64, r8d);
	storeObjectInArray(65, r8e);
	// Scouts 8
	GamePiece* r9a = new GamePiece(this, "r9.png", xs[66], ys[66], 2, 0);
	GamePiece* r9b = new GamePiece(this, "r9.png", xs[67], ys[67], 2, 0);
	GamePiece* r9c = new GamePiece(this, "r9.png", xs[68], ys[68], 2, 0);
	GamePiece* r9d = new GamePiece(this, "r9.png", xs[69], ys[69], 2, 0);
	GamePiece* r9e = new GamePiece(this, "r9.png", xs[70], ys[70], 2, 0);
	GamePiece* r9f = new GamePiece(this, "r9.png", xs[71], ys[71], 2, 0);
	GamePiece* r9g = new GamePiece(this, "r9.png", xs[72], ys[72], 2, 0);
	GamePiece* r9h = new GamePiece(this, "r9.png", xs[73], ys[73], 2, 0);
	pieces.push_back(r9a);
	pieces.push_back(r9b);
	pieces.push_back(r9c);
	pieces.push_back(r9d);
	pieces.push_back(r9e);
	pieces.push_back(r9f);
	pieces.push_back(r9g);
	pieces.push_back(r9h);
	storeObjectInArray(66, r9a);
	storeObjectInArray(67, r9c);
	storeObjectInArray(68, r9b);
	storeObjectInArray(69, r9d);
	storeObjectInArray(70, r9e);
	storeObjectInArray(71, r9f);
	storeObjectInArray(72, r9g);
	storeObjectInArray(73, r9h);
	// Bombs 6
	GamePiece* rba = new GamePiece(this, "rb.png", xs[74], ys[74], 1000, 0);
	GamePiece* rbb = new GamePiece(this, "rb.png", xs[75], ys[75], 1000, 0);
	GamePiece* rbc = new GamePiece(this, "rb.png", xs[76], ys[76], 1000, 0);
	GamePiece* rbd = new GamePiece(this, "rb.png", xs[77], ys[77], 1000, 0);
	GamePiece* rbe = new GamePiece(this, "rb.png", xs[78], ys[78], 1000, 0);
	GamePiece* rbf = new GamePiece(this, "rb.png", xs[79], ys[79], 1000, 0);
	pieces.push_back(rba);
	pieces.push_back(rbb);
	pieces.push_back(rbc);
	pieces.push_back(rbd);
	pieces.push_back(rbe);
	pieces.push_back(rbf);
	storeObjectInArray(74, rba);
	storeObjectInArray(75, rbb);
	storeObjectInArray(76, rbc);
	storeObjectInArray(77, rbd);
	storeObjectInArray(78, rbe);
	storeObjectInArray(79, rbf);


	for (int i = 0; i < 80; i++) {
		GamePiece* temp = pieces[i];
		for (int j = 0; j < 80; j++) {
			if (i != j) {
				GamePiece* target = pieces[j];
				temp->setCollisionObject(target);
			}
		}
	}
	setAllObjectsVisible(true);
	redrawDisplay();
	generated = true;
}