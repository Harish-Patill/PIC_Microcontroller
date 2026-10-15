/* 
 * File:   dynamic_header.h
 * Author: Harish
 *
 * Created on 9 October, 2026, 4:08 PM
 */

#ifndef DYNAMIC_HEADER_H
#define DYNAMIC_HEADER_H

#include <xc.h>

#define ALL_RELEASED    0x0F
#define EDGE            0
#define LEVEL           0


// Digital Switch Macros
#define SW1             0x0E    // Increment
#define SW2             0x0D    // Decrement
#define SW3             0x0B    // Choose Field
#define SW4             0x07    // Set/Edit

// Modes
#define EDIT_MODE       0
#define RUN_MODE        1

// Fields
#define MINUTES_FIELD   0
#define HOURS_FIELD     1

// Global variables
extern volatile unsigned char sec;
extern volatile unsigned char minute;
extern volatile unsigned char hour;
extern volatile unsigned int count;

void display(char ssd[]);
void init_timer0(void);
void init_config(void);

#endif