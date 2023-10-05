/**
 * Generated Pins header File
 * 
 * @file pins.h
 * 
 * @defgroup  pinsdriver Pins Driver
 * 
 * @brief This is generated driver header for pins. 
 *        This header file provides APIs for all pins selected in the GUI.
 *
 * @version Driver Version  3.1.0
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

#ifndef PINS_H
#define PINS_H

#include <xc.h>

#define INPUT   1
#define OUTPUT  0

#define HIGH    1
#define LOW     0

#define ANALOG      1
#define DIGITAL     0

#define PULL_UP_ENABLED      1
#define PULL_UP_DISABLED     0

// get/set RA0 aliases
#define RST1_TRIS                 TRISAbits.TRISA0
#define RST1_LAT                  LATAbits.LATA0
#define RST1_PORT                 PORTAbits.RA0
#define RST1_WPU                  WPUAbits.WPUA0
#define RST1_OD                   ODCONAbits.ODCA0
#define RST1_ANS                  ANSELAbits.ANSELA0
#define RST1_SetHigh()            do { LATAbits.LATA0 = 1; } while(0)
#define RST1_SetLow()             do { LATAbits.LATA0 = 0; } while(0)
#define RST1_Toggle()             do { LATAbits.LATA0 = ~LATAbits.LATA0; } while(0)
#define RST1_GetValue()           PORTAbits.RA0
#define RST1_SetDigitalInput()    do { TRISAbits.TRISA0 = 1; } while(0)
#define RST1_SetDigitalOutput()   do { TRISAbits.TRISA0 = 0; } while(0)
#define RST1_SetPullup()          do { WPUAbits.WPUA0 = 1; } while(0)
#define RST1_ResetPullup()        do { WPUAbits.WPUA0 = 0; } while(0)
#define RST1_SetPushPull()        do { ODCONAbits.ODCA0 = 0; } while(0)
#define RST1_SetOpenDrain()       do { ODCONAbits.ODCA0 = 1; } while(0)
#define RST1_SetAnalogMode()      do { ANSELAbits.ANSELA0 = 1; } while(0)
#define RST1_SetDigitalMode()     do { ANSELAbits.ANSELA0 = 0; } while(0)

// get/set RA1 aliases
#define INT1_Client_TRIS                 TRISAbits.TRISA1
#define INT1_Client_LAT                  LATAbits.LATA1
#define INT1_Client_PORT                 PORTAbits.RA1
#define INT1_Client_WPU                  WPUAbits.WPUA1
#define INT1_Client_OD                   ODCONAbits.ODCA1
#define INT1_Client_ANS                  ANSELAbits.ANSELA1
#define INT1_Client_SetHigh()            do { LATAbits.LATA1 = 1; } while(0)
#define INT1_Client_SetLow()             do { LATAbits.LATA1 = 0; } while(0)
#define INT1_Client_Toggle()             do { LATAbits.LATA1 = ~LATAbits.LATA1; } while(0)
#define INT1_Client_GetValue()           PORTAbits.RA1
#define INT1_Client_SetDigitalInput()    do { TRISAbits.TRISA1 = 1; } while(0)
#define INT1_Client_SetDigitalOutput()   do { TRISAbits.TRISA1 = 0; } while(0)
#define INT1_Client_SetPullup()          do { WPUAbits.WPUA1 = 1; } while(0)
#define INT1_Client_ResetPullup()        do { WPUAbits.WPUA1 = 0; } while(0)
#define INT1_Client_SetPushPull()        do { ODCONAbits.ODCA1 = 0; } while(0)
#define INT1_Client_SetOpenDrain()       do { ODCONAbits.ODCA1 = 1; } while(0)
#define INT1_Client_SetAnalogMode()      do { ANSELAbits.ANSELA1 = 1; } while(0)
#define INT1_Client_SetDigitalMode()     do { ANSELAbits.ANSELA1 = 0; } while(0)
#define RA1_SetInterruptHandler  INT1_Client_SetInterruptHandler

// get/set RA2 aliases
#define RST2_TRIS                 TRISAbits.TRISA2
#define RST2_LAT                  LATAbits.LATA2
#define RST2_PORT                 PORTAbits.RA2
#define RST2_WPU                  WPUAbits.WPUA2
#define RST2_OD                   ODCONAbits.ODCA2
#define RST2_ANS                  ANSELAbits.ANSELA2
#define RST2_SetHigh()            do { LATAbits.LATA2 = 1; } while(0)
#define RST2_SetLow()             do { LATAbits.LATA2 = 0; } while(0)
#define RST2_Toggle()             do { LATAbits.LATA2 = ~LATAbits.LATA2; } while(0)
#define RST2_GetValue()           PORTAbits.RA2
#define RST2_SetDigitalInput()    do { TRISAbits.TRISA2 = 1; } while(0)
#define RST2_SetDigitalOutput()   do { TRISAbits.TRISA2 = 0; } while(0)
#define RST2_SetPullup()          do { WPUAbits.WPUA2 = 1; } while(0)
#define RST2_ResetPullup()        do { WPUAbits.WPUA2 = 0; } while(0)
#define RST2_SetPushPull()        do { ODCONAbits.ODCA2 = 0; } while(0)
#define RST2_SetOpenDrain()       do { ODCONAbits.ODCA2 = 1; } while(0)
#define RST2_SetAnalogMode()      do { ANSELAbits.ANSELA2 = 1; } while(0)
#define RST2_SetDigitalMode()     do { ANSELAbits.ANSELA2 = 0; } while(0)

// get/set RA4 aliases
#define CS1_TRIS                 TRISAbits.TRISA4
#define CS1_LAT                  LATAbits.LATA4
#define CS1_PORT                 PORTAbits.RA4
#define CS1_WPU                  WPUAbits.WPUA4
#define CS1_OD                   ODCONAbits.ODCA4
#define CS1_ANS                  ANSELAbits.ANSELA4
#define CS1_SetHigh()            do { LATAbits.LATA4 = 1; } while(0)
#define CS1_SetLow()             do { LATAbits.LATA4 = 0; } while(0)
#define CS1_Toggle()             do { LATAbits.LATA4 = ~LATAbits.LATA4; } while(0)
#define CS1_GetValue()           PORTAbits.RA4
#define CS1_SetDigitalInput()    do { TRISAbits.TRISA4 = 1; } while(0)
#define CS1_SetDigitalOutput()   do { TRISAbits.TRISA4 = 0; } while(0)
#define CS1_SetPullup()          do { WPUAbits.WPUA4 = 1; } while(0)
#define CS1_ResetPullup()        do { WPUAbits.WPUA4 = 0; } while(0)
#define CS1_SetPushPull()        do { ODCONAbits.ODCA4 = 0; } while(0)
#define CS1_SetOpenDrain()       do { ODCONAbits.ODCA4 = 1; } while(0)
#define CS1_SetAnalogMode()      do { ANSELAbits.ANSELA4 = 1; } while(0)
#define CS1_SetDigitalMode()     do { ANSELAbits.ANSELA4 = 0; } while(0)

// get/set RA5 aliases
#define SCK_TRIS                 TRISAbits.TRISA5
#define SCK_LAT                  LATAbits.LATA5
#define SCK_PORT                 PORTAbits.RA5
#define SCK_WPU                  WPUAbits.WPUA5
#define SCK_OD                   ODCONAbits.ODCA5
#define SCK_ANS                  ANSELAbits.ANSELA5
#define SCK_SetHigh()            do { LATAbits.LATA5 = 1; } while(0)
#define SCK_SetLow()             do { LATAbits.LATA5 = 0; } while(0)
#define SCK_Toggle()             do { LATAbits.LATA5 = ~LATAbits.LATA5; } while(0)
#define SCK_GetValue()           PORTAbits.RA5
#define SCK_SetDigitalInput()    do { TRISAbits.TRISA5 = 1; } while(0)
#define SCK_SetDigitalOutput()   do { TRISAbits.TRISA5 = 0; } while(0)
#define SCK_SetPullup()          do { WPUAbits.WPUA5 = 1; } while(0)
#define SCK_ResetPullup()        do { WPUAbits.WPUA5 = 0; } while(0)
#define SCK_SetPushPull()        do { ODCONAbits.ODCA5 = 0; } while(0)
#define SCK_SetOpenDrain()       do { ODCONAbits.ODCA5 = 1; } while(0)
#define SCK_SetAnalogMode()      do { ANSELAbits.ANSELA5 = 1; } while(0)
#define SCK_SetDigitalMode()     do { ANSELAbits.ANSELA5 = 0; } while(0)

// get/set RB5 aliases
#define IO_RB5_TRIS                 TRISBbits.TRISB5
#define IO_RB5_LAT                  LATBbits.LATB5
#define IO_RB5_PORT                 PORTBbits.RB5
#define IO_RB5_WPU                  WPUBbits.WPUB5
#define IO_RB5_OD                   ODCONBbits.ODCB5
#define IO_RB5_ANS                  ANSELBbits.
#define IO_RB5_SetHigh()            do { LATBbits.LATB5 = 1; } while(0)
#define IO_RB5_SetLow()             do { LATBbits.LATB5 = 0; } while(0)
#define IO_RB5_Toggle()             do { LATBbits.LATB5 = ~LATBbits.LATB5; } while(0)
#define IO_RB5_GetValue()           PORTBbits.RB5
#define IO_RB5_SetDigitalInput()    do { TRISBbits.TRISB5 = 1; } while(0)
#define IO_RB5_SetDigitalOutput()   do { TRISBbits.TRISB5 = 0; } while(0)
#define IO_RB5_SetPullup()          do { WPUBbits.WPUB5 = 1; } while(0)
#define IO_RB5_ResetPullup()        do { WPUBbits.WPUB5 = 0; } while(0)
#define IO_RB5_SetPushPull()        do { ODCONBbits.ODCB5 = 0; } while(0)
#define IO_RB5_SetOpenDrain()       do { ODCONBbits.ODCB5 = 1; } while(0)
#define IO_RB5_SetAnalogMode()      do { ANSELBbits. = 1; } while(0)
#define IO_RB5_SetDigitalMode()     do { ANSELBbits. = 0; } while(0)

// get/set RB6 aliases
#define IO_RB6_TRIS                 TRISBbits.TRISB6
#define IO_RB6_LAT                  LATBbits.LATB6
#define IO_RB6_PORT                 PORTBbits.RB6
#define IO_RB6_WPU                  WPUBbits.WPUB6
#define IO_RB6_OD                   ODCONBbits.ODCB6
#define IO_RB6_ANS                  ANSELBbits.
#define IO_RB6_SetHigh()            do { LATBbits.LATB6 = 1; } while(0)
#define IO_RB6_SetLow()             do { LATBbits.LATB6 = 0; } while(0)
#define IO_RB6_Toggle()             do { LATBbits.LATB6 = ~LATBbits.LATB6; } while(0)
#define IO_RB6_GetValue()           PORTBbits.RB6
#define IO_RB6_SetDigitalInput()    do { TRISBbits.TRISB6 = 1; } while(0)
#define IO_RB6_SetDigitalOutput()   do { TRISBbits.TRISB6 = 0; } while(0)
#define IO_RB6_SetPullup()          do { WPUBbits.WPUB6 = 1; } while(0)
#define IO_RB6_ResetPullup()        do { WPUBbits.WPUB6 = 0; } while(0)
#define IO_RB6_SetPushPull()        do { ODCONBbits.ODCB6 = 0; } while(0)
#define IO_RB6_SetOpenDrain()       do { ODCONBbits.ODCB6 = 1; } while(0)
#define IO_RB6_SetAnalogMode()      do { ANSELBbits. = 1; } while(0)
#define IO_RB6_SetDigitalMode()     do { ANSELBbits. = 0; } while(0)

// get/set RB7 aliases
#define CS3_TRIS                 TRISBbits.TRISB7
#define CS3_LAT                  LATBbits.LATB7
#define CS3_PORT                 PORTBbits.RB7
#define CS3_WPU                  WPUBbits.WPUB7
#define CS3_OD                   ODCONBbits.ODCB7
#define CS3_ANS                  ANSELBbits.ANSELB7
#define CS3_SetHigh()            do { LATBbits.LATB7 = 1; } while(0)
#define CS3_SetLow()             do { LATBbits.LATB7 = 0; } while(0)
#define CS3_Toggle()             do { LATBbits.LATB7 = ~LATBbits.LATB7; } while(0)
#define CS3_GetValue()           PORTBbits.RB7
#define CS3_SetDigitalInput()    do { TRISBbits.TRISB7 = 1; } while(0)
#define CS3_SetDigitalOutput()   do { TRISBbits.TRISB7 = 0; } while(0)
#define CS3_SetPullup()          do { WPUBbits.WPUB7 = 1; } while(0)
#define CS3_ResetPullup()        do { WPUBbits.WPUB7 = 0; } while(0)
#define CS3_SetPushPull()        do { ODCONBbits.ODCB7 = 0; } while(0)
#define CS3_SetOpenDrain()       do { ODCONBbits.ODCB7 = 1; } while(0)
#define CS3_SetAnalogMode()      do { ANSELBbits.ANSELB7 = 1; } while(0)
#define CS3_SetDigitalMode()     do { ANSELBbits.ANSELB7 = 0; } while(0)

// get/set RC0 aliases
#define IO_RC0_TRIS                 TRISCbits.TRISC0
#define IO_RC0_LAT                  LATCbits.LATC0
#define IO_RC0_PORT                 PORTCbits.RC0
#define IO_RC0_WPU                  WPUCbits.WPUC0
#define IO_RC0_OD                   ODCONCbits.ODCC0
#define IO_RC0_ANS                  ANSELCbits.
#define IO_RC0_SetHigh()            do { LATCbits.LATC0 = 1; } while(0)
#define IO_RC0_SetLow()             do { LATCbits.LATC0 = 0; } while(0)
#define IO_RC0_Toggle()             do { LATCbits.LATC0 = ~LATCbits.LATC0; } while(0)
#define IO_RC0_GetValue()           PORTCbits.RC0
#define IO_RC0_SetDigitalInput()    do { TRISCbits.TRISC0 = 1; } while(0)
#define IO_RC0_SetDigitalOutput()   do { TRISCbits.TRISC0 = 0; } while(0)
#define IO_RC0_SetPullup()          do { WPUCbits.WPUC0 = 1; } while(0)
#define IO_RC0_ResetPullup()        do { WPUCbits.WPUC0 = 0; } while(0)
#define IO_RC0_SetPushPull()        do { ODCONCbits.ODCC0 = 0; } while(0)
#define IO_RC0_SetOpenDrain()       do { ODCONCbits.ODCC0 = 1; } while(0)
#define IO_RC0_SetAnalogMode()      do { ANSELCbits. = 1; } while(0)
#define IO_RC0_SetDigitalMode()     do { ANSELCbits. = 0; } while(0)

// get/set RC1 aliases
#define IO_RC1_TRIS                 TRISCbits.TRISC1
#define IO_RC1_LAT                  LATCbits.LATC1
#define IO_RC1_PORT                 PORTCbits.RC1
#define IO_RC1_WPU                  WPUCbits.WPUC1
#define IO_RC1_OD                   ODCONCbits.ODCC1
#define IO_RC1_ANS                  ANSELCbits.
#define IO_RC1_SetHigh()            do { LATCbits.LATC1 = 1; } while(0)
#define IO_RC1_SetLow()             do { LATCbits.LATC1 = 0; } while(0)
#define IO_RC1_Toggle()             do { LATCbits.LATC1 = ~LATCbits.LATC1; } while(0)
#define IO_RC1_GetValue()           PORTCbits.RC1
#define IO_RC1_SetDigitalInput()    do { TRISCbits.TRISC1 = 1; } while(0)
#define IO_RC1_SetDigitalOutput()   do { TRISCbits.TRISC1 = 0; } while(0)
#define IO_RC1_SetPullup()          do { WPUCbits.WPUC1 = 1; } while(0)
#define IO_RC1_ResetPullup()        do { WPUCbits.WPUC1 = 0; } while(0)
#define IO_RC1_SetPushPull()        do { ODCONCbits.ODCC1 = 0; } while(0)
#define IO_RC1_SetOpenDrain()       do { ODCONCbits.ODCC1 = 1; } while(0)
#define IO_RC1_SetAnalogMode()      do { ANSELCbits. = 1; } while(0)
#define IO_RC1_SetDigitalMode()     do { ANSELCbits. = 0; } while(0)

// get/set RC3 aliases
#define SD0_TRIS                 TRISCbits.TRISC3
#define SD0_LAT                  LATCbits.LATC3
#define SD0_PORT                 PORTCbits.RC3
#define SD0_WPU                  WPUCbits.WPUC3
#define SD0_OD                   ODCONCbits.ODCC3
#define SD0_ANS                  ANSELCbits.ANSELC3
#define SD0_SetHigh()            do { LATCbits.LATC3 = 1; } while(0)
#define SD0_SetLow()             do { LATCbits.LATC3 = 0; } while(0)
#define SD0_Toggle()             do { LATCbits.LATC3 = ~LATCbits.LATC3; } while(0)
#define SD0_GetValue()           PORTCbits.RC3
#define SD0_SetDigitalInput()    do { TRISCbits.TRISC3 = 1; } while(0)
#define SD0_SetDigitalOutput()   do { TRISCbits.TRISC3 = 0; } while(0)
#define SD0_SetPullup()          do { WPUCbits.WPUC3 = 1; } while(0)
#define SD0_ResetPullup()        do { WPUCbits.WPUC3 = 0; } while(0)
#define SD0_SetPushPull()        do { ODCONCbits.ODCC3 = 0; } while(0)
#define SD0_SetOpenDrain()       do { ODCONCbits.ODCC3 = 1; } while(0)
#define SD0_SetAnalogMode()      do { ANSELCbits.ANSELC3 = 1; } while(0)
#define SD0_SetDigitalMode()     do { ANSELCbits.ANSELC3 = 0; } while(0)

// get/set RC4 aliases
#define IO_RC4_TRIS                 TRISCbits.TRISC4
#define IO_RC4_LAT                  LATCbits.LATC4
#define IO_RC4_PORT                 PORTCbits.RC4
#define IO_RC4_WPU                  WPUCbits.WPUC4
#define IO_RC4_OD                   ODCONCbits.ODCC4
#define IO_RC4_ANS                  ANSELCbits.ANSELC4
#define IO_RC4_SetHigh()            do { LATCbits.LATC4 = 1; } while(0)
#define IO_RC4_SetLow()             do { LATCbits.LATC4 = 0; } while(0)
#define IO_RC4_Toggle()             do { LATCbits.LATC4 = ~LATCbits.LATC4; } while(0)
#define IO_RC4_GetValue()           PORTCbits.RC4
#define IO_RC4_SetDigitalInput()    do { TRISCbits.TRISC4 = 1; } while(0)
#define IO_RC4_SetDigitalOutput()   do { TRISCbits.TRISC4 = 0; } while(0)
#define IO_RC4_SetPullup()          do { WPUCbits.WPUC4 = 1; } while(0)
#define IO_RC4_ResetPullup()        do { WPUCbits.WPUC4 = 0; } while(0)
#define IO_RC4_SetPushPull()        do { ODCONCbits.ODCC4 = 0; } while(0)
#define IO_RC4_SetOpenDrain()       do { ODCONCbits.ODCC4 = 1; } while(0)
#define IO_RC4_SetAnalogMode()      do { ANSELCbits.ANSELC4 = 1; } while(0)
#define IO_RC4_SetDigitalMode()     do { ANSELCbits.ANSELC4 = 0; } while(0)

// get/set RC5 aliases
#define INT2_Client_TRIS                 TRISCbits.TRISC5
#define INT2_Client_LAT                  LATCbits.LATC5
#define INT2_Client_PORT                 PORTCbits.RC5
#define INT2_Client_WPU                  WPUCbits.WPUC5
#define INT2_Client_OD                   ODCONCbits.ODCC5
#define INT2_Client_ANS                  ANSELCbits.ANSELC5
#define INT2_Client_SetHigh()            do { LATCbits.LATC5 = 1; } while(0)
#define INT2_Client_SetLow()             do { LATCbits.LATC5 = 0; } while(0)
#define INT2_Client_Toggle()             do { LATCbits.LATC5 = ~LATCbits.LATC5; } while(0)
#define INT2_Client_GetValue()           PORTCbits.RC5
#define INT2_Client_SetDigitalInput()    do { TRISCbits.TRISC5 = 1; } while(0)
#define INT2_Client_SetDigitalOutput()   do { TRISCbits.TRISC5 = 0; } while(0)
#define INT2_Client_SetPullup()          do { WPUCbits.WPUC5 = 1; } while(0)
#define INT2_Client_ResetPullup()        do { WPUCbits.WPUC5 = 0; } while(0)
#define INT2_Client_SetPushPull()        do { ODCONCbits.ODCC5 = 0; } while(0)
#define INT2_Client_SetOpenDrain()       do { ODCONCbits.ODCC5 = 1; } while(0)
#define INT2_Client_SetAnalogMode()      do { ANSELCbits.ANSELC5 = 1; } while(0)
#define INT2_Client_SetDigitalMode()     do { ANSELCbits.ANSELC5 = 0; } while(0)
#define RC5_SetInterruptHandler  INT2_Client_SetInterruptHandler

// get/set RC6 aliases
#define SDI_TRIS                 TRISCbits.TRISC6
#define SDI_LAT                  LATCbits.LATC6
#define SDI_PORT                 PORTCbits.RC6
#define SDI_WPU                  WPUCbits.WPUC6
#define SDI_OD                   ODCONCbits.ODCC6
#define SDI_ANS                  ANSELCbits.ANSELC6
#define SDI_SetHigh()            do { LATCbits.LATC6 = 1; } while(0)
#define SDI_SetLow()             do { LATCbits.LATC6 = 0; } while(0)
#define SDI_Toggle()             do { LATCbits.LATC6 = ~LATCbits.LATC6; } while(0)
#define SDI_GetValue()           PORTCbits.RC6
#define SDI_SetDigitalInput()    do { TRISCbits.TRISC6 = 1; } while(0)
#define SDI_SetDigitalOutput()   do { TRISCbits.TRISC6 = 0; } while(0)
#define SDI_SetPullup()          do { WPUCbits.WPUC6 = 1; } while(0)
#define SDI_ResetPullup()        do { WPUCbits.WPUC6 = 0; } while(0)
#define SDI_SetPushPull()        do { ODCONCbits.ODCC6 = 0; } while(0)
#define SDI_SetOpenDrain()       do { ODCONCbits.ODCC6 = 1; } while(0)
#define SDI_SetAnalogMode()      do { ANSELCbits.ANSELC6 = 1; } while(0)
#define SDI_SetDigitalMode()     do { ANSELCbits.ANSELC6 = 0; } while(0)

// get/set RC7 aliases
#define CS2_TRIS                 TRISCbits.TRISC7
#define CS2_LAT                  LATCbits.LATC7
#define CS2_PORT                 PORTCbits.RC7
#define CS2_WPU                  WPUCbits.WPUC7
#define CS2_OD                   ODCONCbits.ODCC7
#define CS2_ANS                  ANSELCbits.ANSELC7
#define CS2_SetHigh()            do { LATCbits.LATC7 = 1; } while(0)
#define CS2_SetLow()             do { LATCbits.LATC7 = 0; } while(0)
#define CS2_Toggle()             do { LATCbits.LATC7 = ~LATCbits.LATC7; } while(0)
#define CS2_GetValue()           PORTCbits.RC7
#define CS2_SetDigitalInput()    do { TRISCbits.TRISC7 = 1; } while(0)
#define CS2_SetDigitalOutput()   do { TRISCbits.TRISC7 = 0; } while(0)
#define CS2_SetPullup()          do { WPUCbits.WPUC7 = 1; } while(0)
#define CS2_ResetPullup()        do { WPUCbits.WPUC7 = 0; } while(0)
#define CS2_SetPushPull()        do { ODCONCbits.ODCC7 = 0; } while(0)
#define CS2_SetOpenDrain()       do { ODCONCbits.ODCC7 = 1; } while(0)
#define CS2_SetAnalogMode()      do { ANSELCbits.ANSELC7 = 1; } while(0)
#define CS2_SetDigitalMode()     do { ANSELCbits.ANSELC7 = 0; } while(0)

/**
 * @ingroup  pinsdriver
 * @brief GPIO and peripheral I/O initialization
 * @param none
 * @return none
 */
