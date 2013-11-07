/*
 * game.c
 *
 *  Created on: Nov 4, 2013
 *      Author: C15Alex.Strom
 */
#include"game.h"
#include"lcdwrite.h"
#include<msp430.h>

unsigned char initPlayer(){
	return 0x80;}

void printPlayer(unsigned char player){
	writeCommandByte(player);
	writeDataByte('*');}

void clearPlayer(unsigned char player){
	writeCommandByte(player);
	writeDataByte(' ');}

unsigned char movePlayer(unsigned char player, unsigned char direction){
	clearPlayer(player);
	LCDclear();

	if(direction == BIT1){
		if(player != 0x87 && player != 0xc7){
			player++;
		}        }
	else if(direction == BIT2){
		if(player != 0x80 && player != 0xc0){
			player--;
		}
	}
	else if(direction == BIT3){
		if(player < 0x88){
			player+=0x40;
		}
		if(player> 0xdf){
			player+=0xc0;
		}
	}
	else if(direction == BIT4){
		player &= ~ROW_MASK;}
	return player;

}

char didPlayerWin(unsigned char player){
	return player == 0xC7;}


