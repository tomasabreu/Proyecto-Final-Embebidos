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

#include "LOG_MANAGER.h"
#include <string.h>
#include <stdio.h>

/* TODO:  Include other files here if needed. */


/* ************************************************************************** */
/* ************************************************************************** */
/* Section: File Scope or Global Data                                         */
/* ************************************************************************** */
/* ************************************************************************** */

/*  A brief description of a section can be given directly below the section
    banner.
 */
#define amountOfSaveTemperatures 10
static char savedTemperatures[amountOfSaveTemperatures][128];
static int lastTemperatureIndex = 0;



/* ************************************************************************** */
/* ************************************************************************** */
// Section: Local Functions                                                   */
/* ************************************************************************** */
/* ************************************************************************** */

/*  A brief description of a section can be given directly below the section
    banner.
 */

/* ************************************************************************** */



/* ************************************************************************** */
/* ************************************************************************** */
// Section: Interface Functions                                               */
/* ************************************************************************** */
/* ************************************************************************** */

/*  A brief description of a section can be given directly below the section
    banner.
 */
bool saveLog(uint8_t* sentence) {
    if (lastTemperatureIndex < amountOfSaveTemperatures) {
        memcpy(savedTemperatures[lastTemperatureIndex], sentence, strlen(sentence));    
        lastTemperatureIndex++;
        return true;
    }
    return false;
}

int getLastTemperatureIndex() {
    return lastTemperatureIndex;
}

char* getLog(int index){
    if(index < lastTemperatureIndex){
        return savedTemperatures[index];
    }
    return NULL;
}
/* *****************************************************************************
 End of File
 */
