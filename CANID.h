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

#define CCP_A_control 0x00A
#define CCP_A_state 0x00B
#define CCP_B_control 0x00C
#define CCP_B_state 0x00D
#define CCP_C_control 0x00E
#define CCP_C_state 0x00F
#define CCP_D_control 0x010
#define CCP_D_state 0x011
#define CCP_E_control 0x012
#define CCP_E_state 0x013
#define CCP_F_control 0x014
#define CCP_F_state 0x015


#define CCP_A_flash_control 0x01A
#define CCP_A_flash_state 0x01B
#define CCP_B_flash_control 0x01C
#define CCP_B_flash_state 0x01D


// uint32_t
#define CCP_lift_off_time_ms 0x040
#define CCP_open_time_ms 0x041
#define CCP_open_time_cmd_ms 0x042
#define CCP_open_time_response_s 0x043

#define CCP_dateandtime 0x046


#define CCP_A_GNSS_latitude_udeg 0x051
#define CCP_A_GNSS_longitude_udeg 0x052
#define CCP_A_GNSS_altitude_mm 0x053
#define CCP_A_GNSS_time_ms 0x054



// uint16_t--NONE


// float

#define CCP_A_pressure_altitude_m 0x080
#define CCP_A_pressure_hPa 0x081
#define CCP_A_temperature_C 0x082
#define CCP_A_humidity_percent 0x083

#define CCP_voltage_main_V 0x090

#define CCP_voltage_actuator_V 0x092

#define CCP_voltage_valve1_V 0x094

#define CCP_voltage_drain_V 0x096

// fp16
#define CCP_A_accel_mss 0x0C0
#define CCP_A_accel_G_cancel_mss 0x0C1
#define CCP_A_gyro_rads 0x0C2

#define CCP_A_mag_uT 0x0C4

#define CCP_A_euler_rad 0x0C6

#endif
