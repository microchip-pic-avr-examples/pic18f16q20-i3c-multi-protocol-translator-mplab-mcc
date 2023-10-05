/**
 * I3C2 Generated Driver Source File
 * 
 * @file i3c2.c
 *            
 * @ingroup i3c_target_driver
 *            
 * @brief This file contains the API implementation for the I3C2 Target DMA driver.
 *            
 * @version I3C Target DMA Source Code Driver Version 1.0.0
 *
 * @version I3C Melody Peripheral Library (PLIB) Version 1.0.0
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

#include <xc.h>
#include "../i3c2.h"
#include "../../dma/dma1.h"
#include "../../dma/dma2.h"

/**  
 * @name Maximum data bytes supported in a DMA transaction.
 */
#define DMA_MAX_BYTES_PER_TRANSACTION (4095U)

static uint16_t I3C2_NumOfBytesReceivedGet(void);  
static void I3C2_RxDMA_DCNTI_Handler(void);
static void I3C2_ResetRxDMA(void);

// I3C2 Default Callback Handlers

static void (*I3C2_TransactionCompleteHandler)(struct I3C_TARGET_TRANSACTION_COMPLETE_STATUS *transactionCompleteStatus) = NULL;


static void (*I3C2_ResetPatternDetectedHandler)(void) = NULL;

static void (*I3C2_RxSoftwareBufferFullHandler)(void) = NULL;

static struct I3C_TARGET_TRANSACTION_COMPLETE_STATUS transactionCompleteStatus;

static volatile bool isI3C2RxSoftwareBufferFull = false;

