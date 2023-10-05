/*
 * File:   application.c
 * Author: I62384
 *
 * Created on September 13, 2023, 8:28 AM
 */


#include <xc.h>
#include "application.h"
#include "mcc_generated_files/system/system.h"
#include <stdbool.h>
#include <stdarg.h>
#define IBI_PAYLOAD_BUFFER_SIZE (MAX_DATA_SIZE_IN_I2C_SPI_BUS)
#define SOFT_TIME_OUT_VALUE (40000U)
#define RESET_TIME_MS 100
#define CLIENT_ID_BIT_POSN 0
#define CLIENT_ID_BIT_MASK 0x07
#define CMD_ID_BIT_MASK (0x60)
#define CMD_ID_BIT_POSN 5
#define RESET_PINS_BIT_MASK 0x07

#define DEBUG_PRINT_ON 

uint8_t ibiPayloadBuffer[IBI_PAYLOAD_BUFFER_SIZE]; //Buffer to store data received in I2C/SPI Read and is send to the controller via IBI
uint8_t errorStatus[1]; //Buffer to store error status which is send to controller via Private Read 
uint8_t resetPinsSelect = 0;
static uint32_t count = 0; //Count for time-out in I2C Read/Write operations

static void CS1Select(void)
{
    CS1_SetLow();
}
static void CS2Select(void)
{
    CS2_SetLow();
}
static void CS3Select(void)
{
    CS3_SetLow();
}
static void CS1DeSelect(void)
{
    CS1_SetHigh();
}
static void CS2DeSelect(void)
{
    CS2_SetHigh();
}
static void CS3DeSelect(void)
{
    CS3_SetHigh();
}

static void RST1High(void)
{
    RST1_SetHigh();
}
static void RST2High(void)
{
    RST2_SetHigh();
}
static void RST1Low(void)
{
    RST1_SetLow();
}
static void RST2Low(void)
{
    RST2_SetLow();
}

static void (*CS_SetHigh[])(void) = {CS1DeSelect,CS2DeSelect,CS3DeSelect};
static void (*CS_SetLow[])(void) = {CS1Select,CS2Select,CS3Select};
static void (*RST_SetHigh[])(void) = {RST1High,RST2High};
static void (*RST_SetLow[])(void) = {RST1Low,RST2Low};

static void ClientSelect(uint8_t spiClientID)
{
    for(uint8_t i =0;spiClientID!=0;i++)
    {
        if(spiClientID & 0x1)
        {
           CS_SetLow[i](); 
        }
        spiClientID >>= 1;
    }
}
 
static void ClientDeselect(uint8_t spiClientID)
{
    for(uint8_t i =0;spiClientID!=0;i++)
    {
        if(spiClientID & 0x1)
        {
           CS_SetHigh[i](); 
        }
        spiClientID >>= 1;
    }
}

static void ResetPinSetHigh(uint8_t resetPin)
{
    for(uint8_t i =0;resetPin!=0;i++)
    {
        if(resetPin & 0x1)
        {
           RST_SetHigh[i](); 
        }
        resetPin >>= 1;
    }
}
static void ResetPinSetLow(uint8_t resetPin)
{
    for(uint8_t i =0;resetPin!=0;i++)
    {
        if(resetPin & 0x1)
        {
           RST_SetLow[i](); 
        }
        resetPin >>= 1;
    } 
}

enum CONTROLLER_COMMAND DecodeCommand(uint8_t functionID)
{
    enum COMMAND_ID commandIDValue = (functionID & CMD_ID_BIT_MASK)>>CMD_ID_BIT_POSN;
    uint8_t clientID = (functionID & CLIENT_ID_BIT_MASK)>>CLIENT_ID_BIT_POSN;
       
    if(commandIDValue == READ_COMMAND_ID)
    {
        if(clientID == I2C_CLIENT_ID)
        {
          return I2C_READ_COMMAND;
        }
        else 
        {
          return SPI_READ_COMMAND;
        }
    }
    else if(commandIDValue == WRITE_COMMAND_ID)
    {
        if(clientID == I2C_CLIENT_ID)
        {
          return I2C_WRITE_COMMAND;
        }
        else 
        {
          return SPI_WRITE_COMMAND;
        }
    }
    else if(commandIDValue == CLIENT_RESET_COMMAND_ID)
    {
        return CLIENT_RESET_COMMAND;
    }
    else
    {
        return INCORRECT_COMMAND;
    }
}

