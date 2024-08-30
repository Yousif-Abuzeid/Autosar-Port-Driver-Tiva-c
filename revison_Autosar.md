# AUTOSAR

## Why AUTOSAR Was Created

AUTOSAR (AUTomotive Open System ARchitecture) was developed to address several challenges in the automotive industry's electronic and software systems. Below are the key reasons for its creation:

### 1. Standardization

- Before AUTOSAR, automotive companies relied on proprietary software solutions for electronic control units (ECUs), leading to compatibility issues and increased development costs.
- AUTOSAR provides a standardized software architecture, ensuring interoperability across different manufacturers and suppliers.

### 2. Modularity and Reusability

- AUTOSAR's architecture allows software components to be developed modularly.
- These components can be reused across various projects and vehicles, reducing development time and costs.

### 3. Integration of Advanced Technologies

- The rise of advanced driver-assistance systems (ADAS), autonomous driving, and connectivity required a robust software architecture.
- AUTOSAR facilitates the integration of complex technologies within vehicles.

### 4. Quality and Safety

- By providing a standardized platform, AUTOSAR enhances the reliability and safety of automotive software.
- It supports compliance with industry standards such as ISO 26262, focusing on functional safety.

### 5. Supplier Collaboration

- AUTOSAR enables better collaboration between OEMs (Original Equipment Manufacturers) and suppliers.
- A common architecture allows different companies to work on different parts of the system while ensuring seamless integration.

### 6. Cost Reduction

- AUTOSAR promotes reusability, standardization, and modular design, leading to reduced development costs and faster time-to-market for new vehicles and systems.

AUTOSAR has become a fundamental part of the automotive industry, helping companies manage the complexity of modern vehicles while fostering innovation and collaboration.

## Collaborative Synergy: The Roles of OEMs, Tier 1, and Tier 2 Suppliers in the Automotive Value Chain

The automotive industry operates within a complex value chain involving multiple stakeholders, including Original Equipment Manufacturers (OEMs), Tier 1 suppliers, and Tier 2 suppliers. Each entity plays a crucial role in the development and production of vehicles, leveraging its expertise to contribute to the final product. Let's explore the roles of these stakeholders in the automotive value chain:

### 1. OEMs (Original Equipment Manufacturers)(Car Manufacturers)

- OEMs are responsible for designing, engineering, and assembling vehicles.
- They define the vehicle's overall architecture, performance specifications, and features.
- OEMs manage the integration of various components and systems to create a functional vehicle.
- Examples of OEMs include Ford, Toyota, Volkswagen, and General Motors.

### 2. Tier 1 Suppliers(Responsible for SW/HW Integration)

- Tier 1 suppliers provide complex systems and modules to OEMs.
- They specialize in specific components such as powertrains, chassis systems, and infotainment systems.
- Tier 1 suppliers often work closely with OEMs during the vehicle development process.
- Examples of Tier 1 suppliers include Bosch, Continental, Denso, valeo and Magna.

### 3. Tier 2 Suppliers

- Tier 2 suppliers deliver individual components and subsystems to Tier 1 suppliers.
- Examples of Tier 2 suppliers include Infineon, NXP, and Aptiv.

Collaboration among these stakeholders is essential to ensure the successful development and production of vehicles. OEMs rely on Tier 1 and Tier 2 suppliers to provide innovative solutions, high-quality components, and advanced technologies that meet industry standards and customer expectations. By working together, these entities drive innovation, efficiency, and competitiveness in the automotive industry.

## Introduction to AUTOSAR

- AUTOSAR (AUTomotive Open System ARchitecture) is a global development partnership of automotive industry stakeholders.
- Standardization initiative of leading automotive OEMs, Tier 1&2 suppliers, and semiconductor vendors.
- It was founded in 2003 to develop an open and standardized software architecture for automotive electronic control units (ECUs).
- `"Cooperate on standards, compete on implementation."`

## Why AUTOSAR?

1. Modularity
2. Scalability
3. Reusability
4. Portability
5. Standardized interfaces
6. Abstracting from hardware

## AUTOSAR Partnership Structure

- Core Partners: BMW, Bosch, Continental, Daimler, Ford, General Motors, PSA, Toyota, Volkswagen, and Volvo.

- Premium Partners: Delphi, Denso, Fiat, Hyundai, Mitsubishi, Nissan, Renault, and Siemens.

- Development Partners: Infineon, Intel, Magna, and NXP.

## AUTOSAR Methodology

- AUTOSAR methodology follows a model-based development approach.
- It uses standardized XML-based file formats for software component descriptions, system configurations, and communication descriptions.
- The methodology supports tool interoperability and facilitates collaboration among different stakeholders in the development process.

## AUTOSAR Software Architecture

- AUTOSAR architecture is based on a layered software architecture.
- It consists of three main layers: `Application Layer`, `Runtime Environment (RTE)`, and `Basic Software Layer (BSW)`.

![AUTOSAR Architecture](AutosarLayers.png)

### BSW (Basic Software Layer)

