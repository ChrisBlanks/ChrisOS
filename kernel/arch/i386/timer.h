/*
 * File: timer.h 
 * Purpose: Defines the interface for all PIT-related function
 * PIT = programmable interval timer
 */

#ifndef TIMER_H
#define TIMER_H

#include <stdint.h>

void initTimer(uint32_t freq);

#endif