void ExecuteI2CWriteCommand(uint8_t clientAddress, uint8_t *writeData, uint8_t writeLength)
{
    bool i2cBusTimeOut = false;
    bool i2cWriteTimeOut = false;
    count = 0;
    i2c_host_error_t i2cErrorStatus;
    
    clientAddress = clientAddress >> 1;  // Right shifting to remove R/W bit from address header
    
    debugPrinter("I2C Write initiated \r\n");
    while(!(I2C1_Write(clientAddress,writeData,writeLength)))
    {
        count++;
        if(count > SOFT_TIME_OUT_VALUE)
        {
            i2cBusTimeOut = true;
            debugPrinter("[!] Timeout due to I2C Bus Busy\r\n");
            break;
        }
    }

    if (!i2cBusTimeOut) 
    {
        count = 0; 
        while (I2C1_IsBusy()) 
        {
            count++;
            if(count > SOFT_TIME_OUT_VALUE)
            {
                i2cWriteTimeOut = true;
                debugPrinter("[!] Timeout during I2C Write \r\n");
                break;
            }
        }
        if (!i2cWriteTimeOut) 
        {
            i2cErrorStatus = I2C1_Host.ErrorGet();
            if (i2cErrorStatus == I2C_ERROR_NONE)
            {
                debugPrinter("I2C Write successful \r\n");
            }
            else
            {
                ErrorReporting(i2cErrorStatus);
            }   
        }
        else
        {
            errorStatus[0] = 0x2;
            I3C2_BufferTransmit(errorStatus, 1);
        }
    }
    else
    {
        errorStatus[0] = 0x1;
        I3C2_BufferTransmit(errorStatus, 1);
    } 
}

void ExecuteI2CReadCommand(uint8_t clientAddress, uint8_t readDataLength)
{
    bool i2cBusTimeOut = false;
    bool i2cReadTimeOut = false;
    count = 0;
    enum I3C_TARGET_IBI_REQUEST_ERROR ibiError;
    i2c_host_error_t i2cErrorStatus;
    
    clientAddress = clientAddress >> 1;  // Right shifting to remove R/W bit from address header
    
    debugPrinter("I2C Read initiated \r\n");
    while(!I2C1_Read(clientAddress,ibiPayloadBuffer,readDataLength))
    {    
        count++;
        if(count > SOFT_TIME_OUT_VALUE)
        {
            i2cBusTimeOut = true;
            debugPrinter("[!] Timeout due to I2C Bus Busy\r\n");
            break;
        }
    }
    if (!i2cBusTimeOut) 
    {
        count = 0; 
        while (I2C1_IsBusy()) 
        {
            count++;
            if(count > SOFT_TIME_OUT_VALUE)
            {
                i2cReadTimeOut = true;
                debugPrinter("[!] Timeout during I2C Read \r\n");
                break;
            }
        }
        if (!i2cReadTimeOut) 
        {
            i2cErrorStatus = I2C1_Host.ErrorGet();
            if (i2cErrorStatus == I2C_ERROR_NONE)
            {
                debugPrinter("Data received in I2C Read\r\n");
                for (uint8_t i = 0; i < readDataLength; i++) 
                {
                    debugPrinter("%x \t", ibiPayloadBuffer[i]);
                }
                debugPrinter("\n");
                I3C2_IBIMandatoryDataByteSet(0x00);
                ibiError = I3C2_IBIRequest(ibiPayloadBuffer, readDataLength);
                IBIErrorHandling(ibiError);
            }
            else
            {
                ErrorReporting(i2cErrorStatus);
            }   
        }
        else
        {
            errorStatus[0] = I2C_READ_WRITE_TIMEOUT_ERROR_CODE;
            I3C2_BufferTransmit(errorStatus, 1);
        }
    }
    else
    {
        errorStatus[0] = I2C_BUS_TIMEOUT_ERROR_CODE;
        I3C2_BufferTransmit(errorStatus, 1);
    } 
}

void ExecuteSPIWriteCommand(uint8_t functionID, uint8_t *writeData, uint8_t writeLength)
{
    debugPrinter("SPI Write initiated\r\n");
    uint8_t spiClientID = (functionID & CLIENT_ID_BIT_MASK)>>CLIENT_ID_BIT_POSN;
    SPI1_Open(SPI1_DEFAULT);
    ClientSelect(spiClientID);
    SPI1_BufferWrite(writeData,writeLength);
    ClientDeselect(spiClientID);
    SPI1_Close();
    debugPrinter("SPI Write successful \r\n");
}

