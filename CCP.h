#ifndef CCP_H
#define CCP_H

// char
#define CCP_parachute_fuse 0x008
#define CCP_parachute_control 0x009
#define CCP_lift_off_judge 0x00A
#define CCP_open_judge 0x00B
#define CCP_opener_control 0x00C
#define CCP_opener_state 0x00D
#define CCP_opener_source 0x00E

#define CCP_A_control 0x018
#define CCP_A_state 0x019
#define CCP_B_control 0x01A
#define CCP_B_state 0x01B

#define CCP_camera_control 0x024
#define CCP_camera_state 0x025

#define CCP_A_flash_control 0x028
#define CCP_A_flash_state 0x029
#define CCP_B_flash_control 0x030
#define CCP_B_flash_state 0x031

// uint32_t
#define CCP_lift_off_time_ms 0x410
#define CCP_open_time_ms 0x411

#define CCP_A_GNSS_latitude_udeg 0x420
#define CCP_A_GNSS_longitude_udeg 0x421
#define CCP_A_GNSS_altitude_mm 0x422
#define CCP_A_GNSS_time_ms 0x423

// uint16_t

// float
#define CCP_open_time_s 0x610

#define CCP_A_pressure_altitude_m 0x620
#define CCP_A_pressure_hPa 0x621
#define CCP_A_temperature_C 0x622
#define CCP_A_humidity_percent 0x623

#define CCP_B_pressure_altitude_m 0x630
#define CCP_B_pressure_hPa 0x631
#define CCP_B_temperature_C 0x632
#define CCP_B_humidity_percent 0x633

#define CCP_voltage_main 0x62C
#define CCP_voltage_actuator 0x63C

// fp16
#define CCP_A_accel_mss 0x720
#define CCP_A_gyro_rads 0x722
#define CCP_A_mag_uT 0x724
#define CCP_A_euler_rad 0x726

#define CCP_B_accel_mss 0x730
#define CCP_B_gyro_rads 0x732
#define CCP_B_mag_uT 0x734
#define CCP_B_euler_rad 0x736

#define CCP_C_accel_mss 0x740
#define CCP_C_gyro_rads 0x742
#define CCP_C_mag_uT 0x744
#define CCP_C_euler_rad 0x746

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
    uint32_t dummy[2]; //??????????????????????????????
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
    void float_to_fp16(byte fp16[2], float data_fp16);
    float fp16_to_float(byte fp16[2]);
};

#endif
