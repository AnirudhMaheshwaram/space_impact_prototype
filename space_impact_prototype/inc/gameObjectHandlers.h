/*
 * gameObjectHandlers.h
 *
 *  Created on: Dec. 17, 2019
 *      Author: anirudh
 */
#include "linkedlist.h"
#include "definations.h"
#include "uartFunctions.h"
#include <stdlib.h>
#ifndef GAMEOBJECTHANDLERS_H_
#define GAMEOBJECTHANDLERS_H_
void intializeTaskParam(taskParam * taskParamAddr);
void reset_user_input();
void vPlayerTask(void * pvParameter);
xList * createGameObject(short id, short posx, short posy, short velx, short vely, short health, xList * gameObjects);
void vTaskEmeny(void * pvParameter);
void vTaskGOPosition(void * pvParameter);
void vTaskBullets(void * pvParameter);
void vTaskgameObjectHandler(void * pvParameter);
void vTaskUart(void * pvParameter);

#endif /* GAMEOBJECTHANDLERS_H_ */
