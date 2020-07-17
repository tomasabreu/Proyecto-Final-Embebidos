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
#include "DATA_MANAGER.h"


/* ************************************************************************** */
/* ************************************************************************** */
/* Section: File Scope or Global Data                                         */
/* ************************************************************************** */
/* ************************************************************************** */

/*  A brief description of a section can be given directly below the section
    banner.
 */

static uint32_t phoneNumber = 91969979;
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

void setID(uint32_t newId) {
    id = newId;
}

uint32_t getID() {
    return id;
}

void setPhone(uint32_t phone) {
    phoneNumber = phone;
}

uint32_t getPhone() {
    return phoneNumber;
}

void setLedColor(uint8_t* ledColors) {
    int i;
    for (i = 0; i < 3; i++){
        switch (ledColors[i]) {
            case 0:
                ledColor[i] = rgb_colors.RGB_WHITE;
                break;
            case 1:
                ledColor[i] = rgb_colors.RGB_BLUE;
                break;
            case 2:
                ledColor[i] = rgb_colors.RGB_GREEN;
                break;
            case 3:
                ledColor[i] = rgb_colors.RGB_RED;
                break;
        }
    }
}

enum rgb_colors* getLedColor(){
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
