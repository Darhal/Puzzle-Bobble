/*************************************************************************
* Project 	: Puzzle Bubble
* Author	: CHIDA Mohamed-Omar
* File		: Animation.c
* Date		: 07 Juin 2018
* Note 		: Responislbe for creating animations
**************************************************************************/

#include "Animation.h"
#include "GameManager.h"
#include <time.h>

Animation* LoadAnimation(char path[50],uint AnimLimit, int posX, int posY, int sizeX, int sizeY)
{
    Animation* anim = (Animation*)malloc(sizeof(Animation));
    anim->sprt = loadSprite(path);
    anim->sprtPosition = (SDL_Rect*)malloc(sizeof(SDL_Rect));
    anim->sprtFrame = (SDL_Rect*)malloc(sizeof(SDL_Rect));
    /*POSITION OF THE SPRITE IN THE SCREEN*/
	anim->sprtPosition->w = sizeX;
	anim->sprtPosition->h = sizeY;
	anim->sprtPosition->x = posX;
	anim->sprtPosition->y = posY;

	/* Define the source rectangle for the BlitSurface */
	anim->sprtFrame->w = sizeX;
	anim->sprtFrame->h = sizeY;
	anim->sprtFrame->x = 0;
    anim->sprtFrame->y = 0;
    anim->lastAnimClock = 0;
    anim->currentAnim=0;
    anim->animLimit = AnimLimit;
    //add(allAnimations, anim);
    return anim;
}
 
void setTimeAnim(Animation* anim)
{
	clock_t start;
	start = clock();
	anim->lastAnimClock = start; // SET THE CPU TIME
}

void updateAnimation(Animation* anim, uint animLimit, uint restValue)
{
    clock_t start;
	start = clock();
    if ((((double)(start - anim->lastAnimClock))/CLOCKS_PER_SEC) >=  0.019){
        anim->currentAnim++;
        setTimeAnim(anim);
        if (anim->currentAnim > animLimit) anim->currentAnim = restValue;
    } 
    anim->sprtFrame->y = anim->sprtFrame->h*anim->currentAnim;
	SDL_BlitSurface(anim->sprt, anim->sprtFrame, localEnv.screen, anim->sprtPosition); 
}

void updateDefaultAnimation(Animation* anim)
{
	clock_t start;
	start = clock();
	if ((((double)(start - anim->lastAnimClock)) / CLOCKS_PER_SEC) >= 0.019) {
		if (anim->resetValue < anim->animLimit) {
			anim->currentAnim++;
			if (anim->currentAnim > anim->animLimit) anim->currentAnim = anim->resetValue;
		}
		else{
			anim->currentAnim--;
			if (anim->currentAnim < anim->animLimit) anim->currentAnim = anim->resetValue;
		}
		setTimeAnim(anim);
	}
	
	anim->sprtFrame->y = anim->sprtFrame->h*anim->currentAnim;
	SDL_BlitSurface(anim->sprt, anim->sprtFrame, localEnv.screen, anim->sprtPosition);
}

void setCurrentAnim(Animation* anim, int cAnim)
{
    anim->currentAnim = cAnim;
}

void setResetValue(Animation* anim, int cAnim)
{
	anim->resetValue = cAnim;
}

void setAnimLimit(Animation* anim, int limit)
{
	anim->animLimit = limit;
}

void IncreaseAnim(Animation* anim){ anim->currentAnim++;}

void DecreaseAnim(Animation* anim){ anim->currentAnim--;}

void drawAnim(Animation* anim)
{
    if (anim->currentAnim > anim->animLimit) anim->currentAnim = anim->animLimit;
	if (anim->currentAnim<0) anim->currentAnim = 0;
    anim->sprtFrame->y = anim->sprtFrame->h*anim->currentAnim;
	SDL_BlitSurface(anim->sprt, anim->sprtFrame, localEnv.screen, anim->sprtPosition); 
}

void setAnimPosition(Animation* anim, int posX, int posY)
{
    anim->sprtPosition->x = posX;
	anim->sprtPosition->y = posY;
}

void deleteAnim(Animation* anim)
{
	SDL_FreeSurface(anim->sprt);
	free(anim);
}