void PIN_MANAGER_Initialize (void);

/**
 * @ingroup  pinsdriver
 * @brief Interrupt on Change Handling routine
 * @param none
 * @return none
 */
void PIN_MANAGER_IOC(void);

/**
 * @ingroup  pinsdriver
 * @brief Interrupt on Change Handler for the INT1_Client pin functionality
 * @param none
 * @return none
 */
void INT1_Client_ISR(void);

/**
 * @ingroup  pinsdriver
 * @brief Interrupt Handler Setter for INT1_Client pin interrupt-on-change functionality.
 *        Allows selecting an interrupt handler for INT1_Client at application runtime
 * @pre Pins intializer called
 * @param InterruptHandler function pointer.
 * @return none
 */
void INT1_Client_SetInterruptHandler(void (* InterruptHandler)(void));

/**
 * @ingroup  pinsdriver
 * @brief Dynamic Interrupt Handler for INT1_Client pin.
 *        This is a dynamic interrupt handler to be used together with the INT1_Client_SetInterruptHandler() method.
 *        This handler is called every time the INT1_Client ISR is executed and allows any function to be registered at runtime.
 * @pre Pins intializer called
 * @param none
 * @return none
 */
extern void (*INT1_Client_InterruptHandler)(void);

/**
 * @ingroup  pinsdriver
 * @brief Default Interrupt Handler for INT1_Client pin. 
 *        This is a predefined interrupt handler to be used together with the INT1_Client_SetInterruptHandler() method.
 *        This handler is called every time the INT1_Client ISR is executed. 
 * @pre Pins intializer called
 * @param none
 * @return none
 */
