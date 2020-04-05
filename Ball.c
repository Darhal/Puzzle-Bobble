/*************************************************************************
* Project 	: Puzzle Bubble
* Author	: CHIDA Mohamed-Omar
* File		: Ball.c
* Date		: 07 Juin 2018
* Note 		: All function needed to load the ball, detect connection
			  All Ball functions
**************************************************************************/

#include "Ball.h"
#include <inttypes.h>
#include <time.h>
#include "defines.h"

/*VARS NEEDED FOR THIS TRANSLATION UNIT*/

// ALL COLORS
char* ballColor[BUB_COLOR] = {
	"black",
	"blue",
	"green",
	"orange",
	"purple",
	"red",
	"white",
	"yellow",
};

// all six directions
int directionForPairX[] = { 0, 1, -1, 1, 0, 1 };
int directionForPairY[] = { -1, -1, 0, 0, 1, 1 };
int directionForImpairX[] = { -1, 0, -1, 1, -1, 0 };
int directionForImpairY[] = { -1, -1, 0, 0, 1, 1 };


/**** FUNCTIONS ****/

void setTime(Ball* ball)
{
	clock_t start;
	start = clock();
	ball->lastReboundSec = ((double)(start) / CLOCKS_PER_SEC); // SET THE CPU TIME
}

void loadDestructionAnim(Ball* ball)
{
	// GET THE FILE PATH
	char path[80];
	strcpy(path, "assets/explode/bubex_");
	strcat(path, ballColor[ball->color]);
	strcat(path, ".bmp");
	/* load bitmap to temp surface */
	SDL_Surface* temp = SDL_LoadBMP(path);

	/* convert bitmap to display format */
	SDL_Surface* sprt = (SDL_Surface*)malloc(sizeof(SDL_Surface));
	sprt = SDL_DisplayFormat(temp);

	/* setup sprite colorkey and turn on RLE */
	int colorkey = SDL_MapRGB(localEnv.screen->format, 255, 0, 255);
	SDL_SetColorKey(sprt, SDL_SRCCOLORKEY | SDL_RLEACCEL, colorkey);
	
	/* free the temp surface */
	SDL_FreeSurface(temp);
	SDL_FreeSurface(ball->sprt); // FREE THE EX-SPRITE
	ball->sprt = sprt; // set the sprite
	ball->color = -1;
	ball->currentBallAnim = 0;
}

void deleteBallAt(int y, int x, Ball* ball)
{
	if (ball->current_board == NULL) { return; }
	if (ball->current_board->pos_index_bub[y][x] != NULL) {
		loadDestructionAnim(ball->current_board->pos_index_bub[y][x]);
		//deleteBall(current_board->pos_index_bub[y][x]);
		ball->current_board->pos_index_bub[y][x] = NULL;
		ball->current_board->bub_array[y][x] = -1; // delete color!
	}	
}

void deleteBall(Ball* ball)
{
	if (ball == NULL) return;
	Board* board = ball->current_board;
	delete(ball, ball->current_board->allBalls);
	//current_board->bub_array[ball->sprtPosition->y][ball->sprtPosition->x] = -1; // delete color!
	//current_board->pos_index_bub[ball->sprtPosition->y][ball->sprtPosition->x] = NULL;
	// WE CHECK WHENEVER WE DELETE A BALL
	SDL_FreeSurface(ball->sprt);
	free(ball->sprtFrame);
	free(ball->sprtPosition);
	free(ball);
	ball = NULL;
	if (length(board->allBalls) == 1) {
		char text[50];
		sprintf(text, "Player %d Wins!", board->playerId);
		updateText(board, text);
		replay(true, board);
		//deleteBall(current_board->allBalls->head->data);
	}
}

void LaunchBall(Ball* ball, int currentAnim, Board* cb)
{
	if (cb != ball->current_board) { return; }
	ball->ballLaunched = true; // SWITCH THIS ON
	if (currentAnim < 2 || currentAnim > 42) { // STRICT THE FAR RIGHT AND THE FAR LEFT FROM LAUNCHING
		ball->ballLaunched = true;
		ball->alpha = (PI/2)-((22.5-currentAnim)*(PI/LAUNCHER_DIV)); // SHARP ANGLE
		return;
	}
	ball->alpha = currentAnim*(PI / 44); // CALCULATE THE ANGLE (i found this more accurate)
	//current_board = cb;
}

bool checkCollision(Ball* ball, int x, int y)
{
	// CHECK FOR COLLISION
	if ((sqrt(pow(ball->sprtPosition->x - ball->current_board->bub_array_centers[y][x][0], 2) + pow(ball->sprtPosition->y - ball->current_board->bub_array_centers[y][x][1], 2)) < BUB_SIZE * ALPHA)
		&& (ball->current_board->bub_array[y][x] >= 0)) {
		return true;
	}
	return false;
}

