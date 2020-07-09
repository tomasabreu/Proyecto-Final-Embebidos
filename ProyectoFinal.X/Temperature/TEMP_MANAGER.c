/* ************************************************************************** */
/** Descriptive File Name

  @Company
    Company Name

  @File Name
    filename.c

  @Summary
    Brief description of the file.

  @Description
    Describe the purpose of this file.
 */
/* ************************************************************************** */

/* ************************************************************************** */
/* ************************************************************************** */
/* Section: Included Files                                                    */
/* ************************************************************************** */
/* ************************************************************************** */

/* This section lists the other files that are included in this file.
 */

/* TODO:  Include other files here if needed. */
#include <stdio.h>
#include <math.h>

#include "TEMP_MANAGER.h"
#include "FreeRTOS.h"
#include "../mcc_generated_files/adc1.h"

/* ************************************************************************** */
/* ************************************************************************** */
/* Section: File Scope or Global Data                                         */
/* ************************************************************************** */
/* ************************************************************************** */

/*  A brief description of a section can be given directly below the section
    banner.
 */

double temperature;
/* ************************************************************************** */
/* ************************************************************************** */
// Section: Local Functions                                                   */
/* ************************************************************************** */
/* ************************************************************************** */

/*  A brief description of a section can be given directly below the section
    banner.
 */

/* ************************************************************************** */

double round(double x) {
    return floor(x + 0.5f);
} // Math.h doesn't have this function.
/* ************************************************************************** */
/* ************************************************************************** */
// Section: Interface Functions                                               */
/* ************************************************************************** */
/* ************************************************************************** */

/*  A brief description of a section can be given directly below the section
    banner.
 */

// *****************************************************************************

void measureTemperature() {
    temperature += (ADC1_GetConversion(TEMP) / 102.3) + 32;
}

float getTemperature() {
    return temperature;
}

void averageTemperature() {
    temperature /= 10;
    temperature = round(10 * temperature) / 10;
}

void resetTemperature() {
    temperature = 0;
}
/* *****************************************************************************
 End of File
 */
