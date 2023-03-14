#include <stdlib.h>
#include <stdio.h>
#include "AdptArray.h"

struct AdptArray_
{
    PElement *elements;
    int size;
    COPY_FUNC copy_func;
    DEL_FUNC del_func;
    PRINT_FUNC print_func;
};

PAdptArray CreateAdptArray(COPY_FUNC copy_func, DEL_FUNC del_func, PRINT_FUNC print_func)
{
    PAdptArray adpt_array = malloc(sizeof(struct AdptArray_));
    if (adpt_array == NULL)
    {
        return NULL;
    }

    adpt_array->elements = NULL;
    adpt_array->size = 0;
    adpt_array->copy_func = copy_func;
    adpt_array->del_func = del_func;
    adpt_array->print_func = print_func;

    return adpt_array;
}
