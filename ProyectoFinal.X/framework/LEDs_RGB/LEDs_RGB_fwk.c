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
#include "LEDs_RGB_fwk.h"
#include "../../platform/WS2812.h"


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
static ws2812_t ledsMatrix[LED_RGB_SIZE];


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
/** 
  @Function
    int ExampleInterfaceFunctionName ( int param1, int param2 ) 

  @Summary
    Brief one-line description of the function.

  @Remarks
    Refer to the example_file.h interface header for function usage details.
 */
void RGB_setLedColor( uint8_t p_index,enum rgb_colors p_color ){
    switch(p_color){
        case RGB_WHITE:
            ledsMatrix[p_index]=WHITE;
            break;
        case RGB_RED:
            ledsMatrix[p_index]=RED;
            break;
        case RGB_BLUE:
            ledsMatrix[p_index]=BLUE;
            break;
        case RGB_GREEN:
            ledsMatrix[p_index]=GREEN;
            break;
        case RGB_BLACK:
            ledsMatrix[p_index]=BLACK;
            break;
    }
}

/**
 * @Function 
 *    void RGB_setAllColor(int num_Led, enum rgb_colors p_color)
 * 
 * @Summary
 *    Cambia todos los leds al color indicado por parameto.
 * 
 * @Param:
 *   @param num_Led
 *   @param p_color
 */
void RGB_setAllColor(int num_Led, enum rgb_colors p_color){
    int i;
    for(i = 0; i < num_Led; i++){RGB_setLedColor(i, p_color);}
}


void RGB_showLeds( uint8_t p_qty ){
    if(p_qty>LED_RGB_SIZE){
        p_qty=LED_RGB_SIZE;
    }
    WS2812_send( ledsMatrix, p_qty );
}


/* *****************************************************************************
 End of File
 */
