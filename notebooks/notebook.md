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

# 4/6/2022 -- More firmware (Elizabeth)

Upgraded BMP debugger to latest firmware which supports STM32WLs. Note that the latest version of arm-none-eabi-gdb is borked on linux, so you need to run v10.3. Source at https://developer.arm.com/tools-and-software/open-source-software/developer-tools/gnu-toolchain/gnu-rm/downloads. 

## Goal today: talk to GPS over UART. 

- reconfigured the STM32 pinout.. whoops. 
- Testing just UART peripheral. Using single core to allow use of a Makefile (not supported by CubeMx for dual-core)

- NOTE: pinout given in EM-506 datasheet is pinout looking IN to the GPS module board (pin 1 on the RH side; grey wire is pin 6.)

First try didn't work. Probed with scope; GPS module clearly sending some data, it is just not being received by the STM32. Next step: try "loop" UART (ie, send from STM32 TX pin -> STM32 RX pin) to make sure I'm implementing the peripheral correctly.

Tutorial for loopback test: 
https://stackoverflow.com/questions/43263467/nucleo-stm32f103rb-f4-discovery/43411114#43411114

https://stackoverflow.com/questions/47574416/uart-loopback-test-using-hal-for-stm32l0


Loopback test code: 

    MX_GPIO_Init();

      MX_USART1_UART_Init();

      // MX_LoRaWAN_Init();

      /* USER CODE BEGIN 2 */

      uint8_t txdata[2] = {0xEC, 0xEB};

      uint8_t rxdata[2] = {0,0};

      /* USER CODE END 2 */

      /* Infinite loop */
      /* USER CODE BEGIN WHILE */
      while (1)

      {

        HAL_UART_Receive_IT(&huart1, rxdata, 2);

        HAL_UART_Transmit(&huart1, txdata, 2, 10);

        /* USER CODE END WHILE */

        // MX_LoRaWAN_Process();

        /* USER CODE BEGIN 3 */
      }


The default communication parameters for PORT B are 9600Baud, 8data bits, 0 stop bits, and no
parity.

EM-506 can be configured to use NMEA messages: 

https://en.wikipedia.org/wiki/NMEA_0183

Ugh. Verified *manually* via oscilloscope that the UART messages have no stop bit -- this means they are *actually* impossible to use, since stty and STM32s do not support UART with no stop bit. 

# 4/10/2022 Second try- new GPS module

Adafruit Ultimate GPS breakout v3

https://learn.adafruit.com/adafruit-ultimate-gps/direct-computer-wiring


Ok, clearly, all of these GPS modules are "meant" to be used with arduino, and all of the arduino serial libraries don't let you specify uart parameters like stop bit, word length and parity... so none of the documentation for the modules specify uart parameters and I can't figure out what the arduino serial libraries are assuming. Goal: figure out default Arduino UART config. 

https://www.engineersgarage.com/articles-arduino-serial-communication-uart/

Default Arduino UART config (`SoftwareSerial.begin()`) is 8N1 (8 bit word, no parity, 1 stop bit.)


Ok, so now it gets the first character ($) and nothing else. Thinking maybe the clock is off since there is no external oscillator... trying STM32 auto baud rate to see if that helps. 

auto baud rate did not help. RIP. 

Going back to the terminal with the IDP . RX LED flashing, clearly the module is sending *something*... but cannot recieve it with Screen. 


Scoped the UART trace. Apparently UART idles low??? bizarre. Trying to invert the polarity w cubeMX next. Does look like 9600 baud tho. 

![](uart_inverted_scope.jpeg)


Decoding binary by hand :cry: .. clearly inverted with 1 start bit, 1 stop bit, 8 bits of data tho
![](bin_rip.jpeg)


ugh. strategy.... do a loopback test while probing the UART from TX/RX on the STM32. adjust settings until it matches the waveform from the GPS module. 

With both TX and RX invert, no Data invert: idles high

only TX invert: also idles high, received data is wrong as to be expected

ok, data invert + software NOT-ing the data reproduces the waveform. Problem: the STM32 still can't rx data from the GPS. 


