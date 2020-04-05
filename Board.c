/*************************************************************************
* Project 	: Puzzle Bubble
* Author	: CHIDA Mohamed-Omar
* File		: Board.c
* Date		: 07 Juin 2018
* Note 		: File that manage boards
**************************************************************************/

#include "defines.h"
#include "GameManager.h"
#include "Ball.h"

Board* initBoard(int b_left, int b_right, int b_top, int b_bottom, int plr)
{
    Board* b = (Board*)malloc(sizeof(Board));

	b->arrow = LoadAnimation("assets/Lanceur/frame_launcher.bmp", 44, (SCREEN_WIDTH - ARROW_SIZE_WIDTH)/2, (SCREEN_HEIGHT - ARROW_SIZE_HEIGHT),
		ARROW_SIZE_WIDTH, ARROW_SIZE_HEIGHT);
	b->arrow->currentAnim = 22;
	b->diable = LoadAnimation("assets/Personnages/frame_bsd_launch.bmp", 88, BOARD_LEFT, (SCREEN_HEIGHT - 100) - 9 * 2, 160, 100);
	b->penguin = LoadAnimation("assets/Personnages/frame_tux_wheel.bmp", 80, BOARD_RIGHT - 100, (SCREEN_HEIGHT - 100) - 9 * 2, 100, 100);
	b->gears = LoadAnimation("assets/Lanceur/frame_gears.bmp", 39, (SCREEN_WIDTH - 124) / 2, (SCREEN_HEIGHT - 116),125, 116);
	b->gears->currentAnim = 20;
	b->wheel = LoadAnimation("assets/Lanceur/frame_wheel.bmp", 15, (SCREEN_WIDTH - 33) / 2, (SCREEN_HEIGHT - 47),33, 47);
	b->wheel->currentAnim = 8;

	b->frame_top = LoadAnimation("assets/Plafond/frame_top.bmp", 0, b_left,b_top,321,9);

	b->chain1 = LoadAnimation("assets/Plafond/frame_ch_att.bmp", 15, ((b_right + b_left)/2)-BUB_SIZE*2, b_top, 22, 26);
	b->chain2 = LoadAnimation("assets/Plafond/frame_ch_att.bmp", 15, ((b_right + b_left)/2)+BUB_SIZE*2, b_top, 22, 26);
	b->bShowLimit = false;

	b->longChain1 = LoadAnimation("assets/Plafond/frame_chain.bmp", 15, ((b_right + b_left) / 2) - BUB_SIZE * 2, b_top, 23, 35);
	b->longChain2 = LoadAnimation("assets/Plafond/frame_chain.bmp", 15, ((b_right + b_left) / 2) + BUB_SIZE * 2, b_top, 23, 35);
	b->longChain1->sprtFrame->h = 0;
	b->longChain2->sprtFrame->h = 0;

	setAnimLimit(b->penguin, 79);
	setResetValue(b->penguin, 65);

	setAnimLimit(b->diable, 87);
	setResetValue(b->diable, 66);

    b->b_left = b_left;
    b->b_right = b_right;
    b->b_top = b_top;
    b->b_bottom = b_bottom;
	b->plafonds = b_top;

	b->playerId = plr;
	b->score = 0;

    setAnimPosition(b->arrow, ((b_right+b_left) - ARROW_SIZE_WIDTH) / 2,(SCREEN_HEIGHT - ARROW_SIZE_HEIGHT)-9*2);
	setAnimPosition(b->gears, ((b_right + b_left) - 115) / 2, (SCREEN_HEIGHT - 116)-9*2);
	setAnimPosition(b->wheel, (((b_right + b_left) / 2)+115/1.699), (SCREEN_HEIGHT - 47) - 9 * 2);
    setAnimPosition(b->diable, b_left, (SCREEN_HEIGHT - 100)-9*2);
    setAnimPosition(b->penguin, b_right-100, (SCREEN_HEIGHT - 100)-9*2);

	b->textLocation = (SDL_Rect*)malloc(sizeof(SDL_Rect));
	b->textLocation->x = ((b_right + b_left) / 2)-60;
	b->textLocation->y = b_top-40;

#ifdef TEXT
	char score[50];
	sprintf(score, "Player %d score : %d", b->playerId, b->score);
	b->text = loadText(score);
#endif

	b->ballIndex = 0;
	b->bCanLaunchBall = true;
	b->allBalls = emptylist();

	int i, j;
	for (i = 0; i < BUB_NY; i++) {
		for (j = 0; j < BUB_NX; j++) {
			b->bub_array[i][j] = -1;
			b->bub_connected_component[i][j] = 0;
			b->pos_index_bub[i][j] = NULL;
		}
	}

	b->boardTop = 0;

	calculateBallFixPos(b); // calculate and init some balls first!
	b->timeStart = clock();
	b->timeStart2 = clock();
	b->timeStart3 = clock();
	
    BoardIndex++;
    return b;
}

