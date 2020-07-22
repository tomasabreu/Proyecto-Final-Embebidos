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
#define amountOfSaveTemperatures 200
static logData savedTemperatures[amountOfSaveTemperatures];
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
bool saveLog(logData log) {
    if (lastTemperatureIndex < amountOfSaveTemperatures) {
        savedTemperatures[lastTemperatureIndex].id = log.id;
        savedTemperatures[lastTemperatureIndex].gps = log.gps;    
        savedTemperatures[lastTemperatureIndex].temperature = log.temperature;    
        savedTemperatures[lastTemperatureIndex].time = log.time;    
        lastTemperatureIndex++;
        return true;
    }
    return false;
}

int getLastTemperatureIndex() {
    return lastTemperatureIndex;
}

void getLog(int index, uint8_t* textToSave){
    if(index < lastTemperatureIndex){
        generateMessage(savedTemperatures[index],textToSave);
    }
}

void generateMessage(logData logToGenerate, uint8_t* textToSave){
    uint8_t googleMapsLink[64];
    GPS_generateGoogleMaps(googleMapsLink, logToGenerate.gps);
    sprintf(textToSave, "%d %s %s %.1f\n", logToGenerate.id, ctime(&logToGenerate.time), googleMapsLink, logToGenerate.temperature);
}
/* *****************************************************************************
 End of File
 */