Loopback: 

Hi: 3.16 V
Lo: -40mV
Period: 108 uS
Idle high
bits: 0 00100100 10 11100010 10 00001010 10


GPS: 

Hi: 3.24 V
Lo: -120 mV 
Period: 108 uS
Idle HIGH 
same bits 
AGHH!!!


Tried with arduino -- works fine. Bizarre. Thought: timing might be *slightly* off, and Arduino is fine with it bc it has a lower clock speed, but the STM32 is pickier. Next step: fiddle with STM32 UART oversampling rate and/or baud rate to see if that fixes it. 

# 4/11/2022 More Debugging -- Elizabeth 


Switched to SWO instead of JTAG in CubeMx.. probably not going to help but worth a try. 

Try: 
-audo baud rate on falling edge + single sample

Ok, abandoning UART for now. Current plan... use Arduino as intermediary between GPS and STM32, hardware serial with level-shifter since the arduino uses 5V logic. 

# 4/11/2022 Late night -- LoRa Work

Now onto the actually difficult part... getting them to talk to each other. Unfortunately the osc screwup is mostly un-bodgeable, so we are relying on the internal oscillator for now. Not great but oh well. 


## Notes about LoRa application structure: 

reference: 
https://www.st.com/content/ccc/resource/technical/document/application_note/group1/de/e1/90/fd/84/e3/49/bd/DM00660451/files/DM00660451.pdf/jcr:content/translations/en.DM00660451.pdf

![](lora_app_structure.png)

This is the LoRA application structure for all of the example applications. To write a custom application, you can write your own application on top of just the LoRaWAN middleware. 

![](rxtxproc.png)

This shows the sequence of RX/TX processing 



State machine: 

![](lora_statemachine.png)


tracing this through the code for LoRaWAN_AT_Slave: 

1. in infinite while loop, MX calls `MX_LoRaWAN_Process()`

- - in `MX_LoRaWAN_Process()`, AT_slave calls the sequencer

2. In init code, MX generates `LoRaWAN_Init()` and `SystemApp_Init()`;