void INT1_Client_DefaultInterruptHandler(void);

/**
 * @ingroup  pinsdriver
 * @brief Interrupt on Change Handler for the INT2_Client pin functionality
 * @param none
 * @return none
 */
void INT2_Client_ISR(void);

/**
 * @ingroup  pinsdriver
 * @brief Interrupt Handler Setter for INT2_Client pin interrupt-on-change functionality.
 *        Allows selecting an interrupt handler for INT2_Client at application runtime
 * @pre Pins intializer called
 * @param InterruptHandler function pointer.
 * @return none
 */
void INT2_Client_SetInterruptHandler(void (* InterruptHandler)(void));

/**
 * @ingroup  pinsdriver
 * @brief Dynamic Interrupt Handler for INT2_Client pin.
 *        This is a dynamic interrupt handler to be used together with the INT2_Client_SetInterruptHandler() method.
 *        This handler is called every time the INT2_Client ISR is executed and allows any function to be registered at runtime.
 * @pre Pins intializer called
 * @param none
 * @return none
 */
extern void (*INT2_Client_InterruptHandler)(void);

/**
 * @ingroup  pinsdriver
 * @brief Default Interrupt Handler for INT2_Client pin. 
 *        This is a predefined interrupt handler to be used together with the INT2_Client_SetInterruptHandler() method.
 *        This handler is called every time the INT2_Client ISR is executed. 
 * @pre Pins intializer called
 * @param none
 * @return none
 */
void INT2_Client_DefaultInterruptHandler(void);


#endif // PINS_H
/**
 End of File
*/