/*
Function to calculate all ball fix positions
*/
void calculateBallFixPos(Board* b)
{
	int index_X, index_Y;
	int diffx;
	srand((uint)time(NULL));
	for (index_Y = 0;index_Y < BUB_NY;index_Y++) {
		int maxX = (index_Y % 2 == 0) ? BUB_NX : BUB_NX - 1;
		for (index_X = 0;
			index_X < maxX;
			index_X++) {
			if (index_Y % 2 == 0) {
				diffx = (b->b_right - b->b_left) / 8;
				b->bub_array_centers[index_Y][index_X][0] = b->b_left + diffx*index_X;
			}
			else {
				b->bub_array_centers[index_Y][index_X][0] =
					(b->bub_array_centers[index_Y - 1][index_X][0] + b->bub_array_centers[index_Y - 1][index_X + 1][0]) / 2;
			}
			b->bub_array_centers[index_Y][index_X][1] = b->b_top + SPACEMENT_X*index_Y;
		}
	}
}

void resetBalls(Board* b)
{
	calculateBallFixPos(b);
	b->boardTop = 0;
	b->bShowLimit = false;
	b->plafonds = b->b_top;
	b->longChain1->sprtFrame->h = 0;
	b->longChain2->sprtFrame->h = 0;
	b->chain1->currentAnim = 0;
	b->chain2->currentAnim = 0;
	b->score = 0;
	setAnimPosition(b->frame_top, b->b_left, (b->b_top - 11) + (b->boardTop*BUB_SIZE));
}

void moveBalls(Board* b) 
{
	if (checkForLimit(b)) {
		char text[50];
		sprintf(text, "Player %d Lost!", b->playerId);
		updateText(b, text);
		deleteBall(b->allBalls->head->data);
		replay(false, b);
		return;
	}

	int index_X, index_Y;
	for (index_Y = 0; index_Y < BUB_NY; index_Y++) {
		int maxX = (index_Y % 2 == 0) ? BUB_NX : BUB_NX - 1;
		for (index_X = 0;
			index_X < maxX;
			index_X++) {
			b->bub_array_centers[index_Y][index_X][1] = b->b_top + SPACEMENT_X * index_Y + b->boardTop*BUB_SIZE;
			
			if (b->pos_index_bub[index_Y][index_X] != NULL) {
				Ball* ball = b->pos_index_bub[index_Y][index_X];
				setPosition(ball, ball->sprtPosition->x, ball->sprtPosition->y + BUB_SIZE);
			}
		}
	}

	b->plafonds = b->b_top+b->boardTop*BUB_SIZE;

	if (b->boardTop > 1) {
		b->longChain1->sprtFrame->h += BUB_SIZE+1;
		b->longChain2->sprtFrame->h += BUB_SIZE+1;
	}
	
	setAnimPosition(b->frame_top, b->b_left, (b->b_top - 13) + (b->boardTop*BUB_SIZE));
	setAnimPosition(b->chain1, ((b->b_right + b->b_left) / 2) - BUB_SIZE * 2, b->b_top+(13-12) + (b->boardTop - 1)*BUB_SIZE); 
	setAnimPosition(b->chain2, ((b->b_right + b->b_left) / 2) + BUB_SIZE * 2, b->b_top+(13-12) + (b->boardTop - 1)*BUB_SIZE);
	IncreaseAnim(b->chain1);
	IncreaseAnim(b->chain2);
}

