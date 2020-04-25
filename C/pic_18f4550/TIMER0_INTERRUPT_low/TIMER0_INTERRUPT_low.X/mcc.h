/* IDE: MPLAB X v3.65 Compiler XC8(Free Mode) V1.45
 * File:   mcc.h
 * Author: Wilson Queiroz
 * 
 * 
 */

#include <xc.h>
#include <pic18f4550.h>

#define _XTAL_FREQ 48000000

#define TRIS_LED  TRISBbits.TRISB0
#define LED LATBbits.LATB0
#define preset_TMR0 0x0000  // <TMR0H:TMR0L>

void CONFIG_mcc(void);