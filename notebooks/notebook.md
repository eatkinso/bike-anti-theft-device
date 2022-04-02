# 2-8-22 Tues [Elizabeth]
## Group and TA meeting

### Agenda: 

- discussed part selection
- began block diagram and proposal 

### Action Items: 


Elizabeth: 
- finish block diagram 
- write subsystem spec and reqs for Microcontroller/LoRa and Alarm 
- subsystem block diagram for microcontroller/LoRa and alarm 


Nidhi: 
- Finish writing main proposal sections
- GPS Module: Write proposal subsystem section


Alex:
- RFID Module and RFID tag: Write proposal subsystem section 
- Write ethics and safety

GOAL: finish these tasks by midnight wednesday, so we can all review the proposal in full and submit on Thursday

# 2-9-22 Individual work notes [Elizabeth]

## Task List by subsystem

### Overall
- CAD/3d printing model for bike unit 
- design main board(s)



### Alarm 
- design alarm PCB (piezo button, driver circuit, power)


### GPS module 

- read datasheet, identify communication protocol 
- design support circuitry

### RFID subsystem 

- read datasheet and understand communication interface
- design support circuitry


### Microcontroller/LoRa

- choose pinout based on serial data requirements
- design support circuitry
- write firmware 

### Reciever 

- research how to write a python backend for the data display GUI
- research how to implement a LoRa mesh network 

# 2/16/22 Design Document Planning Meeting [Elizabeth]

## Agenda: 
- Sketched HW block diagram (physical configuration)
- Sketched firmware state machine
- Discussed division of labor 
- 
## Physical configuration block diagram: 

![physical config](physical_config_block_diagram.jpeg
)

## State diagram: 

![state_diagram](state_diagram.jpeg)

## Hardware tasks: 

- Design main board 
   - RF section: E, N
   - Power section: A
   - MCU support, connectors, etc: E

- Design Alarm driver board: A 
- Design RFID carrier board: N 


## Goal: 

Finish schematic design tasks by evening Saturday





# 3/6/2022 Group PCB Work 

- Each working on finishing PCB layout by Tues deadline
- Alex finished the alarm board, nidhi finished RFID carrier board
- Alex finished alarm BOM, Nidhi finished RFID BOM
- Elizabeth working on main board





# 4/2/2022 Hardware work 


-- Elizabeth: working on running LoRa example application on STM32WL dev board. Pinout and instructions below. 

![lora_devboard](lora_instructions_devboard.jpeg)

![lora_devboard_pin](devboard_pinout.jpeg)

Trying to run the LoRa demo on the board -- following directions below from UM2463 for STM32cubeide. First the blinky example (GPIO_EXTI), then one of the LoRa ones -- File path to LoRa project is `bike-anti-theft-device/Firmware/stm32wl_fwpackage/STM32Cube_FW_WL_V1.2.0/Projects/NUCLEO-WL55JC/Demonstrations/LocalNetwork/`. Running the "sensor" first -- setup is connected to Spectrum analyzer, want to verify that it can transmit something. 


![first_ex](first_ex.png)


NOTE: use IMPORT-> Import STM32CubeExample and then select the desired example. Otherwise it will not load builders and the project won't build (and I couldn't figure out how to add builders after the project has already been imported).

Blinky worked! Now onto trying a LoRa example. Note that the LoRa examples require STM32CubeIDE 1.9+ apparently. 


Back to the AT slave example...ugh. UART on linux: 

screen /dev/ttyACM0 9600


monitor serial: `cat -v /dev/ttyACM0`


send command: `echo -e 'command' > /dev/ttyACM0`


set serial to 9600 baud, 8 bit data, no parity, 1 stop bit: `stty -F /dev/ttyACM0 cs8 -cstopb -parenb`


Successfully ran RF test at 400-500 MHz. Next time, populate board, work on porting LoRa example to our HW. 