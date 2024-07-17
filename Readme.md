# STM32H7 AT Client

## Overview
This project demonstrates how to set up and use an STM32H750 microcontroller to communicate with an FSC-BT1036 Bluetooth module using AT commands. 

The STM32H750 acts as an AT client, sending commands to and receiving responses from the FSC-BT1036, which operates as an AT server.

The project is built using the STM32CubeMX framework and the FreeRTOS operating system.

## Features
* Initialization of the STM32H7's UART peripherals
  * USART1 for communicating with BLE module
  * USART3 for debugging console
* Implementation of the AT client using the stm32wb_at library
* Communication with FSC-BT1036 using AT commands

## Library
The stm32wb_at library has been modified to accommodate the specific AT command set of the FSC-BT1036 module.

## Installation
### Prerequisites
* STM32CubeMX and STM32CubeIDE installed
* STM32H750 development board
* FSC-BT1036 Bluetooth module

### Steps
1. Clone this repository to your local machine.
2. Open the project in STM32CubeIDE.
3. Build the project.
4. Flash the firmware to the STM32H750 board.