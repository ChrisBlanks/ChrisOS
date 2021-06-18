#include <kernel/ordered_array.h>
#include <kernel/kheap.h>

#include <string.h>
#include <kernel/kheap.h>


uint8_t standardLessThanFunc(any_type_t a, any_type_t b){
    return (a < b) ? 1 : 0;
}

//return a newly created ordered array of 'max_size' that compares w/ 'lessThan' func
ordered_array_t createOrderedArray(uint32_t max_size, less_than_func_t lessThan ){
    ordered_array_t new_array;
    
    new_array.array = (void*) kmalloc(max_size * sizeof(any_type_t));
    memset(new_array.array, 0, max_size * sizeof(any_type_t));

    new_array.size = 0;
    new_array.max_size = max_size;
    new_array.less_than_func = lessThan;

    return new_array;
}

//create an ordered array  a specificed address
ordered_array_t placeOrderedArray(void* addr, uint32_t max_size, less_than_func_t lessThan ){
    ordered_array_t new_array;
    
    new_array.array = (any_type_t*)addr;
    
    memset(new_array.array, 0, max_size * sizeof(any_type_t));

    new_array.size = 0;
    new_array.max_size = max_size;
    new_array.less_than_func = lessThan;

    return new_array;
}

//free memory associated with array
void destroyOrderedArray(ordered_array_t* array){
    kfree(array);
}


//insert item into the proper placement in the array
void insertOrderedArray(any_type_t item, ordered_array_t* array){
    if(array->less_than_func){
        uint32_t iterator = 0;

        while(iterator < array->size && array->less_than_func(array->array[iterator], item) == 1){
            iterator++;
        }

        if(iterator == array->size){ //if equal to size of array, place item in next index (a.k.a end of array)
            array->array[array->size++] = item;
        } else {
            any_type_t tmp = array->array[iterator]; //save current item at iterator index
            array->array[iterator] = item; //place item in iterator index

            while(iterator < array->size){ //shuffle values forward in array
                iterator++;
                any_type_t loop_tmp = array->array[iterator];
                array->array[iterator] = tmp;
                tmp = loop_tmp;
            }

            array->size++;
        }
    }
}

// return item at index or NULL if index >= array->size
any_type_t lookupItemInOrderedArray(uint32_t index, ordered_array_t* array){
    if(index < array->size){
        return array->array[index];
    }

    return NULL;
}

//overwrite item at specified index of array
void removeItemInOrderedArray(uint32_t index, ordered_array_t* array){
    while(index < array->size){ //shift all array items left one index to get rid of item
        array->array[index] = array->array[index+1];
        index++;
    }
    array->size--;
}