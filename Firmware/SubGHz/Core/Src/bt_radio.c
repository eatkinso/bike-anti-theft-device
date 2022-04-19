/**
  ******************************************************************************
  * @file    bt_radio.c
  * @brief   This file provides code for the radio transactions for the LoRa bike tracker project. 
  ******************************************************************************
  * @attention
  *
  * Elizabeth Atkinson 
  * eatkinso@illinois.edu
  * April 2022
  *
  ******************************************************************************
  */

#include "bt_radio.h"
#include "radio.h"
#include "radio_fw.h"
#include "radio_driver.h"
#include "radio_conf.h"
#include "mw_log_conf.h"
#include "timer.h"

//IMPORTANT: ALWAYS COMMENT OUT LINES 1415, 1280 in radio.c. 

//// copied from radio.c to fix compilation error
#ifndef IRQ_TX_DBG
#define IRQ_TX_DBG ((uint16_t) 0)
#endif
/*can be overridden in radio_conf.h*/
#ifndef IRQ_RX_DBG
#define IRQ_RX_DBG ((uint16_t) 0)
#endif

// LoRa Parameters

#ifndef btLORA
#define btLORA (uint8_t )


/*!
 * \brief Sets up the radio for TX and RX (channel, frequency, packet type, etc) for this project. 
 * \returns 0 on success, other on failure. 
 * 
 */
void btLoRaSetup(void){
    /*****************
         Set TX config: 
    *****************/
   RFW_DeInit(); /* ST_WORKAROUND: Switch Off FwPacketDecoding by default */

}

/*
* adapted from RadioRx to set up RX for the bike tracker board; sets RF switch and then enters RX. 
* Note this function does not receive or save any data!! that must be done with the callback. 
*/
void btLoRaListen(uint32_t ltimeout)
{
    /* 
    if( 1UL == RFW_Is_Init( ) )
    {
        RFW_ReceiveInit( );
    }
    else
    {
        SUBGRF_SetDioIrqParams( IRQ_RX_DONE | IRQ_RX_TX_TIMEOUT | IRQ_CRC_ERROR | IRQ_HEADER_ERROR | IRQ_RX_DBG,
                                IRQ_RX_DONE | IRQ_RX_TX_TIMEOUT | IRQ_CRC_ERROR | IRQ_HEADER_ERROR | IRQ_RX_DBG,
                                IRQ_RADIO_NONE,
                                IRQ_RADIO_NONE );
    }

    if( ltimeout != 0 )
    {
        TimerSetValue( &RxTimeoutTimer, ltimeout );
        TimerStart( &RxTimeoutTimer );
    }
    // ST_WORKAROUND_BEGIN : Set the debug pin and update the radio switch 
    / switch off RxDcPreambleDetect See STM32WL Errata: RadioSetRxDutyCycle
    SubgRf.RxDcPreambleDetectTimeout = 0;
    // ST_WORKAROUND_END 

    if( SubgRf.RxContinuous == true )
    {
        SUBGRF_SetRx( 0xFFFFFF ); // Rx Continuous
    }
    else
    {
        SUBGRF_SetRx( SubgRf.RxTimeout << 6 );
    }
    /* RF switch configuration
    // For RX, set VC1 high, VC2 low.*/
    HAL_GPIO_WritePin(RFSW_VC1_GPIO_Port, RFSW_VC1_Pin, GPIO_PIN_SET);
    HAL_GPIO_WritePin(RFSW_VC2_GPIO_Port, RFSW_VC2_Pin, GPIO_PIN_RESET);
    Radio.Rx(ltimeout);
}

/*Adapted from 
* Adapted from RadioSend in radio.c. Sets RF switch, loads TX data into register, sets radio into TX. 
*/
void btLoRaTx(uint8_t *pData, uint8_t datalen){
    /* RF switch configuration */
    // For RX, set VC1 low, VC2 high. 
    HAL_GPIO_WritePin(RFSW_VC1_GPIO_Port, RFSW_VC1_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(RFSW_VC2_GPIO_Port, RFSW_VC2_Pin, GPIO_PIN_SET);
    /*
    /* ST_WORKAROUND_BEGIN : Set the debug pin and update the radio switch 
    SUBGRF_SetDioIrqParams( IRQ_TX_DONE | IRQ_RX_TX_TIMEOUT | IRQ_TX_DBG,
                            IRQ_TX_DONE | IRQ_RX_TX_TIMEOUT | IRQ_TX_DBG,
                            IRQ_RADIO_NONE,
                            IRQ_RADIO_NONE );
    /* ST_WORKAROUND_END */

    /* ST_WORKAROUND_BEGIN : Set the debug pin and update the radio switch 
    /* Set DBG pin 
    DBG_GPIO_RADIO_TX( SET );
    /* WORKAROUND - Modulation Quality with 500 kHz LoRaTM Bandwidth*/
    /* RegTxModulation = @address 0x0889 
    if( ( SubgRf.Modem == MODEM_LORA ) && ( SubgRf.ModulationParams.Params.LoRa.Bandwidth == LORA_BW_500 ) )
    {
        SUBGRF_WriteRegister( SUBGHZ_SDCFG0R, SUBGRF_ReadRegister( SUBGHZ_SDCFG0R ) & ~( 1 << 2 ) );
    }
    else
    {
        SUBGRF_WriteRegister( SUBGHZ_SDCFG0R, SUBGRF_ReadRegister( SUBGHZ_SDCFG0R ) | ( 1 << 2 ) );
    }
    /* WORKAROUND END
    SubgRf.PacketParams.Params.LoRa.PayloadLength = datalen;
    SUBGRF_SetPacketParams( &SubgRf.PacketParams );
    SUBGRF_SendPayload( pData, datalen, 0 );
    TimerSetValue( &TxTimeoutTimer, SubgRf.TxTimeout );
    TimerStart( &TxTimeoutTimer ); */
    
    Radio.Send(pData, datalen);

}