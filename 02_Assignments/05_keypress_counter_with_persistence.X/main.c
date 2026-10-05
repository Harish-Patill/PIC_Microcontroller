/*
 * File:   main.c
 * Author: Harish
 *
 * Created on 28 September, 2026, 3:58 PM
 *
 * Program: 4-digit counter on seven segment displays with EEPROM save.
 *   RC0 short press : increment the count
 *   RC0 long press  : reset the count to 0
 *   RC1 press       : save the count into internal EEPROM
 *   Power on        : the saved count is loaded back from EEPROM
 */


#include <xc.h>

// Writes one byte (data) into the internal EEPROM location (address)
void write_internal_eeprom(unsigned char address,unsigned char data){
    EEADR=address;      // tell the EEPROM module WHERE to write
    EEDATA=data;        // tell the EEPROM module WHAT to write

    EEPGD=0;            // 0 = access data EEPROM (1 would be program flash)
    CFGS=0;             // 0 = access EEPROM/flash (1 would be config registers)
    WREN=1;             // enable writing (writes are blocked otherwise)
    GIE=0;              // disable interrupts, the unlock sequence must not be interrupted

    EECON2=0X55;        // mandatory unlock sequence, step 1
    EECON2=0XAA;        // mandatory unlock sequence, step 2

    WR=1;               // start the write, must come right after 0XAA
    GIE=1;              // enable interrupts again

    while(EEIF!=1);     // wait until the hardware finishes writing (EEIF is set)

    EEIF=0;             // clear the flag manually, hardware never clears it
    WREN=0;             // disable writing again to avoid accidental writes
}

// Reads one byte from the internal EEPROM location (address)
unsigned char read_internal_eeprom(unsigned char address){
    EEADR=address;      // tell the EEPROM module WHICH location to read
    EEPGD=0;            // select data EEPROM
    CFGS=0;             // select EEPROM/flash, not config registers
    RD=1;               // start the read (fast, no unlock and no waiting needed)
    return EEDATA;      // the byte read from EEPROM is now available in EEDATA
}

void display(char *ssd){
    for(int i=0;i<4;i++){
        PORTD=ssd[i];                   // segment pattern of digit i goes on PORTD
        PORTA=(PORTA&0xF0)|1<<i;        // enable only digit i (RA0 to RA3), upper bits unchanged
        for(int delay=800;delay--;);
    }
}

void main(void) {

    PORTD=0X00;             // clear the segment lines
    TRISD=0X00;             // PORTD all outputs (segment data lines)

    TRISA=TRISA&0XF0;       // RA0 to RA3 as outputs (digit select), upper bits unchanged
    PORTA=PORTA&0XF0;       // all digits off at start

    TRISC=TRISC|0XF0;       // RC4 to RC7 as inputs, RC0 to RC3 unchanged (RC0, RC1 are buttons)

    int flag=1;
    int count=0;
    char ssd[4];
    unsigned int num=0;
    unsigned int delay=0;

    unsigned char low_byte;
    unsigned char high_byte;

    unsigned char digit[]={0XE7,0X21,0XCB,0X6B,0X2D,0X6E,0XEE,0X23,0XEF,0X6F};

    low_byte=read_internal_eeprom(0);       // read the saved lower byte from address 0
    high_byte=read_internal_eeprom(1);      // read the saved upper byte from address 1

    num=((unsigned int)high_byte<<8)|low_byte;

    while(1){
        if(RC0==0){
            count++;

            if(count>300){
                num=0;
                flag=0;
            }
            else if(flag){
                num++;
                flag=0;
            }
        }
        else if(RC1==0){
            low_byte=num&0XFF;
            high_byte=(num>>8)&0XFF;

            write_internal_eeprom(0,low_byte);      // save lower byte at address 0
            write_internal_eeprom(1,high_byte);     // save upper byte at address 1

            while(RC1==0){
                display(ssd);
            }
        }

        else{
            flag=1;
            count=0;
        }

        ssd[0]=digit[num/1000];
        ssd[1]=digit[(num/100)%10];
        ssd[2]=digit[(num/10)%10];
        ssd[3]=digit[num%10];
        display(ssd);
    }
    return;
}