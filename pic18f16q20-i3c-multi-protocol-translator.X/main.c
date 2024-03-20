 /*
 * MAIN Generated Driver File
 * 
 * @file main.c
 * 
 * @defgroup main MAIN
 * 
 * @brief This is the generated driver implementation file for the MAIN driver.
 *
 * @version MAIN Driver Version 1.0.0
*/

/*
© [2024] Microchip Technology Inc. and its subsidiaries.

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
#include "mcc_generated_files/system/system.h"
#include "application.h"
#define PRIVATE_WRITE_BUFFER_SIZE (MAX_DATA_SIZE_IN_I2C_SPI_BUS + FUNCTION_ID_SIZE  + I2C_ADDRESS_SIZE + 1) 

uint8_t receiveDataBuffer[PRIVATE_WRITE_BUFFER_SIZE]; //Buffer to store data received from the I3C controller
uint16_t numberOfBytesReceived;
volatile bool isDataReceived = false;
volatile bool isResetPatternDetected = false;
volatile bool isInterrupt1Received = false;
enum CONTROLLER_COMMAND commandReceived;
enum I3C_TARGET_HJ_REQUEST_ERROR hjRequestErrorState;

void ResetPatternDetectedCallback(void);
void INT_pin1_UserInterruptHandler(void);
void TransactionCompleteCallback(struct I3C_TARGET_TRANSACTION_COMPLETE_STATUS *transactionCompleteStatus);

/*
    Main application
*/