void I3C2_Initialize(void)                                                  
{
	//Disable the module before setup
	I3C2CON0bits.EN = 0;
	
	// I3C SCL pin input buffer settings
	RB6FEATbits.I3CBUF = 5;
	// I3C SDA pin input buffer settings
	RB5FEATbits.I3CBUF = 5;
	
	// ACKPOS disabled; SASDRMD disabled; 
    I3C2CON1 = 0x0;
	// TXB 0x0; 
    I3C2TXB = 0x0;
	// RNW target idle or writing; RSTDET not detected; 
    I3C2STAT0 = 0x0;
	// TE0ERR error not detected; TE1ERR error not detected; TE2ERR error not detected; TE3ERR error not detected; TE4ERR error not detected; TE5ERR error not detected; TE6ERR error not detected; 
    I3C2BSTAT = 0x0;
	// SCCCIF disabled; BTFIF Byte transfer not finished; DADRIF Dynamic address not matched; SADRIF Static address match not detected; I2CACKIF Acknowledge not received; RSCIF Restart condition not detected; PCIF Stop condition not detected; SCIF Start condition not detected; 
    I3C2PIR0 = 0x0;
	// IBIDONEIF Transmission not completed; DACHIF not cleared; TCOMPIF Transmission not completed; 
    I3C2PIR1 = 0x0;
	// UCCCIF Not received; BTOIF No error; BUSEIF No error; IBIEIF Not exceeded; HJEIF Not exceeded; RXOIF Overrun not occurred; TXUIF Underrun not occurred; I2CNACKIF No NACK/Error detected; 
    I3C2ERRIR0 = 0x0;
	// RXREIF Not occurred; TXWEIF Not occurred; MWLOEIF Not occurred; ABEIF not aborted; 
    I3C2ERRIR1 = 0x0;
	// BIDLL 0x0; 
    I3C2BIDLL = 0x0;
	// BIDLH 0x32; 
    I3C2BIDLH = 0x32;
	// BAVL 64; 
    I3C2BAVL = 0x40;
	// BTOL 0x0; 
    I3C2BTOL = 0x0;
	// BTOH 0xF; 
    I3C2BTOH = 0xF;
	// RETRY 3; 
    I3C2RETRY = 0x3;
	// HJCAP Capable; 
    I3C2FEAT = 0x1;
	// SADR 0x00; 
    I3C2SADR = 0x0;
	// MWLL 0x0; 
    I3C2MWLL = 0x0;
	// MWLH 0x0; 
    I3C2MWLH = 0x0;
	// MRLL 0x0; 
    I3C2MRLL = 0x0;
	// MRLH 0x0; 
    I3C2MRLH = 0x0;
	// IBIPSZ 0x0; 
    I3C2IBIPSZ = 0x0;
	// I3C2PID0 0; 
    I3C2PID0 = 0x0;
	// PID_11_8 0; PID_15_12 0; 
    I3C2PID1 = 0x0;
	// I3C2PID2 0; 
    I3C2PID2 = 0x0;
	// I3C2PID3 0; 
    I3C2PID3 = 0x0;
	// PID32 false; PID_39_33 0x4D; 
    I3C2PID4 = 0x9A;
	// I3C2PID5 6; 
    I3C2PID5 = 0x6;
	// DCR 0xC6; 
    I3C2DCR = 0xC6;
	// INTPEND No pending interrupt; ACTMODE 0x0; 
    I3C2DSTAT0 = 0x0;
	// VRSV 0x0; 
    I3C2DSTAT1 = 0x0;
	// MWS_2_0 FSCL max; MWS3 0x0; 
    I3C2MWS = 0x0;
	// MRS_2_0 FSCL max; MRS_5_3 8ns; MRS6 does not permits; 
    I3C2MRS = 0x0;
	// MRTL 0x0; 
    I3C2MRTL = 0x0;
	// MRTH 0x0; 
    I3C2MRTH = 0x0;
	// MRTU 0x0; 
    I3C2MRTU = 0x0;
	// RSTACT 0x0; 
    I3C2RSTACT = 0x0;
	// FLTEN disabled; SDAHT No hold time; 
    I3C2I2CCON = 0x0;
	// CLK Fosc; 
    I3C2CLK = 0x1;
	// BCR0 not limited; 
    I3C2BCR = 0x1E;
	// IBIMDB_4_0 0x0; IBIMDB_7_5 0x0; 
    I3C2IBIMDB = 0x0;

	
	// SCCCIE disabled; BTFIE disabled; DADRIE disabled; SADRIE disabled; I2CACKIE disabled; RSCIE disabled; PCIE disabled; SCIE disabled; 
	I3C2PIE0 = 0x0;
	// IBIDONEIE disabled; DACHIE disabled; TCOMPIE enabled; 
	I3C2PIE1 = 0x80;
	
	// UCCCIE disabled; BTOIE disabled; BUSEIE disabled; IBIEIE disabled; HJEIE disabled; RXOIE disabled; TXUIE disabled; I2CNACKIE disabled; 
	I3C2ERRIE0 = 0x00;
	// RXREIE disabled; TXWEIE disabled; MWLOEIE disabled; ABEIE disabled; 
	I3C2ERRIE1 = 0x00;
	
	// General interrupt enabled
    PIE9bits.I3C2IE = 1; 
	// Error interrupt disabled
	PIE9bits.I3C2EIE = 0;
	// Transmit interrupt disabled
	PIE9bits.I3C2TXIE = 0;	
	// Receive interrupt disabled
	PIE9bits.I3C2RXIE = 0;
	// Reset interrupt enabled
    PIE9bits.I3C2RIE = 1;
	
    DMA_I3C2_RX_DCNTIInterruptHandlerSet(I3C2_RxDMA_DCNTI_Handler);
	
	I3C2_TxBufferFIFOClear(); 
	I3C2_RxBufferFIFOClear(); 
	    
    // IBIREQ not initiated; HJREQ not initiated; ACKP Not Acknowledge; CLRTXB not initiated; CLRRXB not initiated; RST not initiated; BTOEN disabled; EN enabled; 
    I3C2CON0 = 0x84;
}

void I3C2_Enable(void)                                                      
{
	I3C2CON0bits.EN = 1;    
}

void I3C2_Disable(void)                                                     
{
	I3C2CON0bits.EN = 0; 
}

void I3C2_AllPrivateTransactionACK(void)                                          
{
	I3C2CON0bits.ACKP = 0;   
}

void I3C2_AllPrivateTransactionNACK(void)                                          
{
	I3C2CON0bits.ACKP = 1;      
}

