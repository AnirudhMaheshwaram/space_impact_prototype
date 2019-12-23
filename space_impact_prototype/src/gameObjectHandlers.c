#include "gameObjectHandlers.h"
void intializeTaskParam(taskParam * taskParamAddr){
	player player1;//initialize player
	player1.posx = intialPlayerxPosition;
	player1.posy = intialPlayeryPosition;
	player1.health = 100;
	xList bullets = vListCreateElement(NULL);	//initialize bullets
	bullets.id = 2;
	bullets.posx = intialPlayerxPosition;
	bullets.posy = intialPlayeryPosition;
	bullets.speedx = xAxisSpeed;
	bullets.speedy = (yAxisSpeed<<1),	// speed
	bullets.health = 20;
	xList enemies = vListCreateElement(NULL);	//initialize enemies
	enemies.id = 3;
	enemies.posx = 4;
	enemies.posy = yAxisRes-4;
	enemies.speedx = xAxisSpeed;
	enemies.speedy = (yAxisSpeed<<1),	// speed
	enemies.health = 30;
	user_input_str userInput;	//initialize user input
	userInput.down=0;
	userInput.up=0;
	taskParamAddr->bulletsAddr=*bullets;
	taskParamAddr->enemiesAddr=*enemies;
	taskParamAddr->playerAddr=*player1;
	taskParamAddr->playerAlive = TRUE;
}

void reset_user_input(){//resets user input to zeros
	user_input.down = 0;
	user_input.up = 0;
	user_input.weapon1=0;
	user_input.weapon2=0;
}

void vPlayerTask(void * pvParameter){//takes user input and modifies player position
	/*get player input*/
	taskParam * taskParameter = (taskParam *)pvParameter;
	player * pAddr = taskParameter->playerAddr;
	portTickType	xLastWakeTime;
	//check for player health
	while(playerAlive){
		if(pAddr->health<=0){//checks for health and modifies playerAlive flag
			playerAlive=FALSE;
		}
		if(user_input.down>0){
			pAddr->posx = pAddr->posx+user_input.down;
		}
		if(user_input.up>0){
			pAddr->posx = pAddr->posx-user_input.up;
		}
		/*if(user_input.weapon1>0){
			createGameObject(6, pAddr->posx, (pAddr->posy+4), 0, (yAxisSpeed*2), 20);
		}*/
		/*uncommnent if your are using second weapon
		 * if(user_input.weapon2>0){
			createGameObject(7, pAddr->posx, ((pAddr->posy)+4), 0, 3, 20);
		}*/
		reset_user_input();
		vTaskDelayUntil(&xLastWakeTime,framerate);
	}
}
/*creates new linked list with filled in atributes and returns the new address*/
xList * createGameObject(short id, short posx, short posy, short velx, short vely, short health, xList * gameObjects){
	xList * newObject = vListCreateElement(gameObjects);
	newObject->id = id;
	newObject->posx = posx;
	newObject->posy = posy;
	newObject->speedx = velx;
	newObject->speedy = vely;
	newObject->health = health;
	return newObject;
}
/*deletes the element of linked list and
 * return the address of element taking its place*/
xList * deleteGameObject(xList* current, xList * head){
	if(current == head){
		head = vListDelete(current);
		return head;
	}
	else{
		return vListDelete(current);
	}
}

/*used to generate random number
 * used to spawn random types of enemies at random location*/