- The Basic Software is further divided into four layers: `Microcontroller Abstraction Layer (MCAL)`, `ECU Abstraction Layer (ECU Abstraction)`, `Services Layer`, and `Complex Drivers`.
- Provide Services to the Application .
- In Charge of running the functional part of software.
  - Ex : Communication(e.g CAN,LIN,FLEX RAY ...), Memory Management, Diagnostics, etc.
  - Contains ECU specific components.

#### The Basic Software Layer (BSW) Can Be Further Divided Into The Following Sub-Layers

- Input/Output (I/O)
- Memory
- Communication
- System

## MCAL (Microcontroller Abstraction Layer)

- The MCAL is the lowest layer of the Basic Software.
- It Contains Internal drivers, which are software modules with direct access to the microcontroller and internal peripherals.
- Task
  - Make higher software layers independent of microcontroller
- Properties
  - Hardware dependent
  - Upper layers are independent of hardware
- Drivers in this layer are mainly provided by the microcontroller vendors or by Tier2.

**The MCAL Layer Consits of the Following Module groups**

- Communication Drivers( CAN, LIN, FlexRay, Ethernet, etc.)
- I/O Drivers( ADC, PWM, DIO, etc.)
- Memory Drivers( Flash, EEPROM, RAM, etc.)
- MCU Drivers

      - Drivers for internal peripherals of the microcontroller.(Watchdog, GPT, etc.)

- These 4 module groups contain 18 modules in total.

![MCAL](MCAL.png)

### MCAL IO Drivers

#### 1. PORT Driver 

- The PORT driver is responsible for the configuration of the microcontroller's input/output ports.
**Configuration of the following parameters:**
  - Pin direction (input/output)
  - Pin mode (push-pull, open-drain)
  - Pin level (high/low)
  - Change pin direction/mode

#### 2. DIO Driver

- The DIO driver is responsible for reading and writing digital input/output signals.

#### 3. ADC Driver

- Setup and control analog-to-digital conversion parameters.
- Obtain the converted digital value of an analog input signal for defined pin channels.

#### 4. PWM Driver

- Initialize and generate pulse-width modulation signals.
- Control the duty cycle and frequency of the PWM signal.

#### 5. ICU Driver

- Capture the time of a rising or falling edge of an input signal.
- Provide the time difference between two captured edges.

### MCAL Communication Drivers

#### 1. SPI Handler/Driver

- Provides Services for communication over the SPI bus.
- Handles multiple users and multiple devices on the SPI bus.

##### Handler

- The **SPI Handler Driver** allows concurrent access of several clients to one or more SPI buses.
- Handler is a specific interface which controls the concurrent access of one or multiple clients to one or multiple SPI buses.
- It performs buffering, queuing, and arbitration of the requests from different clients.

![SPI Handler](SpiHandler.png)

#### 2. LIN Driver

- The LIN driver provides services for communication over the LIN bus.
- Allows the ECU node to operate as a LIN master.

#### 3. CAN Driver

- The CAN driver provides services for communication over the CAN bus.

#### 4. FlexRay Driver

- The FlexRay driver provides services for communication over the FlexRay bus.

#### 5. Ethernet Driver

- The Ethernet driver provides services for communication over the Ethernet bus.

### MCAL Memory Drivers

#### 1. Internal EEPROM Driver

- The internal EEPROM driver provides services for reading and writing data to the internal EEPROM memory.

#### 2. Internal Flash Driver

- The internal flash driver provides services for reading and writing data to the internal flash memory.

### MCAL MCU Drivers

#### 1. Watchdog Driver

- The watchdog driver provides services for configuring and controlling the watchdog timer.

#### 2. GPT Driver

- The GPT driver provides services for configuring and controlling the general-purpose timer.

#### 3. MCU Driver

**Provides services for:**
- MCU initialization
- Initialization of the clock system, PLL and clock prescalers
- Initialze RAM sections

## ECU Abstraction Layer

**ECU Abstraction Layer Provides:**

- Interfaces the drivers of the MCAL layer
- It Contains drivers for external peripherals.
- **Offers an API for accessing the peripherals and devices regardless of their location(MCU internal/External) and Their Connection to the MCU(Port Pins,type of interface)**
- **Task**
  - Make the upper software layers independent of the ECU hardware.
- **Properties**
  - MCU independent
  - ECU Dependent
  - **Upper layers are independent of ECU and MCU hardware**

### ECU Abstraction Layer Types

![ECU Abstraction Layer](ECUAbstraction.png)
- **External Devices**
  - Contains drivers for external peripherals.
  - Ex: External Flash, External EEPROM, External ADC, External DAC, etc.
- **Interface Module**
  - Contains the functionality to abstract from modules which are architecturally placed below them.
  - It provides a generic API to access a specific type of device independent of:
      - **Number of Exitsting devices** of that type.
      - **Location** of the device.
  - The interface does not change the content of the data.
  - **Example**:
        - CAN/LIN/Ethernet Interface
        - Memory Interface
        - Watchdog Interface

### ECU Abstraction Layer Modules

#### **I/O Hardware Abstraction Module**

#### **Communication Hardware Abstraction Module**

#### **Memory Hardware Abstraction Module**

