#include "AdptArray.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Define the structure of the adaptive array */
struct AdptArray_
{
    int capacity;          /* maximum capacity of the array */
    int size;              /* current size of the array */
    COPY_FUNC copy_func;   /* function to copy an element of the array */
    DEL_FUNC del_func;     /* function to delete an element of the array */
    PRINT_FUNC print_func; /* function to print an element of the array */
    PElement *elements;    /* pointer to array of elements */
};