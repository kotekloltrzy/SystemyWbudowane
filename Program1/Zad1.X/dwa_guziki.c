/*
 * File:   dwa_guziki.c
 * Author: local
 *
 * Created on 15 kwietnia 2026, 10:29
 */


#include <xc.h>
#include <libpic30.h>

int kodGraya(int n){
    int temp[32];
    int i=0, j=0;
    while (n>0){
        temp[i] = n%2;
        n = n/2;
        i++;
    }
    temp[i] = 0;
    i++;
    int wynik[i];
    while(i>1){
        wynik[j] = temp[i-1]^temp[i-2];
        i--;
        j++;
    }
    return drukowanieTablicy(wynik, j);
}

int drukowanieTablicy(int tab[], int size){
    for(int k=0; k<size; k++){
        return(tab[k]);
    }
}

int main(void) {
    
    unsigned portValue = 0x0001;
    char current6 = 0, prev6 = 0, current7 =0, prev7 = 0;
    int value = 1;
    TRISA = 0x0000;
    TRISD = 0xFFFF;
    while (1){
        switch(value){
            case 1:
                LATA = portValue;
                portValue++;
                if(portValue == 0xFF){ //co jesli przekorczymy 8 bitow
                    portValue = 0; // reset portValue
                }
                break;
            case 2:
                LATA = portValue;
                portValue--;
                if(portValue == 0xFF){
                    portValue = 0;
                }
                break;
            case 3:
                LATA = kodGraya(portValue);
                portValue++;
                if(portValue == 0xFF){
                    portValue = 0;
                }
                break;
            case 4:
                LATA = portValue + 7;
                break;
            default:
                LATA = value;
        }
        
        prev6 = PORTDbits.RD6;
        prev7 = PORTDbits.RD7;
        __delay32(150000);
        current6 = PORTDbits.RD6;
        current7 = PORTDbits.RD7;
        
        if(current6 - prev6 == 1){
            value--;
            portValue = 1;
            if(value <= 0){
                value = 4;
            }
        }
        if(current7 - prev7 == 1){
            value++;
            portValue = 1;
            if(value >= 5){
                value = 1;
            }
        }
    }
    
    return 0;
}
