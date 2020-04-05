/*************************************************************************
* Project 	: Puzzle Bubble
* Author	: CHIDA Mohamed-Omar
* File		: Animation.c
* Date		: 07 Juin 2018
* Note 		: Responislbe for creating animations
**************************************************************************/

#ifndef __ANIMATION_H__
#define __ANIMATION_H__

#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include "list.h"
#include "defines.h"
#include <time.h>

typedef struct animation
{
    SDL_Surface* sprt;
	SDL_Rect* sprtFrame;
	SDL_Rect* sprtPosition;
	int currentAnim;
	int animLimit;
	int resetValue;
    clock_t lastAnimClock;
} Animation;

//List* allAnimations; //init in gamemanager

Animation* LoadAnimation(char path[50], uint AnimLimit, int posX, int posY, int sizeX, int sizeY);
void updateAnimation(Animation* anim, uint animLimit, uint restValue);
void setTimeAnim(Animation* anim);
void setCurrentAnim(Animation* anim, int cAnim);
void drawAnim(Animation* anim);
void IncreaseAnim(Animation* anim);
void DecreaseAnim(Animation* anim);
void setAnimPosition(Animation* anim, int posX, int posY);
void deleteAnim(Animation*);
void setAnimLimit(Animation* anim, int limit);
void setResetValue(Animation* anim, int cAnim);
void updateDefaultAnimation(Animation* anim);
#endif