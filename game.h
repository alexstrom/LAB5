/*
 * game.h
 *
 *  Created on: Nov 4, 2013
 *      Author: C15Alex.Strom
 */

#ifndef GAME_H_
#define GAME_H_
#define UP 1
#define DOWN 2
#define LEFT 3
#define RIGHT 4
#define ROW_MASK 0x40
#define NUM_MINES 2

unsigned char initPlayer();

void printPlayer(unsigned char player);

void clearPlayer(unsigned char player);

unsigned char movePlayer(unsigned char player, unsigned char direction);

char didPlayerWin(unsigned char player);

void collision (unsigned char player, unsigned char mine);


#endif /* GAME_H_ */
