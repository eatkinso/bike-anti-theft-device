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



/*!
 * \brief Sets up the radio for TX and RX (channel, frequency, packet type, etc) for this project. 
 * \returns 0 on success, other on failure. 
 * 
 */
void btLoRaSetup(void){
    /* radio_init already called in MX_SubGHz_Phy_Init(), this just sets up other params

     * modem: \param [in] modem        Radio modem to be used [0: FSK, 1: LoRa]
    * \param [in] bandwidth    Sets the bandwidth
    *                          FSK : >= 2600 and <= 250000 Hz
    *                          LoRa: [0: 125 kHz, 1: 250 kHz,
    *                                 2: 500 kHz, 3: Reserved]
    * \param [in] datarate     Sets the Datarate
    *                          FSK : 600..300000 bits/s
    *                          LoRa: [6: 64, 7: 128, 8: 256, 9: 512,
    *                                10: 1024, 11: 2048, 12: 4096  chips]
    * \param [in] coderate     Sets the coding rate (LoRa only)
    *                          FSK : N/A ( set to 0 )
    *                          LoRa: [1: 4/5, 2: 4/6, 3: 4/7, 4: 4/8]
    * \param [in] bandwidthAfc Sets the AFC Bandwidth (FSK only)
    *                          FSK : >= 2600 and <= 250000 Hz
    *                          LoRa: N/A ( set to 0 )
    * \param [in] preambleLen  Sets the Preamble length
    *                          FSK : Number of bytes
    *                          LoRa: Length in symbols (the hardware adds 4 more symbols)
    * \param [in] symbTimeout  Sets the RxSingle timeout value
    *                          FSK : timeout in number of bytes
    *                          LoRa: timeout in symbols
    * \param [in] fixLen       Fixed length packets [0: variable, 1: fixed]
    * \param [in] payloadLen   Sets payload length when fixed length is used. guessing this is bytes but no clue. 
    * \param [in] crcOn        Enables/Disables the CRC [0: OFF, 1: ON]
    * \param [in] FreqHopOn    Enables disables the intra-packet frequency hopping
    *                          FSK : N/A ( set to 0 )
    *                          LoRa: [0: OFF, 1: ON]
    * \param [in] HopPeriod    Number of symbols between each hop
    *                          FSK : N/A ( set to 0 )
    *                          LoRa: Number of symbols
    * \param [in] iqInverted   Inverts IQ signals (LoRa only)
    *                          FSK : N/A ( set to 0 )
    *                          LoRa: [0: not inverted, 1: inverted]
    * \param [in] rxContinuous Sets the reception in continuous mode
    *                          [false: single mode, true: continuous mode]
    */

    RadioSetRxConfig(1, 1, 12, 4, 0, 8, 12, 1, 90, 1, 0, 0, 0, 0);
    /*!
 * \brief Sets the transmission parameters
 *
 * \param [in] modem        Radio modem to be used [0: FSK, 1: LoRa]
 * \param [in] power        Sets the output power [dBm]
 * \param [in] fdev         Sets the frequency deviation (FSK only)
 *                          FSK : [Hz]
 *                          LoRa: 0
 * \param [in] bandwidth    Sets the bandwidth (LoRa only)
 *                          FSK : 0
 *                          LoRa: [0: 125 kHz, 1: 250 kHz,
 *                                 2: 500 kHz, 3: Reserved]
 * \param [in] datarate     Sets the Datarate
 *                          FSK : 600..300000 bits/s
 *                          LoRa: [6: 64, 7: 128, 8: 256, 9: 512,
 *                                10: 1024, 11: 2048, 12: 4096  chips]
 * \param [in] coderate     Sets the coding rate (LoRa only)
 *                          FSK : N/A ( set to 0 )
 *                          LoRa: [1: 4/5, 2: 4/6, 3: 4/7, 4: 4/8]
 * \param [in] preambleLen  Sets the preamble length
 *                          FSK : Number of bytes
 *                          LoRa: Length in symbols (the hardware adds 4 more symbols)
 * \param [in] fixLen       Fixed length packets [0: variable, 1: fixed]
 * \param [in] crcOn        Enables disables the CRC [0: OFF, 1: ON]
 * \param [in] FreqHopOn    Enables disables the intra-packet frequency hopping
 *                          FSK : N/A ( set to 0 )
 *                          LoRa: [0: OFF, 1: ON]
 * \param [in] HopPeriod    Number of symbols between each hop
 *                          FSK : N/A ( set to 0 )
 *                          LoRa: Number of symbols
 * \param [in] iqInverted   Inverts IQ signals (LoRa only)
 *                          FSK : N/A ( set to 0 )
 *                          LoRa: [0: not inverted, 1: inverted]
 * \param [in] timeout      Transmission timeout [ms]
 * 
 * Notes about bike tracker config: 
 *  -- board is setup to use the high-power RF output config (RFO_HP, VR_PA=VCC=3V3.) Max output power is 22 dBm; 
 *      setting ours to 17 dBm because these things are like 1 foot apart.
 *      Note that +15dBm is the minimum power from the RFO_HP output. 
 *  -- RF switch (SKY13370) can handle up to 40 dBm, insertion loss = 0.7dB. 
 * 
 */
    RadioSetTxConfig(1, 17, 0, 1, 12, 4, 8, 1, 0, 0, 0, 0, 100);
}

