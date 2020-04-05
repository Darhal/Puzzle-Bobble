/*************************************************************************
* Project 	: Puzzle Bubble
* Author	: CHIDA Mohamed-Omar, BATTIKH Lynda
* File		: GameManager.c
* Date		: 07 Juin 2018
* Note 		: Responsible to load the game and do the logic
**************************************************************************/

/*TEMP NOTE MAKE SURE U DO EVERYTHING FOR BOTH BOARDS !*/

#include "Ball.h"
#include "Animation.h"
#include <time.h>

SDL_Surface* init_SDL()
{
	/* initialize SDL */
	SDL_Init(SDL_INIT_VIDEO);

	/* set the title bar */
	SDL_WM_SetCaption(WIN_TITLE, WIN_TITLE);

	/* create window */
	SDL_Surface* screen = (SDL_Surface*)malloc(sizeof(SDL_Surface*));
	screen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, 0, 0);
	/* set keyboard repeat */
	SDL_EnableKeyRepeat(10, 10);

#ifdef TEXT
	TTF_Init();
#endif
	localEnv.screen = screen;
	BoardIndex = -1;
	localEnv.PlayerCount = 0;
	return screen;
}

void loadMenu()
{
	//MENU LOADING FUNCTIONS HERE !
	SDL_Surface* menu = loadSprite("assets/menu.bmp");
	localEnv.menu = menu;
}

void initGame()
{
	Board* board;
	if (localEnv.PlayerCount == 2) {
		SDL_Surface* frame = loadSprite("assets/frame/frame_2p.bmp");
		localEnv.frame = frame;

		board = initBoard(25, 345, BOARD_TOP, BOARD_BOTTOM, 1);
		localEnv.GameBoard[BoardIndex] = board;
		board = initBoard(375, 695, BOARD_TOP, BOARD_BOTTOM, 2);
		localEnv.GameBoard[BoardIndex] = board;
		
		initBalls(localEnv.GameBoard[BoardIndex]);
		initBalls(localEnv.GameBoard[BoardIndex - 1]); // INIT FIRST LINES OF BALLS
		loadNextBall(localEnv.GameBoard[BoardIndex], -1); // Generate number between 0 and BUB_COLOR excluded
		srand((uint)time(NULL));
		loadNextBall(localEnv.GameBoard[BoardIndex-1], -1);
	}
	else if (localEnv.PlayerCount == 1) {
		SDL_Surface* frame = loadSprite("assets/frame/frame_1p.bmp");
		localEnv.frame = frame;

		board = initBoard(BOARD_LEFT, BOARD_RIGHT, BOARD_TOP, BOARD_BOTTOM,1);
		localEnv.GameBoard[BoardIndex] = board;
		initBalls(localEnv.GameBoard[BoardIndex]); // INIT FIRST LINES OF BALLS
		srand((uint)time(NULL));
		loadNextBall(board, -1);
	}
}

void initBalls(Board* board)
{
	if (board != NULL) {
		int index_X, index_Y;
		for (index_Y = 0;index_Y < 3;index_Y++) {
			int maxX = (index_Y % 2 == 0) ? BUB_NX : BUB_NX - 1;
			for (index_X = 0;
				index_X < maxX;
				index_X++) {
				Ball* bub = loadBall(random_number(0, BUB_COLOR - 1), board);
				setPosition(bub, board->bub_array_centers[index_Y][index_X][0], board->bub_array_centers[index_Y][index_X][1]);
				board->bub_array[index_Y][index_X] = bub->color;
				bub->x = index_X;
				bub->y = index_Y;
				board->pos_index_bub[index_Y][index_X] = bub;
			}
		}
	}
}

void replay(bool win, Board* board)
{
	// MAKE SURE WE CLEAR THIS
	if (board != NULL) {
		Node* toDeleteBall = board->allBalls->head;
		Node* toNextDeleteBall = board->allBalls->head;
		resetBalls(board);
		srand((uint)time(NULL));
		if (board->allBalls->head != NULL) {
			while (toDeleteBall != NULL) {
				toNextDeleteBall = toDeleteBall->next;
				if (toDeleteBall->data != NULL) {
					if (toDeleteBall->data->sprtPosition->y == (LAUNCHER_CENTER + SCREEN_HEIGHT / 1.563)) {
						deleteBall(toDeleteBall->data);
					}
					else
						deleteBallAt(toDeleteBall->data->y, toDeleteBall->data->x, toDeleteBall->data);
				}
				toDeleteBall = toNextDeleteBall;
			}
		}
		//deleteBall(localEnv.GameBoard[BoardIndex]->allBalls->head->data);
		initBalls(board);
	}
	srand((uint)time(NULL));
	loadNextBall(board, -1);
	board->bCanLaunchBall = true;
}

