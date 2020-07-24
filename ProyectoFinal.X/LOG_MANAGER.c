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
#include "DataManager/DATA_MANAGER.h"
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
static logData savedLogs[amountOfSaveTemperatures];
static uint8_t lastTemperatureIndex = 0;



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
        savedLogs[lastTemperatureIndex].id = lastTemperatureIndex+1;
        savedLogs[lastTemperatureIndex].gps = log.gps;    
        savedLogs[lastTemperatureIndex].temperature = log.temperature;    
        savedLogs[lastTemperatureIndex].time = log.time;    
        lastTemperatureIndex++;
        return true;
    }
    return false;
}


/** 
 * @Function
 *   int getLastTemperatureIndex()
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
 *   void getLog(int index)
 *
 * @Summary
 *   Esta funcion se encarga dar el log de datos.
 * @Param:
 *   index -> el index es el lugar donde esta el log de datos en el array con logs de datos
 */
logData getLog(int index){
    logData data;
    if(index < lastTemperatureIndex){
        data = savedLogs[index];
    }
    return data;
}


/** 
 * @Function
 *    void generateMessage(logData logToGenerate, uint8_t* textToSave, bool withID)
 *
 * @Summary
 *   Esta funcion se encarga generar el mensaje completo para ser enviado por mensaje de texto.
 * @Param:
 *   logToGenerate -> este es el log que quiere ser generado.
 *   textoToSend -> el lugar para guardar el mensaje.
 *   withID -> algunos mensajes pueden necesitar que se envíe con ID del dispositivo o ID del log, este bool cuando verdadero
 *             define que se debe envíar el mensaje con el ID del dispotivo. Sino se manda con el ID del log.
 */
void generateMessage(logData logToGenerate, uint8_t* textToSave, bool withID){
    static uint8_t googleMapsLink[64];
    GPS_generateGoogleMaps(googleMapsLink, logToGenerate.gps);
    uint32_t idOrNumOfArray = logToGenerate.id;
    if(withID){
        idOrNumOfArray = getID();
    }
    sprintf(textToSave, "%d %s %s %.1f\n", idOrNumOfArray, ctime(&logToGenerate.time), googleMapsLink, logToGenerate.temperature);
}
/* *****************************************************************************
 End of File
 */