void I3C2_NextPrivateTransactionACK(void)                                        
{
	I3C2CON1bits.ACKPOS = 1;  
}

uint16_t I3C2_MaxWriteLengthGet(void)                                     
{
    return I3C2MWL;  
}

void I3C2_MaxWriteLengthSet(uint16_t maxWriteLen)                         
{
    I3C2MWL = maxWriteLen; 
}

uint16_t I3C2_MaxReadLengthGet(void)                                      
{
    return I3C2MRL;  
}

void I3C2_MaxReadLengthSet(uint16_t maxReadLen)                         
{
    I3C2MRL = maxReadLen;
}

enum I3C_TARGET_BUFFER_RECEIVE_ERROR I3C2_BufferReceive(uint8_t *rxBuf, uint16_t len) 
{
    enum I3C_TARGET_BUFFER_RECEIVE_ERROR receiveRegisterError = I3C_TARGET_BUFFER_RECEIVE_NO_ERROR;
	
    if(len <= DMA_MAX_BYTES_PER_TRANSACTION)
    {           
		receiveRegisterError = I3C_TARGET_BUFFER_RECEIVE_NO_ERROR;             
        
		I3C2_RxBufferFIFOClear(); 
        isI3C2RxSoftwareBufferFull = false;
       
		// Set the application RX buffer as destination for DMA transfer
        DMA_I3C2_RX_Disable();
        DMA_I3C2_RX_DestinationAddressSet((uint16_t)rxBuf);
        DMA_I3C2_RX_DestinationSizeSet(len);
        DMA_I3C2_RX_Enable();
        
        DMA_I3C2_RX_TransferWithTriggerStart();
    }
    else
    {
        receiveRegisterError = I3C_TARGET_BUFFER_RECEIVE_BUFFER_SIZE_EXCEEDED;
    }
	
	return receiveRegisterError;
} 

enum I3C_TARGET_BUFFER_TRANSMIT_ERROR I3C2_BufferTransmit(uint8_t *txBuf, uint16_t len)   
{
	enum I3C_TARGET_BUFFER_TRANSMIT_ERROR sendError = I3C_TARGET_BUFFER_TRANSMIT_NO_ERROR;
	
    if(len <= DMA_MAX_BYTES_PER_TRANSACTION)
    {
		sendError = I3C_TARGET_BUFFER_TRANSMIT_NO_ERROR;
		
		I3C2_TxBufferFIFOClear(); 
       
		// Set the application TX buffer as source for DMA transfer
        DMA_I3C2_TX_Disable();
        DMA_I3C2_TX_SourceAddressSet((uint24_t)txBuf);
        DMA_I3C2_TX_SourceSizeSet(len);
        DMA_I3C2_TX_Enable();
        
        DMA_I3C2_TX_TransferWithTriggerStart();
    }
    else
    {
        sendError = I3C_TARGET_BUFFER_TRANSMIT_BUFFER_SIZE_EXCEEDED;
    }
	
	return sendError;
} 

uint8_t I3C2_ByteReceive(void)
{
    return I3C2RXB;
}

bool I3C2_IsTxFIFOEmpty(void)                                        
{
    return (!I3C2STAT1bits.TXFNE); 
}

bool I3C2_IsTxBufferEmpty(void)                                      
{
    return (I3C2STAT0bits.TXBE);
}

bool I3C2_IsRxBufferFull(void)                                       
{
    return (I3C2STAT0bits.RXBF); 
} 

void I3C2_TxBufferFIFOClear(void)                                    
{
    I3C2CON0bits.CLRTXB = 1;
}

void I3C2_RxBufferFIFOClear(void)                                   
{
    I3C2CON0bits.CLRRXB = 1;  
}

enum I3C_TARGET_HJ_REQUEST_ERROR I3C2_HotJoinRequest(void) 
{
    enum I3C_TARGET_HJ_REQUEST_ERROR status = I3C_TARGET_HJ_REQUEST_NO_ERROR;
    
