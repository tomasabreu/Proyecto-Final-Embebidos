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

#include "UI.h"
#include "../../framework/USB/USB_fwk.h"
#include "../Temperature/TEMP_MANAGER.h"
#include "../DataManager/DATA_MANAGER.h"
#include "../LOG_MANAGER.h"
#include <string.h>
#include <ctype.h>
#include <stdio.h>

/* ************************************************************************** */
/* ************************************************************************** */
/* Section: File Scope or Global Data                                         */
/* ************************************************************************** */
/* ************************************************************************** */

/*  A brief description of a section can be given directly below the section
    banner.
 */

/* ************************************************************************** */
/** Descriptive Data Item Name

  @Summary
    Brief one-line summary of the data item.

  @Description
    Full description, explaining the purpose and usage of data item.
    <p>
    Additional description in consecutive paragraphs separated by HTML
    paragraph breaks, as necessary.
    <p>
    Type "JavaDoc" in the "How Do I?" IDE toolbar for more information on tags.

  @Remarks
    Any additional remarks
 */
const uint8_t ui_welcomeText[] = "Bienvenido al Proyecto de Sistemas Embebidos\nPor favor presione una tecla para continuar...\n";
const uint8_t ui_optionsText[] = "\nIndique la opci�n deseada:\n1) Cambiar el ID del dispositivo \n2) Cambiar el umbral de temperatura usado\n3) Cambiar el telefono al que se le manda el mensaje\n4) Cambiar los colores de las medidas de temperatura\n5) Mostrar el log de datos\n";

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

// *****************************************************************************

void UI_showMenu(void) {
    static ui_menu_states_t menuState = UI_MENU_STATE_INIT_SHOW;
    static uint8_t dataArray1[64];
    static bool showWelcome = false;
    static bool needNewInput1 = false;
    static int counter = 0;
    USB_checkStatus();
    if (USB_getConnectedStatus()) {
        switch (menuState) {
            case( UI_MENU_STATE_INIT_SHOW):
                if (!showWelcome && UI_waitForInput(dataArray1))
                    showWelcome = true;
                if (showWelcome && USB_send((uint8_t*) ui_welcomeText)) {
                    memset(dataArray1, 0, sizeof (dataArray1));
                    menuState = UI_MENU_STATE_INIT_WAIT;
                }
                break;
            case( UI_MENU_STATE_INIT_WAIT):
                if (UI_waitForInput(dataArray1)) {
                    menuState = UI_MENU_STATE_OPTIONS_SHOW;
                }
                break;
            case( UI_MENU_STATE_OPTIONS_SHOW):
                if (USB_send((uint8_t*) ui_optionsText)) {
                    memset(dataArray1, 0, sizeof (dataArray1));
                    menuState = UI_MENU_STATE_OPTIONS_WAIT;
                }
                break;
            case( UI_MENU_STATE_OPTIONS_WAIT):
                if (UI_waitForInput(dataArray1)) {
                    menuState = UI_MENU_STATE_OPTIONS_CHECK;
                }
                break;
            case( UI_MENU_STATE_OPTIONS_CHECK):
                if ((UI_checkValidOption(dataArray1, UI_OPTION_NUM, 5, 1))) {
                    menuState = UI_MENU_STATE_OPTIONS_CHECK + atoi(dataArray1);
                } else {
                    menuState = UI_MENU_STATE_OPTIONS_SHOW;
                }
                break;
            case( UI_MENU_STATE_CHANGE_ID):
                if (needNewInput1 && UI_waitForInput(dataArray1)) {
                    needNewInput1 = false;
                }
                if (!needNewInput1 && switchID(&counter, &needNewInput1, dataArray1)) {
                    menuState = UI_MENU_STATE_OPTIONS_SHOW;
                }
                break;
            case( UI_MENU_STATE_TEMPERATURE_THRESHOLD_CHANGE):
                if (needNewInput1 && UI_waitForInput(dataArray1)) {
                    needNewInput1 = false;
                }
                if (!needNewInput1 && switchThreshold(&counter, &needNewInput1, dataArray1)) {
                    menuState = UI_MENU_STATE_OPTIONS_SHOW;
                }
                break;
            case( UI_MENU_STATE_PHONE_CHANGE):
                if (needNewInput1 && UI_waitForInput(dataArray1)) {
                    needNewInput1 = false;
                }
                if (!needNewInput1 && switchPhoneNumber(&counter, &needNewInput1, dataArray1)) {
                    menuState = UI_MENU_STATE_OPTIONS_SHOW;
                }
                break;
            case( UI_MENU_STATE_LED_COLOR_CHANGE):
                if (needNewInput1 && UI_waitForInput(dataArray1)) {
                    needNewInput1 = false;
                }
                if (!needNewInput1 && switchChangeLedColor(&counter, &needNewInput1, dataArray1)) {
                    menuState = UI_MENU_STATE_OPTIONS_SHOW;
                }
                break;
            case( UI_MENU_STATE_SHOW_ALL_LOGS):
                if (switchShowAllLog(&counter)) {
                    menuState = UI_MENU_STATE_OPTIONS_SHOW;
                }
                break;
        }
    } else {
        menuState = UI_MENU_STATE_INIT_SHOW;
    }
}

bool UI_waitForInput(uint8_t *p_dest) {
    uint8_t bytesReceived;

    bytesReceived = USB_receive(p_dest);
    if (bytesReceived > 0) {
        p_dest[bytesReceived] = '\0';
        return true;
    }
    return false;
}

