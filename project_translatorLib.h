/* 
 * File:   redfe017_project_translatorLib.h
 * Author: redfe017
 *
 * Created on April 15, 2022, 1:58 PM
 */

#ifndef PROJECT_TRANSLATORLIB_H
#define	PROJECT_TRANSLATORLIB_H
#define NILL 4
#define dot 1
#define dash 0
#define up 0
#define down  1

#ifdef	__cplusplus
extern "C" {
#endif
    
char MorseTable(int first, int second, int third, int fourth);
void __attribute__((__interrupt__,__auto_psv__)) _T2Interrupt(void);
int check_up_or_down(void);
void T2_init(void);

#ifdef	__cplusplus
}
#endif

#endif	/* REDFE017_PROJECT_TRANSLATORLIB_H */