short randomNumberGenerator(int upperLimit, int lowerLimit){
	return (short)((rand() % (upperLimit - lowerLimit + 1)) + lowerLimit);
}
/*creates a enemy every 1.6seconds*/
void vTaskEmeny(void * pvParameter){
	int id;
	portTickType	xLastWakeTime;
	taskParam * taskParameter = (taskParam *)pvParameter;
	while(taskParameter->playerAlive){
		xList * enemiesAddr = taskParameter->enemiesAddr;
		createGameObject(id = randomNumberGenerator(3,3), //random emeny id generated between 3 and 3
			randomNumberGenerator(0,xAxisRes),	//random emeny position generated
			(yAxisRes-4),	//enemy position started from left most
			xAxisSpeed, yAxisSpeed,	//enemy speed
			id*10, enemiesAddr);	//Enemy health
		vTaskDelayUntil(&xLastWakeTime,(framerate<<3));
	}
}
/*creates continous stream of bullets from player location*/
void vTaskBullets(void * pvParameter){
	int id = 2;
	portTickType	xLastWakeTime;
	taskParam * taskParameter = (taskParam *)pvParameter;
	while(taskParameter->playerAlive){
		xList * bulletAddr = taskParameter->bulletsAddr;
		createGameObject(id, //random emeny id generated between 3 and 3
			pAddr->posx,(pAddr->posy+4),	//bullet position same a player position
			xAxisSpeed, (yAxisSpeed<<1),	// speed
			20,bulletAddr);
		vTaskDelayUntil(&xLastWakeTime,(framerate));
	}
}
/*checks for collision between game objects*/
void vTaskgameObjectHandler(void * pvParameter){
	portTickType	xLastWakeTime;
	taskParam * taskParameter = (taskParam *)pvParameter;
	while(taskParameter->playerAlive){
		xList * bulletAddr = taskParameter->bulletsAddr;
		xList * enemiesAddr = taskParameter->enemiesAddr;
		player * playerAddr = taskParameter->playerAddr;
		while((enemiesAddr->pxNext)!=NULL){
			/*loop checks for enemy and player collision*/
			if((((playerAddr->posx)+8)>(enemiesAddr->posx))&&
					(((playerAddr->posy)+16)>(enemiesAddr->posy))){
				playerAddr->health = playerAddr->health-enemiesAddr->health;
				enemiesAddr->health = enemiesAddr->health - playerAddr->health;
			}
			while((bulletAddr->pxNext)!=NULL){
				/*loop checks for enemy and bullets collision*/
				if((bulletAddr->posx<=enemiesAddr->posx)&&
						((bulletAddr->posx+8)>=enemiesAddr->posx)&&
						(bulletAddr->posy==enemiesAddr->posy)){
					enemiesAddr->health = enemiesAddr->health - bulletAddr->health;
					bulletAddr = deleteGameObject(bulletAddr,taskParameter->bulletsAddr);
				}
				else{
					bulletAddr = bulletAddr->pxNext;
				}
			}
			if(enemiesAddr->health>0){
				enemiesAddr = enemiesAddr->pxNext;
			}
			else{
				enemiesAddr = deleteGameObject(enemiesAddr,taskParameter->enemiesAddr);
			}
		}
		vTaskDelayUntil(&xLastWakeTime,framerate<<1);

	}
}
void vTaskUart(void * pvParameter){
	//used to send game object location through uart
	portTickType	xLastWakeTime;
	taskParam * taskParameter = (taskParam *)pvParameter;
	while(taskParameter->playerAlive){
		xList * bulletAddr = taskParameter->bulletsAddr;
		xList * enemiesAddr = taskParameter->enemiesAddr;
		player * playerAddr = taskParameter->playerAddr;
		/*used three time to avoid any errors on reciever side*/
		sendMessage(0x00);	//clears the screen
		sendMessage(0x00);	//clears the screen
		sendMessage(0x00);	//clears the screen
		sendMessage(0x01);	//code for player position
		sendMessage((uint8_t)playerAddr->posx);
		sendMessage((uint8_t)playerAddr->posy);
		while(enemiesAddr->pxNext!=NULL){
			//loop send all enemy information
			sendMessage(0x03);	//code for enemy position
			sendMessage((uint8_t)enemiesAddr->posx);//send position as byte
			sendMessage((uint8_t)enemiesAddr->posy);
			enemiesAddr = enemiesAddr->pxNext;
		}
		while(bulletAddr->pxNext!=NULL){
			sendMessage(0x02);	//code for enemy position
			sendMessage((uint8_t)bulletAddr->posx);//send position as byte
			sendMessage((uint8_t)bulletAddr->posy);
			bulletAddr = bulletAddr->pxNext;
		}
	vTaskDelayUntil(&xLastWakeTime,framerate);
	}
}
/*updates GO postion using their speed parameter*/
void vTaskGOPosition(void * pvParameter){
	portTickType	xLastWakeTime;
	taskParam * taskParameter = (taskParam *)pvParameter;
	while(taskParameter->playerAlive){
		xList * bulletAddr = taskParameter->bulletsAddr;
		xList * enemiesAddr = taskParameter->enemiesAddr;
		while(enemiesAddr->pxNext!=NULL){
			/*adds enemy object speed to position*/
			enemiesAddr->posx = enemiesAddr->posx+enemiesAddr->speedx;
			enemiesAddr->posy = enemiesAddr->posy-enemiesAddr->speedy;
			if((enemiesAddr->posx<1)&&(enemiesAddr->posx>(xAxisRes-1))){
				//reverse polarity of speed if enemy is going out
				//off vertical screen boundaries
				enemiesAddr->speedx = enemiesAddr->speedx*-1;
			}
			if((enemiesAddr->posy)<1){
				deleteGameObject(enemiesAddr,taskParameter->enemiesAddr);
			}
		}
		while(bulletAddr->pxNext!=NULL){//need to only update horizontal postion of bullet objects
			bulletAddr->posy = bulletAddr->posy+bulletAddr->speedy;
			if((bulletAddr->posx)>yAxisRes){
				bulletAddr = deleteGameObject(bulletAddr,taskParameter->bulletsAddr);
			}

		}
		vTaskDelayUntil(&xLastWakeTime,framerate);
	}
}



