#ifndef CANID_H
#define CANID_H

// char
#define CCP_parachute_fuse 0x001
#define CCP_parachute_control 0x002
#define CCP_lift_off_judge 0x003
#define CCP_key_state 0x004
#define CCP_opener_control 0x005
#define CCP_opener_state 0x006
#define CCP_opener_source 0x007
#define CCP_A_flash_control 0x008
#define CCP_A_flash_state 0x009
#define CCP_B_flash_control 0x00A
#define CCP_B_flash_state 0x00B
#define CCP_C_flash_control 0x00C
#define CCP_C_flash_state 0x00D
#define CCP_sensor_control 0x00E


#define CCP_surface_pressure1_status 0x108
#define CCP_surface_pressure2_status 0x109
#define CCP_surface_pressure3_status 0x10A
#define CCP_surface_pressure4_status 0x10B
#define CCP_surface_pressure5_status 0x10C
#define CCP_surface_pressure6_status 0x10D

#define CCP_nose_adc 0x11A

// uint32_t
#define CCP_lift_off_time_ms 0x040
#define CCP_open_time_ms 0x041
#define CCP_open_time_s 0x042
#define CCP_open_time_repeat_s 0x043
#define CCP_A_GNSS_latitude_udeg 0x044
#define CCP_A_GNSS_longitude_udeg 0x045
#define CCP_A_GNSS_altitude_mm 0x046
#define CCP_A_GNSS_time_ms 0x047
#define CCP_B_GNSS_latitude_udeg 0x048
#define CCP_B_GNSS_longitude_udeg 0x049
#define CCP_B_GNSS_altitude_mm 0x04A
#define CCP_B_GNSS_time_ms 0x04B
#define CCP_downlink 0x04C


// float
#define CCP_difpressure_hPa 0x080
#define CCP_difpressure_voltage_V 0x081
#define CCP_A_pressure_altitude_m 0x082
#define CCP_A_pressure_hPa 0x083
#define CCP_A_temperature_C 0x084
#define CCP_A_humidity_percent 0x085
#define CCP_A_altitude_m 0x086
#define CCP_B_pressure_altitude_m 0x087
#define CCP_B_pressure_hPa 0x088
#define CCP_B_temperature_C 0x089

#define CCP_surface_pressure1_pressure_hPa 0x08A
#define CCP_surface_pressure2_pressure_hPa 0x08B
#define CCP_surface_pressure3_pressure_hPa 0x08C
#define CCP_surface_pressure4_pressure_hPa 0x08D
#define CCP_surface_pressure5_pressure_hPa 0x08E
#define CCP_surface_pressure6_pressure_hPa 0x08F
#define CCP_surface_pressure7_pressure_hPa 0x090
#define CCP_surface_pressure8_pressure_hPa 0x091

#define CCP_nose_pressure_hPa 0x092
#define CCP_nose_temperature_C 0x093
#define CCP_nose_humidity_percent 0x094
#define CCP_nose_altitude_m 0x095
#define CCP_nose_gas_KOhms 0x096

// fp16
#define CCP_A_accel_mss 0x0C0
#define CCP_A_gyro_rads 0x0C1
#define CCP_A_mag_uT 0x0C2
#define CCP_A_euler_rad 0x0C3
#define CCP_A_magnetic_Am 0x0C
#define CCP_A_gravity_mss 0x0C

#define CCP_B_accel_mss 0x0C4
#define CCP_B_gyro_rads 0x0C5
#define CCP_B_mag_uT 0x0C6
#define CCP_B_euler_rad 0x0C7
#define CCP_B_magnetic_Am 0x734
#define CCP_B_gravity_mss 0x735


#endif

