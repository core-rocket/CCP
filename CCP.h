#ifndef CCP_H
#define CCP_H

#include "CANID.h"
#include "Arduino.h"

typedef struct
{
    uint16_t time16;
    char string[6];
} string_msg_struct;

typedef struct
{
    uint32_t time32;
    uint32_t data_uint32;
} uint32_msg_struct;

typedef struct
{
    uint16_t time16;
    uint16_t data_uint16_0, data_uint16_1, data_uint16_2;
} uint16_msg_struct;

typedef struct
{
    uint32_t time32;
    float data_float;
} float_msg_struct;

typedef struct
{
    uint16_t time16;
    byte data_fp16_0[2], data_fp16_1[2], data_fp16_2[2];
} fp16_msg_struct;

typedef union
{
    uint32_t dummy[2]; //不整列アドレスを防ぐ
    uint8_t msg_byte[8];
    string_msg_struct string_msg;
    uint32_msg_struct uint32_msg;
    uint16_msg_struct uint16_msg;
    float_msg_struct float_msg;
    fp16_msg_struct fp16_msg;
} msg_union;

class CCP
{
protected:
    // Device dependent
    virtual byte write_device() = 0; // write id and msg.msg_byte to the device, then return sndStat

public:
    // Device dependent
    virtual int begin() = 0;
    virtual void read_device() = 0; // read id and msg.msg_byte from the device

    // CORE CAN Protocol
    long unsigned int id = 0;
    msg_union msg = {{0, 0}};

    // encode,transfer
    byte byte_to_device(long unsigned int _id, byte _data_byte[8]);
    byte string_to_device(long unsigned int _id, char *_string);
    byte uint32_to_device(long unsigned int _id, uint32_t _data_uint32);
    byte uint16_to_device(long unsigned int _id, uint16_t _data_uint16_0, uint16_t _data_uint16_1, uint16_t _data_uint16_2);
    byte float_to_device(long unsigned int _id, float _data_float);
    byte fp16_to_device(long unsigned int _id, float _data_fp16_0, float _data_fp16_1, float _data_fp16_2);

    // decode
    void string(char *str_buf, int str_len);       // ex."ACTIVE":str_len=7(including \0)
    bool str_match(char *str_to_cmp, int str_len); // ex."OPEN":str_len=4
    uint16_t time16();
    uint32_t time32();
    uint32_t data_uint32();
    uint16_t data_uint16_0(), data_uint16_1(), data_uint16_2();
    float data_float();
    float data_fp16_0(), data_fp16_1(), data_fp16_2();

    // floating point processing
    static void float_to_fp16(byte fp16[2], float data_fp16);
    static float fp16_to_float(byte fp16[2]);
};

#endif
