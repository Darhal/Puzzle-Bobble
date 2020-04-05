/*************************************************************************
* Project 	: Puzzle Bubble
* Author	: CHIDA Mohamed-Omar, BATTIKH Lynda
* File		: GameManager.h
* Date		: 07 Juin 2018
* Note 		: Global Game varriables
**************************************************************************/
#ifndef __GVars_H__
#define __GVars_H__

#include "defines.h"
#include "Animation.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "Board.h"

typedef struct GeneralEnv
{
	SDL_Surface* screen;
	SDL_Surface* frame;
	SDL_Surface* menu;
	int PlayerCount;
	Board* GameBoard[2];
} GeneralEnviroment;
// STRUCT STORING ALL VARRIABLES
GeneralEnviroment localEnv;
int BoardIndex;

/***************************
* MAIN FUNCTION PROTOTYPES *
****************************/
// function to init sdl
SDL_Surface* init_SDL();

// to remove sdl
void remove_SDL();

//init the ball at the beginning of the game
void initBalls(Board*);

// get random numbers
int random_number(int, int);

// init game resources
void initGame();

// to replay it take bool wether the player lost or won the current round
void replay(bool, Board*);

/*Catch any keyboard events*/
void HandleEvent(SDL_Event, int*);

// called every frame
void gameLogic();

// load an image to memory
SDL_Surface* loadSprite(char path[50]);

// load menu
void loadMenu();

//unload board
void returnToMenu();

#ifdef TEXT
SDL_Surface* loadText(char text[50]);
#endif
#endif 