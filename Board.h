/*************************************************************************
* Project 	: Puzzle Bubble
* Author	: CHIDA Mohamed-Omar
* File		: Board.h
* Date		: 07 Juin 2018
* Note 		: File that manage boards 
**************************************************************************/

#include "defines.h"
#include "Animation.h"

typedef struct board 
{
    int b_left;
    int b_right;
    int b_top;
    int b_bottom;
	int plafonds;

	int playerId;
	int ballIndex;
	int nextBallColor;

	// ARRAY TO CALC BALL FIXED POS
	int bub_array_centers[BUB_NY][BUB_NX][2];
	int bub_array[BUB_NY][BUB_NX];
	int bub_fifo[BUB_NY*BUB_NX][2];
	int bub_connected_component[BUB_NY][BUB_NX];

    Animation* arrow;
    Animation* penguin;
    Animation* diable;
	Animation* gears;
	Animation* wheel;
	Animation* frame_top;
	Animation* chain1;
	Animation* chain2;
	Animation* longChain1;
	Animation* longChain2;
	Animation* nextBall;

	SDL_Surface* text;
	SDL_Rect* textLocation;


	bool bShowLimit;
    bool bCanLaunchBall;
	uint boardTop;
	uint score;
	
 
    /*LIST CONTAIN ALL BALLS IN THE GAME*/
    List* allBalls; //init in gamemanager
    /*table to index balls*/
    Ball* pos_index_bub[BUB_NY][BUB_NX];

	clock_t timeStart;
	clock_t timeStart2;
	clock_t timeStart3;

} Board;

Board* initBoard(int b_left, int b_right, int b_top, int b_bottom, int plr);
/*Function to calculate all ball fix positions*/
void calculateBallFixPos(Board* b);
void moveBalls(Board* b); // move balls down when the cieling move
void updateBoardLimit(Board* b); // Increment the board limit
void resetBalls(Board* b); // reset limit and board settings
void updateBoard(Board* b); //update the board
void deleteBoard(Board*); // delete the board
void moveArrowToLeft(Board* b); // responsible for moving the arrow to the left
void moveArrowToRight(Board* b); // responsible for moving the arrow to the right
void launch(Board* b); //launch the ball happen when pressed space or l
void updateScoreText(Board* b); // update the score text
void updateText(Board* b, char text[50]); // update the score text with a customp text
void loadNextBall(Board* b, int color); // Load the next ball