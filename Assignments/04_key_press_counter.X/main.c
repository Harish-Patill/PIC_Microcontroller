/*
 * File:   main.c
 * Author: Haris
 *
 * Created on 28 September, 2026, 4:26 PM
 */


#include <xc.h>
void display(char *ssd){
    for(int i=0;i<4;i++){
        PORTD=ssd[i];
        PORTA= PORTA & 0XF0|1<<i;
        
        for(int delay=1000; delay--;);
    }
}

void main(void){
    TRISD=0X00;
    PORTD=0X00;
    
    TRISA = TRISA & 0XF0;
    PORTA = PORTA & 0XF0;
    
    unsigned char digit[]={0XE7,0X21,0XCB,0X6B,0X2D,0X6E,0XEE,0X23,0XEF,0X6F};
    int flag=1;
    int num=0;
    int count=0;
    
    char ssd[4];
    
    while(1){
        if(RC0 == 0){
            count++;

            if(count > 300){
                num = 0;
                flag = 0;
            }
            else if(flag){
                num++;
                flag = 0;
            }
        }
        else{
            flag = 1;
            count = 0;
        }
        
        ssd[0]=digit[num/1000];
        ssd[1]=digit[(num/100)%10];
        ssd[2]=digit[(num/10)%10];
        ssd[3]=digit[num%10];
        
        display(ssd);  
    }
    return;
}