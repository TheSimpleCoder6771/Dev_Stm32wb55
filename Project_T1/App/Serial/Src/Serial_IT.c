// ***************************************************************************************
// Copy Rights messsage
// ***************************************************************************************

//
// Include.
//

// This file's

#include "Serial_IT.h"

// Standard includes

// Sri includes

// Third Party Includes

#include <stm32wb55xx.h>
#include <stm32wbxx_ll_usart.h>

//
// Constatnts and Macro Definitions.
//

//
// Type defines.
//

//
// Private Prototype.
//

static void SerialItRxRcvdCb( void );

//
// File Globals.
//

//
// Public Function definitions.
//

// *****************************************************************************
// @brief This function enables the required interupts
//
// *****************************************************************************
void SerialItEnable( void )
{
    LL_USART_EnableIT_IDLE( USART1 );
    LL_USART_EnableIT_ERROR( USART1 );
    LL_USART_EnableIT_RXNE( USART1 );
}

// *****************************************************************************
// @brief This function disables the required interupts
//
// *****************************************************************************
void SerialItDisable( void )
{
    if ( LL_USART_IsEnabledIT_IDLE( USART1 ) )
    {
        LL_USART_DisableIT_IDLE( USART1 );
    }
    if ( LL_USART_IsEnabledIT_ERROR( USART1 ) )
    {
        LL_USART_DisableIT_ERROR( USART1 );
    }
    if ( LL_USART_IsEnabledIT_RXNE( USART1 ) )
    {
        LL_USART_DisableIT_RXNE( USART1 );
    }
}

// *****************************************************************************
// @brief
//
// *****************************************************************************
void SerialItIrq( void )
{
    HalSerialRxEvent_e event = 0;

    // Notification flags
    if ( USART1->ISR & USART_ISR_RXNE_RXFNE )
    {
        event |= HalSerialRxEventData;
        SerialItRxRcvdCb();
    }
    if ( USART1->ISR & USART_ISR_IDLE )
    {
        USART1->ICR = USART_ICR_IDLECF;
        event |= HalSerialRxEventIdle;
    }
    // Error flags
    if ( USART1->ISR & USART_ISR_ORE )
    {
        USART1->ICR = USART_ICR_ORECF;
        event |= HalSerialRxEventOverrunError;
    }
    if ( USART1->ISR & USART_ISR_NE )
    {
        USART1->ICR = USART_ICR_NECF;
        event |= HalSerialRxEventNoiseError;
    }
    if ( USART1->ISR & USART_ISR_FE )
    {
        USART1->ICR = USART_ICR_FECF;
        event |= HalSerialRxEventFrameError;
    }
    if ( USART1->ISR & USART_ISR_PE )
    {
        USART1->ICR = USART_ICR_PECF;
        event |= HalSerialRxEventParityError;
    }

}

//
// Private Function definitions.
//

// *****************************************************************************
// @brief Data Receive Callback Function.
//
// *****************************************************************************
void SerialItRxRcvdCb( void )
{
    uint8_t data = LL_USART_ReceiveData8( USART1 );

    if ( 'A' == data )
    {
        LL_USART_TransmitData8( USART1, data );
    }

}

//
// Debug Functions
//

//
// End
//
