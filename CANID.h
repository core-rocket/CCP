#ifndef CANID_H
#define CANID_H

// char
#define CCP_parachute_fuse 0x001
#define CCP_parachute_control 0x002
#define CCP_lift_off_judge 0x003
#define CCP_open_judge 0x004
#define CCP_opener_control 0x005
#define CCP_opener_state 0x006
#define CCP_opener_source 0x007
#define CCP_A_flash_control 0x008
#define CCP_A_flash_state 0x009
#define CCP_B_flash_control 0x00A
#define CCP_B_flash_state 0x00B

// uint32_t
#define CCP_lift_off_time_ms 0x040
#define CCP_open_time_ms 0x041
#define CCP_open_time_s 0x042
#define CCP_open_time_repeat_s 0x043
#define CCP_GNSS_latitude_udeg 0x044
#define CCP_GNSS_longitude_udeg 0x045
#define CCP_GNSS_altitude_mm 0x046
#define CCP_GNSS_time_ms 0x047

// float
#define CCP_pressure_altitude_m 0x080
#define CCP_pressure_hPa 0x081
#define CCP_temperature_C 0x082
#define CCP_difpressure_hPa 0x083
#define CCP_difpressure_voltage_V 0x084


// fp16
#define CCP_accel_mss 0x0C0
#define CCP_gyro_rads 0x0C1
#define CCP_mag_uT 0x0C2
#define CCP_euler_rad 0x0C3

#endif
