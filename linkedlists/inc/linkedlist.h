/*
 * linkedlist.h
 *
 *  Created on: Dec. 4, 2019
 *      Author: anirudh
 */

#ifndef LINKEDLIST_H_
#define LINKEDLIST_H_

#ifndef configLIST_VOLATILE
	#define configLIST_VOLATILE
#endif /* configSUPPORT_CROSS_MODULE_OPTIMISATION */

struct xLIST_STRUCT
{
	volatile short id;	//<
	struct xLIST_STRUCT * volatile pxNext;	/*< Pointer to the next xListItem in the list. */
	struct xLIST_STRUCT * volatile pxPrevious;/*< Pointer to the previous xListItem in the list. */
	volatile short posx;									/*< Pointer to the object (normally a TCB) that contains the list item.  There is therefore a two way link between the object containing the list item and the list item itself. */
	volatile short posy;
	volatile short speedx;
	volatile short speedy;
	volatile short health;
};
typedef struct xLIST_STRUCT xList;


xList * vListCreateElement(xList * pAddr);

void vListInsert(xList * pAddr);

xList * vListDelete(xList * pAddr);

//xList * vListFind(xList * pAddr, void variable1, void variable2, char variableType, void condition);

//void vListFindDelete(xList * pAddr, void variable2,);

void vDeleteList(xList * pAddr);

#endif /* LINKEDLIST_H_ */