    // If target is not Hot-Join capable
    if(!I3C2FEATbits.HJCAP)
    {
        status = I3C_TARGET_HJ_REQUEST_NOT_HJ_CAPABLE;
    }
	// If target already has a Dynamic Address assigned
    else if((I3C2_OperatingModeGet() ==  I3C_TARGET_OPERATING_MODE_I3C_SDR) 
	|| (I3C2_OperatingModeGet() ==  I3C_TARGET_OPERATING_MODE_I3C_HDR))
    {
        status =  I3C_TARGET_HJ_REQUEST_DYNAMIC_ADDRESS_ALREADY_ASSIGNED;
    }
	// If Hot-Join is not enabled on the bus
    else if (!I3C2ECbits.HJEN)
    {
        status = I3C_TARGET_HJ_REQUEST_HJ_DISABLED_ON_BUS;
    }
	// Request for Hot-Join
    else
    {
       I3C2CON0bits.HJREQ = 1; 
    }
	
    return status;
}

enum I3C_TARGET_HJ_STATUS  I3C2_HotJoinStatusGet(void)       
{
	enum I3C_TARGET_HJ_STATUS hotJoinStatus = I3C_TARGET_HJ_COMPLETED_OR_NOT_STARTED;
	
    if(I3C2CON0bits.HJREQ == 0)
    {
        hotJoinStatus = I3C_TARGET_HJ_COMPLETED_OR_NOT_STARTED;
    }
    else 
    {
        hotJoinStatus = I3C_TARGET_HJ_PENDING;
    }
	
	return hotJoinStatus;
}  

bool I3C2_IsHotJoinEnabledOnBus(void)                                      
{
    return (I3C2ECbits.HJEN);   
}

enum I3C_TARGET_IBI_REQUEST_ERROR I3C2_IBIRequest(uint8_t *payloadBuf, uint16_t payloadLen) 
{
    enum I3C_TARGET_IBI_REQUEST_ERROR status = I3C_TARGET_IBI_REQUEST_NO_ERROR;
    
    I3C2_TxBufferFIFOClear();
    
    if (I3C2_OperatingModeGet() != I3C_TARGET_OPERATING_MODE_I3C_SDR)
    {
      status = I3C_TARGET_IBI_REQUEST_NOT_IN_I3C_MODE;
    }
    else if(!I3C2ECbits.IBIEN)
    {
       status = I3C_TARGET_IBI_REQUEST_IBI_DISABLED_ON_BUS;
    }
	else if(payloadLen >= DMA_MAX_BYTES_PER_TRANSACTION)
    {
        status = I3C_TARGET_IBI_REQUEST_SEND_BUFFER_SIZE_EXCEEDED;
    }
	// Sends the payload after IBI request is enabled and mandatory byte is sent
    else 
    {
        status = I3C_TARGET_IBI_REQUEST_NO_ERROR;    
        
		if(payloadLen > 0U)
		{
			// Set the application TX buffer as source for DMA transfer
			DMA_I3C2_TX_Disable();
			DMA_I3C2_TX_SourceAddressSet((uint24_t)payloadBuf);
			DMA_I3C2_TX_SourceSizeSet(payloadLen);
			DMA_I3C2_TX_Enable();

			DMA_I3C2_TX_TransferWithTriggerStart();   
		}

        // Request IBI
        I3C2CON0bits.IBIREQ = 1;
    }  
	
    return status;
}

void I3C2_IBIPayloadSizeSet(uint8_t payloadLen)                         
{
    I3C2IBIPSZ = payloadLen;
}

uint8_t I3C2_IBIPayloadSizeGet(void)                                      
{
    return  I3C2IBIPSZ;
}

void I3C2_IBIMandatoryDataByteSet(uint8_t mdandatoryByte)                            
{
    I3C2IBIMDB = mdandatoryByte;
}

bool I3C2_IsIBIEnabledOnBus(void)                                      
{
    return (I3C2ECbits.IBIEN);  
}

void I3C2_BusTimeoutEnable(void)                                            
{
	I3C2CON0bits.BTOEN = 1;
}

void I3C2_BusTimeoutDisable(void)                                          
{
	I3C2CON0bits.BTOEN = 0;
    
}