void ExecuteSPIReadCommand(uint8_t functionID, uint8_t readDataLength)
{
    debugPrinter("SPI Read initiated\r\n");
    enum I3C_TARGET_IBI_REQUEST_ERROR ibiError;
    uint8_t spiClientID = (functionID & CLIENT_ID_BIT_MASK)>>CLIENT_ID_BIT_POSN;
    SPI1_Open(SPI1_DEFAULT);
    ClientSelect(spiClientID);
    SPI1_BufferRead(ibiPayloadBuffer, readDataLength);
    ClientDeselect(spiClientID);
    SPI1_Close();
    debugPrinter("Data received in SPI Read\r\n");
    for (uint8_t i = 0; i < readDataLength; i++) 
    {
        debugPrinter("%x \t", ibiPayloadBuffer[i]);
    }
    debugPrinter("\n");
    I3C2_IBIMandatoryDataByteSet(0x00);
    ibiError = I3C2_IBIRequest(ibiPayloadBuffer, readDataLength);
    IBIErrorHandling(ibiError);
}

void ExecuteClientResetCommand(uint8_t resetPinNumber)
{
    resetPinsSelect = resetPinNumber & RESET_PINS_BIT_MASK;
}

void ExecuteResetAction(void)
{
    enum I3C_RESET_ACTION resetAction;
    
    resetAction = I3C2_ResetActionGetAndClear(); 
    
    if(resetAction == I3C_RESET_ACTION_NO_RESET)
    {
        debugPrinter("I3C_RESET_ACTION_NO_RESET\r\n");    
       
        debugPrinter("Resetting client devices \r\n");
        
        //Reset pin selected based on previous reset command received from controller
        ResetPinSetLow(resetPinsSelect);  
        __delay_ms(RESET_TIME_MS);  
        ResetPinSetHigh(resetPinsSelect);  
        
        //Clearing reset pin selection. Controller has to send command with reset pin number if a client has to be reset again
        resetPinsSelect = 0;
    }
    else if(resetAction == I3C_RESET_ACTION_RESET_PERIPHERAL)
    {
        debugPrinter("I3C_RESET_ACTION_RESET_PERIPHERAL\r\n");

        //Reset I3C2 peripheral
        I3C2_PeripheralReset();

        I3C2_Initialize();
        I3C2_HotJoinRequest();    
    }
    else if(resetAction == I3C_RESET_ACTION_RESET_WHOLE_TARGET)
    {
        debugPrinter("I3C_RESET_ACTION_RESET_WHOLE_TARGET\r\n");
   
        //Soft reset of microcontroller
        RESET();
    }
}

void SendAlertFromClient(uint8_t intPinNumber)
{
    enum I3C_TARGET_IBI_REQUEST_ERROR ibiError;
    I3C2_IBIMandatoryDataByteSet(intPinNumber);
    ibiError = I3C2_IBIRequest(NULL, 0);
    IBIErrorHandling(ibiError);
}

void IBIErrorHandling(enum I3C_TARGET_IBI_REQUEST_ERROR ibiStatusError) 
{
    if (ibiStatusError == I3C_TARGET_IBI_REQUEST_NOT_IN_I3C_MODE) 
    {
        debugPrinter("Target is not in I3C mode \r\n");
    }
    else if (ibiStatusError == I3C_TARGET_IBI_REQUEST_IBI_DISABLED_ON_BUS)
    {
        debugPrinter("IBI is not enabled on the bus \r\n");
    } 
    else if (ibiStatusError == I3C_TARGET_IBI_REQUEST_SEND_BUFFER_SIZE_EXCEEDED)
    {
        debugPrinter("Software buffer size exceeded \r\n");
    } 
    else if (ibiStatusError == I3C_TARGET_IBI_REQUEST_NO_ERROR) 
    {
        debugPrinter("No error during IBI request \r\n");
    }
}

void ErrorReporting(i2c_host_error_t i2cErrorStatus)
{
    if (i2cErrorStatus == I2C_ERROR_ADDR_NACK) 
    {
        errorStatus[0] = I2C_ADDR_NACK_ERROR_CODE;
        debugPrinter("Client returned Address NACK \r\n");
        I3C2_BufferTransmit(errorStatus, 1);
    } 
    else if (i2cErrorStatus == I2C_ERROR_DATA_NACK) 
    {
        errorStatus[0] = I2C_CODE_DATA_NACK_ERROR;
        debugPrinter("Client returned Data NACK \r\n");
        I3C2_BufferTransmit(errorStatus, 1);
    } 
    else if (i2cErrorStatus == I2C_ERROR_BUS_COLLISION) 
    {
        errorStatus[0] = I2C_BUS_COLLISION_ERROR_CODE;
        debugPrinter("Bus Collision Error\r\n");
        I3C2_BufferTransmit(errorStatus, 1);
    }
}

void debugPrinter(char* format, ...)
{
    
#ifdef DEBUG_PRINT_ON
    va_list argptr;
    va_start(argptr, format);
    vprintf(format , argptr);
    va_end(argptr);
#endif
}