/*******************************************************************************
 * File Name          : se_interface_exception.s
 * Author             : MCD Application Team
 * Description        : This file defines function to handle user interrupts
 *                      raised in Firewall
 *******************************************************************************
 *  @attention
 *
 * Copyright (c) 2020 STMicroelectronics. All rights reserved.
 *
 *  This software component is licensed by ST under Ultimate Liberty license
 *  SLA0044, the "License"; You may not use this file except in compliance with
 *  the License. You may obtain a copy of the License at:
 *                              www.st.com/SLA0044
 *
 *******************************************************************************
 */

        .section .text.SE_UserHandlerWrapper
        .global DummyMemAccess
        .global SE_UserHandlerWrapper
        .global SeCallGateStatusParam
        .global __ICFEDIT_SE_CallGate_region_ROM_start__
        .syntax unified
        .thumb

/******************************************
 * Function Name  : SE_UserHandlerWrapper
 * Description    : call Appli IT Handler
 * input          : R0 : @ Appli IT Handler
 *                : R1 : Primask value
 * internal       : R3
 * output         : R0 : SE_CallGate 1st input param: Service ID
 *                : R1 : SE_CallGate 2nd input param: return status var @
 *                : R2 : SE_CallGate 3rd input param: Primask
 * return         : None
 ******************************************
 */
SE_UserHandlerWrapper:
// restore Primask
        MSR PRIMASK, R1
// Specific B-L4S5I-IOT01A : force a SRAM data access outside FWALL protected SRAM to close correctly the FWALL
        // See errata sheet: ES0393 - Rev 6 - October 2019
        // DummyMemAccess variable used to force data access outside FWALL protected SRAM1
        // and outside the 18 LSB range protected by FWALL.
        LDR R2, =DummyMemAccess
        LDR R2, [R2]
// call User IT Handler
        // SE_UserHandlerWrapper shall be mapped at @ bit[4] = 1 in linker script file
        // the purpose is to have LR bit [4] = 1 after executing the next instruction BLX R0
        // So be careful not to modify code here that changes LR bit [4] after executing the next instruction BLX R0
        BLX R0
// disable IT
        CPSID i
// set input param for SE_CallGate
        MOV R0, #0x00001000              // SE_EXIT_INTERRUPT
        LDR R1, =SeCallGateStatusParam
        MOV R2, #0xFFFFFFFF              // invalid Primask
// re-enter in firewall via SE_CallGate
        LDR R3, =__ICFEDIT_SE_CallGate_region_ROM_start__
        ADD R3, R3, #5
        BLX R3                           // LR shall be updated otherwise __IS_CALLER_SE_IF will fail in Se_CallGate
// we shall not raise this point
        // B NVIC_SystemReset

.end
/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
