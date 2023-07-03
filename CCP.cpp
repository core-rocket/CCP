#include "Arduino.h"
#include "CCP.h"

/*
    if (id < 0x40)
    {
        // string
    }
    else if (id < 0x80)
    {
        // uint32
    }
    else if (id < 0xC0)
    {
        // float
    }
    else
    {
        // fp16
    }
*/

/*--CANtransfer--*/

byte CCP::byte_to_device(long unsigned int _id, byte _data_byte[8])
{
    id = _id;
    memcpy(msg.msg_byte, _data_byte, 8);
    return write_device();
}

byte CCP::string_to_device(long unsigned int _id, char *_string)
{
    id = _id;
    msg.string_msg.time16 = millis() / 1000;
    for (int i = 0; i < 6; i++)
    {
        msg.string_msg.string[i] = ' ';
    }
    for (int i = 0; i < 6; i++)
    {
        if (_string[i] <= 0x1f)
        {
            break;
        }
        msg.string_msg.string[i] = _string[i];
    }

    return write_device();
}

byte CCP::uint32_to_device(long unsigned int _id, uint32_t _data_uint32)
{
    id = _id;
    msg.uint32_msg.time32 = millis();
    msg.uint32_msg.data_uint32 = _data_uint32;

    return write_device();
}

byte CCP::uint16_to_device(long unsigned int _id, uint16_t _data_uint16_0, uint16_t _data_uint16_1, uint16_t _data_uint16_2)
{
    id = _id;
    msg.uint16_msg.time16 = millis() / 1000;
    msg.uint16_msg.data_uint16_0 = _data_uint16_0;
    msg.uint16_msg.data_uint16_1 = _data_uint16_1;
    msg.uint16_msg.data_uint16_2 = _data_uint16_2;

    return write_device();
}

byte CCP::float_to_device(long unsigned int _id, float _data_float)
{
    id = _id;
    msg.float_msg.time32 = millis();
    msg.float_msg.data_float = _data_float;

    return write_device();
}

byte CCP::fp16_to_device(long unsigned int _id, float _data_fp16_0, float _data_fp16_1, float _data_fp16_2)
{
    id = _id;
    msg.fp16_msg.time16 = millis() / 1000;
    float_to_fp16(msg.fp16_msg.data_fp16_0, _data_fp16_0);
    float_to_fp16(msg.fp16_msg.data_fp16_1, _data_fp16_1);
    float_to_fp16(msg.fp16_msg.data_fp16_2, _data_fp16_2);

    return write_device();
}

/*--receive,decode-*/

void CCP::string(char *str_buf, int str_len)
{
    int i = 0;
    for (; i < 6 && i < str_len - 1; i++)
    {
        str_buf[i] = msg.string_msg.string[i];
    }
    for (; i < str_len - 1; i++)
    {
        str_buf[i] = ' ';
    }
    str_buf[i + 1] = '\0';
}

bool CCP::str_match(char *str_to_cmp, int str_len)
{
    bool isMatch = true;
    for (int i = 0; i < str_len && i < 6; i++)
    {
        if (str_to_cmp[i] != msg.string_msg.string[i])
        {
            isMatch = false;
        }
    }
    return isMatch;
}

uint16_t CCP::time16()
{
    // time16 = time32 / 1000;
    return msg.string_msg.time16;
}
uint32_t CCP::time32()
{
    // time32 = time16 * 1000;
    return msg.uint32_msg.time32;
}
uint32_t CCP::data_uint32()
{
    return msg.uint32_msg.data_uint32;
}
uint16_t CCP::data_uint16_0()
{
    return msg.uint16_msg.data_uint16_0;
}
uint16_t CCP::data_uint16_1()
{
    return msg.uint16_msg.data_uint16_1;
}
uint16_t CCP::data_uint16_2()
{
    return msg.uint16_msg.data_uint16_2;
}
float CCP::data_float()
{
    return msg.float_msg.data_float;
}
float CCP::data_fp16_0()
{
    return fp16_to_float(msg.fp16_msg.data_fp16_0);
}
float CCP::data_fp16_1()
{
    return fp16_to_float(msg.fp16_msg.data_fp16_1);
}
float CCP::data_fp16_2()
{
    return fp16_to_float(msg.fp16_msg.data_fp16_2);
}
/*--float-fp16--*/
typedef union
{
    float fp32;
    byte fp32_byte[4];
} float_byte_union;

void CCP::float_to_fp16(byte fp16[2], float data_fp16)
{
    float_byte_union float_byte;
    float_byte.fp32 = data_fp16;
    // float_byte→fp16
    fp16[1] = (float_byte.fp32_byte[3] & 0b11000000) + ((float_byte.fp32_byte[3] & 0b00000111) << 3) + ((float_byte.fp32_byte[2] & 0b11100000) >> 5);
    fp16[0] = ((float_byte.fp32_byte[2] & 0b00011111) << 3) + ((float_byte.fp32_byte[1] & 0b11100000) >> 5);
}

float CCP::fp16_to_float(byte fp16[2])
{
    float_byte_union float_byte;
    float_byte.fp32_byte[3] = (fp16[1] & 0b11000000) + ((fp16[1] & 0b00111100) >> 3);
    float_byte.fp32_byte[2] = ((fp16[1] & 0b00000100) << 5) + ((fp16[1] & 0b00000011) << 5) + ((fp16[0] & 0b11111000) >> 3);
    float_byte.fp32_byte[1] = ((fp16[0] & 0b00000111) << 5);
    float_byte.fp32_byte[0] = 0;
    if (!(fp16[1] & 0b01000000))
    {
        float_byte.fp32_byte[3] += 0b00111000;
    }
    // mantissa0→exp0
    if (((fp16[1] | 0b11111100) == 0b11111100) && (fp16[0] == 0))
    {
        float_byte.fp32_byte[3] = (float_byte.fp32_byte[1] & 0b10000000);
        float_byte.fp32_byte[2] = (float_byte.fp32_byte[2] & 0b01111111);
    }
    return float_byte.fp32;
}
