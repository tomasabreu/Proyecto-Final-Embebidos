/**
  Generated main.c file from MPLAB Code Configurator

  @Company
    Microchip Technology Inc.

  @File Name
    main.c

  @Summary
    This is the generated main.c using PIC24 / dsPIC33 / PIC32MM MCUs.

  @Description
    This source file provides main entry point for system initialization and application code development.
    Generation Information :
        Product Revision  :  PIC24 / dsPIC33 / PIC32MM MCUs - 1.167.0
        Device            :  PIC32MM0256GPM064
    The generated drivers are tested against the following:
        Compiler          :  XC16 v1.50
        MPLAB 	          :  MPLAB X v5.35
 */

/*
    (c) 2020 Microchip Technology Inc. and its subsidiaries. You may use this
    software and any derivatives exclusively with Microchip products.

    THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER
    EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED
    WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS FOR A
    PARTICULAR PURPOSE, OR ITS INTERACTION WITH MICROCHIP PRODUCTS, COMBINATION
    WITH ANY OTHER PRODUCTS, OR USE IN ANY APPLICATION.

    IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE,
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND
    WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS
    BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO THE
    FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS IN
    ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF ANY,
    THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.

    MICROCHIP PROVIDES THIS SOFTWARE CONDITIONALLY UPON YOUR ACCEPTANCE OF THESE
    TERMS.
 */

/**
  Section: Included Files
 */

/* Kernel includes. */
#include <stdio.h>

#include "FreeRTOS.h"
#include "task.h"
#include "stdint.h"
#include "mcc_generated_files/system.h"
#include "mcc_generated_files/pin_manager.h"
#include "platform/WS2812.h"
#include "mcc_generated_files/usb/usb.h"
#include "framework/LEDs_RGB/LEDs_RGB_fwk.h"
#include "framework/USB/USB_fwk.h"
#include "string.h"
#include "mcc_generated_files/adc1.h"
#include "Temperature/TEMP_MANAGER.h"

void takeTemperature(void *p_param);
void temperatureSwitch(void *p_param);
void sendUsbTemperature(void *p_param);
static bool BTN1_pressed = false;

/*
                         Main application
 */
int main(void) {
    // initialize the device
    SYSTEM_Initialize();
    /* Create the tasks defined within this file. */
    xTaskCreate(sendUsbTemperature, "Take Temperature", configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY + 1, NULL);
//    xTaskCreate(takeTemperature, "Take Temperature", configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY + 1, NULL);
//    xTaskCreate(temperatureSwitch, "Take Temperature", configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY + 1, NULL);

    /* Finally start the scheduler. */
    vTaskStartScheduler();

    /* If all is well, the scheduler will now be running, and the following line
    will never be reached.  If the following line does execute, then there was
    insufficient FreeRTOS heap memory available for the idle and/or timer tasks
    to be created.  See the memory management section on the FreeRTOS web site
    for more details. */
    for (;;);
}

void temperatureSwitch(void *p_param) {
    for (;;) {
        if (BTN1_GetValue()) {
            BTN1_pressed = !BTN1_pressed;
            RGB_setAllColor(8, RGB_BLACK);
            RGB_showLeds(8);
            while (BTN1_GetValue()) {
                vTaskDelay(pdMS_TO_TICKS(100));
            }
        }
    }
}

void sendUsbTemperature(void *p_param) {
    for (;;) {
        USB_checkStatus();
        if (USB_getConnectedStatus()) {
            
            sprintf(usb_writeBuffer,"%d\n",getTemperature());
            USB_send(usb_writeBuffer);
            vTaskDelay(pdMS_TO_TICKS(100));
        }
    }
}

