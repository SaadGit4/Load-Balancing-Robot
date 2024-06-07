#include <hidef.h>      /* common defines and macros */
#include "derivative.h"      /* derivative-specific definitions */


void PLL_init(void);
void myDelay(void);

void SCI0_init(void);
void SCI0_Tx(unsigned char);
unsigned char SCI0_Rx(void);
void Forward(void);
void Back(void);
void Right(void);
void Left(void) ;
void Stop(void);

void IRQ_init(void);


unsigned char flag;
unsigned char myRxChar;



void interrupt 6 handler(){   //IRQ ISR
 
     

    

           
     
    myRxChar=SCI0_Rx();
    
    if ( myRxChar == 'F') {
      Stop();
    }
    if ( myRxChar == 'R') {
      Right();
    }
    if ( myRxChar == 'L') {
      Left();
    }    ;
     if ( myRxChar == 'B') {
      Back();
    }
     if ( myRxChar == 'S') {
      Stop();
    }     
    
 }



void main(void) {
  /* put your own code here */            
  
unsigned char myRxChar;


  PLL_init();
  SCI0_init();
  IRQ_init();
  
  
  DDRB = 0xFF;
  
  
	EnableInterrupts;



  for(;;) {
           
     myRxChar=SCI0_Rx();

    if ( myRxChar == 'F') {
      Forward();
    }    ;
     if ( myRxChar == 'R') {
      Right();
    }
    if ( myRxChar == 'L') {
      Left();
    }    ;
     if ( myRxChar == 'B') {
      Back();
    }
     if ( myRxChar == 'S') {
      Stop();
    }
    

      
    _FEED_COP(); /* feeds the dog */
  } /* loop forever */
  /* please make sure that you never leave main */
}



void PLL_init(void){

SYNR = 2;
REFDV = 0; // at 8MHz Osc -->  48MHz PLL
PLLCTL = 0x60;// ON, Auto
while(!(CRGFLG & 0x08));//wait the lock BIT TO SET
CLKSEL = CLKSEL | 0x80; // select the PLL clk
}

void myDelay(void){
unsigned char j;
unsigned int k;

 for(j=0;j<15;j++){
   for(k=0; k<20000; k++){
     j=j;
     k=k;
   
   }
 
 }

}                 


void SCI0_init(void){
    SCI0BDL = 156;
    SCI0BDH = 0; // 9600bps @ 24MHz E clk
    SCI0CR1 = 0; // No Loop, 8 data bits, no parity
    SCI0CR2 = 0x0C; // Enable Tx, Rx
      
}
void SCI0_Tx(unsigned char myByte){
  while(!(SCI0SR1 & 0x80));
  SCI0DRL = myByte;


}


unsigned char SCI0_Rx(void){
  while(!(SCI0SR1 & 0x20));
  return(SCI0DRL);

}

void Forward(void){
  PORTB = 0x05;  //PortB = b0000 0101      
}

void Back(void){
  PORTB = 0x0A;  //PortB = b0000 1010     
}

void Left(void){
  PORTB = 0x06;  //PortB = b0000 0110     
}

void Right(void){
  PORTB = 0x09;  //PortB = b0000 1001     
}

void Stop(void){
  PORTB = 0x00;  //PortB = b0000 0000     
}

void IRQ_init(void){

 INTCR = 0x40;// Enable IRQ on low level

}


