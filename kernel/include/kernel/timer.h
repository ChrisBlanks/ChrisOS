/*
 * File: timer.h 
 * Purpose: Defines the interface for all PIT-related function
 * PIT = programmable interval timer
 */

#ifndef TIMER_H
#define TIMER_H

#include <stdint.h>

#define INPUT_CLOCK_CONSTANT 1193180 //input clock of PIT that is divided to get frequency
#define DEFAULT_TIMER_FREQ 50


void initTimer(uint32_t freq);
uint32_t getCurrentTick();
uint32_t getCurrentFrequency();
void updateTimerFrequency(uint32_t freq);
void wait(uint32_t ticks);

#endif