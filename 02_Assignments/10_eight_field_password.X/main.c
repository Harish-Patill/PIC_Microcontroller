/*
 * File:   main.c
 * Author: Harish
 *
 * Created on 20 October, 2026, 12:01 PM
 */


#include "header.h"

extern unsigned int time;
extern unsigned int count0;     // this is for the underscore in the clcd

void init_config(void){
    init_timer0();
    init_clcd();
    init_matrix_keypad();

    TRISB0=0x00;        // this is for the first led only
    PORTBbits.RB0=0;
    
    GIE = 1;
    PEIE = 1;
}

void main(void) {
    init_config();   
    
    unsigned char key;
    unsigned char str[9];
    unsigned char password[]="00000000";
    
    unsigned int i=0;
    unsigned int tries=5;
    unsigned int wrong_flag=1;
    unsigned int time_divisor;
    
    clcd_print((unsigned char *)"Enter Password",LINE1(0));
    while(1){
		if(tries == 0){
			clcd_print((unsigned char *)"System Locked! ", LINE1(0));
			clcd_print((unsigned char *)"Max attempts failed", LINE2(0));
			PORTBbits.RB0 = 1;
			while(1);
		}
          
        time_divisor = 1;
		wrong_flag = 0;
		time = 100000 / time_divisor;
        
        for(unsigned int count=0;count<8;count++){
            key = read_switches(STATE_CHANGE);
            if(key == MK_SW1){
                str[count] = '0';
                clcd_putch('*',LINE2(count));
                    
                if(password[count] != '0'){
                    time_divisor++;
					time = 100000 / time_divisor;
                    wrong_flag = 1;
                }
            }
                
            else if(key == MK_SW2){
                str[count] = '1';
                clcd_putch('*',LINE2(count));
                    
                if(password[count] != '1'){
                    time_divisor++;
					time = 100000 / time_divisor;
                    wrong_flag = 1;
                }
            }
                
            if(count0 < 10000){
                clcd_putch('_',LINE2(count+1));
            }
            else{
                clcd_putch(' ',LINE2(count+1));
            }
        }
        str[8]='\0';

           
        if(wrong_flag == 0){
            clcd_print((unsigned char *)"Successful!!!  ", LINE1(0));
            PORTBbits.RB0 = 0;
            while(1);
        }
        else{
            tries--;

            clcd_print((unsigned char *)"Tries left",LINE2(2));
			clcd_putch((tries + 0x30), LINE2(4));
                
            __delay_ms(1500);

            clcd_print((unsigned char *)"Enter Password", LINE1(0));
            clcd_print((unsigned char *)"                ", LINE2(0));
        }
    }
    return;
}