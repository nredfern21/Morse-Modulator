/*
 * File:   REAL_PROJECT_MAIN.c
 * Author: redfe017
 *
 * Created on April 15, 2022, 1:14 PM
 */
#include "xc.h"
#include <stdio.h>
#include "lab5_displayLib.h"
#include "project_ADClib.h"
#include "project_translatorLib.h"

#pragma config ICS = PGx1          // Comm Channel Select (Emulator EMUC1/EMUD1 pins are shared with PGC1/PGD1)
#pragma config FWDTEN = OFF        // Watchdog Timer Enable (Watchdog Timer is disabled)
#pragma config GWRP = OFF          // General Code Segment Write Protect (Writes to program memory are allowed)
#pragma config GCP = OFF           // General Code Segment Code Protect (Code protection is disabled)
#pragma config JTAGEN = OFF        // JTAG Port Enable (JTAG port is disabled)


// CW2: FLASH CONFIGURATION WORD 2 (see PIC24 Family Reference Manual 24.1)
#pragma config I2C1SEL = PRI       // I2C1 Pin Location Select (Use default SCL1/SDA1 pins)
#pragma config IOL1WAY = OFF       // IOLOCK Protection (IOLOCK may be changed via unlocking seq)
#pragma config OSCIOFNC = ON       // Primary Oscillator I/O Function (CLKO/RC15 functions as I/O pin)
#pragma config FCKSM = CSECME      // Clock Switching and Monitor (Clock switching is enabled, 
                                       // Fail-Safe Clock Monitor is enabled)
#pragma config FNOSC = FRCPLL      // Oscillator Select (Fast RC Oscillator with PLL module (FRCPLL))

extern volatile int overflow;


void setup(){
    _RCDIV = 0;
    AD1PCFG = 0xffff;
}

int main(void) {
    setup();                                                    //Initialization
    lcd_init();
    adc_init();
    T2_init();
    
    int currentsymbol = NILL;                                   //Holds the current symbol
    unsigned long TimeElapsed = 0;                              //How long the finger has been up for
    unsigned long OnTime = 0;                                   //Holds time at which finger was held down
    int currentPos;                                             //These are the position values of the flex sensor
    int previousPos;
    char letter;                                           //Holds the character
    int s1 = NILL;                                              //Holds the symbols
    int s2 = NILL;
    int s3 = NILL;
    int s4 = NILL;
    int printState = 0;                                         //This is a state variable that determines if a character can be printed (1 = can be print; 0 = can't be printed)
    int resetState = 0;                                         // This is a state variable that determines if a reset can be done (1 = reset)
    lcd_setCursor(0,0);
    while(1){
        previousPos = currentPos;                                //changes last position to previous
        currentPos = check_up_or_down();                         //Checks the current position of the flex sensor
        if (currentPos == down && previousPos == up){            //If fingers moved down reset timer and OnTime values
            TMR2 = 0;
            overflow = 0;
            OnTime = 0;
        }
        else if (currentPos == up && previousPos == down){      //Finger moves back up, dot or dash is given
            OnTime = ((uint32_t)(PR2+1)*overflow + TMR2);       //Calculates how long the finger was down for
            
            if (OnTime > (2*(PR2 +1))){                         //More than two seconds, current symbol is a dash
                currentsymbol = dash;
                s4 = s3;                                        //Shifting symbols down for current symbol
                s3 = s2;
                s2 = s1;
                s1 = currentsymbol;
                printState = 1;                                 //State variable changed to one
            }
            else if (OnTime < (2*(PR2 +1))){                    //Less than two seconds, current symbol is a dot
               currentsymbol = dot;
                s4 = s3;                                        //Shifting symbols down for current symbol
                s3 = s2;
                s2 = s1;
                s1 = currentsymbol;
                printState = 1;                                 //State variable changed to one
            }
        }
        else if (currentPos == up && printState == 1){          //If finger has been up for a while, and a character is ready to be printed go into this loop
            
            TimeElapsed = ((uint32_t)(PR2+1)*overflow + TMR2) - OnTime; //Calculates the time elapsed since the finger has been up
            
            if (TimeElapsed >= (3 * (uint32_t)(PR2 +1))){               // If time elapsed is great than 3 seconds, print the character (3 is arbitrary)
                int i = 0;                                      //Counter variable
                for(i = 0; i < 3; i++){                         //Puts all of the symbols in the right place. Since s4 is the first symbol, it moves the first symbol up accordingly if less than 4 symbols are given
                    if(s4 != NILL){                             //Breaks out of the loop if s4 is not NILL
                        break;
                    }
                    s4 = s3;                                    //Shifts all of the symbols up a place and makes the lower state NILL. Makes sure Earliest symbols are at the highest s values
                    s3 = s2;
                    s2 = s1;
                    s1 = NILL;
                }

                letter = MorseTable(s4, s3, s2, s1);            //Helper function that determines the character depending on the symbols
                lcd_printChar(letter);                          //Prints character to the lcd screen
                s4 = NILL;                                      //Resets the symbols
                s3 = NILL;
                s2 = NILL;
                s1 = NILL;
                TMR2 = 0;                                       //Resets the timer values and state variables
                overflow = 0;
                OnTime = 0;
                printState = 0;
                resetState = 0;
            }
        }
        else if((((uint32_t)(PR2+1)*overflow + TMR2) - OnTime) >= (7 * (uint32_t)(PR2 +1)) && resetState != 1){ //If the time elapsed since the last printed character is greater than 7 seconds, print a space
            TMR2 = 0;                                           //Resets timer values
            overflow = 0;
            OnTime = 0;
            lcd_printChar(' ');                                 //Prints space to the lcd screen
            resetState = 1;
        }
        if((((uint32_t)(PR2+1)*overflow + TMR2) - OnTime) >= (8 * (uint32_t)(PR2 +1)) && resetState ==1){
            TMR2 = 0;                                           //Resets timer values
            overflow = 0;
            OnTime = 0;
            resetState = 0;
            printState = 0;
            lcd_cmd(0b00000001);                                //RESET command for LCD
            lcd_setCursor(0,0);
        }
            
    } 
}

  
    
   