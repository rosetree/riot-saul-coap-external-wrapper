/*
 * Copyright (C) 2020 Alex Fuhr Hochschule für Angewandte Wissenschaften-Hamburg (HAW)
 * Projekt: RIOT
 */

/**
 * @ingroup     examples
 * @{
 * @file
 * @brief       messuring relative height of one node 
 * 
 * @author      Alex Fuhr
 * @}
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define P0 101325
#define f(x1) 7990
#define f(x2) 8435
#define x1 0
#define x2 15
/**
*@var: high_offset height offset to sea ​​level height
*/

// extrapulation of the altitude values
double ground_height(int temp, int high_offset) {
    return (((f(x2) + (f(x2) - f(x1)) / (x2 - x1)) * temp) + high_offset);
}
// calculate the height using the pressure
double node_height(int temperature, int high_offset, int pressure)
{
    double ground_meter = ground_height(temperature, high_offset);
    double temp_pressure_difference = pressure/P0;
    return (-1) * ground_meter * log(temp_pressure_difference);
}