/*
* adapted from RadioRx to set up RX for the bike tracker board; sets RF switch and then enters RX. 
* Note this function does not receive or save any data!! that must be done with the callback. 
*/
void btLoRaListen(uint8_t ltimeout)
{
    /* RF switch configuration */
    // For RX, set VC1 high, VC2 low. 
    HAL_GPIO_WritePin(RFSW_VC1_GPIO_Port, RFSW_VC1_Pin, GPIO_PIN_SET);
    HAL_GPIO_WritePin(RFSW_VC2_GPIO_Port, RFSW_VC2_Pin, GPIO_PIN_RESET);
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
    /* ST_WORKAROUND_BEGIN : Set the debug pin and update the radio switch */
    /* switch off RxDcPreambleDetect See STM32WL Errata: RadioSetRxDutyCycle*/
    SubgRf.RxDcPreambleDetectTimeout = 0;
    /* ST_WORKAROUND_END */

    if( SubgRf.RxContinuous == true )
    {
        SUBGRF_SetRx( 0xFFFFFF ); // Rx Continuous
    }
    else
    {
        SUBGRF_SetRx( SubgRf.RxTimeout << 6 );
    }
}

/*Adapted from 
* Adapted from RadioSend in radio.c. Sets RF switch, loads TX data into register, sets radio into TX. 
*/
void btLoRaTx(uint8_t *pData, uint8_t datalen){
    /* RF switch configuration */
    // For RX, set VC1 low, VC2 high. 
    HAL_GPIO_WritePin(RFSW_VC1_GPIO_Port, RFSW_VC1_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(RFSW_VC2_GPIO_Port, RFSW_VC2_Pin, GPIO_PIN_SET);
    /* ST_WORKAROUND_BEGIN : Set the debug pin and update the radio switch */
    SUBGRF_SetDioIrqParams( IRQ_TX_DONE | IRQ_RX_TX_TIMEOUT | IRQ_TX_DBG,
                            IRQ_TX_DONE | IRQ_RX_TX_TIMEOUT | IRQ_TX_DBG,
                            IRQ_RADIO_NONE,
                            IRQ_RADIO_NONE );
    /* ST_WORKAROUND_END */

    /* ST_WORKAROUND_BEGIN : Set the debug pin and update the radio switch */
    /* Set DBG pin */
    DBG_GPIO_RADIO_TX( SET );
    /* WORKAROUND - Modulation Quality with 500 kHz LoRaTM Bandwidth*/
    /* RegTxModulation = @address 0x0889 */
    if( ( SubgRf.Modem == MODEM_LORA ) && ( SubgRf.ModulationParams.Params.LoRa.Bandwidth == LORA_BW_500 ) )
    {
        SUBGRF_WriteRegister( SUBGHZ_SDCFG0R, SUBGRF_ReadRegister( SUBGHZ_SDCFG0R ) & ~( 1 << 2 ) );
    }
    else
    {
        SUBGRF_WriteRegister( SUBGHZ_SDCFG0R, SUBGRF_ReadRegister( SUBGHZ_SDCFG0R ) | ( 1 << 2 ) );
    }
    /* WORKAROUND END */
    SubgRf.PacketParams.Params.LoRa.PayloadLength = datalen;
    SUBGRF_SetPacketParams( &SubgRf.PacketParams );
    SUBGRF_SendPayload( pData, datalen, 0 );
    TimerSetValue( &TxTimeoutTimer, SubgRf.TxTimeout );
    TimerStart( &TxTimeoutTimer );
}