3. `LoRaWAN_INIT()` calls `LmHandlerInit(&LmHandlerCallbacks)`, initializing the LoRa State machine
 - - In the user code sections here, the user must place their own app initialization code. 


 Commands: 

 commands for the AT_slave application are in `lora_at.c` and `lora_command.c`. 


 The two basic commands for *just* sending data and joining a network:

 ![](ATjoin.png)



    ATEerror_t AT_Send(const char *param)
    {
      /* USER CODE BEGIN AT_Send_1 */

      /* USER CODE END AT_Send_1 */
      const char *buf = param;
      uint16_t bufSize = strlen(param);
      uint32_t appPort;
      LmHandlerMsgTypes_t isTxConfirmed;
      unsigned size = 0;
      char hex[3] = {0, 0, 0};
      LmHandlerErrorStatus_t lmhStatus = LORAMAC_HANDLER_ERROR;
      ATEerror_t status = AT_ERROR;

      /* read and set the application port */
      if (1 != tiny_sscanf(buf, "%u:", &appPort))
      {
        AT_PRINTF("AT+SEND without the application port\r\n");
        return AT_PARAM_ERROR;
      }

      /* skip the application port */
      while (('0' <= buf[0]) && (buf[0] <= '9') && bufSize > 1)
      {
        buf ++;
        bufSize --;
      };

      if ((bufSize == 0) || (':' != buf[0]))
      {
        AT_PRINTF("AT+SEND missing : character after app port\r\n");
        return AT_PARAM_ERROR;
      }
      else
      {
        /* skip the char ':' */
        buf ++;
        bufSize --;
      }

      switch (buf[0])
      {
        case '0':
          isTxConfirmed = LORAMAC_HANDLER_UNCONFIRMED_MSG;
          break;
        case '1':
          isTxConfirmed = LORAMAC_HANDLER_CONFIRMED_MSG;
          break;
        default:
          AT_PRINTF("AT+SEND without the acknowledge flag\r\n");
          return AT_PARAM_ERROR;
      }

      if (bufSize > 0)
      {
        /* skip the acknowledge flag */
        buf ++;
        bufSize --;
      }

      if ((bufSize == 0) || (':' != buf[0]))
      {
        AT_PRINTF("AT+SEND missing : character after ack flag\r\n");
        return AT_PARAM_ERROR;
      }
      else
      {
        /* skip the char ':' */
        buf ++;
        bufSize --;
      }

      while ((size < LORAWAN_APP_DATA_BUFFER_MAX_SIZE) && (bufSize > 1))
      {
        hex[0] = buf[size * 2];
        hex[1] = buf[size * 2 + 1];
        if (tiny_sscanf(hex, "%hhx", &AppData.Buffer[size]) != 1)
        {
          return AT_PARAM_ERROR;
        }
        size++;
        bufSize -= 2;
      }
      if (bufSize != 0)
      {
        return AT_PARAM_ERROR;
      }

      AppData.BufferSize = size;
      AppData.Port = appPort;

      lmhStatus = LmHandlerSend(&AppData, isTxConfirmed, false);

      switch (lmhStatus)
      {
        case LORAMAC_HANDLER_SUCCESS:
          status = AT_OK;
          break;
        case LORAMAC_HANDLER_BUSY_ERROR:
        case LORAMAC_HANDLER_COMPLIANCE_RUNNING:
          status = (LmHandlerJoinStatus() != LORAMAC_HANDLER_SET) ? AT_NO_NET_JOINED : AT_BUSY_ERROR;
          break;
        case LORAMAC_HANDLER_NO_NETWORK_JOINED:
          status = AT_NO_NET_JOINED;
          break;
        case LORAMAC_HANDLER_DUTYCYCLE_RESTRICTED:
          status = AT_DUTYCYCLE_RESTRICTED;
          break;
        case LORAMAC_HANDLER_CRYPTO_ERROR:
          status = AT_CRYPTO_ERROR;
          break;
        case LORAMAC_HANDLER_ERROR:
        default:
          status = AT_ERROR;
          break;
      }

      return status;
      /* USER CODE BEGIN AT_Send_2 */

      /* USER CODE END AT_Send_2 */
    }

  

Note that the above function basically just manages the LmHandler. Note also that `*param` is a pointer to a string that *contains* the parameters .. very helpfully not explained at all in the code. From [AN5481, 'LoRaWAN AT Commands for STM32CubeWL](https://www.st.com/content/ccc/resource/technical/document/application_note/group1/63/ee/3a/53/c3/49/46/c1/DM00699239/files/DM00699239.pdf/jcr:content/translations/en.DM00699239.pdf): 

![](atjoinparams.png)

## Tentative path forward: 

0. Fix linker file. Use template if possible.

1. Import basically the entire AT application source code into the user-defined MX skeleton (likely easier said than done... )


2. Remove sequencer initialization, etc, from init and setup code. Also attempt to remove serial writes (AT_PRINTF) or disable interface entirely. 

3. VERIFY RF SWITCH CONNECTIONS

4. Write test program that explicitly calls RF tests at the LoRa frequency; DO NOT FORGET RF SWITCH EXPLICIT CONTROL

4. Write test program that explicitly calls AT_Send with dummy data to see if we can send something 

5. Proceed with state machine implementation using explicit AT commands. 

# 4/12/2022 More LoRa brainstorming


After more thought, it might actually be better to go a few more layers down in the protocol and avoid the LoRa MAC entirely. Also because I don't want to deal with making a WAN. The MAC is just me uhhh... having one TX unit and one RX unit. 

https://forum.digikey.com/t/using-the-low-level-sub-ghz-radio-driver-for-the-stm32wl-series/18253

Ok, regenerated firmware in SubGHz firmware with just SubGHz_PHY enabled. radio_driver.c looks like it has the low-level functions to directly control the radio (literally just reading/writing registers in the hardware). 

-> try and check LoRa examples for sequency of SGHZ commands, but looks like you can pretty directly just set TX params, set packet params, and go ahead and send stuff. for example `SUBGRF_SetPacketParams ` lets you just set the packet type as LoRA. 