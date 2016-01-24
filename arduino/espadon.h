/*
  SerialComm.h - Library for serial communications
  Created by David Hautbois.
  Released into the public domain.
*/
#ifndef espadon
#define espadon_h


/*
  A serial channel is activated by creating an instance of the SerialComm class passing
  a Stream object (hard or soft).

  The methods are:
    SerialComm - Class for sending and receiving messages.
    attach( command , function )  - Attaches a function to a command.
    check_reception() - Checks for incomings messages.
    getId( ) - Returns the message id of the incoming message.
               Used to return the ack to the current incoming message.
    sendMessage( command , ack , values ... ) - Send a message with the specified command and values.
                                                Set ack to true to received an ack.
                                                Return true if an ack has been received.
    sendAck( values... ) - Send an ack with values.
    getData(const char * , ... ) - Extract data from incoming message or ack.
                                   Return true if success
 */

#include "Arduino.h"

class ESPadon
{
  public:
	ESPadon( );
     
  private:
};

#endif
