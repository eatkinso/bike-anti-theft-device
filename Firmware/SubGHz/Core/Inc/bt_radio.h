/**
  ******************************************************************************
  * @file    bt_radio.h
  * @brief   This file contains all the function prototypes for
  *          the bt_radio.c file
  ******************************************************************************
  * @attention
  *
  * Elizabeth Atkinson 
  * eatkinso@illinois.edu
  * April 2022
  *
  ******************************************************************************
  */
// prevent recursive inclusion
#ifndef __BT_RADIO__
#define __BT_RADIO__
#endif

// includes 

#include "main.h"
#include "radio.h"
#include "radio_fw.h"
#include "timer.h"


void btLoRaSetup(void);



void btLoRaListen(uint32_t ltimeout);




void btLoRaTx(uint8_t *pData, uint8_t datalen);