void updateBoardLimit(Board* b)
{
	clock_t end;
	end = clock();
	if (((((double)(end - b->timeStart)) / CLOCKS_PER_SEC)) >= LIMIT_CHANGE)
	{
		b->timeStart = clock();
		if (b->boardTop < 1) {
			b->bShowLimit = true;
		}
		b->boardTop++;
		moveBalls(b);
	}
	if (((((double)(end - b->timeStart2)) / CLOCKS_PER_SEC)) >= 0.3) {
		b->timeStart2 = clock();
		setAnimLimit(b->diable, 87);
		setResetValue(b->diable, 66);
	}
	if (((((double)(end - b->timeStart3)) / CLOCKS_PER_SEC)) >= 0.7) {
		b->timeStart3 = clock();
		setAnimLimit(b->penguin, 79);
		setResetValue(b->penguin, 65);
	}
}

void updateBoard(Board* b)
{
	updateBoardLimit(b);

	/*SETTING MAX AND MIN INTERVAL FOR THESE*/
	if (getBall(b)->currentBallAnim>24) getBall(b)->currentBallAnim = 24;
	if (getBall(b)->currentBallAnim<0) getBall(b)->currentBallAnim = 0;

	/*CALL OF EVERY FRAME FUNCTIONS*/
	if (getBall(b)->ballLaunched) {
		MoveBall(getBall(b));
	}
	if (getBall(b)->ballBounce) {
		Rebound(getBall(b));
	}

	getBall(b)->sprtFrame->y = BUB_SIZE * getBall(b)->currentBallAnim; // UPDATE BALL ANIM

	drawAnim(b->gears); // DRAW the arrow
	drawAnim(b->wheel); // DRAW the arrow
	drawAnim(b->arrow); // DRAW the arrow
	drawAnim(b->nextBall);
	SDL_BlitSurface(b->longChain1->sprt, b->longChain1->sprtFrame, localEnv.screen, b->longChain1->sprtPosition);
	SDL_BlitSurface(b->longChain2->sprt, b->longChain2->sprtFrame, localEnv.screen, b->longChain2->sprtPosition);
	if (b->bShowLimit) {
		drawAnim(b->frame_top); // DRAW the arrow
		drawAnim(b->chain1); // DRAW the arrow
		drawAnim(b->chain2); // DRAW the arrow
	}

//TEXT FUNCTIONS
#ifdef TEXT
	SDL_BlitSurface(b->text, NULL, localEnv.screen, b->textLocation);
#endif

	// DRAW EVERY BALL WE HAVE!
	Node* current = b->allBalls->head;
	Node* toNextDeleteBall;
	if (b->allBalls->head != NULL) {
		while (current != NULL) {
			if (current->data != NULL) {
				if (current->data->color == -1) { // color is -1 means its going to be deleted
					current->data->sprtFrame->y = BUB_SIZE * current->data->currentBallAnim; // UPDATE BALL ANIM
					SDL_BlitSurface(current->data->sprt, current->data->sprtFrame, localEnv.screen, current->data->sprtPosition); // DRAW the bulle
					current->data->currentBallAnim++;
					toNextDeleteBall = current->next;
					if (current->data->currentBallAnim > 24) {
						deleteBall(current->data);
					}
					current = toNextDeleteBall;
				}
				else {
					SDL_BlitSurface(current->data->sprt, current->data->sprtFrame, localEnv.screen, current->data->sprtPosition); // DRAW the bulle
					current = current->next;
				}
			}
		}
	}
	updateDefaultAnimation(b->diable);
	updateDefaultAnimation(b->penguin);
}

