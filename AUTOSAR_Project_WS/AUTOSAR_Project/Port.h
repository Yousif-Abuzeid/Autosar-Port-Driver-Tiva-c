/******************************************************************************
 *
 * Module: Port
 *
 * File Name: Port.h
 *
 * Description: Header file for TM4C123GH6PM Microcontroller - Port Driver
 *
 * Author: Youssef Abuzeid
 ******************************************************************************/

#ifndef PORT_H
#define PORT_H

/* Id for the company in the AUTOSAR
 * for example Youssef Abuzeid's ID = 5000 :) */
#define PORT_VENDOR_ID    (5000U)

/* Port Module Id */
#define PORT_MODULE_ID    (124U)

/* Port Instance Id */
#define PORT_INSTANCE_ID  (0U)

/*
 * Module Version 1.0.0
 */
#define PORT_SW_MAJOR_VERSION           (1U)
#define PORT_SW_MINOR_VERSION           (0U)
#define PORT_SW_PATCH_VERSION           (0U)

/*
 * AUTOSAR Version 4.0.3
 */
#define PORT_AR_RELEASE_MAJOR_VERSION   (4U)
#define PORT_AR_RELEASE_MINOR_VERSION   (0U)
#define PORT_AR_RELEASE_PATCH_VERSION   (3U)


/*
 * Macros for PORT Status
 */
#define PORT_INITIALIZED                (1U)
#define PORT_NOT_INITIALIZED            (0U)

/* Standard AUTOSAR types */
#include "Std_Types.h"
/* AUTOSAR checking between Std Types and Port Modules */
#if ((STD_TYPES_AR_RELEASE_MAJOR_VERSION != PORT_AR_RELEASE_MAJOR_VERSION)\
 ||  (STD_TYPES_AR_RELEASE_MINOR_VERSION != PORT_AR_RELEASE_MINOR_VERSION)\
 ||  (STD_TYPES_AR_RELEASE_PATCH_VERSION != PORT_AR_RELEASE_PATCH_VERSION))
  #error "The AR version of Std_Types.h does not match the expected version"
#endif

#include "Port_Cfg.h"
/* AUTOSAR checking between Port_Cfg.h and Port.h files */
#if ((PORT_CFG_AR_RELEASE_MAJOR_VERSION != PORT_AR_RELEASE_MAJOR_VERSION)\
 ||  (PORT_CFG_AR_RELEASE_MINOR_VERSION != PORT_AR_RELEASE_MINOR_VERSION)\
 ||  (PORT_CFG_AR_RELEASE_PATCH_VERSION != PORT_AR_RELEASE_PATCH_VERSION))
  #error "The AR version of Std_Types.h does not match the expected version"
#endif

   /* Software Version checking between Port_Cfg.h and Port.h files */
#if ((PORT_CFG_SW_MAJOR_VERSION != PORT_SW_MAJOR_VERSION)\
 ||  (PORT_CFG_SW_MINOR_VERSION != PORT_SW_MINOR_VERSION)\
 ||  (PORT_CFG_SW_PATCH_VERSION != PORT_SW_PATCH_VERSION))
  #error "The SW version of Port_Cfg.h does not match the expected version"
#endif   
   
/* Non AUTOSAR files */
#include "Common_Macros.h"


/******************************************************************************
 *                      API Service Id Macros                                 *
 ******************************************************************************/
/*Servie ID For Port Init*/
#define PORT_INIT_SID                             (uint8)0x00
/*Servie ID For Port Set Pin Direction*/
#define PORT_SET_PIN_DIRECTION_SID                (uint8)0x01
/*Servie ID For Port Refresh Port Direction*/
#define PORT_REFRESH_PORT_DIRECTION_SID           (uint8)0x02
/*Servie ID For Port Get  Version Info*/
#define PORT_GET_VERSION_INFO_SID                 (uint8)0x03
/*Servie ID For Port Set Pin Mode*/
#define PORT_SET_PIN_MODE_SID                     (uint8)0x04



/*******************************************************************************
 *                      DET Error Codes                                        *
 *******************************************************************************/


/*Invalid Port Pin ID requested */
#define   PORT_E_PARAM_PIN                        (uint8)0x0A
/*Port Pin not configured as changeable */
#define   PORT_E_DIRECTION_UNCHANGEABLE           (uint8)0x0B
/*API Port_Init service called with wrong parameter */
#define   PORT_E_PARAM_CONFIG                     (uint8)0x0C
/*API Port_SetPinMode service called with invalud mode*/
#define   PORT_E_PARAM_INVALID_MODE               (uint8)0x0D
/*API Port_SetPinMode service called when mode is unchangeable*/
#define   PORT_E_MODE_UNCHANGEABLE                (uint8)0x0E
/*API service called without module initialization */
#define   PORT_E_UNINIT                           (uint8)0x0F
/*APIs called with a Null Pointer*/
#define   PORT_E_PARAM_POINTER                    (uint8)0x10