int detectConnectedBalls(int x, int y, int condition, Ball* ball)
{
	int head = 1;
	int tail = 0;
	if (ball->current_board->bub_connected_component[y][x]) return 1;
	ball->current_board->bub_connected_component[y][x] = 1;
	/*cached_position[tail][0] = x;
	cached_position[tail][1] = y;*/
	ball->current_board->bub_fifo[tail][0] = x;
	ball->current_board->bub_fifo[tail][1] = y;
	while (tail < head) {
		int cx = ball->current_board->bub_fifo[tail][0];
		int cy = ball->current_board->bub_fifo[tail][1];
		int *dirx = cy % 2 ? directionForPairX : directionForImpairX;
		int *diry = cy % 2 ? directionForPairY : directionForImpairY;
		for (int i = 0; i<6; ++i) {
			int dx = cx + dirx[i];
			int dy = cy + diry[i];
			if (dy < 0 || dy >= BUB_NY || dx < 0 || dx >= BUB_NX - dy % 2) continue;
			if ((!condition && ball->current_board->bub_array[dy][dx] >= 0 && ball->current_board->bub_array[dy][dx] < 8 && ball->current_board->pos_index_bub[dy][dx] != NULL) || (condition && ball->current_board->bub_array[dy][dx] == ball->current_board->bub_array[cy][cx] && (ball->current_board->bub_array[dy][dx] >= 0 && ball->current_board->bub_array[dy][dx] < 8))) {
				if (!ball->current_board->bub_connected_component[dy][dx]) {
					ball->current_board->bub_connected_component[dy][dx] = 1;
					ball->current_board->bub_fifo[head][0] = dx;
					ball->current_board->bub_fifo[head][1] = dy;
					++head;
				}
			}
		}
		++tail;
	}
	return tail;
}

bool checkForBallsToDelete(int y, int x, Ball* ball)
{
	// RESET ALL
	Node* current = ball->current_board->allBalls->head;
	if (ball->current_board->allBalls->head != NULL) {
		while (current != NULL) {
			if ((current->data->y != -1 && current->data->x != -1) && ball->current_board->bub_connected_component[current->data->y][current->data->x] == 1) {
				ball->current_board->bub_connected_component[current->data->y][current->data->x] = 0;
			}
			current = current->next;
		}
	}

	int connectedBalls = detectConnectedBalls(x, y,true, ball); // CALC BALLS CONNECTED WITH SAME COLOR
	if (connectedBalls  >= 3) { // IF ITS MORE THAN 3
		current = ball->current_board->allBalls->head;
		if (ball->current_board->allBalls->head != NULL) {
			while (current != NULL) {
				if ((current->data->y != -1 && current->data->x != -1) && ball->current_board->bub_connected_component[current->data->y][current->data->x] == 1) {
					// THEN DELETE THEM
					deleteBallAt(current->data->y, current->data->x, ball);
					ball->current_board->score++;
					ball->current_board->bub_array[current->data->y][current->data->x] = -1; // delete color!
					ball->current_board->bub_connected_component[current->data->y][current->data->x] = 0;
				}
				current = current->next;
			}
		}
		/*delete balls not connected to the top of the board*/
		int itrX;
		for (itrX = 0;itrX < BUB_NX;++itrX) {
			if (ball->current_board->pos_index_bub[0][itrX] != NULL) // if the ball exsit !
				connectedBalls = detectConnectedBalls(itrX, 0, false, ball);// CHECK BALLS NOT CONNECTED TO THE TOP
		}
		current = ball->current_board->allBalls->head;
		if (ball->current_board->allBalls->head != NULL) {
			while (current != NULL) {
				if ((current->data->y != -1 && current->data->x != -1) && ball->current_board->bub_connected_component[current->data->y][current->data->x] == false) {
					/*DELETE THEM THEN*/
					deleteBallAt(current->data->y, current->data->x, ball);
					ball->current_board->score++;
					ball->current_board->bub_array[current->data->y][current->data->x] = -1;
				}
				ball->current_board->bub_connected_component[current->data->y][current->data->x] = 0;
				current = current->next;
			}
		}
		updateScoreText(ball->current_board);
	}
	ball->current_board->bub_connected_component[y][x] = 0; // RESET
	return length(ball->current_board->allBalls) == connectedBalls;
}

