/*************************************************************************
* Project 	: Puzzle Bubble
* Author	: CHIDA Mohamed-Omar
* File		: list.h
* Date		: 03 Mai 2018
* Note 		: Linked List Core functions
**************************************************************************/

#ifndef LINKEDLIST_HEADER
#define LINKEDLIST_HEADER

#include <stdio.h>
#include <stdlib.h>

typedef struct ball Ball;

typedef struct node {
  struct ball* data;
  struct node* next;
} Node;

typedef struct list {
  Node* head; 
} List;

List * emptylist();
void add(Ball* data, List * list);
void delete(Ball* data, List * list);
void reverse(List * list);
void destroy(List * list);
Node* createnode(Ball* data);
unsigned int length(List* list);
#endif
