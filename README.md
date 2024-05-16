# GPS_PROJECT

## Project Description:
- The aim of this project is to create an embedded system using C programming. This system will continuously gather real-time positional coordinates through a microcontroller (specifically, the TM4C123G LaunchPad) while in motion, starting from power-on until it reaches a designated endpoint. The gathered data will then be efficiently transferred to a personal computer (PC) and displayed on a map application. 
- There are three options for defining the endpoint:

1- Once the moved distance exceeds 100m, stop adding new points to the trajectory and the last point added to the trajectory is the target destination.

2- Stop adding new points when a push button is pressed, and the last point added to the trajectory is the last destination.

3- Predefine the destination point in your code and when the system reaches this point, stop adding new points to the trajectory.

## Project Requirements.
- Tiva TM4C123GH6PM Microcontroller based on ARM Cortex-M4.
- GPS Module.
- A personal computer (PC)
- Connecting cables (USB, serial, etc.)
- Display source (LCD, Seven segment, esp module wifi, etc)

## Algorithm :
- Getting the current location coordinates from GPS Module using UART, then calculating the distance between it and destination point which is hard coded inside the code.
- the distance is calculated using Haversine formula.
- We use ESP module Wifi to display the covered distance on the smart phone.
- When the destination point is arrived , the LED turns ON.

## Repo Folders:
- HEADERS: Contains Functions Prototypes and all Hash Defines (files.h) used in all files.
- SRC : Contains source code (files.c) of each Driver(GPS.c, GPIO.c, UART.c, etc.).
- SERVICES : Contain Bit_Operations which contain some Sets, Gets and clears + header file of tiva which contains registers adrresses + Startup code  

## Video Link:
- https://drive.google.com/drive/folders/1sWtfXL9iE0wN74YOkhtSlasSGLfTBbVK