// ****************************************************************************************
// Copy Rights
// ***************************************************************************************

#ifndef SERIAL_IT_H
#define SERIAL_IT_H

//
// Includes
//

//
// Constants and macro definitions.
//

//
// Type definitions.
//

typedef enum HalSerialRxEvent_T
{
    /**< Data: new data available */
    HalSerialRxEventData = ( 1 << 0 ),
    /**< Idle: bus idle detected */
    HalSerialRxEventIdle = ( 1 << 1 ),
    /**< Framing Error: incorrect frame detected */
    HalSerialRxEventFrameError = ( 1 << 2 ),
    /**< Noise Error: noise on the line detected */
    HalSerialRxEventNoiseError = ( 1 << 3 ),
    /**< Overrun Error: no space for received data */
    HalSerialRxEventOverrunError = ( 1 << 4 ),
    /**< Parity Error: incorrect parity bit received */
    HalSerialRxEventParityError = ( 1 << 5 ),
}
HalSerialRxEvent_e;

//
// Globals.
//

//
// Public Prototypes.
//

void SerialItEnable( void );
void SerialItDisable( void );

void SerialItIrq( void );

#endif // SERIAL_IT_H
