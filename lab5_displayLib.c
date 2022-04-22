/*
 * File:   redfe017_lab5_displayLib.c
 * Author: nathanredfern
 *
 * Created on April 2, 2022, 9:52 PM
 */


#include "xc.h"
#include "lab5_displayLib.h"

    void lcd_cmd(char Package);
    void lcd_setCursor(char x, char y);
    void lcd_printChar(char myChar);
    void lcd_init(void);
    void lcd_printStr(const char s[]);
    void delay(unsigned int ms);
    
    void lcd_printStr(const char s[]){
    IFS3bits.MI2C2IF = 0;
    I2C2CONbits.SEN = 1;
    while(I2C2CONbits.SEN ==1){};
    IFS3bits.MI2C2IF = 0;
    I2C2TRN = 0b01111100;
    while(IFS3bits.MI2C2IF == 0){};
    IFS3bits.MI2C2IF = 0;
    int index = 0;
    while(s[index]){
    
        if(s[index + 1] != '\0'){
            
            I2C2TRN = 0b11000000;
            
            while(IFS3bits.MI2C2IF == 0){};
            IFS3bits.MI2C2IF = 0;
            I2C2TRN = s[index];
            
            while(IFS3bits.MI2C2IF == 0){};
            IFS3bits.MI2C2IF = 0;
            
            
        }else{
            
            I2C2TRN = 0b01000000;
            
            while(IFS3bits.MI2C2IF == 0){};
            IFS3bits.MI2C2IF = 0;
            I2C2TRN = s[index];
            
            while(IFS3bits.MI2C2IF == 0){};
            IFS3bits.MI2C2IF = 0;
            
        }
        index++;
    }
    
    I2C2CONbits.PEN = 1;
    while(I2C2CONbits.PEN == 1){};
    }
    
    void lcd_init(void){
    I2C2CONbits.I2CEN = 0;
    I2C2BRG = 0x9D;
    IFS3bits.MI2C2IF = 0;
    TRISBbits.TRISB6 = 0;
    I2C2CONbits.I2CEN = 1; 
    
    delay(50);
    
    lcd_cmd(0b00111000);
    lcd_cmd(0b00111001);
    lcd_cmd(0b00010100);
    lcd_cmd(0b01110000);
    lcd_cmd(0b01011110);
    lcd_cmd(0b01101100);
    
    delay(215);
    
    lcd_cmd(0b00111000);
    lcd_cmd(0b00001100);
    lcd_cmd(0b00000001);
    
    delay(5);
}
    
    
    void lcd_cmd(char Package){
    IFS3bits.MI2C2IF = 0;
    I2C2CONbits.SEN = 1;
    while(I2C2CONbits.SEN ==1){};
    IFS3bits.MI2C2IF = 0;
    I2C2TRN = 0b01111100;
    
    while(IFS3bits.MI2C2IF == 0){};
    IFS3bits.MI2C2IF = 0;
    I2C2TRN = 0b00000000;
    
    while(IFS3bits.MI2C2IF == 0){};
    IFS3bits.MI2C2IF = 0;
    I2C2TRN = Package;
   
    while(IFS3bits.MI2C2IF == 0){};
    IFS3bits.MI2C2IF = 0;
    I2C2CONbits.PEN = 1;
    
    while(I2C2CONbits.PEN == 1){};
}

void lcd_setCursor(char x, char y){
    int cursor = 0x40*(y) + x;
    cursor = cursor | 0b10000000;
    lcd_cmd(cursor);
}

void lcd_printChar(char myChar){
    IFS3bits.MI2C2IF = 0;
    I2C2CONbits.SEN = 1;
    while(I2C2CONbits.SEN ==1){};
    IFS3bits.MI2C2IF = 0;
    I2C2TRN = 0b01111100;
    
    while(IFS3bits.MI2C2IF == 0){};
    IFS3bits.MI2C2IF = 0;
    I2C2TRN = 0b01000000;
    
    while(IFS3bits.MI2C2IF == 0){};
    IFS3bits.MI2C2IF = 0;
    I2C2TRN = myChar;
    
    while(IFS3bits.MI2C2IF == 0){};
    IFS3bits.MI2C2IF = 0;
    I2C2CONbits.PEN = 1;
    
    while(I2C2CONbits.PEN == 1){};
    return;
}

void delay(unsigned int ms) {
    int k;
    for (k = 0; k < ms; k++) {
        asm("repeat #15993");
        asm("nop");
    }
    return;
}
    

