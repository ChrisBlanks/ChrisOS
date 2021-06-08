/*
 * File: timer.h 
 * Purpose: Defines the interface for all PIT-related function
 * PIT = programmable interval timer
 */

#ifndef KEYBOARD_H
#define KEYBOARD_H

#include <stdint.h>

#define KEYBOARD_CONTROL_REGISTER 0x64
#define KEYBOARD_DATA_REGISTER    0x60

#define KEYBOARD_KEY_RELEASE_EVENT_MASK 0x80

void initKeyboard(void);

#endif