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


/** 
 * @Function
 *    bool saveLog(logData log)
 *
 * @Summary
 *   Esta funcion se encarga de salvar cada uno de los atributos que se necesita salvar en el log de datos.
 * @Param:
 *   el log que tiene los atributos para guardar.
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


/** 
 * @Function
 *    int getLastTemperatureIndex()
 *
 * @Summary
 *   Esta funcion se encarga dar el tamaño del log de datos hasta el momento.
 * 
 */
int getLastTemperatureIndex() {
    return lastTemperatureIndex;
}



/** 
 * @Function
 *    void getLog(int index, uint8_t* textToSave)
 *
 * @Summary
 *   Esta funcion se encarga dar el log de datos.
 * @Param:
 *   index -> el index es el lugar donde esta el log de datos en el array con logs de datos
 *   textToSend -> el mensaje para ser enviado.
 */
void getLog(int index, uint8_t* textToSave){
    if(index < lastTemperatureIndex){
        generateMessage(savedTemperatures[index],textToSave);
    }
}


/** 
 * @Function
 *    void generateMessage(logData logToGenerate, uint8_t* textToSave)
 *
 * @Summary
 *   Esta funcion se encarga generar el mensaje completo para ser enviado por mensaje de texto.
 * @Param:
 *   logToGenerate -> este es el log que quiere ser generado.
 *   textoToSend -> el lugar para guardar el mensaje.
 */
void generateMessage(logData logToGenerate, uint8_t* textToSave){
    uint8_t googleMapsLink[64];
    GPS_generateGoogleMaps(googleMapsLink, logToGenerate.gps);
    sprintf(textToSave, "%d %s %s %.1f\n", logToGenerate.id, ctime(&logToGenerate.time), googleMapsLink, logToGenerate.temperature);
}
/* *****************************************************************************
 End of File
 */
