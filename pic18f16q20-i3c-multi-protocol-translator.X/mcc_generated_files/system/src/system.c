/**
 * System Driver Source File
 * 
 * @file system.c
 * 
 * @ingroup systemdriver
 * 
 * @brief This file contains the API implementation for the System driver.
 *
 * @version Driver Version 1.0.2
 *
 * @version Package Version 1.0.2
*/

/*
� [2024] Microchip Technology Inc. and its subsidiaries.

    Subject to your compliance with these terms, you may use Microchip 
    software and any derivatives exclusively with Microchip products. 
    You are responsible for complying with 3rd party license terms  
    applicable to your use of 3rd party software (including open source  
    software) that may accompany Microchip software. SOFTWARE IS ?AS IS.? 
    NO WARRANTIES, WHETHER EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS 
    SOFTWARE, INCLUDING ANY IMPLIED WARRANTIES OF NON-INFRINGEMENT,  
    MERCHANTABILITY, OR FITNESS FOR A PARTICULAR PURPOSE. IN NO EVENT 
    WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY 
    KIND WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF 
    MICROCHIP HAS BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE 
    FORESEEABLE. TO THE FULLEST EXTENT ALLOWED BY LAW, MICROCHIP?S 
    TOTAL LIABILITY ON ALL CLAIMS RELATED TO THE SOFTWARE WILL NOT 
    EXCEED AMOUNT OF FEES, IF ANY, YOU PAID DIRECTLY TO MICROCHIP FOR 
    THIS SOFTWARE.
*/

#include "../system.h"

/** 
* @ingroup systemdriver
* @brief Initializes the CPU module.
* @param None.
* @return None.
*/
void CPU_Initialize(void);


/**
 * @ingroup systemdriver
 * @brief Performs lock operation. It is mandatory for DMA operation.
 * @param None.
 * @return None.
*/
void SystemArbiter_Initialize();

void SYSTEM_Initialize(void)
{
    CLOCK_Initialize();
    PIN_MANAGER_Initialize();
    CPU_Initialize();
    DMA1_Initialize();
    DMA2_Initialize();
    I2C1_Host_Initialize();
    I3C2_Initialize();
    MVIO_Initialize();
    SPI1_Host_Initialize();
    UART1_Initialize();
    UART2_Initialize();
    INTERRUPT_Initialize();
    SystemArbiter_Initialize();
}

void CPU_Initialize(void)
{
    //PRLOCKED unlocked; 
    PRLOCK = 0x0;
    //PR priority level 7; 
    SCANPR = 0x7;
    //PR priority level 7; 
    DMA1PR = 0x7;
    //PR priority level 7; 
    DMA2PR = 0x7;
    //PR priority level 7; 
    DMA3PR = 0x7;
    //PR priority level 7; 
    DMA4PR = 0x7;
    //PR priority level 7; 
    MAINPR = 0x7;
    //PR priority level 7; 
    ISRPR = 0x7;
    //PRODH undefined; 
    PRODH = 0x0;
    //PRODL undefined; 
    PRODL = 0x0;
}

void SystemArbiter_Initialize(void)
{
    // This function is dependant on the PR1WAY CONFIG bit
    PRLOCK = 0x55;
    PRLOCK = 0xAA;
    PRLOCKbits.PRLOCKED = 1;
}
