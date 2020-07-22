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

#include "DATA_MANAGER.h"
#include "../framework/LEDs_RGB/LEDs_RGB_fwk.h"


/* ************************************************************************** */
/* ************************************************************************** */
/* Section: File Scope or Global Data                                         */
/* ************************************************************************** */
/* ************************************************************************** */

/*  A brief description of a section can be given directly below the section
    banner.
 */

static uint32_t phoneNumber = 99472077;
static uint32_t id = 1234;
static enum rgb_colors ledColor[3] = {RGB_BLUE, RGB_GREEN, RGB_RED};

/* ************************************************************************** */
/* ************************************************************************** */
// Section: Local Functions                                                   */
/* ************************************************************************** */
/* ************************************************************************** */

/*  A brief description of a section can be given directly below the section
    banner.
 */

/* ************************************************************************** */


/** 
 * @Function
 *    void setID(uint32_t newId)
 *
 * @Summary
 *   Esta funcion se encarga de setear el id del dispositivo.
 *  
 * @Param:
 *   newId -> el nuevo id que quiere colocar.
 */
void setID(uint32_t newId) {
    id = newId;
}


/** 
 * @Function
 *    uint32_t getID()
 *
 * @Summary
 *   Esta funcion da el id del dispositivo.
 *  
 */
uint32_t getID() {
    return id;
}


/** 
 * @Function
 *    void setPhone(uint32_t phone)
 *
 * @Summary
 *   Esta funcion se encarga de setear el telefono para enviar mensaje.
 *  
 * @Param:
 *   phone -> celular para setear.
 */
void setPhone(uint32_t phone) {
    phoneNumber = phone;
}


/** 
 * @Function
 *    uint32_t getPhone()
 *
 * @Summary
 *   Esta funcion da el celular que se usa para enviar un mensaje de texto.
 *  
 */
uint32_t getPhone() {
    return phoneNumber;
}


/** 
 * @Function
 *    void setLedColor(uint8_t* arrayColors)
 *
 * @Summary
 *   Esta funcion se encarga de setear los colores para la medida de temperatura.
 *  En esto se setea el color para cuando se esta midiendo la temperatura,
 *  el color para cuando la temperatura es mayor al umbral y
 *  el colo para cuando la temperatura es menor al umbral.
 *  
 * @Param:
 *   arrayColors -> es el array con los numeros de colores que el usuario quiere cambiar.
 */
void setLedColor(uint8_t* arrayColors) {
    uint8_t i;
    for (i = 0; i < 3; i++) {
        uint8_t value = arrayColors[i];
        switch (value) {
            case 0:
                ledColor[i] = RGB_WHITE;
                break;
            case 1:
                ledColor[i] = RGB_RED;
                break;
            case 2:
                ledColor[i] = RGB_GREEN;
                break;
            case 3:
                ledColor[i] = RGB_BLUE;
                break;
        }
    }
}


/** 
 * @Function
 *    enum rgb_colors* getLedColor()
 *
 * @Summary
 *   Esta funcion da el color de los leds.
 *  
 */
enum rgb_colors* getLedColor() {
    return ledColor;
}

/* ************************************************************************** */
/* ************************************************************************** */
// Section: Interface Functions                                               */
/* ************************************************************************** */
/* ************************************************************************** */

/*  A brief description of a section can be given directly below the section
    banner.
 */

// *****************************************************************************



/* *****************************************************************************
 End of File
 */
