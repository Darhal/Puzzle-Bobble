/*************************************************************************
* Project 	: Puzzle Bubble
* Author	: CHIDA Mohamed-Omar
* File		: main.c
* Date		: 07 Juin 2018
* Note 		: main entry
**************************************************************************/

#include "GameManager.h"

int main(int argc, char *argv[])
{
	init_SDL(); //Screen returned by the SDL

	loadMenu(); // LOAD MAIN MENU

	gameLogic(); // GAME LOGIC

	remove_SDL(); // remove everything
	return 0;
}
