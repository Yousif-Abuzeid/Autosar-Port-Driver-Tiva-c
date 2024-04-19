 /******************************************************************************
 *
 * Module: PORT
 *
 * File Name: Port_Cfg.h
 *
 * Description: Pre-Compile Configuration Header file for TM4C123GH6PM Microcontroller - Port Driver
 *
 * Author: Youssef Abuzeid
 ******************************************************************************/
#ifndef PORT_CFG_H
#define PORT_CFG_H

/*
 * Module Version 1.0.0
 */
#define PORT_CFG_SW_MAJOR_VERSION              (1U)
#define PORT_CFG_SW_MINOR_VERSION              (0U)
#define PORT_CFG_SW_PATCH_VERSION              (0U)

/*
 * AUTOSAR Version 4.0.3
 */
#define PORT_CFG_AR_RELEASE_MAJOR_VERSION     (4U)
#define PORT_CFG_AR_RELEASE_MINOR_VERSION     (0U)
#define PORT_CFG_AR_RELEASE_PATCH_VERSION     (3U)


/* Pre-compile option for Development Error Detect */
#define PORT_DEV_ERROR_DETECT                (STD_ON)

/* Pre-compile option for Version Info API */
#define PORT_VERSION_INFO_API                (STD_ON)

/* Precompile option for setting Pin MODEection API */
#define PORT_SET_PIN_DIRECTION_API            (STD_ON)
											  
/* Precompile option to set pin mode API */
#define PORT_SET_PIN_MODE_API                 (STD_ON)

/* Pre-compile parameter for number of pins */
#define PORT_NUMBER_OF_PORT_PINS                   (43U)     
   
/* Precompile and Post Build option for Port pin mode changeability */
#define PORT_PIN_MODE_CHANGEABLE              (STD_ON)   
/* Precompile and Post Build option for Port pin direction changeability */
#define PORT_PIN_DIRECTION_CHANGEABLE         (STD_ON)


/*Modes Of Configuration */
#define PORT_PIN_MODE_ADC        (uint8)9     /* ADC Mode */
#define PORT_PIN_MODE_DIO        (uint8)0     /* DIO Mode */
#define PORT_PIN_MODE_UART       (uint8)1     /* UART Mode */
#define PORT_PIN_MODE_SPI        (uint8)2     /* SPI Mode */
#define PORT_PIN_MODE_I2C        (uint8)3     /* I2C Mode */
#define PORT_PIN_MODE_PWM        (uint8)4     /*PWM Mode*/
#define PORT_PIN_MODE_M0PWM      (uint8)4     /*M0PWM Mode */
#define PORT_PIN_MODE_M0FAULT    (uint8)4     /*Motion Control Module  Mode */
#define PORT_PIN_MODE_M1PWM      (uint8)5     /*M1PWM Mode */
#define PORT_PIN_MODE_IDX_PHASE  (uint8)6     /* IDX AND PHASE Mode */
#define PORT_PIN_MODE_GPT        (uint8)7     /* TIMER  Mode */  
#define PORT_PIN_MODE_CAN        (uint8)8     /* CAN Mode */
#define PORT_PIN_MODE_USB        (uint8)8     /* USB Mode */
#define PORT_PIN_MODE_NMI        (uint8)8     /*Non-Maskable Interrupt*/

/*PORT INDEXS*/   
#define PORT_A     (0U)
#define PORT_B     (1U)
#define PORT_C     (2U)
#define PORT_D     (3U)
#define PORT_E     (4U)
#define PORT_F     (5U) 

/*PIN INDEXS*/    
#define PORT_PIN0 				(uint8)0
#define PORT_PIN1 				(uint8)1
#define PORT_PIN2 				(uint8)2
#define PORT_PIN3 				(uint8)3
#define PORT_PIN4 				(uint8)4
#define PORT_PIN5 				(uint8)5
#define PORT_PIN6 				(uint8)6
#define PORT_PIN7 				(uint8)7   
   
   
/*Port Pin ID number
Used as a parameters to SetPin_Direction();*/
#define PORT_A_PIN_0    (Port_PinType)0
#define PORT_A_PIN_1    (Port_PinType)1
#define PORT_A_PIN_2    (Port_PinType)2
#define PORT_A_PIN_3    (Port_PinType)3
#define PORT_A_PIN_4    (Port_PinType)4
#define PORT_A_PIN_5    (Port_PinType)5
#define PORT_A_PIN_6    (Port_PinType)6
#define PORT_A_PIN_7    (Port_PinType)7
   
