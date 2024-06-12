# AUTOSAR Port Driver

This project provides a comprehensive implementation of an AUTOSAR-compliant Port Driver. The driver manages the configuration and control of General-Purpose Input/Output (GPIO) pins, adhering to the AUTOSAR standard to ensure modularity, scalability, and reusability.

## Overview

### Key Features
- **AUTOSAR Compliance**: Implements the AUTOSAR Port Driver module specifications.
- **Layered Architecture**: Follows the AUTOSAR layered architecture to separate concerns.
- **Scalability**: Easily extensible to support new hardware or additional features.
- **Configurability**: Flexible configuration of GPIO pins through configuration files.


## Port Driver Features

- **Pin Configuration**: Setup GPIO pins as input, output, or alternate function.
- **Pin Mode Selection**: Configure pin modes such as pull-up, pull-down, open-drain, and digital.
- **Initial Value Setting**: Define initial states for output pins.
- **Direction Control**: Set the direction of GPIO pins (input/output).
- **Interrupt Configuration**: Enable and configure interrupts for GPIO pins.

## Configuration

The driver uses configuration files to define settings for each GPIO pin, including direction, initial state, and mode. The configuration is read during initialization and applied to the hardware.

### Example Configuration
```c
/* Port_Cfg.h */
#define PORT_PIN_COUNT 5

typedef struct {
    uint8_t pinId;
    Port_PinDirectionType direction;
    Port_PinModeType mode;
    uint8_t initialValue;
} Port_ConfigType;

/* Example configuration */
extern const Port_ConfigType Port_Config[PORT_PIN_COUNT];
