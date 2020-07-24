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
#include "USB_fwk.h"
#include "../../mcc_generated_files/usb/usb.h"
#include "../../mcc_generated_files/pin_manager.h"
#include <string.h>
#include "FreeRTOS.h"


/* ************************************************************************** */
/* ************************************************************************** */
/* Section: File Scope or Global Data                                         */
/* ************************************************************************** */
/* ************************************************************************** */

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

static bool usb_connected = false;


/* ************************************************************************** */
/* ************************************************************************** */
// Section: Local Functions                                                   */
/* ************************************************************************** */
/* ************************************************************************** */

/* ************************************************************************** */

/**
  @Function
    int ExampleLocalFunctionName ( int param1, int param2 )

  @Summary
    Brief one-line description of the function.

  @Description
    Full description, explaining the purpose and usage of the function.
    <p>
    Additional description in consecutive paragraphs separated by HTML
    paragraph breaks, as necessary.
    <p>
    Type "JavaDoc" in the "How Do I?" IDE toolbar for more information on tags.

  @Precondition
    List and describe any required preconditions. If there are no preconditions,
    enter "None."

  @Parameters
    @param param1 Describe the first parameter to the function.

    @param param2 Describe the second parameter to the function.

  @Returns
    List (if feasible) and describe the return values of the function.
    <ul>
      <li>1   Indicates an error occurred
      <li>0   Indicates an error did not occur
    </ul>

  @Remarks
    Describe any special behavior not described above.
    <p>
    Any additional remarks.

  @Example
    @code
    if(ExampleFunctionName(1, 2) == 0)
    {
        return 3;
    }
 */


/* ************************************************************************** */
/* ************************************************************************** */
// Section: Interface Functions                                               */
/* ************************************************************************** */
/* ************************************************************************** */

// *****************************************************************************

/**
  @Function
    int ExampleInterfaceFunctionName ( int param1, int param2 )

  @Summary
    Brief one-line description of the function.

  @Remarks
    Refer to the example_file.h interface header for function usage details.
 */
void USB_checkStatus( void ) {
    if( (USBGetDeviceState() >= CONFIGURED_STATE) && !USBIsDeviceSuspended()) {
        CDCTxService();
        usb_connected = true;
    }
    else {
        usb_connected = false;
    }
}

bool USB_getConnectedStatus( void ) {
    return usb_connected;
}

void USB_setConnectedStatus( bool p_status ) {
    usb_connected = p_status;
}

uint8_t USB_receive( uint8_t *p_dest ) {
    return getsUSBUSART(p_dest, CDC_DATA_IN_EP_SIZE);
}

bool USB_send( uint8_t *p_src ) {
    if( USBUSARTIsTxTrfReady() ) {
        putsUSBUSART(p_src);
        return true;
    }
    else {
        return false;
    }
}

/** 
 * @Function
 *    void sendUsb(uint8_t* text)
 *
 * @Summary
 *   Este se encarga de mandar por usb un texto dado, si este falla un número de veces en este caso 10, se libera.
 *  
 *  
 * @Param: uint8_t* text: texto que se envia por el puerto usb.
 */
void sendUsb(uint8_t* text) {
    uint8_t i;
    for (i = 0; i < 10; i++) {
        USB_checkStatus();
        if (USB_getConnectedStatus() && USB_send(text)) {
            break;
        }
        vTaskDelay(pdMS_TO_TICKS(100));
    }
    USB_checkStatus();
}


/* *****************************************************************************
 End of File
 */