void gameLogic()
{
	/* main loop: check events and re-draw the window until the end */
	int gameover = 0;

	while (!gameover)
	{
		SDL_Event event;
		/* look for an event; possibly update the position and the shape
		* of the sprite. */
		if (SDL_PollEvent(&event)) {
			HandleEvent(event, &gameover);
		}
		
		SDL_FillRect(localEnv.screen, NULL, SDL_MapRGB(localEnv.screen->format, 0, 0, 0)); // CLEAR EVERYTHING
		if (localEnv.PlayerCount == 0){ // PlayerCount == 0 that means we should show main menu
			// render the main using SDL_FillRect or SDL_BlitSurface menu here ! 
			SDL_BlitSurface(localEnv.menu, NULL, localEnv.screen, NULL); // draw main menu
		}
		else {
			/* Draw all game elements */
			SDL_BlitSurface(localEnv.frame, NULL, localEnv.screen, NULL); // draw background 
			int bIndex = 0;
			for (bIndex = 0; bIndex <= BoardIndex; bIndex++)
			{
				if (localEnv.GameBoard[bIndex] != NULL)
					updateBoard(localEnv.GameBoard[bIndex]);
			}
		}

		/* update the screen */
		SDL_UpdateRect(localEnv.screen, 0, 0, 0, 0);
	}
}

/*Catch any keyboard events*/
void HandleEvent(SDL_Event event, int *quit)
{
	switch (event.type) {
		/* close button clicked */
	case SDL_QUIT:
		*quit = 1;
		break;
	case SDL_MOUSEBUTTONDOWN: {
		// MOUSE EVENT STUFF HERE
		//printf("X:%d, Y:%d\n", event.motion.x, event.motion.y);
		if (localEnv.PlayerCount == 0) {
			//IF THE MOUSE IS ON THE BUTTON OF MULTIPLAYER AND IS CLICKED DO THE FOLLOWING
			if ((event.motion.x >= 162) && (event.motion.x <= 560) && (event.motion.y >= 229) && (event.motion.y <= 280)) {
				//IF MULTIPLAYER IS CLICKED CALL set PlayerCount Varriable to 2 and call initGame
				localEnv.PlayerCount = 1;
				initGame();
			}
			//IF THE MOUSE IS ON THE BUTTON OF SOLO AND IS CLICKED DO THE FOLLOWING
			if ((event.motion.x >= 162) && (event.motion.x <= 560) && (event.motion.y >= 310) && (event.motion.y <= 372)) {
				//IF SOLO IS CLICKED CALL set PlayerCount Varriable to 1 and call initGame
				localEnv.PlayerCount = 2;
				initGame();
			}
			// QUIT CLICKED
			if ((event.motion.x >= 241) && (event.motion.x <= 503) && (event.motion.y >= 372) && (event.motion.y <= 433)) {
				*quit = 1;
			}
		}
		break;
	}
							  /* handle the keyboard */
	case SDL_KEYDOWN:
		switch (event.key.keysym.sym) {
		case SDLK_ESCAPE: {
			if (localEnv.PlayerCount != 0)
				returnToMenu();
			break;
		}
		case SDLK_e:
			*quit = 1;
			break;
		case SDLK_LEFT:
			moveArrowToLeft(localEnv.GameBoard[BoardIndex]);
			break;
		case SDLK_RIGHT:
			moveArrowToRight(localEnv.GameBoard[BoardIndex]);
			break;
		case SDLK_SPACE:
			launch(localEnv.GameBoard[BoardIndex]);
			break;
		case SDLK_q:
			if (BoardIndex == 1)
				moveArrowToLeft(localEnv.GameBoard[BoardIndex - 1]);
			break;
		case SDLK_d:
			if (BoardIndex == 1)
				moveArrowToRight(localEnv.GameBoard[BoardIndex - 1]);
			break;
		case SDLK_l:
			if (BoardIndex == 1)
				launch(localEnv.GameBoard[BoardIndex - 1]);
			break;
		default:
			break;
		}
		break;
	case SDL_KEYUP: {
		/*int i;
		for (i = 0; i <= BoardIndex; i++) {
			//setAnimLimit(localEnv.GameBoard[i]->penguin, 79);
			//setResetValue(localEnv.GameBoard[i]->penguin, 61);
			setAnimLimit(localEnv.GameBoard[i]->diable, 87);
			setResetValue(localEnv.GameBoard[i]->diable, 66);
		}*/
		break;
		}
	}
}

void remove_SDL()
{
	// FREE ALL THINGS RELATED TO BOARD AND GAME ELEMENTS
	int bIndex = 0;
	for (bIndex = 0; bIndex <= BoardIndex; bIndex++)
	{
		deleteBoard(localEnv.GameBoard[bIndex]);
	}
	SDL_FreeSurface(localEnv.menu);

	/* cleanup SDL */
	SDL_Quit();
}

void returnToMenu()
{
	localEnv.PlayerCount = 0;
	int bIndex = 0;
	for (bIndex = 0; bIndex <= BoardIndex; bIndex++)
	{
		deleteBoard(localEnv.GameBoard[bIndex]);
	}
	BoardIndex = -1;
	SDL_FreeSurface(localEnv.frame);
}