void fixBall(Ball* ball)
{
	int index_X, index_Y;
	for (index_Y = 0;index_Y < BUB_NY;index_Y++) {
		int maxX = (index_Y % 2 == 0) ? BUB_NX : BUB_NX - 1;
		for (index_X = 0;index_X < maxX;index_X++) {
			if (checkCollision(ball, index_X, index_Y)) { // IF THERE IS A POTENTIEL COLLISION
				int startY = (index_Y == 0) ? index_Y : index_Y - 1; // GET THE LINE JUST BEFORE IF YOUR NOT IN LINE 0
				int endY = (index_Y == BUB_NY) ? index_Y : index_Y + 1; // GET THE LINE AFTER IF YOUR NOT IN THE LAST LINE
				int itrY, itrX;
				for (itrY = startY; itrY <= endY;itrY++) { // GO FROM START TO END 
					int maxX = (itrY % 2 == 0) ? BUB_NX : BUB_NX - 1; // BASICLLY BECAUSE LINES DONT HAVE SAME AMOUNT OF BALLS
					for (itrX = 0;itrX < maxX;itrX++) {
						// IF THERE IS A CLOSE POSITION THATS NOT OCCUPIED BY ANOTHER BALL THEN JUST SET THE BALL THERE
						if ((sqrt(pow(ball->sprtPosition->x - ball->current_board->bub_array_centers[itrY][itrX][0], 2)
							+ pow(ball->sprtPosition->y - ball->current_board->bub_array_centers[itrY][itrX][1], 2)) <  BUB_SIZE*ALPHA) && (ball->current_board->bub_array[itrY][itrX] < 0)) {
							ball->current_board->bub_array[itrY][itrX] = ball->color;
							ball->current_board->pos_index_bub[itrY][itrX] = ball;
							ball->ballLaunched = false;
							ball->sprtPosition->x = ball->current_board->bub_array_centers[itrY][itrX][0];
							ball->sprtPosition->y = ball->current_board->bub_array_centers[itrY][itrX][1];
							ball->x = itrX;
							ball->y = itrY;
							// DETECT CONNECTED BALLS
							checkForBallsToDelete(itrY, itrX, ball);
							// WE FINISHED EVERYTHING CREATE ANOTHER BALL
							srand((uint)time(NULL));
							loadNextBall(ball->current_board, 0);
							return; // EXIST THE FUNCTION THAT ALL WE NEED
						}
					}
				}
				return; // DOESNT CACUSE ANY BUG SINCE IT WILL GAME OVER
			}
			// IF IT REACH THE TOP
			if ((ball->sprtPosition->y<ball->current_board->plafonds)) {
				// FIND THE CLOSEST POSITION
				if ((sqrt(pow(ball->sprtPosition->x - ball->current_board->bub_array_centers[index_Y][index_X][0], 2)
					+ pow(ball->sprtPosition->y - ball->current_board->bub_array_centers[index_Y][index_X][1], 2)) < BUB_SIZE / 2)) {
					ball->ballLaunched = false;
					ball->sprtPosition->x = ball->current_board->bub_array_centers[index_Y][index_X][0];
					ball->sprtPosition->y = ball->current_board->bub_array_centers[index_Y][index_X][1];
					ball->x = index_X;
					ball->y = index_Y;
					ball->current_board->bub_array[index_Y][index_X] = ball->color;
					ball->current_board->pos_index_bub[index_Y][index_X] = ball;
					//Detected connected balls
					checkForBallsToDelete(index_Y, index_X, ball);
					// WE FINISHED EVERYTHING CREATE ANOTHER BALL
					srand((uint)time(NULL));
					loadNextBall(ball->current_board,0);
					return;
				}
			}
		}
	}
}

void Rebound(Ball* ball)
{
	// GET THE TIME
	clock_t start;
	start = clock();
	// IF ITS ALREADY OUT OF THE BOUNDARY AND DELTA TIME IS GREAT THAN TIME LAPSE
	if (((ball->sprtPosition->x < ball->current_board->b_left) || ((ball->sprtPosition->x + ball->sprtPosition->h) > ball->current_board->b_right))
		&& (((double)(start) / CLOCKS_PER_SEC) - ball->lastReboundSec) >= TIME_LAPSE)
	{
		// BALL START REBOUNDING
		ball->tempX = 0.0;
		ball->tempY = 0.0;
		setTime(ball);
		ball->alpha = PI - ball->alpha;
	}
	// ACUMMLATE THESE VALUES IN FLOAT OR DOUBLE AND IF ITS IMPORTANT THEN JUST SET IT BCUZ OF DATA LOST
	ball->tempX += ((VELOCITY)*(cos(ball->alpha)));
	ball->tempY += ((VELOCITY)*(sin(ball->alpha)));
	if (abs(ball->tempX) > 1) {
		ball->sprtPosition->x -= ball->tempX;
		ball->tempX = 0.0;
	}
	if (abs(ball->tempY) > 1) {
		ball->sprtPosition->y -= ball->tempY;
		ball->tempY = 0.0;
	}
	// THERE MIGHT BE COLLISION OR SMTHG
	fixBall(ball);
}