void moveArrowToLeft(Board* b) 
{
	if (b == NULL) return;
	DecreaseAnim(b->arrow); // CHANGE ANIMATION OF THE ARROW
	DecreaseAnim(b->gears);
	setCurrentAnim(b->wheel, b->arrow->currentAnim / 2.8);
	setAnimLimit(b->penguin, 32);
	setResetValue(b->penguin, 44);
	if (!getBall(b)->ballLaunched)  // IF ITS NOT LAUCNHED THEN SET THE ANIM FOR THE BALL
		getBall(b)->currentBallAnim = b->arrow->currentAnim / 2;
}

void moveArrowToRight(Board* b)
{
	if (b == NULL) return;
	IncreaseAnim(b->arrow);// CHANGE ANIMATION OF THE ARROW
	setCurrentAnim(b->wheel, b->arrow->currentAnim / 2.8);
	IncreaseAnim(b->gears);
	setAnimLimit(b->penguin, 32);
	setResetValue(b->penguin, 44);
	if (!getBall(b)->ballLaunched) // IF ITS NOT LAUCNHED THEN SET THE ANIM FOR THE BALL
		getBall(b)->currentBallAnim = b->arrow->currentAnim / 2;
}

void launch(Board* b)
{
	if (b == NULL) return;
	if (b->bCanLaunchBall) {
		b->bCanLaunchBall = false;
		LaunchBall(getBall(b), b->arrow->currentAnim, b);
		updateScoreText(b);
	}
}

void updateScoreText(Board* b) 
{
#ifdef TEXT
	char score[50];
	sprintf(score, "Player %d score : %d", b->playerId, b->score);
	if (b->text != NULL) {
		SDL_FreeSurface(b->text);
	}
	b->text = loadText(score);
#endif
}

void updateText(Board* b, char text[50])
{
#ifdef TEXT
	if (b->text != NULL) {
		SDL_FreeSurface(b->text);
	}
	b->text = loadText(text);
#endif
}

void deleteBoard(Board* b)
{
	// MAKE SURE WE CLEAR THIS
	if (b != NULL && b->allBalls != NULL) {
		destroy(b->allBalls); // otherwise it will be a memory leak!
		deleteAnim(b->diable);
		deleteAnim(b->penguin);
		deleteAnim(b->arrow);
		deleteAnim(b->chain1);
		deleteAnim(b->chain2);
		deleteAnim(b->longChain1);
		deleteAnim(b->longChain2);
		deleteAnim(b->nextBall);
#ifdef TEXT
		SDL_FreeSurface(b->text);
#endif
		free(b);
	}
}

void loadNextBall(Board* b, int color)
{
	// WE FINISHED EVERYTHING CREATE ANOTHER BALL
	if (color != -1) {
		loadBall(b->nextBallColor, b);
		setAnimPosition(b->nextBall, b->b_left, (SCREEN_HEIGHT - 100));
		setAnimLimit(b->diable, 65);
		setResetValue(b->diable, 48);
		b->bCanLaunchBall = true;
		b->nextBallColor = rand() % BUB_COLOR;
		char path[80];
		strcpy(path, "assets/Billes/bub_");
		strcat(path, ballColor[b->nextBallColor]);
		strcat(path, ".bmp");
		deleteAnim(b->nextBall);
		b->nextBall = LoadAnimation(path, 23, ((b->b_right +b->b_left) - 220) / 2, b->b_bottom + BUB_SIZE * 1.5, BUB_SIZE, BUB_SIZE);
	}
	else {
		loadBall(rand() % BUB_COLOR, b);
		b->bCanLaunchBall = true;
		b->nextBallColor = rand() % BUB_COLOR;
		char path[80];
		strcpy(path, "assets/Billes/bub_");
		strcat(path, ballColor[b->nextBallColor]);
		strcat(path, ".bmp");
		b->nextBall = LoadAnimation(path, 23, ((b->b_right +b->b_left) - 220) / 2, b->b_bottom+BUB_SIZE*1.5, BUB_SIZE, BUB_SIZE);
	}
}