/*******************************************************************************
 *                              Module Data Types                              *
 *******************************************************************************/


typedef uint8 Port_PinType;

/* Description: Enum to hold PIN direction */
typedef enum{
  PORT_PIN_IN,/*Sets port pin as input*/
  PORT_PIN_OUT /*Sets port pin as output*/
}Port_PinDirectionType;

typedef uint8 Port_PinModeType;

/* Description: Enum to hold internal resistor type for PIN */
typedef enum
{
    OFF,
    PULL_UP,
    PULL_DOWN
}Port_InternalResistor;

/* Description: Structure to configure each individual PIN:
 *	1. the PORT Which the pin belongs to. A, B, C, D, E or F
 *	2. the number of the pin in the PORT.
 *  3. the mode of the pin
 *  4. the direction of pin --> INPUT or OUTPUT
 *  5. is the direction of pin changable during runtime
 *  6. is the mode of pin changable during runtime
 *  7. the internal resistor --> Disable, Pull up or Pull down
 *  8. Initial value for the pin
 */
typedef struct 
{
    Port_PinType port_num; 
    Port_PinType pin_num; 
    Port_PinDirectionType pin_direction;
    uint8 pin_direction_changable;
    uint8 pin_mode_changable;
    Port_InternalResistor pin_resistor;
    uint8 pin_level_init_value;
     Port_PinModeType pin_mode;
    
}Port_ConfigPins;

/*
 * Structure of congirations for all of pins
*/
typedef struct
{
	Port_ConfigPins Pins[PORT_NUMBER_OF_PORT_PINS ];      
}Port_ConfigType;

/*******************************************************************************
 *                      Function Prototypes                                    *
 *******************************************************************************/


/************************************************************************************
* Service Name: Port_Init
* Sync/Async: Synchronous
* Service ID[hex]:0x00
* Reentrancy: Non-reentrant
* Parameters (in): ConfigPtr - Pointer to post-build configuration data
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description: Function to Initializes the Port Driver module.
*              - Setup the pins as Digital GPIO pins
*              - Setup the direction of the GPIO pins
*              - Setup the internal resistor for i/p pins
*              - Setup the inintial value for pins  
************************************************************************************/
void port_init(const Port_ConfigType* ConfigPtr);



/************************************************************************************
* Service Name: Port_SetPinDirection
* Sync/Async: Synchronous
* Service ID[hex]:0x01
* Reentrancy: Reentrant
* Parameters (in):  Pin > Port Pin ID number 
                    Direction> Port Pin Direction 
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description: Function to Sets the port pin direction.
************************************************************************************/
#if (PORT_SET_PIN_DIRECTION_API == STD_ON)
void Port_SetPinDirection( Port_PinType Pin, Port_PinDirectionType Direction );
#endif

/************************************************************************************
* Service Name: Port_RefreshPortDirection
* Sync/Async: Synchronous
* Service ID[hex]:0x02
* Reentrancy:Non-reentrant
* Parameters (in): None
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description: Refreshes port direction. 
************************************************************************************/
void Port_RefreshPortDirection( void );

/************************************************************************************
* Service Name: Port_GetVersionInfo
* Sync/Async: Synchronous
* Service ID[hex]:0x03
* Reentrancy: Non-reentrant
* Parameters (in): None
* Parameters (inout): None
* Parameters (out): versioninfo > Pointer to where to store the version information of this module. 
* Return value: None
* Description: Returns the version information of this module.
************************************************************************************/
#if (PORT_VERSION_INFO_API == STD_ON)
void Port_GetVersionInfo( Std_VersionInfoType* versioninfo );
#endif


/************************************************************************************
* Service Name: Port_SetPinMode
* Sync/Async: Synchronous
* Service ID[hex]:0x04
* Reentrancy: Reentrant
* Parameters (in): Pin > Port Pin ID number 
                    Mode > Port Pin Mode 
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description: Sets the port pin mode.
************************************************************************************/
#if (PORT_SET_PIN_MODE_API == STD_ON)
void Port_SetPinMode( Port_PinType Pin, Port_PinModeType Mode );
#endif


/*******************************************************************************
 *                       External Variables                                    *
 *******************************************************************************/

/* Extern PB structure to be used by PORT module */
extern const Port_ConfigType Port_Configuration;


#endif