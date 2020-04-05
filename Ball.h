/*************************************************************************
* Project 	: Puzzle Bubble
* Author	: CHIDA Mohamed-Omar
* File		: Ball.h
* Date		: 07 Juin 2018
* Note 		: A little bug when the ball hit the top left corner
**************************************************************************/

#ifndef __BALL_H__
#define __BALL_H__

#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include "GameManager.h"
#include "list.h"

/*********************
Struct Ball
**********************/
typedef struct ball
{
	SDL_Surface* sprt;
	SDL_Rect* sprtFrame;
	SDL_Rect* sprtPosition;
	int currentBallAnim;
	bool ballLaunched;
	bool ballBounce;
	double alpha;
	double tempX; /*THESE TWO TO FIX THE ANGLE BUG*/
	double tempY; /*THESE TWO TO FIX THE ANGLE BUG*/
	double lastReboundSec;
	int x;
	int y;
	int color;
	Board* current_board;
} Ball;


char* ballColor[BUB_COLOR];

/*************************************
function loadBall
*Load a ball into memeory and init it
@param unisgned int color
@param Board* board
@return Ball*
**************************************/
Ball* loadBall(uint, Board*);

/*************************************
function launchBall
*Responsible for launching the ball
@param Ball* ball
@param int currentBallAnim
@param Board* board
**************************************/
void LaunchBall(Ball*, int, Board*);

/*************************************
function fixBall
* To fix the ball in the right position
@param Ball* ball
**************************************/
void fixBall(Ball*);

/*************************************
function Rebound
* Responsible for rebounding the ball
when it hit the border
@param Ball* ball
**************************************/
void Rebound(Ball*);

/*************************************
function MoveBall
* Responsible of moving the ball
called every frame
@param Ball* ball
**************************************/
void MoveBall(Ball*);

/*************************************
function setPosition
* set ball position
@param Ball* ball
@param int x
@param int y
**************************************/
void setPosition(Ball*, int, int);

/*************************************
function getBall
* get the ball from a given id
@param int id
@param Board* board
**************************************/
Ball* getBall(Board*);

/*************************************
function checkCollision
* check collision
@param Ball* ball
@param int pos Y in the table
@param int pos X in the table
@return boolean
**************************************/
bool checkCollision(Ball*, int, int);

/*************************************
function setTime
* set the all time for rebound Bug
@param Ball* ball
**************************************/
void setTime(Ball*);

/**************************************
* function for detecting nearyby balls
* @param int x position of the ball
* @param int y position of the ball
* @param color of the ball
* @param Ball* the ball
**************************************/
int detectConnectedBalls(int, int, int, Ball*);

/**************************************
* function to delete a specifi ball
* @param Ball* ball
**************************************/
void deleteBall(Ball*);

/**************************************
* function to delete a specific ball
* at a specific position
* @param int x pos of the ball
* @param int y pos of the ball
* @param Ball* the ball
**************************************/
void deleteBallAt(int, int, Ball*);

/**************************************
* function to check balls should be 
* deleted
* @param int x pos of the ball
* @param int y pos of the ball
* @param Ball* the ball
**************************************/
bool checkForBallsToDelete(int, int, Ball*);

/**************************************
* function to load destruction 
* animation
* @param Ball* the ball
**************************************/
void loadDestructionAnim(Ball* ball);

/**************************************
* function to check for limit
* @param Board* the board
**************************************/
bool checkForLimit(Board* board);
#endif 