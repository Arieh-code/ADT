#include <stdlib.h>
#include <stdio.h>
#include "AdptArray.h"

// Define a struct for the adaptive array
struct AdptArray_
{
    PElement *elements;
    int size;
    COPY_FUNC copy_func;
    DEL_FUNC del_func;
    PRINT_FUNC print_func;
};

// create a new adapt array
PAdptArray CreateAdptArray(COPY_FUNC copy_func, DEL_FUNC del_func, PRINT_FUNC print_func)
{
    // Allocate memory for the new adaptive array
    PAdptArray adpt_array = malloc(sizeof(struct AdptArray_));
    if (adpt_array == NULL)
    {
        return NULL;
    }

    // Initialize the new adapt array
    adpt_array->elements = NULL;
    adpt_array->size = 0;
    adpt_array->copy_func = copy_func;
    adpt_array->del_func = del_func;
    adpt_array->print_func = print_func;

    return adpt_array;
}

// Delete an adaptive array and its elements
void DeleteAdptArray(PAdptArray adpt_array)
{
    if (adpt_array == NULL)
    {
        return;
    }

    // Free each element in the adaptive array
    if (adpt_array->elements != NULL)
    {
        for (int i = 0; i < adpt_array->size; i++)
        {
            if (adpt_array->elements[i] != NULL)
            {
                adpt_array->del_func(adpt_array->elements[i]);
            }
        }

        // Free the memory allocated for the adaptive array's elements
        free(adpt_array->elements);
    }

    // Free the memory allocated for the adaptive array
    free(adpt_array);
}