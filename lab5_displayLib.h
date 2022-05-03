/* 
 * File:   redfe017_lab5_displayLib.h
 * Authors: Nathan Redfern, Andy Lambrecht, Ben Deyle
 *
 * Created on April 2, 2022, 9:52 PM
 */

#ifndef LAB5_DISPLAYLIB_H
#define	LAB5_DISPLAYLIB_H

#ifdef	__cplusplus
extern "C" {
#endif

    void lcd_cmd(char Package);
    void lcd_setCursor(char x, char y);
    void lcd_printChar(char myChar);
    void lcd_init(void);
    void lcd_printStr(const char s[]);
    void delay(unsigned int ms);
    


#ifdef	__cplusplus
}
#endif

#endif	/* REDFE017_LAB5_DISPLAYLIB_H */

