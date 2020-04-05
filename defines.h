/*************************************************************************
* Project 	: Puzzle Bubble
* Author	: CHIDA Mohamed-Omar, BATTIKH Lynda
* File		: defines.h
* Date		: 07 Juin 2018
* Note 		: Game defines
**************************************************************************/
#ifndef __defines_H__
#define __defines_H__

#include <SDL.h>
#undef WIN_PLATFORM 			// CHANGE THIS IF YOUR ON LINUX
#define TEXT						// CHANGE THIS IF YOU HAVE TFF LIBRARY
#ifdef TEXT
#include <SDL_ttf.h>
#endif
#ifdef WIN_PLATFORM
	#pragma warning(disable:4996) // DISABLE STUPID VS ERRORS
	#define TIME_LAPSE		 0.1 // DELTA TIME FOR REBOUND DIFFERENT FOR DIFFERENT CPUs
#else
	#define TIME_LAPSE		0.01 // DELTA TIME FOR REBOUND DIFFERENT FOR DIFFERENT CPUs
#endif
/* Size of the window */
#define SCREEN_WIDTH        720 // horizontal size of the frame
#define SCREEN_HEIGHT       540 // vertical size of the frame
#define WIN_TITLE           "Puzzy Bubble (Groupe: b6 | TP3.1)"
/* Size of the sprite; this is a square */
#define ARROW_SIZE_WIDTH    187
#define ARROW_SIZE_HEIGHT   157
/* Size of the grass texture picture */
#define BG_SIZE             32
#define PI                  3.14159265359
#define BOARD_LEFT          200 // x-coord of the left border of the game board
#define BOARD_RIGHT         520 // x-coord of the right border of the game board
#define BOARD_TOP           31  // y-coord of the top border of the game board
#define BOARD_BOTTOM        422 // y-coord of the bottom border of the game board (will be useful in next levels)
#define LAUNCHER_WIDTH      187 // width of the launcher surface
#define LAUNCHER_HEIGHT     157 // height of the launcher surface
#define LAUNCHER_CENTER     94  // y-coord of the launcher center
#define LAUNCHER_DIV        48  // PI/LAUNCHER_DIV is the angular distance between each of the 45 launcher orientations
#define BUB_SIZE            40  // horizontal and vertical size of the bubble surface
#define VELOCITY            2   // bubbles velocity
#define BUB_NX              8   //max. number of bubbles in horizontal direction
#define BUB_NY              11  //max. number of bubbles in vertical directions
#define SPACEMENT_X         34 // spacement between balls in impair lines
#define BUB_COLOR			8 // NUMBER OF BUB COLORS
#define uint				unsigned int // TO MAKE IT EASIER WRITING UINT
#define ALPHA				0.87 // alpha for detect collision
#define LIMIT_CHANGE		15 // TIME TO UPDATE THE BOARD LIMIT

#endif 
