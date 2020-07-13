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
#include "semphr.h"
#include "SIM808/SIM808.h" 

/* TODO:  Include other files here if needed. */


/* ************************************************************************** */
/* ************************************************************************** */
/* Section: File Scope or Global Data                                         */
/* ************************************************************************** */
/* ************************************************************************** */

/*  A brief description of a section can be given directly below the section
    banner.
 */
uint8_t phoneNumber[9];

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
// Section: Interface Functions                                               */
/* ************************************************************************** */
/* ************************************************************************** */

uint8_t* getPhoneNumber(){
    return phoneNumber;
}

void setPhoneNumber(uint8_t* phone){
    strcpy(phoneNumber,phone);
}



void sendSMS(char* text){
    for(;;){
        if(c_semGSMIsReady != NULL && xSemaphoreTake(c_semGSMIsReady, portMAX_DELAY) == pdTRUE){
            SIM808_sendSMS("099472077",text);
            xSemaphoreGive(c_semGSMIsReady);
        }
        vTaskDelay(pdMS_TO_TICKS(100));
    }
}