int main(void)
{
    enum APP_STATE currentState = APP_INIT;

    SYSTEM_Initialize();

    //Setting SPI SCK pin as output
    TRISAbits.TRISA5 = 0;
    
     //Register user custom callback
    I3C2_TransactionCompleteCallbackRegister(TransactionCompleteCallback); 
    I3C2_ResetPatternDetectedCallbackRegister(ResetPatternDetectedCallback);
    INT_pin1_SetInterruptHandler(INT_pin1_UserInterruptHandler);
    SPI1_Host.TxCompleteCallbackRegister(SPI1_TxCompleteUserInterruptHandler);
    SPI1_Host.RxCompleteCallbackRegister(SPI1_RxCompleteUserInterruptHandler);

    // If using interrupts in PIC18 High/Low Priority Mode you need to enable the Global High and Low Interrupts 
    // If using interrupts in PIC Mid-Range Compatibility Mode you need to enable the Global Interrupts 
    // Use the following macros to: 

    // Enable the Global Interrupts 
    //INTERRUPT_GlobalInterruptEnable(); 

    // Disable the Global Interrupts 
    //INTERRUPT_GlobalInterruptDisable(); 

    __delay_ms(1000);
    debugPrinter("*****Multi-Protocol Translator using I3C*****\r\n");
    
    while(1)
    {
        switch(currentState)
        {
            case APP_INIT:
                debugPrinter("Application Initialization \r\n");
                
                //Request for hot-Join
                hjRequestErrorState = I3C2_HotJoinRequest();
                debugPrinter("Status of Hot-Join Request: %u\r\n",hjRequestErrorState);
                
                debugPrinter("Waiting for Dynamic address to be assigned \r\n");
                while(I3C2_HotJoinStatusGet() == I3C_TARGET_HJ_PENDING);
                
                debugPrinter("Hot-Join completed \r\n");
                
                //Keeping application buffer ready to receive data from controller
                I3C2_BufferReceive(receiveDataBuffer,sizeof(receiveDataBuffer));
                I3C2_NextPrivateTransactionACK();
                
                currentState = EVENT_EXECUTE;
                break;
                
            case EVENT_EXECUTE:
                if(isDataReceived)
                {
                    isDataReceived = false;
                    
                    debugPrinter("Data received from Controller \r\n");        
                    commandReceived = DecodeCommand(receiveDataBuffer[FUNCTION_ID_INDEX]);
                    
                    switch(commandReceived)
                    {
                        case I2C_WRITE_COMMAND:      
                            debugPrinter("Command received : I2C Write \r\n");
                            ExecuteI2CWriteCommand(receiveDataBuffer[I2C_ADDRESS_INDEX],receiveDataBuffer+2,numberOfBytesReceived-2);
                            break;  
                            
                        case I2C_READ_COMMAND:
                            debugPrinter("Command received : I2C Read \r\n");
                            ExecuteI2CReadCommand(receiveDataBuffer[I2C_ADDRESS_INDEX],receiveDataBuffer[I2C_READ_BUFFER_SIZE_HIGH_INDEX],receiveDataBuffer[I2C_READ_BUFFER_SIZE_LOW_INDEX]);
                            break;
                            
                        case SPI_WRITE_COMMAND:                            
                            debugPrinter("Command received : SPI Write \r\n");
                            ExecuteSPIWriteCommand(receiveDataBuffer[FUNCTION_ID_INDEX],receiveDataBuffer+1,numberOfBytesReceived-1);
                            break;
                            
                        case SPI_READ_COMMAND:                           
                            debugPrinter("Command received : SPI Read \r\n");
                            ExecuteSPIReadCommand(receiveDataBuffer[FUNCTION_ID_INDEX],receiveDataBuffer[SPI_READ_BUFFER_SIZE_HIGH_INDEX], receiveDataBuffer[SPI_READ_BUFFER_SIZE_LOW_INDEX]);
                            break;
                            
                        case UART_WRITE_COMMAND:
                            debugPrinter("Command received : UART Write \r\n");
                            ExecuteUARTWriteCommand(receiveDataBuffer[FUNCTION_ID_INDEX],receiveDataBuffer+1,numberOfBytesReceived-1);
                            break;
                            
                        case UART_READ_COMMAND:
                            debugPrinter("Command received : UART Read \r\n");
                            ExecuteUARTReadCommand(receiveDataBuffer[FUNCTION_ID_INDEX],receiveDataBuffer[UART_READ_STOP_BYTE_INDEX]);
                            break;
                            
                        case CLIENT_RESET_COMMAND:
                            debugPrinter("Command Received : Reset Client Device \r\n");
                            ExecuteClientResetCommand(receiveDataBuffer[CLIENT_RESET_PIN_INDEX]);
                            break;
                            
                        case INCORRECT_COMMAND:
                            debugPrinter("Incorrect Command Received \r\n");
                            break;
                    }
                    //Setup to receive data in next private write transaction
                    I3C2_BufferReceive(receiveDataBuffer,sizeof(receiveDataBuffer)); 
                    I3C2_NextPrivateTransactionACK();
                    debugPrinter("Ready to receive next data\r\n\n");
                }
                if(isResetPatternDetected)
                {
                    isResetPatternDetected = false;
                    debugPrinter("Reset pattern detected \r\n\n");
                    ExecuteResetAction();
                    
                    //Setup to receive data in next private write transaction if I3C Target peripheral has been reset.
                    //RSTACT CCC (Direct CCC )from controller can clear ACKPOS in B0 silicon revision, hence enabling one-shot ACK.
                    I3C2_BufferReceive(receiveDataBuffer,sizeof(receiveDataBuffer)); 
                    I3C2_NextPrivateTransactionACK();
                    debugPrinter("Ready to receive next data\r\n\n");     
                }
                if(isInterrupt1Received)  // Checking if interrupts have occurred on any client devices
                {
                    SendAlertFromClient(0x01);
                    isInterrupt1Received = false;
                }
                if(UART_PROTOCOL_PORT.IsRxReady() == true)
                {
                    UARTProtocolRxBufferProcessing();    
                }
                break;
        }
    }    
}

void TransactionCompleteCallback(struct I3C_TARGET_TRANSACTION_COMPLETE_STATUS *transactionCompleteStatus)
{
    if(transactionCompleteStatus->dataFlowDirection == I3C_TARGET_DATA_RECEIVED)
    {
        isDataReceived = true;  
        numberOfBytesReceived = transactionCompleteStatus->numOfBytesReceived;
    }  
}

void ResetPatternDetectedCallback(void)
{
    isResetPatternDetected = true;
}

void INT_pin1_UserInterruptHandler(void)
{
    isInterrupt1Received = true;
}