void MoveBall(Ball* ball)
{
	// IF ITS ALREADY OUT OF THE BOUNDARY SET IT TO REBOUND FOR FIRST TIME
	if (((ball->sprtPosition->x < ball->current_board->b_left) || ((ball->sprtPosition->x + ball->sprtPosition->h) > ball->current_board->b_right)))
	{
		ball->ballLaunched = false;
		ball->ballBounce = true;
		ball->tempX = 0.0;
		ball->tempY = 0.0;
		ball->alpha = PI - ball->alpha;
		setTime(ball);
		return;
	}
	// ACUMMLATE THESE VALUES IN FLOAT OR DOUBLE AND IF ITS IMPORTANT THEN JUST SET IT BCUZ OF DATA LOST
	ball->tempX += ((VELOCITY)*(cos(ball->alpha)));
	ball->tempY += ((VELOCITY)*(sin(ball->alpha)));
	if (abs(ball->tempX) > 1) {
		ball->sprtPosition->x -= ball->tempX;
		ball->tempX = 0.0;
	}
	if (abs(ball->tempY) > 1) {
		ball->sprtPosition->y -= ball->tempY;
		ball->tempY = 0.0;
	}
	fixBall(ball);
}

Ball* getBall(Board* board)
{
	return board->allBalls->head->data;
}

void setPosition(Ball* ball, int x, int y)
{
	ball->sprtPosition->x = x;
	ball->sprtPosition->y = y;
}

bool checkForLimit(Board* board)
{
	int itrX;
	for (itrX = 0;itrX < BUB_NX;++itrX) {
		if (board->pos_index_bub[(BUB_NY - 1)-board->boardTop][itrX] != NULL) // if the ball exsit !
			return true;
	}
	return false;
}

Ball* loadBall(uint color, Board* board)
{
	/*WE SHOULD CEHCK WHENEVER WE CREATE A BALL FOR THE LIMIT*/
	if (board != NULL) {
		if (checkForLimit(board)) {
			char text[50];
			sprintf(text, "Player %d Lost!", board->playerId);
			updateText(board, text);
			replay(false, board);
			return NULL;
		}
	}
	
	// GET THE FILE PATH
	char path[80];
	strcpy(path, "assets/Billes/bub_");
	strcat(path, ballColor[color]);
	strcat(path, ".bmp");
	/* load bitmap to temp surface */
	SDL_Surface* temp = SDL_LoadBMP(path);

	/* convert bitmap to display format */
	SDL_Surface* sprt = (SDL_Surface*)malloc(sizeof(SDL_Surface));
	sprt = SDL_DisplayFormat(temp);

	/* setup sprite colorkey and turn on RLE */
	int colorkey = SDL_MapRGB(localEnv.screen->format, 255, 0, 255);
	SDL_SetColorKey(sprt, SDL_SRCCOLORKEY | SDL_RLEACCEL, colorkey);

	/* free the temp surface */
	SDL_FreeSurface(temp);

	// ALLOCATE THE MEMORY FOR OUR BALL
	Ball* MyBall = (Ball*)malloc(sizeof(Ball));
	MyBall->sprt = sprt; // set the sprite

						 // SET THE SIZE
	SDL_Rect* sprtSize = (SDL_Rect*)malloc(sizeof(SDL_Rect));
	sprtSize->y = BUB_SIZE * 12;
	sprtSize->w = BUB_SIZE;
	sprtSize->h = BUB_SIZE;
	sprtSize->x = 0;
	MyBall->sprtFrame = sprtSize;

	// SET THE POSITION
	SDL_Rect* sprtPosition = (SDL_Rect*)malloc(sizeof(SDL_Rect));
	sprtPosition->w = BUB_SIZE;
	sprtPosition->h = BUB_SIZE;
	sprtPosition->x = ((board->b_left+board->b_right)/2 - (ARROW_SIZE_WIDTH/9.009));
	sprtPosition->y = LAUNCHER_CENTER + SCREEN_HEIGHT / 1.563;
	MyBall->sprtPosition = sprtPosition;

	// INIT OTHER VARS
	MyBall->ballLaunched = false;
	MyBall->ballBounce = false;
	MyBall->currentBallAnim = 12;
	MyBall->tempX = 0.0;
	MyBall->tempY = 0.0;
	MyBall->lastReboundSec = 0;
	MyBall->color = color;
	MyBall->x = -1;
	MyBall->y = -1;
	MyBall->current_board = board;
	// ADD INDEX AND RETURN THE ENTITY
	add(MyBall, board->allBalls);
	board->ballIndex++;
	return MyBall;
}