#define PORT_B_PIN_0    (Port_PinType)8
#define PORT_B_PIN_1    (Port_PinType)9
#define PORT_B_PIN_2    (Port_PinType)10 
#define PORT_B_PIN_3    (Port_PinType)11 
#define PORT_B_PIN_4    (Port_PinType)12 
#define PORT_B_PIN_5    (Port_PinType)13 
#define PORT_B_PIN_6    (Port_PinType)14
#define PORT_B_PIN_7    (Port_PinType)15
   
#define PORT_C_PIN_0    (Port_PinType)16
#define PORT_C_PIN_1    (Port_PinType)17 
#define PORT_C_PIN_2    (Port_PinType)18
#define PORT_C_PIN_3    (Port_PinType)19
#define PORT_C_PIN_4    (Port_PinType)20
#define PORT_C_PIN_5    (Port_PinType)21
#define PORT_C_PIN_6    (Port_PinType)22 
#define PORT_C_PIN_7    (Port_PinType)23
   
#define PORT_D_PIN_0    (Port_PinType)24
#define PORT_D_PIN_1    (Port_PinType)25   
#define PORT_D_PIN_2    (Port_PinType)26   
#define PORT_D_PIN_3    (Port_PinType)27   
#define PORT_D_PIN_4    (Port_PinType)28   
#define PORT_D_PIN_5    (Port_PinType)29   
#define PORT_D_PIN_6    (Port_PinType)30   
#define PORT_D_PIN_7    (Port_PinType)31
   
#define PORT_E_PIN_0    (Port_PinType)32
#define PORT_E_PIN_1    (Port_PinType)33
#define PORT_E_PIN_2    (Port_PinType)34
#define PORT_E_PIN_3    (Port_PinType)35
#define PORT_E_PIN_4    (Port_PinType)36
#define PORT_E_PIN_5    (Port_PinType)37
   
#define PORT_F_PIN_0    (Port_PinType)38
#define PORT_F_PIN_1    (Port_PinType)39
#define PORT_F_PIN_2    (Port_PinType)40
#define PORT_F_PIN_3    (Port_PinType)41
#define PORT_F_PIN_4    (Port_PinType)42   

/* Pin changable direction during RunTime */
#define PORT_A_PIN_0_DIR_CHANG         (STD_OFF)
#define PORT_A_PIN_1_DIR_CHANG         (STD_OFF)
#define PORT_A_PIN_2_DIR_CHANG         (STD_OFF)
#define PORT_A_PIN_3_DIR_CHANG         (STD_OFF)
#define PORT_A_PIN_4_DIR_CHANG         (STD_OFF)
#define PORT_A_PIN_5_DIR_CHANG         (STD_OFF)
#define PORT_A_PIN_6_DIR_CHANG         (STD_OFF)
#define PORT_A_PIN_7_DIR_CHANG         (STD_OFF)

#define PORT_B_PIN_0_DIR_CHANG         (STD_OFF)
#define PORT_B_PIN_1_DIR_CHANG         (STD_OFF)
#define PORT_B_PIN_2_DIR_CHANG         (STD_OFF)
#define PORT_B_PIN_3_DIR_CHANG         (STD_OFF)
#define PORT_B_PIN_4_DIR_CHANG         (STD_OFF)
#define PORT_B_PIN_5_DIR_CHANG         (STD_OFF)
#define PORT_B_PIN_6_DIR_CHANG         (STD_OFF)
#define PORT_B_PIN_7_DIR_CHANG         (STD_OFF)

#define PORT_C_PIN_0_DIR_CHANG         (STD_OFF)
#define PORT_C_PIN_1_DIR_CHANG         (STD_OFF)
#define PORT_C_PIN_2_DIR_CHANG         (STD_OFF)
#define PORT_C_PIN_3_DIR_CHANG         (STD_OFF)
#define PORT_C_PIN_4_DIR_CHANG         (STD_OFF)
#define PORT_C_PIN_5_DIR_CHANG         (STD_OFF) 
#define PORT_C_PIN_6_DIR_CHANG         (STD_OFF)
#define PORT_C_PIN_7_DIR_CHANG         (STD_OFF)

#define PORT_D_PIN_0_DIR_CHANG         (STD_OFF)
#define PORT_D_PIN_1_DIR_CHANG         (STD_OFF)
#define PORT_D_PIN_2_DIR_CHANG         (STD_OFF) 
#define PORT_D_PIN_3_DIR_CHANG         (STD_OFF)
#define PORT_D_PIN_4_DIR_CHANG         (STD_OFF)
#define PORT_D_PIN_5_DIR_CHANG         (STD_OFF)
#define PORT_D_PIN_6_DIR_CHANG         (STD_OFF)
#define PORT_D_PIN_7_DIR_CHANG         (STD_OFF) 

