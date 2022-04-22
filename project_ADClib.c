/*
 * File:   redfe017_project_ADClib.c
 * Author: redfe017
 *
 * Created on April 15, 2022, 1:20 PM
 */


#include "xc.h"
#include "project_ADClib.h"


void adc_init(void);

void adc_init(void){
    TRISAbits.TRISA0 =1;
    AD1PCFGbits.PCFG0 = 0;
    AD1CON2bits.VCFG = 0b000;
    AD1CON3bits.ADCS = 0b00000001;
    AD1CON1bits.SSRC = 0b010;
    AD1CON3bits.SAMC = 0b00001;
    AD1CON1bits.FORM = 0b00;
    AD1CON1bits.ASAM = 0b1;
    AD1CON2bits.SMPI = 0b0000;
    AD1CON1bits.ADON = 1;
    
    _AD1IF = 0;
    _AD1IE = 0;
    
    
    _T3IF = 0;
    _T3IE = 0;
    TMR3 = 0;
    T3CON = 0;
    T3CONbits.TCKPS = 0b10;
    PR3 = 15624;
    T3CONbits.TON = 1;
}