bool switchID(int* counter, bool* needNewInput, uint8_t* dataArray) {
    uint32_t id;
    switch (*counter) {
        case 0:
            USB_send("\nIngrese el ID del dispositivo, debe ser un n�mero de 32 bits entre 0 y 4294967295\n");
            (*counter)++;
            return false;
        case 1:
            if (!(*needNewInput)) {
                *needNewInput = true;
                (*counter)++;
                return false;
            }
        case 2:
            if (UI_checkValidOption(dataArray, UI_OPTION_NUM, 4294967295.0, 0)) {
                sscanf(dataArray, "%u", &id);
                setID(id);
                USB_send("\nSe cambio exitosamente el ID del dispositivo\n");
            } else {
                USB_send("\nPor favor ingrese un valor v�lido de 32 bits\n");
            }
            *counter = 0;
            return true;
    }
}

bool switchThreshold(int* counter, bool* needNewInput, uint8_t* dataArray1) {
    float umbral;
    uint8_t array[10];
    switch (*counter) {
        case 0:
            USB_send("\nIngrese la temperatura umbral nueva\n");
            (*counter)++;
            return false;
        case 1:
            if (!(*needNewInput)) {
                *needNewInput = true;
                (*counter)++;
                return false;
            }
        case 2:
            if (UI_checkValidOption(dataArray1, UI_OPTION_NUM, 42, 32)) {
                sscanf(dataArray1, "%f", &umbral);
                strcpy(array, dataArray1);
                setThreshold(umbral);
                USB_send("\nSe cambi� exitosamente la temperatura umbral\n");
            } else {
                USB_send("\nPor favor ingrese un valor v�lido entre 32 y 42 grados\n");
            }
            *counter = 0;
            return true;
    }
}

bool switchPhoneNumber(int* counter, bool* needNewInput, uint8_t* dataArray2) {
    uint32_t newPhone;
    switch (*counter) {
        case 0:
            USB_send("\nIngrese un nuevo n�mero de tel�fono\n");
            (*counter)++;
            return false;
        case 1:
            if (!(*needNewInput)) {
                *needNewInput = true;
                (*counter)++;
                return false;
            }
        case 2:
            if (UI_checkValidOption(dataArray2, UI_OPTION_NUM, 99999999, 91000000)) {
                sscanf(dataArray2, "%u", &newPhone);
                setPhone(newPhone);
                USB_send("\nSe cambi� exitosamente el n�mero telef�nico\n");
            } else {
                USB_send("\nPor favor n�mero v�lido\n");
            }
            *counter = 0;
            return true;
    }
}

bool switchChangeLedColor(int* counter, bool* needNewInput, uint8_t* dataArray) {

    int firstColor;
    int secondColor;
    int thirdColor;

    switch (*counter) {
        case 0:
            USB_send("\nIngrese n�meros desde 0 a 3.\n0 = Blanco\n1 = Rojo\n2 = Verde\n3 = Azul\nEl formato es \"1,2,3\"\nEl primer n�mero es el color parpadiante al medir la temperatura\nEl segundo se presenta cuando la temperatura es menor al umbral\nY tercero cuando es mayor.\n");
            (*counter)++;
            return false;
        case 1:
            if (!(*needNewInput)) {
                *needNewInput = true;
                (*counter)++;
                return false;
            }
        case 2:

            sscanf(dataArray, "%d,%d,%d", &firstColor, &secondColor, &thirdColor);
            if (firstColor >= 0 && firstColor < 4 && secondColor >= 0 && secondColor < 4 && thirdColor >= 0 && thirdColor < 4) {
                uint8_t arrayColors[3] = {firstColor, secondColor, thirdColor};
                USB_send("\nSe cambi� exitosamente los colores\n");
                setLedColor(arrayColors);
            } else {
                USB_send("\nLos datos ingresados no respetan el formato, por favor ingrese los n�meros de los colores correspondientes siendo estos 0,1,2,3\n");
            }
            *counter = 0;
            return true;
    }
}

bool switchShowAllLog(int* counter) {
    static int i = 0;
    static uint8_t logText[128];
    switch (*counter) {
        case 0:
            if (i < getLastTemperatureIndex()) {
                USB_send("\nEl log guardado hasta el momento es el siguiente:\n");
            }
            else{
                USB_send("\nEl log de datos est� vacio\n");
            }
            (*counter)++;
            return false;
        case 1:
            if (i < getLastTemperatureIndex()) {
                getLog(i,logText);
                if (logText) {
                    i++;
                }
                return false;
            }
            i = 0;
            *counter = 0;
            return true;
    }
}

bool UI_checkValidOption(uint8_t *p_src, ui_options_t p_type, double p_max, double p_min) {
    double intValue;
    uint32_t i;

    switch (p_type) {
        case UI_OPTION_NUM:
            for (i = 0; i < strlen(p_src); i++) {
                if (isdigit(p_src[i]) == 0) {
                    return false;
                }
            }
            intValue = atof(p_src);
            if ((intValue < p_min) || (intValue > p_max)) {
                return false;
            }
            break;

        case UI_OPTION_ALPHANUM:
            for (i = 0; i < strlen(p_src); i++) {
                if (isalnum(p_src[i]) == 0) {
                    return false;
                }
            }
            if (strlen(p_src) > p_max) {
                return false;
            }
            break;

        case UI_OPTION_ALPHA:
            for (i = 0; i < strlen(p_src); i++) {
                if (isalpha(p_src[i]) == 0) {
                    return false;
                }
            }
            if (strlen(p_src) > p_max) {
                return false;
            }
            break;
    }
    return true;
}


/* *****************************************************************************
 End of File
 */
