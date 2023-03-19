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

Result SetAdptArrayAt(PAdptArray adpt_array, int index, PElement element)
{
    if (index < 0) // Check if index is less than zero
    {
        return FAIL; // Return failure if index is less than zero
    }

    if (index >= adpt_array->size) // Check if index is greater than or equal to size of array
    {
        PElement *new_elements = realloc(adpt_array->elements, (index + 1) * sizeof(PElement)); // Allocate memory for new elements
        if (new_elements == NULL)                                                               // Check if allocation failed
        {
            return FAIL; // Return failure if allocation failed
        }

        adpt_array->elements = new_elements;            // Assign new elements to array
        for (int i = adpt_array->size; i <= index; i++) // Set values of new elements to NULL
        {
            adpt_array->elements[i] = NULL;
        }
        adpt_array->size = index + 1; // Update size of array
    }

    if (adpt_array->elements[index] != NULL) // Check if element at index is not NULL
    {
        adpt_array->del_func(adpt_array->elements[index]); // Call delete function to free memory
    }

    adpt_array->elements[index] = adpt_array->copy_func(element); // Copy element to array

    return SUCCESS; // Return success
}

PElement GetAdptArrayAt(PAdptArray adpt_array, int index)
{
    if (index < 0 || index >= adpt_array->size || adpt_array->elements[index] == NULL) // Check if index is out of bounds or element is NULL
    {
        return NULL; // Return NULL if index is out of bounds or element is NULL
    }

    return adpt_array->copy_func(adpt_array->elements[index]); // Copy element to return value
}

int GetAdptArraySize(PAdptArray adpt_array)
{
    return adpt_array->size; // Return size of array
}

void PrintDB(PAdptArray adpt_array)
{
    for (int i = 0; i < adpt_array->size; i++) // Iterate over each element in the array
    {
        if (adpt_array->elements[i] != NULL) // Check if element is not NULL
        {
            adpt_array->print_func(adpt_array->elements[i]); // Print element
        }
    }
}
