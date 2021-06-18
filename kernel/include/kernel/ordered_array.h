#ifndef ORDERED_ARRAY_H
#define ORDERED_ARRAY_H

#include <stddef.h>
#include <stdint.h>

typedef void* any_type_t; 

//funciton pointer that compares first arg against second
// if 1st < 2nd, return any nonzero integer. Any other case, return 0
typedef uint8_t (*less_than_func_t)(any_type_t, any_type_t);

typedef struct ordered_array_t {
    any_type_t* array;
    uint32_t size;
    uint32_t max_size;
    less_than_func_t less_than_func;
} ordered_array_t ;


uint8_t standardLessThanFunc(any_type_t a, any_type_t b);

ordered_array_t createOrderedArray(uint32_t max_size, less_than_func_t lessThan );
ordered_array_t placeOrderedArray(void* addr, uint32_t max_size, less_than_func_t lessThan );


void destroyOrderedArray(ordered_array_t* array);
void insertOrderedArray(any_type_t item, ordered_array_t* array);
any_type_t lookupItemInOrderedArray(uint32_t index, ordered_array_t* array);
void removeItemInOrderedArray(uint32_t index, ordered_array_t* array);

#endif