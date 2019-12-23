/*
 * linkedlist.c
 *
 *  Created on: Dec. 4, 2019
 *      Author: anirudh
 */

#include <stdlib.h>
#include "FreeRTOS.h"
#include "linkedlist.h"


xList * vListCreateElement(xList * pAddr){
	if(pAddr==NULL){
		xList * head = NULL;
		head = pvPortMalloc(sizeof(xList));
		head -> pxPrevious = NULL;
		head -> pxNext = NULL;
		return head;
	}
	xList * element = NULL;
	element = pvPortMalloc(sizeof(xList));
	element->pxNext = NULL;
	xList * last = pAddr;
	while(last->pxNext!=NULL){
		last = last->pxNext;
	}
	element->pxPrevious = last;
	last->pxNext = element;
	return element;
}

void vListInsert(xList * pAddr){
	xList * element = NULL;
	element = pvPortMalloc(sizeof(xList));
	element-> pxNext = pAddr->pxNext;
	pAddr-> pxNext = element;
	element -> pxPrevious = pAddr;
}

xList * vListDelete(xList * pAddr){

	xList * element;
	if(pAddr->pxPrevious!=NULL){
		element = pAddr->pxPrevious;
		element->pxNext= pAddr->pxNext;;
		element = pAddr->pxNext;
		element->pxPrevious=pAddr->pxPrevious;
		pvPortFree(pAddr);
		return element;
	}
	else{
		element = pAddr->pxNext;
		element->pxPrevious = NULL;
		pvPortFree(pAddr);
		return element;
	}
}

void vDeleteList(xList * pAddr){
	xList * next;
	xList * current = pAddr;
	while(current!=NULL){
		next = current->pxNext;
		pvPortFree(current);
		current = next;
	}
}

