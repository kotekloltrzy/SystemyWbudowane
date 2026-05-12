/*
 * File:   newmainXC16.c
 * Author: local
 *
 * Created on May 6, 2026, 10:01 AM
 */

// PIC24FJ128GA010 Configuration Bit Settings

// 'C' source line config statements

// CONFIG2
#pragma config POSCMOD = XT             // Primary Oscillator Select (XT Oscillator mode selected)
#pragma config OSCIOFNC = ON            // Primary Oscillator Output Function (OSC2/CLKO/RC15 functions as port I/O (RC15))
#pragma config FCKSM = CSDCMD           // Clock Switching and Monitor (Clock switching and Fail-Safe Clock Monitor are disabled)
#pragma config FNOSC = PRI              // Oscillator Select (Primary Oscillator (XT, HS, EC))
#pragma config IESO = ON                // Internal External Switch Over Mode (IESO mode (Two-Speed Start-up) enabled)

// CONFIG1
#pragma config WDTPS = PS32768          // Watchdog Timer Postscaler (1:32,768)
#pragma config FWPSA = PR128            // WDT Prescaler (Prescaler ratio of 1:128)
#pragma config WINDIS = ON              // Watchdog Timer Window (Standard Watchdog Timer enabled,(Windowed-mode is disabled))
#pragma config FWDTEN = ON              // Watchdog Timer Enable (Watchdog Timer is enabled)
#pragma config ICS = PGx2               // Comm Channel Select (Emulator/debugger uses EMUC2/EMUD2)
#pragma config GWRP = OFF               // General Code Segment Write Protect (Writes to program memory are allowed)
#pragma config GCP = OFF                // General Code Segment Code Protect (Code protection is disabled)
#pragma config JTAGEN = OFF             // JTAG Port Enable (JTAG port is disabled)

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.

#include "xc.h"
#include <libpic30.h>

void init(void){
    AD1PCFG = 0xFFFF;
    TRISA = 0x0000;
    LATA = 0x0000;
    TRISDbits.TRISD6 = 1; // przycisk nastepny
    TRISDbits.TRISD13 = 1; // przycisk poprzedni
}

int checkButtons(int currentProgram){
    if(NEXT_BUTTON == 0){
        __delay32(200000);
        currentProgram++;
        if(currentProgram > 9)
            currentProgram = 1;
        while(NEXT_BUTTON == 0);
    }
    if(PREV_BUTTON == 0){
        __delay32(200000);
        currentProgram--;
        if(currentProgram < 1)
            currentProgram = 9;
        while(PREV_BUTTON == 0);
    }
    return currentProgram;
}

void program1(int *program){
    unsigned int portValue = 0;
    LATA = portValue;
    portValue++;
    __delay32(1000000);
    *program = checkButtons(*program);
}

void program2(int *program){
    unsigned int portValue = 255;
    LATA = portValue;
    portValue--;
    __delay32(1000000);
    *program = checkButtons(*program);
}

void program3(int *program){
    unsigned int gray = 0;
    unsigned int i = 0;
    gray = i ^ (i >> 1);
    LATA = gray;
    i++;
    __delay32(1000000);
    *program = checkButtons(*program);
}

void program4(int *program){
    unsigned int gray = 0;
    unsigned int i = 255;
    gray = i ^ (i >> 1);
    LATA = gray;
    i--;
    __delay32(1000000);
    *program = checkButtons(*program);
}

void program5(int *program) {
    static unsigned int i = 0;
    unsigned int bcd;
    int jednosci = i % 10;
    int dziesiatki = i / 10;
    bcd = (dziesiatki << 4) | jednosci;
    LATA = bcd;
    i++;
    if(i > 99)
        i = 0;
    __delay32(1000000);
    *program = checkButtons(*program);
}

void program6(int *program){
    static unsigned int i = 99;
    unsigned int bcd;
    int jednosci = i % 10;
    int dziesiatki = i / 10;
    bcd = (dziesiatki << 4) | jednosci;
    LATA = bcd;
    i--;
    if(i < 0)
        i = 99;
    __delay32(1000000);
    *program = checkButtons(*program);
}

void program7(int *program){
    static unsigned int waz = 0x07;
    static int dir = 1;
    LATA = waz;
    if(dir == 1){
        waz <<= 1;
        if(waz == 0xE0)
            dir = 0;
    }
    else{
        waz >>= 1;
        if(waz == 0x07)
            dir = 1;
    }
    __delay32(1000000);
    *program = checkButtons(*program);
}

void program8(int *program){
    unsigned int kol = 0x00;
    LATA = kol;
    kol = (kol << 1) | 1;
    __delay32(1000000);
    *program = checkButtons(*program);
}

void program9(int *program){
    unsigned int gll = 0x3F;
    unsigned int bit;
    LATA = gll;
    bit = ((gll >> 5) ^ (gll >> 4) ^ (gll >> 3) ^ (gll >> 0)) & 1;
    gll = (gll << 1) | bit;
    gll &= 0x3F;
    __delay32(1000000);
    *program = checkButtons(*program);
}


int main(void) {
    init();
    int currentProgram = 1;
    while(1){
        switch(currentProgram){
        case 1:
            program1(&currentProgram);
            break;
        case 2:
            program2(&currentProgram);
            break;
        case 3:
            program3(&currentProgram);
            break;
        case 4:
            program4(&currentProgram);
            break;
        case 5:
            program5(&currentProgram);
            break;
        case 6:
            program6(&currentProgram);
            break;
        case 7:
            program7(&currentProgram);
            break;
        case 8:
            program8(&currentProgram);
            break;
        case 9:
            program9(&currentProgram);
            break;
        }
    }
    return 0;
}