enum I3C_CCC I3C2_LastCCCReceivedGet(void)          
{
	return (I3C2CCC);    
}

uint8_t I3C2_BusContextGet(void)                                            
{
	return (I3C2BUSCXT);  
}

enum I3C_TARGET_OPERATING_MODE I3C2_OperatingModeGet(void) 
{
    return (I3C2STAT0bits.OPMD);
}

bool I3C2_IsBusFree(void)                                                
{
    return (I3C2STAT0bits.BFREE);
}

uint8_t I3C2_BusErrorStatusGetAndClear(void)                                
{    
    uint8_t busErrorStatus = I3C2BSTAT;
    I3C2BSTAT = 0x00;
    return busErrorStatus;   
}

void I3C2_PeripheralReset(void)                                             
{
    I3C2CON0bits.RST = 1;
} 

enum I3C_RESET_ACTION I3C2_ResetActionGetAndClear(void) 
{
	uint8_t resetAction = I3C2RSTACT;
    I3C2RSTACT = I3C_RESET_ACTION_NO_ACTION_SET;
    return resetAction;   
}

void I3C2_TransactionCompleteCallbackRegister(void (*handler)(struct I3C_TARGET_TRANSACTION_COMPLETE_STATUS *transactionCompleteStatus))
{
    if(handler != NULL)
    {
        I3C2_TransactionCompleteHandler = handler;
    }
}

void I3C2_ResetPatternDetectedCallbackRegister(void (*handler)(void))
{
    if(handler != NULL)
    {
        I3C2_ResetPatternDetectedHandler = handler;
    }
}

void I3C2_RxSoftwareBufferFullCallbackRegister(void (*handler)(void))
{
    if(handler != NULL)
    {
        I3C2_RxSoftwareBufferFullHandler = handler;
    }  
}

void __interrupt(irq(IRQ_I3C2),base(8)) I3C2_General_ISR(void)
{
	if(I3C2PIR1bits.TCOMPIF == 1)
	{
		I3C2PIR1bits.TCOMPIF = 0;
		
		transactionCompleteStatus.numOfBytesReceived = I3C2_NumOfBytesReceivedGet();
        
        if (transactionCompleteStatus.numOfBytesReceived > 0U) 
        {
            //Last transaction was Private Write
            
            transactionCompleteStatus.dataFlowDirection = I3C_TARGET_DATA_RECEIVED;
            I3C2_ResetRxDMA();
        
        } 
        else
        {
            //Last transaction was Private Read or IBI
            
            transactionCompleteStatus.dataFlowDirection = I3C_TARGET_DATA_TRANSMITTED;
        }      
        
        I3C2_TransactionCompleteHandler(&transactionCompleteStatus);
	}
}

void __interrupt(irq(IRQ_I3C2R),base(8)) I3C2_Reset_ISR(void)
{		
	// Clear RSTDET bit to clear the RIF flag
	I3C2STAT0bits.RSTDET = 0;
	
	if(I3C2_ResetPatternDetectedHandler != NULL)
	{
		I3C2_ResetPatternDetectedHandler();
	}
}

void I3C2_Tasks(void)
{
}

static uint16_t I3C2_NumOfBytesReceivedGet(void)                           
{
	uint16_t NumOfBytesReceived = 0;
	
    if(!isI3C2RxSoftwareBufferFull)
	{
		NumOfBytesReceived = (DMA_I3C2_RX_DestinationSizeGet() - DMA_I3C2_RX_DestinationCountGet());
    }
    else
    {
        NumOfBytesReceived = DMA_I3C2_RX_DestinationSizeGet();
    } 
	
	return NumOfBytesReceived;
}

static void I3C2_RxDMA_DCNTI_Handler(void)
{ 
    isI3C2RxSoftwareBufferFull = true;
            
    if(I3C2_RxSoftwareBufferFullHandler != NULL)
    {
        I3C2_RxSoftwareBufferFullHandler();
    }
}

static void I3C2_ResetRxDMA(void)
{
    DMA_I3C2_RX_Disable();
    DMA_I3C2_RX_Enable();
	isI3C2RxSoftwareBufferFull = false;
}
/**
 End of File
*/