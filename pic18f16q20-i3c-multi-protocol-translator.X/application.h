/* Microchip Technology Inc. and its subsidiaries.  You may use this software 
 * and any derivatives exclusively with Microchip products. 
 * 
 * THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS".  NO WARRANTIES, WHETHER 
 * EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED 
 * WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS FOR A 
 * PARTICULAR PURPOSE, OR ITS INTERACTION WITH MICROCHIP PRODUCTS, COMBINATION 
 * WITH ANY OTHER PRODUCTS, OR USE IN ANY APPLICATION. 
 *
 * IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
 * INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND 
 * WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS 
 * BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE.  TO THE 
 * FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS 
 * IN ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF 
 * ANY, THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.
 *
 * MICROCHIP PROVIDES THIS SOFTWARE CONDITIONALLY UPON YOUR ACCEPTANCE OF THESE 
 * TERMS. 
 */

// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef APPLICATION_H
#define	APPLICATION_H

#include <xc.h> // include processor files - each processor file is guarded.  
#include <stdbool.h>
#include "mcc_generated_files/i2c_host/i2c_host_types.h"
#include "mcc_generated_files/i3c_target/i3c_target_types.h"
#define MAX_DATA_SIZE_IN_I2C_SPI_BUS (500U)
#define FUNCTION_ID_SIZE (1U)  
#define I2C_ADDRESS_SIZE (1U)

enum COMMAND_ID
{
    I2C_CLIENT_ID = 0b000,
    UART1_DEVICE_ID = 0b01,
    UART2_DEVICE_ID = 0b10,
    UART_INCORRECT_DEVICE_ID = 0b11,
    READ_COMMAND_ID = 0b01,
    WRITE_COMMAND_ID = 0b10,
    CLIENT_RESET_COMMAND_ID = 0b11,
    RESERVED_COMMAND_ID = 0b00,
};

enum APP_STATE
{
    APP_INIT,
    EVENT_EXECUTE,
};

enum COMMAND_INDEX
{
    FUNCTION_ID_INDEX = 0,
    I2C_ADDRESS_INDEX = 1,
    SPI_READ_BUFFER_SIZE_HIGH_INDEX = 1,
    SPI_READ_BUFFER_SIZE_LOW_INDEX = 2,
    CLIENT_RESET_PIN_INDEX = 1,
    I2C_READ_BUFFER_SIZE_HIGH_INDEX = 2,
    I2C_READ_BUFFER_SIZE_LOW_INDEX = 3,
    UART_READ_STOP_BYTE_INDEX = 1
};

enum CONTROLLER_COMMAND
{
    I2C_WRITE_COMMAND,
    I2C_READ_COMMAND,
    UART_WRITE_COMMAND,
    UART_READ_COMMAND,
    SPI_WRITE_COMMAND,
    SPI_READ_COMMAND,
    CLIENT_RESET_COMMAND,
    INCORRECT_COMMAND
};

enum ERROR_CODES
{
    I2C_BUS_TIMEOUT_ERROR_CODE = 0x1,
    I2C_READ_WRITE_TIMEOUT_ERROR_CODE = 0x2,
    I2C_ADDR_NACK_ERROR_CODE = 0x3,
    I2C_CODE_DATA_NACK_ERROR = 0x4,
    I2C_BUS_COLLISION_ERROR_CODE = 0x5,
};

enum CONTROLLER_COMMAND DecodeCommand(uint8_t functionID);
void ExecuteI2CWriteCommand(uint8_t clientAddress, uint8_t *writeData, uint16_t writeLength);
void ExecuteI2CReadCommand(uint8_t clientAddress, uint8_t readDataLengthHigh, uint8_t readDataLengthLow);
void ExecuteSPIWriteCommand(uint8_t functionID, uint8_t *writeData, uint16_t writeLength);
void ExecuteSPIReadCommand(uint8_t functionID, uint8_t readDataLengthHigh, uint8_t readDataLengthLow);
void ExecuteUARTWriteCommand(uint8_t functionID, uint8_t *writeData, uint16_t writeLength);
void ExecuteUARTReadCommand(uint8_t functionID, uint8_t stopByteCommandValue);
void ExecuteClientResetCommand(uint8_t resetPinNumber);
void ExecuteResetAction(void);
void SendAlertFromClient(uint8_t intPinNumber);
void IBIErrorHandling(enum I3C_TARGET_IBI_REQUEST_ERROR ibiError);
void ErrorReporting(i2c_host_error_t i2cErrorStatus);
void UARTProtocolRxBufferProcessing(void);
void SPI1_TxCompleteUserInterruptHandler(void);
void SPI1_RxCompleteUserInterruptHandler(void);

void debugPrinter(char* format, ...);


#endif	/* APPLICATION_H */

