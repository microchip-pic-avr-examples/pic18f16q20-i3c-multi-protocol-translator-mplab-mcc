/**
 * Generated Driver File
 * 
 * @file pins.c
 * 
 * @ingroup  pinsdriver
 * 
 * @brief This is generated driver implementation for pins. 
 *        This file provides implementations for pin APIs for all pins selected in the GUI.
 *
 * @version Driver Version 3.1.0
*/

/*
© [2023] Microchip Technology Inc. and its subsidiaries.

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

#include "../pins.h"

void (*INT1_Client_InterruptHandler)(void);
void (*INT2_Client_InterruptHandler)(void);

void PIN_MANAGER_Initialize(void)
{
   /**
    LATx registers
    */
    LATA = 0x15;
    LATB = 0x80;
    LATC = 0x83;

    /**
    TRISx registers
    */
    TRISA = 0x22;
    TRISB = 0x60;
    TRISC = 0x60;

    /**
    ANSELx registers
    */
    ANSELA = 0x0;
    ANSELB = 0x0;
    ANSELC = 0x0;

    /**
    WPUx registers
    */
    WPUA = 0x0;
    WPUB = 0x0;
    WPUC = 0x0;

    /**
    ODx registers
    */
    ODCONA = 0x0;
    ODCONB = 0x60;
    ODCONC = 0x3;

    /**
    SLRCONx registers
    */
    SLRCONA = 0x37;
    SLRCONB = 0xE0;
    SLRCONC = 0xFB;

    /**
    INLVLx registers
    */
    INLVLA = 0x3F;
    INLVLB = 0xE0;
    INLVLC = 0xFB;

   /**
    RxyI2C | RxyFEAT registers   
    */
    RC0FEAT = 0x20;
    RC1FEAT = 0x20;
    RC4FEAT = 0x0;
    RC5FEAT = 0x0;
    RB5FEAT = 0x20;
    RB6FEAT = 0x20;
    /**
    PPS registers
    */
    SPI1SDIPPS = 0x16; //RC6->SPI1:SDI1;
    RC4PPS = 0x13;  //RC4->UART1:TX1;
    RC3PPS = 0x1A;  //RC3->SPI1:SDO1;
    I2C1SCLPPS = 0x10;  //RC0->I2C1:SCL1;
    RC0PPS = 0x1C;  //RC0->I2C1:SCL1;
    I2C1SDAPPS = 0x11;  //RC1->I2C1:SDA1;
    RC1PPS = 0x1D;  //RC1->I2C1:SDA1;
    SPI1SCKPPS = 0x5;  //RA5->SPI1:SCK1;
    RA5PPS = 0x19;  //RA5->SPI1:SCK1;

   /**
    IOCx registers 
    */
    IOCAP = 0x2;
    IOCAN = 0x0;
    IOCAF = 0x0;
    IOCWP = 0x0;
    IOCWN = 0x0;
    IOCWF = 0x0;
    IOCBP = 0x0;
    IOCBN = 0x0;
    IOCBF = 0x0;
    IOCCP = 0x20;
    IOCCN = 0x0;
    IOCCF = 0x0;

    INT1_Client_SetInterruptHandler(INT1_Client_DefaultInterruptHandler);
    INT2_Client_SetInterruptHandler(INT2_Client_DefaultInterruptHandler);

    // Enable PIE3bits.IOCIE interrupt 
    PIE3bits.IOCIE = 1; 
}
  
void PIN_MANAGER_IOC(void)
{
    // interrupt on change for pin INT1_Client
    if(IOCAFbits.IOCAF1 == 1)
    {
        INT1_Client_ISR();  
    }
    // interrupt on change for pin INT2_Client
    if(IOCCFbits.IOCCF5 == 1)
    {
        INT2_Client_ISR();  
    }
}
   
/**
   INT1_Client Interrupt Service Routine
*/
void INT1_Client_ISR(void) {

    // Add custom INT1_Client code

    // Call the interrupt handler for the callback registered at runtime
    if(INT1_Client_InterruptHandler)
    {
        INT1_Client_InterruptHandler();
    }
    IOCAFbits.IOCAF1 = 0;
}

/**
  Allows selecting an interrupt handler for INT1_Client at application runtime
*/
void INT1_Client_SetInterruptHandler(void (* InterruptHandler)(void)){
    INT1_Client_InterruptHandler = InterruptHandler;
}

/**
  Default interrupt handler for INT1_Client
*/
void INT1_Client_DefaultInterruptHandler(void){
    // add your INT1_Client interrupt custom code
    // or set custom function using INT1_Client_SetInterruptHandler()
}
   
/**
   INT2_Client Interrupt Service Routine
*/
void INT2_Client_ISR(void) {

    // Add custom INT2_Client code

    // Call the interrupt handler for the callback registered at runtime
    if(INT2_Client_InterruptHandler)
    {
        INT2_Client_InterruptHandler();
    }
    IOCCFbits.IOCCF5 = 0;
}

/**
  Allows selecting an interrupt handler for INT2_Client at application runtime
*/
void INT2_Client_SetInterruptHandler(void (* InterruptHandler)(void)){
    INT2_Client_InterruptHandler = InterruptHandler;
}

/**
  Default interrupt handler for INT2_Client
*/
void INT2_Client_DefaultInterruptHandler(void){
    // add your INT2_Client interrupt custom code
    // or set custom function using INT2_Client_SetInterruptHandler()
}
/**
 End of File
*/