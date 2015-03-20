/** 
 * \brief Compiler and Platform specific definitions and typedefs common to
 * all platforms.  
 *
 * platform-common.h provides PLATFORM_HEADER defaults and common definitions.
 * This head should never be included directly, it should only be included
 * by the specific PLATFORM_HEADER used by your platform.
 *
 * See platform-common.h for source code.
 *@{
 */

/**
 * @addtogroup stm32w-cpu
 * @{ */

/** \file hal/micro/generic/compiler/platform-common.h
 * See \ref platform_common for detailed documentation.
 *
 * <!--(C) COPYRIGHT 2010 STMicroelectronics. All rights reserved.        -->
 */


#ifndef PLATFORMCOMMON_H_
#define PLATFORMCOMMON_H_
////////////////////////////////////////////////////////////////////////////////
// Many of the common definitions must be explicitly enabled by the 
//  particular PLATFORM_HEADER being used
////////////////////////////////////////////////////////////////////////////////
#include <avr/io.h>

#define TRUE  1
#define HIGH 1
#define FALSE 0
#define LOW 0
#ifndef NULL
#define NULL ((void *)0)
#endif

#define BIT(x) (1 << (x))  // Unsigned avoids compiler warnings re BIT(15)

#define SETBIT(reg, bit)      reg |= BIT(bit)
#define SETBITS(reg, bits)    reg |= (bits)
#define CLEARBIT(reg, bit)    reg &= ~(BIT(bit))
#define CLEARBITS(reg, bits)  reg &= ~(bits)
#define READBIT(reg, bit)     (reg & (BIT(bit)))
#define READBITS(reg, bits)   (reg & (bits))


#define MAX_INT8U_VALUE 0xFF
#define MAX_INT16U_VALUE 0xFFFF
#define MAX_INT32U_VALUE 0xFFFFFFFF

// ========= PORT B Assignement and Description =====================


#define SSD_MOSI_PORT		  PORTB
#define SSD_MOSI_DIR		  DDRB
#define SSD_MOSI_PIN		  PORTB2

#define SSD_MISO_PORT		  PORTB
#define SSD_MISO_DIR		  DDRB
#define SSD_MISO_PIN		  PORTB3

#define SSD_CLK_PORT		  PORTB
#define SSD_CLK_DIR 		  DDRB
#define SSD_CLK_PIN 		  PORTB1


// ========= PORT C Assignement and Description =====================
// None So Far 


// ========= PORT D Assignement and Description =====================

#define SSD_RES_PORT		  PORTD
#define SSD_RES_DIR 		  DDRD
#define SSD_RES_PIN 		  PORTD5

// ========= PORT E Assignement and Description =====================

#define SSD_DC_PORT 		  PORTE
#define SSD_DC_DIR			  DDRE
#define SSD_DC_PIN			  PORTE2


#define LED_STATUS_PORT		  PORTE
#define LED_STATUS_DIR		  DDRE
#define LED_STATUS_PIN		  PORTE4

#define LED_OLED3_PORT		  PORTE
#define LED_OLED3_DIR		  DDRE
#define LED_OLED3_PIN		  PORTE4



// ========= PORT F Assignement and Description =====================
//None so Far 


// ========= PORT G Assignement and Description =====================

#define SSD_CS_PORT 		  PORTG
#define SSD_CS_DIR			  DDRG
#define SSD_CS_PIN			  PORTG0









#endif //PLATFORMCOMMON_H_

/** @}  END addtogroup */
/** @} */

