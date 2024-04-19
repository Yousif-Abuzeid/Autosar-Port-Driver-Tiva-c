 /******************************************************************************
 *
 * Module: Port
 *
 * File Name: Port.c
 *
 * Description: Source file for TM4C123GH6PM Microcontroller - Port Driver
 *
 * Author: Youssef Abuzeid
 ******************************************************************************/
#include "Port.h"
#include "Port_Regs.h"

#if(PORT_DEV_ERROR_DETECT==STD_ON)
#include "Det.h"
/* AUTOSAR Version checking between Det and Port Modules */
#if ((DET_AR_MAJOR_VERSION != PORT_AR_RELEASE_MAJOR_VERSION)\
 || (DET_AR_MINOR_VERSION != PORT_AR_RELEASE_MINOR_VERSION)\
 || (DET_AR_PATCH_VERSION != PORT_AR_RELEASE_PATCH_VERSION))
  #error "The AR version of Det.h does not match the expected version"
#endif
#endif  

STATIC const Port_ConfigPins * Port_Config = NULL_PTR;
STATIC uint8 PORT_Status = PORT_NOT_INITIALIZED;


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
void port_init(const Port_ConfigType* ConfigPtr){
   #if(PORT_DEV_ERROR_DETECT==STD_ON)
	/* check if the input configuration pointer is not a NULL_PTR */
    if(NULL_PTR==ConfigPtr)
    Det_ReportError(PORT_MODULE_ID,PORT_INSTANCE_ID,PORT_INIT_SID,
    PORT_E_PARAM_POINTER);
    /*
	 * Set the module state to initialized and point to the PB configuration structure using a global pointer.
	 * This global pointer is global to be used by other functions to read the PB configuration structures
	 */
    else
    #endif
    {
    Port_Config=ConfigPtr->Pins; /*Address of the first Pin Structure*/
    PORT_Status = PORT_INITIALIZED;
    
    }
     /* point to the required Port Registers base address */
     volatile uint32 * PortGpio_Ptr = NULL_PTR; 
     /* index for pins array of strutures*/
     uint8 pin_index=0; 
     for(pin_index=0; pin_index<PORT_NUMBER_OF_PORT_PINS; pin_index++){

        switch(Port_Config[pin_index].port_num)
    {
        case  0: PortGpio_Ptr = (volatile uint32 *)GPIO_PORTA_BASE_ADDRESS; /* PORTA Base Address */
		         break;
     	case  1: PortGpio_Ptr = (volatile uint32 *)GPIO_PORTB_BASE_ADDRESS; /* PORTB Base Address */
		         break;
	    case  2: PortGpio_Ptr = (volatile uint32 *)GPIO_PORTC_BASE_ADDRESS; /* PORTC Base Address */
		         break;
	    case  3: PortGpio_Ptr = (volatile uint32 *)GPIO_PORTD_BASE_ADDRESS; /* PORTD Base Address */
		         break;
        case  4: PortGpio_Ptr = (volatile uint32 *)GPIO_PORTE_BASE_ADDRESS; /* PORTE Base Address */
		         break;
        case  5: PortGpio_Ptr = (volatile uint32 *)GPIO_PORTF_BASE_ADDRESS; /* PORTF Base Address */
		         break;
    }
    /* Check if the pin is locked*/
     if( ((Port_Config[pin_index].port_num == 3) && (Port_Config[pin_index].pin_num == 7)) || ((Port_Config[pin_index].port_num == 5) && (Port_Config[pin_index].pin_num == 0)) ) /* PD7 or PF0 */
    {
        *(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_LOCK_REG_OFFSET) = 0x4C4F434B;                     /* Unlock the GPIOCR register */   
        SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_COMMIT_REG_OFFSET) , Port_Config[pin_index].pin_num);  /* Set the corresponding bit in GPIOCR register to allow changes on this pin */
    }
    else if( (Port_Config[pin_index].port_num == 2) && (Port_Config[pin_index].pin_num <= 3) ) /* PC0 to PC3 */
    {
        /* Do Nothing ...  this is the JTAG pins */
    }
    else
    {
        /* Do Nothing ... No need to unlock the commit register for this pin */
    }
    switch (Port_Config[pin_index].pin_mode)
    {
        /*Dio mode*/
    case PORT_PIN_MODE_DIO:
        /*Disable Analog*/
        CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ANALOG_MODE_SEL_REG_OFFSET),Port_Config[pin_index].pin_num);
        /*Disable Alternate Function*/  
        CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ALT_FUNC_REG_OFFSET) , Port_Config[pin_index].pin_num);       
        /*Select Regular I/O Function in Control Register*/
        *(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_CTL_REG_OFFSET) &= ~(0x0000000F << (Port_Config[pin_index].pin_num * 4));
        /*Choose Direction*/
        if(PORT_PIN_IN==Port_Config[pin_index].pin_direction){
            /*Configure As Input Pin*/
            CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIR_REG_OFFSET) , Port_Config[pin_index].pin_num);
            /*Choose PULL UP or PULL DOWN or OFF*/
            if(PULL_UP==Port_Config[pin_index].pin_resistor){
                SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_PULL_UP_REG_OFFSET) , Port_Config[pin_index].pin_num);
            }else if(PULL_DOWN==Port_Config[pin_index].pin_resistor){
                SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_PULL_DOWN_REG_OFFSET) , Port_Config[pin_index].pin_num);
            }else{
                /*Do Nothing*/
            }

        }else{
            /*Configure as Output Pin*/
            SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIR_REG_OFFSET) , Port_Config[pin_index].pin_num); 
            if(STD_HIGH==Port_Config[pin_index].pin_level_init_value){
                /*Initalize the pin with Logic High*/
                SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DATA_REG_OFFSET) , Port_Config[pin_index].pin_num); 
            }else{
                /*Initalize the pin with Logic Low*/
                CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DATA_REG_OFFSET) , Port_Config[pin_index].pin_num);
            }
        }
        /*Digital Enable*/
        SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIGITAL_ENABLE_REG_OFFSET) , Port_Config[pin_index].pin_num); 
        
        break;
        /*ADC Mode*/
    case PORT_PIN_MODE_ADC:
        /*Enable Alternate Function*/
        SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ALT_FUNC_REG_OFFSET) , Port_Config[pin_index].pin_num);
        /*Set Direction As Ipnut*/    
        CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIR_REG_OFFSET) , Port_Config[pin_index].pin_num);
        /*Disable Digital*/
        CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIGITAL_ENABLE_REG_OFFSET) , Port_Config[pin_index].pin_num);
        /*Enable Analog Mode*/
        SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ANALOG_MODE_SEL_REG_OFFSET),Port_Config[pin_index].pin_num);

        break;
        /*UART Mode*/
    case PORT_PIN_MODE_UART:
         /*Enable Alternate Function*/
        SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ALT_FUNC_REG_OFFSET) , Port_Config[pin_index].pin_num);
         /*Disable Analog Mode*/
        CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ANALOG_MODE_SEL_REG_OFFSET),Port_Config[pin_index].pin_num);
        /*Choose Direction Tx or Rx*/
        if(PORT_PIN_IN==Port_Config[pin_index].pin_direction){
             /*Configure As Input Pin (Rx)*/
            CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIR_REG_OFFSET) , Port_Config[pin_index].pin_num);

        }else{
            /*Configure As Output Pin (Tx)*/
            SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIR_REG_OFFSET) , Port_Config[pin_index].pin_num);
        }
        /*Choose Uart in Control Register*/
        *(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_CTL_REG_OFFSET) |= ((uint32)PORT_PIN_MODE_UART << (Port_Config[pin_index].pin_num * 4));
        /*Digital Enable*/
        SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIGITAL_ENABLE_REG_OFFSET) , Port_Config[pin_index].pin_num);
        break;
        /*SPI Mode*/
    case PORT_PIN_MODE_SPI:

        /*Enable Alternate Function*/
        SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ALT_FUNC_REG_OFFSET) , Port_Config[pin_index].pin_num);
        /*Disable Analog*/
        CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ANALOG_MODE_SEL_REG_OFFSET),Port_Config[pin_index].pin_num); 
        /*Choose Direction Tx or Rx*/
        if(PORT_PIN_IN==Port_Config[pin_index].pin_direction){
            /*Configure As Input Pin (Rx)*/
            CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIR_REG_OFFSET) , Port_Config[pin_index].pin_num);

        }else{
            /*Configure As Output Pin (Tx)*/
            SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIR_REG_OFFSET) , Port_Config[pin_index].pin_num);
        }      
        if(pin_index>=PORT_D_PIN_0 && pin_index<=PORT_D_PIN_3)/*PD0,PD1,PD2,PD3*/
        { 
            *(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_CTL_REG_OFFSET) |= ((PORT_PIN_MODE_SPI-1) << (Port_Config[pin_index].pin_num * 4));  
        }
        else
          {
         *(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_CTL_REG_OFFSET) |= (PORT_PIN_MODE_SPI << (Port_Config[pin_index].pin_num * 4)); 
          }
          /*Digital Enable*/
        SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIGITAL_ENABLE_REG_OFFSET) , Port_Config[pin_index].pin_num); 
        break;
            /*I2C Mode*/
        case PORT_PIN_MODE_I2C:
            /*Alternate Function Enable*/
            SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ALT_FUNC_REG_OFFSET) , Port_Config[pin_index].pin_num);
            /*Disable Analog*/
            CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ANALOG_MODE_SEL_REG_OFFSET),Port_Config[pin_index].pin_num); 
            /*OPen drain select for data pin*/
            if(pin_index%2!=0){
            SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_OPEN_DRAIN_REG_OFFSET) , Port_Config[pin_index].pin_num); 
            } 
            /*Choose I2C in Control Register*/
            *(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_CTL_REG_OFFSET) |= (PORT_PIN_MODE_I2C << (Port_Config[pin_index].pin_num * 4));
            /*Digital Enable*/
            SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIGITAL_ENABLE_REG_OFFSET) , Port_Config[pin_index].pin_num);
        break;
        case PORT_PIN_MODE_PWM:
            /*Alternate Function Enable*/
            SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ALT_FUNC_REG_OFFSET) , Port_Config[pin_index].pin_num);
            /*Disable Analog*/
            CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ANALOG_MODE_SEL_REG_OFFSET),Port_Config[pin_index].pin_num);
            /*Configure As Output Pin (Tx)*/
            SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIR_REG_OFFSET) , Port_Config[pin_index].pin_num);
            if((pin_index>=PORT_B_PIN_4 &&pin_index <=PORT_B_PIN_7)||(pin_index>=PORT_C_PIN_4 && pin_index<=PORT_C_PIN_5)||(pin_index>=PORT_D_PIN_0 && pin_index<=PORT_D_PIN_1)||(pin_index>=PORT_E_PIN_4 && pin_index<=PORT_E_PIN_5)){
                 /*Choose M0PWM in Control Register*/
            *(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_CTL_REG_OFFSET) |= (PORT_PIN_MODE_M0PWM << (Port_Config[pin_index].pin_num * 4));
            }else{
               /*Choose M1PWM in Control Register*/
            *(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_CTL_REG_OFFSET) |= (PORT_PIN_MODE_M1PWM << (Port_Config[pin_index].pin_num * 4));

            }
            /*Digital Enable*/
            SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIGITAL_ENABLE_REG_OFFSET) , Port_Config[pin_index].pin_num);
        break;
        case PORT_PIN_MODE_GPT:
            /*Alternate Function Enable*/
            SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ALT_FUNC_REG_OFFSET) , Port_Config[pin_index].pin_num);
            /*Disable Analog*/
            CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ANALOG_MODE_SEL_REG_OFFSET),Port_Config[pin_index].pin_num);
              /*Choose Direction*/
        if(PORT_PIN_IN==Port_Config[pin_index].pin_direction){
            /*Configure As Input Pin */
            CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIR_REG_OFFSET) , Port_Config[pin_index].pin_num);

        }else{
            /*Configure As Output Pin */
            SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIR_REG_OFFSET) , Port_Config[pin_index].pin_num);
        }
            /*Choose TxCCPx in Control Register*/
            *(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_CTL_REG_OFFSET) |= (PORT_PIN_MODE_GPT << (Port_Config[pin_index].pin_num * 4));
             /*Digital Enable*/
            SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIGITAL_ENABLE_REG_OFFSET) , Port_Config[pin_index].pin_num);
        break;
        /*if a pin has no congifuration exist configure the pin as input DIO*/        
        default:
             /*Disable Analog*/
            CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ANALOG_MODE_SEL_REG_OFFSET),Port_Config[pin_index].pin_num);
             /*Disable Alternate Function*/  
             CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ALT_FUNC_REG_OFFSET) , Port_Config[pin_index].pin_num);       
            /*Select Regular I/O Function in Control Register*/
            *(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_CTL_REG_OFFSET) &= ~(0x0000000F << (Port_Config[pin_index].pin_num * 4));
            /*Configure As Input Pin*/
            CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIR_REG_OFFSET) , Port_Config[pin_index].pin_num);
             /*Digital Enable*/
            SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIGITAL_ENABLE_REG_OFFSET) , Port_Config[pin_index].pin_num);
            break;

    }
    if (Port_Config[pin_index].pin_mode==PORT_PIN_MODE_CAN ||Port_Config[pin_index].pin_mode==PORT_PIN_MODE_USB||Port_Config[pin_index].pin_mode==PORT_PIN_MODE_NMI)
    {
        /*Alternate Function Enable*/
        SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ALT_FUNC_REG_OFFSET) , Port_Config[pin_index].pin_num);
        /*Disable Analog*/
        if(PORT_PIN_IN==Port_Config[pin_index].pin_direction){
            /*Configure As Input Pin */
            CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIR_REG_OFFSET) , Port_Config[pin_index].pin_num);

        }else{
            /*Configure As Output Pin */
            SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIR_REG_OFFSET) , Port_Config[pin_index].pin_num);
        }
        CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ANALOG_MODE_SEL_REG_OFFSET),Port_Config[pin_index].pin_num);
        if(PORT_A_PIN_0==pin_index||PORT_A_PIN_1==pin_index||PORT_B_PIN_4==pin_index||PORT_B_PIN_5==pin_index||PORT_E_PIN_4==pin_index||PORT_E_PIN_5==pin_index){
            *(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_CTL_REG_OFFSET) |= (PORT_PIN_MODE_CAN << (Port_Config[pin_index].pin_num * 4));
        }else if(PORT_C_PIN_6==pin_index||PORT_C_PIN_7==pin_index||PORT_D_PIN_2==pin_index||PORT_D_PIN_3==pin_index||PORT_F_PIN_4==pin_index){
            *(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_CTL_REG_OFFSET) |= (PORT_PIN_MODE_CAN << (Port_Config[pin_index].pin_num * 4));
        }else{
             /*Choose PULL UP or PULL DOWN or OFF*/
            if(PULL_UP==Port_Config[pin_index].pin_resistor){
                SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_PULL_UP_REG_OFFSET) , Port_Config[pin_index].pin_num);
            }else if(PULL_DOWN==Port_Config[pin_index].pin_resistor){
                SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_PULL_DOWN_REG_OFFSET) , Port_Config[pin_index].pin_num);
            }else{
                /*Do Nothing*/
            }
            /*Choose NMI in Control Register*/
            *(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_CTL_REG_OFFSET) |= (PORT_PIN_MODE_NMI << (Port_Config[pin_index].pin_num * 4));

        }
          /*Digital Enable*/
            SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIGITAL_ENABLE_REG_OFFSET) , Port_Config[pin_index].pin_num);
    }
    

}
    PORT_Status=PORT_INITIALIZED;
}

/************************************************************************************
* Service Name: Port_SetPinDirection
* Sync/Async: Synchronous
* Service ID[hex]:0x01
* Reentrancy: Non-reentrant
* Parameters (in):  Pin > Port Pin ID number 
                    Direction> Port Pin Direction 
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description: Function to Sets the port pin direction.
************************************************************************************/
#if (PORT_SET_PIN_DIRECTION_API == STD_ON)
void Port_SetPinDirection( Port_PinType Pin, Port_PinDirectionType Direction ){

}
#endif


#if (PORT_VERSION_INFO_API == STD_ON)
void Port_GetVersionInfo( Std_VersionInfoType* versioninfo );
#endif


#if (PORT_SET_PIN_MODE_API == STD_ON)
void Port_SetPinMode( Port_PinType Pin, Port_PinModeType Mode );
#endif


void Port_RefreshPortDirection( void );
