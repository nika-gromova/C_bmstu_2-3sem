#ifndef DEFINES_H
#define DEFINES_H

#include <math.h>

#define OK 0
#define MEMORY_ERROR -1
#define NULL_POINTER_ERROR -2


#define EPS 1e-10
#define IS_EQUAL(num1, num2) (fabs((num1) - (num2)) <= EPS)

#endif // DEFINES_H