#define PORT_E_PIN_0_DIR_CHANG         (STD_OFF)
#define PORT_E_PIN_1_DIR_CHANG         (STD_OFF)
#define PORT_E_PIN_2_DIR_CHANG         (STD_OFF) 
#define PORT_E_PIN_3_DIR_CHANG         (STD_OFF)
#define PORT_E_PIN_4_DIR_CHANG         (STD_OFF)
#define PORT_E_PIN_5_DIR_CHANG         (STD_OFF)   

#define PORT_F_PIN_0_DIR_CHANG         (STD_OFF)
#define PORT_F_PIN_1_DIR_CHANG         (STD_OFF)
#define PORT_F_PIN_2_DIR_CHANG         (STD_OFF) 
#define PORT_F_PIN_3_DIR_CHANG         (STD_OFF)
#define PORT_F_PIN_4_DIR_CHANG         (STD_OFF)   
      
/* Pin changable mode during RunTime */
#define PORT_A_PIN_0_MODE_CHANG         (STD_OFF)
#define PORT_A_PIN_1_MODE_CHANG         (STD_OFF)
#define PORT_A_PIN_2_MODE_CHANG         (STD_OFF)
#define PORT_A_PIN_3_MODE_CHANG         (STD_OFF)
#define PORT_A_PIN_4_MODE_CHANG         (STD_OFF)
#define PORT_A_PIN_5_MODE_CHANG         (STD_OFF)
#define PORT_A_PIN_6_MODE_CHANG         (STD_OFF)
#define PORT_A_PIN_7_MODE_CHANG         (STD_OFF)

#define PORT_B_PIN_0_MODE_CHANG         (STD_OFF)
#define PORT_B_PIN_1_MODE_CHANG         (STD_OFF)
#define PORT_B_PIN_2_MODE_CHANG         (STD_OFF)
#define PORT_B_PIN_3_MODE_CHANG         (STD_OFF)
#define PORT_B_PIN_4_MODE_CHANG         (STD_OFF)
#define PORT_B_PIN_5_MODE_CHANG         (STD_OFF)
#define PORT_B_PIN_6_MODE_CHANG         (STD_OFF)
#define PORT_B_PIN_7_MODE_CHANG         (STD_OFF)

#define PORT_C_PIN_0_MODE_CHANG         (STD_OFF)
#define PORT_C_PIN_1_MODE_CHANG         (STD_OFF)
#define PORT_C_PIN_2_MODE_CHANG         (STD_OFF)
#define PORT_C_PIN_3_MODE_CHANG         (STD_OFF)
#define PORT_C_PIN_4_MODE_CHANG         (STD_OFF)
#define PORT_C_PIN_5_MODE_CHANG         (STD_OFF) 
#define PORT_C_PIN_6_MODE_CHANG         (STD_OFF)
#define PORT_C_PIN_7_MODE_CHANG         (STD_OFF)

#define PORT_D_PIN_0_MODE_CHANG         (STD_OFF)
#define PORT_D_PIN_1_MODE_CHANG         (STD_OFF)
#define PORT_D_PIN_2_MODE_CHANG         (STD_OFF) 
#define PORT_D_PIN_3_MODE_CHANG         (STD_OFF)
#define PORT_D_PIN_4_MODE_CHANG         (STD_OFF)
#define PORT_D_PIN_5_MODE_CHANG         (STD_OFF)
#define PORT_D_PIN_6_MODE_CHANG         (STD_OFF)
#define PORT_D_PIN_7_MODE_CHANG         (STD_OFF) 

#define PORT_E_PIN_0_MODE_CHANG         (STD_OFF)
#define PORT_E_PIN_1_MODE_CHANG         (STD_OFF)
#define PORT_E_PIN_2_MODE_CHANG         (STD_OFF) 
#define PORT_E_PIN_3_MODE_CHANG         (STD_OFF)
#define PORT_E_PIN_4_MODE_CHANG         (STD_OFF)
#define PORT_E_PIN_5_MODE_CHANG         (STD_OFF)   

#define PORT_F_PIN_0_MODE_CHANG         (STD_OFF)
#define PORT_F_PIN_1_MODE_CHANG         (STD_OFF)
#define PORT_F_PIN_2_MODE_CHANG         (STD_OFF) 
#define PORT_F_PIN_3_MODE_CHANG         (STD_OFF)
#define PORT_F_PIN_4_MODE_CHANG         (STD_OFF)   
      

#endif