#include <msp430.h> 
#include "lcdwrite.h"
#include "game.h"
#include "button.h"
#include "clkspeed.h"

/*
 * main.c
 */

void init_timer();
void init_buttons();
void gameWon();
void gameOver();

char count = 0;
char inprogress;
char BUTTON;
char HIT;	//Got this idea of hit from c2c schiners code

char message1[] = "you     ";
char message2[] = "win!    ";
char message3[] = "game    ";
char message4[] = "over!   ";

int main(void){
	WDTCTL = (WDTPW|WDTHOLD);
      unsigned char player = initPlayer();
      initSPI();
      init_timer();
      init_buttons();
      LCDinit();
      LCDclear();
      printPlayer(player);
      HIT = 0;
      inprogress = 1;
      init_timer();
      __enable_interrupt();

      while(1)        {
    	  LCDclear();
    	  printPlayer(player);

    	  while(inprogress){
    	  LCDclear();
    	  printPlayer(player);

    	  if(HIT){
    		  HIT = 0;
    		  count = 0;
    		  player = movePlayer(player, BUTTON);
    		  TACTL |= TACLR;
    	  }
    	  if(didPlayerWin(player)){
    		  inprogress = 0;
    		  gameWon();
    		  player = initPlayer();
    		  while(!inprogress){

    		  }
    	  }
    	  }
    	  if(!inprogress){
    		  gameOver();
    		  player = initPlayer();
    		  while(!inprogress);
    	  }
      }
      return 0;}

#pragma vector=TIMER0_A1_VECTOR
__interrupt void TIMER0_A1_ISR(){
	TACTL &= ~TAIFG;
	count++;
	if (count >= 4)    {
		inprogress = 0;
	}
}

void testAndRespondToButtonPush(char buttonToTest){
	if (buttonToTest & P2IFG)    {
		if (buttonToTest & P2IES)        {
			inprogress = 1;
			P2IFG &= ~buttonToTest;
			BUTTON = buttonToTest;
			HIT = 1;
		}
		else        {
			__delay_cycles(1000);
		}
		P2IES ^= buttonToTest;
		P2IFG &= ~buttonToTest;
	}
}


#pragma vector = PORT2_VECTOR

__interrupt void Port_2(void){

	testAndRespondToButtonPush(BIT1);
	testAndRespondToButtonPush(BIT2);
	testAndRespondToButtonPush(BIT3);
	testAndRespondToButtonPush(BIT4);}

void init_timer(){
	TACTL &= ~(MC1|MC0);
	TACTL |= TACLR;
	TACTL |= TASSEL1;
	TACTL |= ID1|ID0;
	TACTL &= ~TAIFG;
	TACTL |= MC1;
	TACTL |= TAIE;
}

void init_buttons(){
	P2DIR &= ~(BIT1|BIT2|BIT3|BIT4);
	P2IE |= BIT1|BIT2|BIT3|BIT4;
	P2IES |= BIT1|BIT2|BIT3|BIT4;
	P2REN |= BIT1|BIT2|BIT3|BIT4;	// forgot to enable resistors had to look at  C2C schriners code
	P2OUT |= BIT1|BIT2|BIT3|BIT4;
	P2IFG &= ~(BIT1|BIT2|BIT3|BIT4);
}

void gameWon(){
	LCDclear();
	cursorToLineOne();
	writeString(message1,8);
	cursorToLineTwo();
	writeString(message2,8);
}
void gameOver(){
	LCDclear();
	cursorToLineOne();
	writeString(message3,8);
	cursorToLineTwo();
	writeString(message4,8);
}


