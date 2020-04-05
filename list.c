/*************************************************************************
* Project 	: Puzzle Bubble
* Author	: CHIDA Mohamed-Omar
* File		: list.c
* Date		: 03 Mai 2018
* Note 		: Linked List Core functions
**************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "Ball.h"
#include "list.h"

Node* createnode(Ball* data)
{
	Node * newNode = malloc(sizeof(Node));
	newNode->data = data;
	newNode->next = NULL;
	return newNode;
}

List * emptylist()
{
	List* list = malloc(sizeof(List));
	list->head = NULL;
	return list;
}

void add(Ball* data, List * list)
{
	Node * current = NULL;
	if (list->head == NULL) {
		list->head = createnode(data);
	}
	else {
		current = createnode(data);
		current->next = list->head;
		list->head = current;
	}
}

void delete(Ball* data, List * list)
{
	Node * current = list->head;
	Node * previous = current;
	while (current != NULL) {
		if (current->data == data) {
			previous->next = current->next;
			if (current == list->head)
				list->head = current->next;
			free(current);
			return;
		}
		previous = current;
		current = current->next;
	}
}

void reverse(List * list)
{
	Node * reversed = NULL;
	Node * current = list->head;
	Node * temp = NULL;
	while (current != NULL) {
		temp = current;
		current = current->next;
		temp->next = reversed;
		reversed = temp;
	}
	list->head = reversed;
}

void destroy(List * list)
{
	Node * current = list->head;
	Node * next = current;
	while (current != NULL) {
		next = current->next;
		SDL_FreeSurface(current->data->sprt);
		free(current);
		current = next;
	}
	free(list);
}

uint length(List* list)
{
	Node * current = list->head;
	Node * next = current;
	uint s = 0;
	while (current != NULL) {
		next = current->next;
		s++;
		current = next;
	}
	return s;
}