#### **Onboard Device Hardware Abstraction Module**


### I/O Hardware Abstraction Module

- The **I/O Hardware Abstraction Module** is a group of modules which abstracts from the **Location** of the peripheral I/O devices.
**Task**
  - Represent I/O devices connectet to the ECU.
  - Hide ECU hardware details from the upper software layers.

![I/O Hardware Abstraction Module](IOAbstraction.png)

### Communication Hardware Abstraction Module

- The **Communication Hardware Abstraction Module** is a group of modules which abstracts from the **Location** of the communication controllers and the 
**ECU Hardware Layout**.

- Contains **Communication Transceiver Drivers** like `CanTrcv`, `LinTrcv`, `FlexRayTrcv`, etc.
- The CAN Tranciever Driver connects the CAN controller to the physical transmission medium. it Converts single ended signals used by CAN Controller to differential signals transmitted over the CAN bus.

- Communication Hardware Abstraction contains the communication bus interface modules like `CanIf`, `LinIf`, `FlexRayIf`, etc.

- **Bus Interface Modules** Contains the functionality to abstract from modules which are architecturally placed below them.
  - It provides a generic API to access a specific type of device independent of:
      - **Number of Exitsting devices** of that type.
      - **Location** of the device.
  - The interface does not change the content of the data.
  - **Example**:
        - CAN/LIN/Ethernet Interface
        - Memory Interface
        - Watchdog Interface
- Provide equal mechanisms for accessing a bus channel regardless of its location(on-chip/on-board).

- A `Can Interface` module provides a generic API to access a specific type of device independent of the number of existing devices of that type and their location.
- **Example**:
  - An ECU has a MCU with 2 internal CAN channels and an additional on-board ASIC with 4 CAN controllers connected to the MCU via SPI.
  - The Can Interface module provides a generic API to access all 6 CAN channels.

### Memory Hardware Abstraction Module

- The **Memory Hardware Abstraction Module** is a group of modules which abstracts from the **Location** of the memory devices.
- **Task**
  - Represent memory devices connected to the ECU.
  - Hide ECU hardware details from the upper software layers.

### Onboard Device Hardware Abstraction Module

- The **Onboard Device Hardware Abstraction Module** is a group of modules which abstracts from the **Location** of the onboard devices.
- **Task**
  - Represent onboard devices connected to the ECU.
  - Hide ECU hardware details from the upper software layers.

## Services Layer

- The **Services Layer** is the highest layer of the Basic Software Which provides services to the Application Layer.
- **The Service Layer offers**
  - **Operating System Functionality**
  - **Vehicle Network Communication**
  - **Memory Management**
  - **Diagnostics Services**
  - **ECU State Management**
  - **SuperVisor Services**
  - **Error Reporting Services**

### AUTOSAR OS

- The AUTOSAR OS is a real-time operating system based on the `OSEK` OS.


### Service Layer

#### Det Module

- It Collects all the development errors reported from the BSW modules and takes the required action based on type of error and the BSW module that reported the error.

#### Dem Module

- Production errors are reported to the Dem module.
- It stores and processes the errors and their associated data.
- Then it provides the info to **DCM(Diagnostic Communication Manger)** module, Which can communicate the information to the tester tools connected to the vehicle.

## SWS (Software Specification)

- The Software Specification (SWS) is a document that describes the software architecture, design, and behavior of an AUTOSAR module.
- It provides detailed information about the module's interfaces, configuration parameters, and functionality.
- The SWS serves as a reference for software developers, integrators, and testers working on AUTOSAR projects.

### SWS Structure

- The SWS document typically consists of the following sections:
  - **Introduction**: Provides an overview of the module and its purpose.
  - **Scope**: Describes the scope of the module and its intended use.
  - **References**: Lists the documents and standards referenced in the SWS.
  - **Glossary**: Defines the terms and acronyms used in the document.
  - **Design Overview**: Explains the design principles and architecture of the module.
  - **Functional Description**: Describes the functionality and behavior of the module.
  - **Interfaces**: Details the interfaces exposed by the module, including ports, signals, and operations.
  - **Configuration**: Specifies the configuration parameters and settings for the module.
  - **Error Handling**: Describes how errors and exceptions are handled by the module.
  - **Testing and Validation**: Outlines the testing procedures and validation criteria for the module.
  - **Performance**: Provides information on the performance characteristics of the module.
  - **Limitations**: Lists any known limitations or constraints of the module.
  - **Appendices**: Includes additional information, examples, or reference material.

### Benefits of SWS

- **Clarity**: The SWS document provides a clear and detailed description of the module's functionality and behavior.
- **Consistency**: It ensures that all stakeholders have a common understanding of the module's interfaces and configuration.
- **Reference**: The SWS serves as a reference for developers, testers, and integrators working on the module.
- **Compliance**: It helps ensure that the module complies with the AUTOSAR standards and requirements.
- **Maintenance**: The SWS document can be updated and maintained as the module evolves over time.

## SWS Example (Dio Module)


## Full Software Architecture

![AUTOSAR Architecture](FullArcheticture.png)