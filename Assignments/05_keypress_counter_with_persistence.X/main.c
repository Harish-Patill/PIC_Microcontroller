///*
// * File:   main.c
// * Author: Harish
// *
// * Created on 28 September, 2026, 3:58 PM
// */
//
//
//#include <xc.h>
//
//void write_internal_eeprom(unsigned char address, unsigned char data){
//    EEADR=address;
//    EEDATA=data;
//    
//    EEPGD=0;
//    CFGS=0;
//    WREN=1;
//    GIE=0;
//    
//    EECON2=0X55;
//    EECON2=0XAA;
//    
//    WR=1;
//    GIE=1;
//    
//    while(EEIF != 1);
//    
//    EEIF=0;
//    WREN=0;
//}
//
//unsigned char read_internal_eeprom(unsigned char address){
//    EEADR = address;
//    EEPGD = 0;   
//    CFGS = 0;
//    RD = 1;
//    return EEDATA;
//}
//
//void display(char *ssd){
//    for(int i=0;i<4;i++){
//        PORTD = ssd[i];
//        PORTA = (PORTA & 0xF0) | 1<<i;
//        for(int delay=800;delay--;);
//    }
//}
//
//void main(void) {
//    
//    PORTD=0X00;
//    TRISD=0X00;
//    
//    TRISA=TRISA & 0XF0;
//    PORTA=PORTA & 0XF0;
//    
//    TRISC=TRISC | 0X0F;
//    
//    int num=0;
//    int flag=1;
//    int count=0;
//    char ssd[4];
//    unsigned int num=0;
//    unsigned int delay=0;
//    
//    unsigned char low_byte;
//    unsigned char high_byte;
//    
//    unsigned char digit[] = {0XE7,0X21,0XCB,0X6B,0X2D,0X6E,0XEE,0X23,0XEF,0X6F};
//    
//    low_byte = read_internal_eeprom(0);
//    high_byte = read_internal_eeprom(1);
//            
//    num = low_byte | ((unsigned int)high_byte << 8) | low_byte;    
//    
//    while(1){
//        if(RC0 == 0){
//            count++;
//
//            if(count > 300){
//                num = 0;
//                flag = 0;
//            }
//            else if(flag){
//                num++;
//                flag = 0;
//            }
//        }
//        else if(RC1 == 0){
//            low_byte = num & 0XFF;
//            high_byte = (num >> 8) & 0XFF;
//            
//            write_internal_eeprom(0, low_byte);
//            write_internal_eeprom(1, high_byte);
//            
//            
//            while(RC1 == 0){
//                display(ssd);
//            }
//        }
//        
//        else{
//            flag = 1;
//            count = 0;
//        }
//        
//        ssd[0]=digit[num/1000];
//        ssd[1]=digit[(num/100)%10];
//        ssd[2]=digit[(num/10)%10];
//        ssd[3]=digit[num%10];
//        display(ssd);
//    }
//    return;
//}


#include <xc.h>
void write_internal_eeprom(unsigned char address, unsigned char data)
{
    EEADR = address;
    EEDATA = data;
    EEPGD = 0;
    CFGS=0;
    
    WREN=1;
    
    GIE=0;
    
    EECON2 = 0X55;
    EECON2 = 0XAA;
    
    WR=1;
    
    GIE=1;
    
    while(EEIF!=1);
    
    EEIF=0;
    
    WREN=0;
       
}

unsigned char read_internal_eeprom(unsigned char address)
{
    EEADR=address;
    EEPGD = 0;
    CFGS=0;
    
    RD=1;
    
    return EEDATA;
    
}
void display(char *ssd)
{
    for(int i=0;i<4;i++)
    {
        PORTA = PORTA & 0XF0;
                
        PORTD=ssd[i];
        PORTA=(PORTA & 0XF0 )| 1<<i;
        for(int delay=500;delay--;);
    }
}

void main(void) 
{
    TRISD=0X00;
    PORTD=0X00;
    
    TRISA=TRISA & 0XF0;
    PORTA=PORTA & 0XF0;
    
    TRISC=TRISC | 0XF0;
    
    unsigned char digit[]={0XE7,0X21,0XCB,0X6B,0X2D,0X6E,0XEE,0X23,0XEF,0X6F};
    char ssd[4];
    unsigned int num=0;
    unsigned int delay=0;
    int flag=0;
    int count=0;
    
    unsigned int low_byte;
    unsigned int high_byte;
    
    low_byte = read_internal_eeprom(0);
    high_byte = read_internal_eeprom(1);

     num = ((unsigned int)high_byte << 8) | low_byte;
    while(1)
    {
        if(RC0 == 0)
        {
            count++;

            if(count > 300)
            {
                num = 0;
                flag = 0;
            }
            else if(flag)
            {
                num++;

                flag = 0;
            
            }
        }
        
        else if(RC1==0)
        {
            low_byte =  num & 0XFF;
            high_byte = (num >> 8) & 0xFF;
            
            write_internal_eeprom(0, low_byte);
            write_internal_eeprom(1, high_byte);
            
            while(RC1==0)
            {
                display(ssd);
            }
            
        }
        else
        {
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