#ifndef CCP_MCP2515_H
#define CCP_MCP2515_H

#include "Arduino.h"

#include <CCP.h>
#include <mcp_can.h>
// https://github.com/coryjfowler/MCP_CAN_lib

class CCP_MCP2515 : public CCP, public MCP_CAN
{
public:
    CCP_MCP2515(uint8_t csPin, uint8_t intPin) : MCP_CAN((INT8U)csPin)
    {
        _csPin = csPin;   // chip select pin
        _intPin = intPin; // chip select pin
    }
    int begin();
    void read_device();
    byte write_device(); // return sndStat

protected:
    uint8_t _csPin;
    uint8_t _intPin;
    unsigned char len = 0;
};

#endif