void takeTemperature(void *p_param) {
    // Add your code here
    uint8_t i, counterPressed;
    uint16_t finishedTemperature;
    for (;;) {
        if (BTN1_pressed) {
            for (counterPressed = 0; counterPressed < 10; counterPressed++) {
                if (!BTN1_pressed) {
                    break;
                }
                if (counterPressed % 2 == 0) {
                    RGB_setAllColor(8, RGB_BLUE);
                } else {
                    RGB_setAllColor(8, RGB_BLACK);
                }
                finishedTemperature += getTemperature(); //Temperature has a 10 ms delay
                vTaskDelay(pdMS_TO_TICKS(240));
                RGB_showLeds(8);
            }
            if (counterPressed == 10) {
                finishedTemperature /= 10;
                if (finishedTemperature > 37) {
                    RGB_setAllColor(8, RGB_RED);
                } else {
                    RGB_setAllColor(8, RGB_GREEN);
                }
                RGB_showLeds(8);
                BTN1_pressed = false;
                vTaskDelay(pdMS_TO_TICKS(2000));
                RGB_setAllColor(8, RGB_BLACK);
                RGB_showLeds(8);
            }
        }
    }
}

void vApplicationMallocFailedHook(void) {
    /* vApplicationMallocFailedHook() will only be called if
    configUSE_MALLOC_FAILED_HOOK is set to 1 in FreeRTOSConfig.h.  It is a hook
    function that will get called if a call to pvPortMalloc() fails.
    pvPortMalloc() is called internally by the kernel whenever a task, queue,
    timer or semaphore is created.  It is also called by various parts of the
    demo application.  If heap_1.c or heap_2.c are used, then the size of the
    heap available to pvPortMalloc() is defined by configTOTAL_HEAP_SIZE in
    FreeRTOSConfig.h, and the xPortGetFreeHeapSize() API function can be used
    to query the size of free heap space that remains (although it does not
    provide information on how the remaining heap might be fragmented). */
    taskDISABLE_INTERRUPTS();
    for (;;);
}

/*-----------------------------------------------------------*/

void vApplicationIdleHook(void) {
    /* vApplicationIdleHook() will only be called if configUSE_IDLE_HOOK is set
    to 1 in FreeRTOSConfig.h.  It will be called on each iteration of the idle
    task.  It is essential that code added to this hook function never attempts
    to block in any way (for example, call xQueueReceive() with a block time
    specified, or call vTaskDelay()).  If the application makes use of the
    vTaskDelete() API function (as this demo application does) then it is also
    important that vApplicationIdleHook() is permitted to return to its calling
    function, because it is the responsibility of the idle task to clean up
    memory allocated by the kernel to any task that has since been deleted. */
}

/*-----------------------------------------------------------*/

void vApplicationStackOverflowHook(TaskHandle_t pxTask, char *pcTaskName) {
    (void) pcTaskName;
    (void) pxTask;

    /* Run time task stack overflow checking is performed if
    configCHECK_FOR_STACK_OVERFLOW is defined to 1 or 2.  This hook	function is 
    called if a task stack overflow is detected.  Note the system/interrupt
    stack is not checked. */
    taskDISABLE_INTERRUPTS();
    for (;;);
}

/*-----------------------------------------------------------*/

void vApplicationTickHook(void) {
    /* This function will be called by each tick interrupt if
    configUSE_TICK_HOOK is set to 1 in FreeRTOSConfig.h.  User code can be
    added here, but the tick hook is called from an interrupt context, so
    code must not attempt to block, and only the interrupt safe FreeRTOS API
    functions can be used (those that end in FromISR()). */
}

/*-----------------------------------------------------------*/

/*-----------------------------------------------------------*/

void vAssertCalled(const char * pcFile, unsigned long ulLine) {
    volatile unsigned long ul = 0;

    (void) pcFile;
    (void) ulLine;

    __asm volatile( "di");
    {
        /* Set ul to a non-zero value using the debugger to step out of this
        function. */
        while (ul == 0) {
            portNOP();
        }
    }
    __asm volatile( "ei");
}

/**
 End of File
 */

