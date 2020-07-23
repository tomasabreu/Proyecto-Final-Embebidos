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
const uint8_t ui_optionsText2[] = "1) Cambiar ID del dispositivo \n2) Cambiar el umbral de temperatura usado\n3) Cambiar el telefono receptor de advertencias\n4) Cambiar los colores de las medidas de temperatura\n5) Mostrar el log de datos\n";
const uint8_t ui_optionsText1[] = "\nIndique la opción deseada:\nPara tomar la temperatura presione el botón s2 de la placa\n";
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
                switch (counter) {
                    case 0:
                        if (USB_send((uint8_t*) ui_optionsText1)) {
                            counter++;
                        }
                        break;
                    case 1:
                        if (USB_send((uint8_t*) ui_optionsText2)) {
                            memset(dataArray1, 0, sizeof (dataArray1));
                            menuState = UI_MENU_STATE_OPTIONS_WAIT;
                            counter = 0;
                        }
                        break;
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



/** 
 * @Function
 *    bool switchID(int* counter, bool* needNewInput, uint8_t* dataArray)
 *
 * @Summary
 *   Tarea encargada de cambiar el id del dispositivo cuando se lo pide por UI, la misma permite un numero
 *  de 32bits desde 0 hasta 4294967295 
 * 
 * @Param
 *  counter -> el contador para poder utilizar los inputs, este contador se utiliza en el switch.
 * 
 *  needNewInput -> booleano que sirve para ver si se necesita un nuevo input o no.
 * 
 *  dataArray -> el input que se hizo.
 *  
 */
bool switchID(int* counter, bool* needNewInput, uint8_t* dataArray) {
    uint32_t id;
    switch (*counter) {
        case 0:
            USB_send("\nIngrese el ID del dispositivo, debe ser un número entero de 32 bits entre 0 y 4294967295\n");
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
                USB_send("\nPor favor ingrese un valor válido de 32 bits\n");
            }
            *counter = 0;
            return true;
    }
}


/** 
 * @Function
 *    bool switchThreshold(int* counter, bool* needNewInput, uint8_t* dataArray1)
 *
 * @Summary
 *   Tarea encargada de cambiar el numero de umbral o "treshold" de la temperatura, esta tarea utilizando el hercules
 *  cambia la temperatura umbral del dispositivo a medida del usuario.
 * 
 * @Param
 *  counter -> el contador para poder utilizar los inputs, este contador se utiliza en el switch.
 * 
 *  needNewInput -> booleano que sirve para ver si se necesita un nuevo input o no.
 * 
 *  dataArray -> el input que se hizo.
 *  
 */
bool switchThreshold(int* counter, bool* needNewInput, uint8_t* dataArray1) {
    float umbral;
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
            if(dataArray1[2]==','){
                dataArray1[2]='.';
            }
            sscanf(dataArray1, "%f", &umbral);
            if (umbral<=42.0 && umbral >=32.0) {
                setThreshold(umbral);
                USB_send("\nSe cambió exitosamente la temperatura umbral\n");
            } else {
                USB_send("\nPor favor ingrese un valor válido entre 32 y 42 grados\n");
            }
            *counter = 0;
            return true;
    }
}


/** 
 * @Function
 *    bool switchPhoneNumber(int* counter, bool* needNewInput, uint8_t* dataArray2)
 *
 * @Summary
 *   Tarea encargada de cambiar el numero de telefono al cual se va a mandar cuando la temperatura es mayor al umbral
 *  Esto se cambia por el USB, mediante el hecules, el input tiene que ser un numero de telefono correcto uruguayo.
 * 
 * @Param
 *  counter -> el contador para poder utilizar los inputs, este contador se utiliza en el switch.
 * 
 *  needNewInput -> booleano que sirve para ver si se necesita un nuevo input o no.
 * 
 *  dataArray -> el input que se hizo.
 *  
 */
bool switchPhoneNumber(int* counter, bool* needNewInput, uint8_t* dataArray2) {
    uint32_t newPhone;
    switch (*counter) {
        case 0:
            USB_send("\nIngrese un nuevo número de teléfono\n");
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
                USB_send("\nSe cambió exitosamente el número telefónico\n");
            } else {
                USB_send("\nPor favor ingrese un número válido\n");
            }
            *counter = 0;
            return true;
    }
}


/** 
 * @Function
 *    bool switchChangeLedColor(int* counter, bool* needNewInput, uint8_t* dataArray)
 *
 * @Summary
 *   Tarea encargada de cambiar el los colores de los leds, para esta tarea se piden tres numeros de esta forma "1,1,2"
 *  Los numeros tienen que ser del 0 al 3 y cada uno se refiere a un color del led.
 *  Una vez ingresados, si los datos son correctos se cambian los colores de los leds, todo esto es atravez del hercules.
 * 
 * @Param
 *  counter -> el contador para poder utilizar los inputs, este contador se utiliza en el switch.
 * 
 *  needNewInput -> booleano que sirve para ver si se necesita un nuevo input o no.
 * 
 *  dataArray -> el input que se hizo.
 *  
 */
bool switchChangeLedColor(int* counter, bool* needNewInput, uint8_t* dataArray) {

    int firstColor;
    int secondColor;
    int thirdColor;

    switch (*counter) {
        case 0:
            USB_send("\nIngrese números desde 0 a 3.\n0 = Blanco\n1 = Rojo\n2 = Verde\n3 = Azul\nEl formato es \"1,2,3\"\nEl primer número es el color parpadeante al medir la temperatura\nEl segundo se presenta cuando la temperatura es menor al umbral\nY tercero cuando es mayor.\n");
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
                USB_send("\nSe cambió exitosamente los colores\n");
                setLedColor(arrayColors);
            } else {
                USB_send("\nLos datos ingresados no respetan el formato, por favor ingrese los números de los colores correspondientes siendo estos 0,1,2,3\n");
            }
            *counter = 0;
            return true;
    }
}


/** 
 * @Function
 *    bool switchShowAllLog(int* counter)
 *
 * @Summary
 *   Tarea encargada de mostrar el log de datos.
 * 
 * @Param
 *  counter -> el contador para poder utilizar los inputs, este contador se utiliza en el switch.
 *  
 */
bool switchShowAllLog(int* counter) {
    static int i = 0;
    static uint8_t logText[128];
    switch (*counter) {
        case 0:
            if (i < getLastTemperatureIndex()) {
                USB_send("\nEl log guardado hasta el momento es el siguiente:\n");
            } else {
                USB_send("\nEl log de datos está vacio\n");
            }
            (*counter)++;
            return false;
        case 1:
            if (i < getLastTemperatureIndex()) {
                getLog(i, logText);
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
