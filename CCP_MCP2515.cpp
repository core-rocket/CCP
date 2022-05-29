#include "CCP_MCP2515.h"

int CCP_MCP2515::begin()
{
    while (MCP_CAN::begin(MCP_ANY, CAN_1000KBPS, MCP_16MHZ) != CAN_OK)
    {
        Serial.println("CAN: Init Fail!");
        delay(100);
    }
    MCP_CAN::setMode(MCP_NORMAL);
    return 0;
}

void CCP_MCP2515::read_device()
{
    MCP_CAN::readMsgBuf(&id, &len, msg.msg_byte);
}

byte CCP_MCP2515::write_device()
{
    byte sndStat = MCP_CAN::sendMsgBuf(id, 0, 8, msg.msg_byte);
    delayMicroseconds(500);
    return sndStat;
}