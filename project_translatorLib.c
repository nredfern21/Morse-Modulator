/*
 * File:   redfe017_project_translatorLib.c
 * Authors: Nathan Redfern, Andy Lambrecht, Ben Deyle
 *
 * Created on April 15, 2022, 1:58 PM
 */


#include "xc.h"
#include "lab5_displayLib.h"
#include "project_translatorLib.h"



char MorseTable(int first, int second, int third, int fourth);
int check_up_or_down(void);
void __attribute__((__interrupt__,__auto_psv__)) _T2Interrupt(void);
void T2_init(void);
volatile int overflow;

void __attribute__((__interrupt__,__auto_psv__)) _T2Interrupt(void) 
{
    _T2IF = 0;             //clear interrupt flag
    overflow++;
    
}

void T2_init(void){     //timer initialization of 1 sec
    TMR2 =0;
    T2CON = 0;
    T2CONbits.TCKPS = 0b11;
    PR2 = 62499;
    
    T2CONbits.TON =1;
    _T2IF = 0;
    _T2IE = 1;
    }
int check_up_or_down(void){
    int val;
    val = ADC1BUF0;
    if (val < 225){     // if latest value stored in ADC register return up or down
        return down;
    }else {
        return up;
    }
}

char MorseTable(int first, int second, int third, int fourth){ // depending on the four values passed in, the function returns the corresponding morse letter
    
    if (first == dot && second == dash && third == NILL){return 'A';}
    else if (first == dash && second == dot && third == dot && fourth == dot){return 'B';}
    else if (first == dash && second == dot && third == dash && fourth == dot){return 'C';}
    else if (first == dash && second == dot && third == dot && fourth == NILL){return 'D';}
    else if (first == dot && second == NILL){return 'E';}
    else if (first == dot && second == dot && third == dash && fourth == dot){return 'F';}
    else if (first == dash && second == dash && third == dot && fourth == NILL){return 'G';}
    else if (first == dot && second == dot && third == dot && fourth == dot){return 'H';}
    else if (first == dot && second == dot && third == NILL){return 'I';}
    else if (first == dot && second == dash && third == dash && fourth == dash){return 'J';}
    else if (first == dash && second == dot && third == dash && fourth == NILL){return 'K';}
    else if (first == dot && second == dash && third == dot && fourth == dot){return 'L';}
    else if (first == dash && second == dash && third == NILL){return 'M';}
    else if (first == dash && second == dot && third == NILL){return 'N';}
    else if (first == dash && second == dash && third == dash && fourth == NILL){return 'O';}
    else if (first == dot && second == dash && third == dash && fourth == dot){return 'P';}
    else if (first == dash && second == dash && third == dot && fourth == dash){return 'Q';}
    else if (first == dot && second == dash && third == dot && fourth == NILL){return 'R';}
    else if (first == dot && second == dot && third == dot && fourth == NILL){return 'S';}
    else if (first == dash && second == NILL){return 'T';}
    else if (first == dot && second == dot && third == dash){return 'U';}
    else if (first == dot && second == dot && third == dot && fourth == dash){return 'V';}
    else if (first == dot && second == dash && third == dash && fourth == NILL){return 'W';}
    else if (first == dash && second == dot && third == dot && fourth == dash){return 'X';}
    else if (first == dash && second == dot && third == dash && fourth == dash){return 'Y';}
    else if (first == dash && second == dash && third == dot && fourth == dot){return 'Z';}
    else{return ' ';}
}




