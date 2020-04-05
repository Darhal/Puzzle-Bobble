/*************************************************************************
* Project 	: Puzzle Bubble
* Author	: CHIDA Mohamed-Omar
* File		: utils.c
* Date		: 07 Juin 2018
* Note 		: Some util functions
**************************************************************************/

#include "GameManager.h"
#include <time.h>

int random_number(int min_num, int max_num)
{
	int result = 0, low_num = 0, hi_num = 0;

	if (min_num < max_num)
	{
		low_num = min_num;
		hi_num = max_num + 1; // include max_num in output
	}
	else {
		low_num = max_num + 1; // include max_num in output
		hi_num = min_num;
	}

	result = (rand() % (hi_num - low_num)) + low_num;
	return result; // THIS FOR RANDOM BALLS
	/*THIS IS FOR SAME COLOR JUST TO TEST*/
	if (max_num <= BUB_NX)
		return 3;
	else
		return 28;
}

SDL_Surface* loadSprite(char path[50])
{
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
	return sprt;
}


SDL_Surface* loadText(char text[50])
{
#ifdef TEXT
	TTF_Font* font = TTF_OpenFont("assets/fonts/arial.ttf", 16);
	SDL_Surface* textSurface = (SDL_Surface*)malloc(sizeof(SDL_Surface));
	SDL_Color foregroundColor = { 255, 255, 255 };
	SDL_Color backgroundColor = { 65, 65, 65 };
	textSurface = TTF_RenderText_Shaded(font, text,
		foregroundColor, backgroundColor);
	TTF_CloseFont(font);

	return textSurface;
#endif // TEXT
	return NULL;
}
