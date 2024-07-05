#ifndef CANID_H
#define CANID_H

// char
#define CCP_parachute_fuse 0x008
#define CCP_parachute_control 0x009
#define CCP_lift_off_judge 0x00A
#define CCP_open_judge 0x00B
#define CCP_opener_control 0x00C
#define CCP_opener_state 0x00D
#define CCP_opener_source 0x00E
#define CCP_nose_status 0x00F

#define CCP_surface_pressure1_status 0x108
#define CCP_surface_pressure2_status 0x109
#define CCP_surface_pressure3_status 0x10A
#define CCP_surface_pressure4_status 0x10B
#define CCP_surface_pressure5_status 0x10C
#define CCP_surface_pressure6_status 0x10D

#define CCP_nose_adc 0x11A

// uint32_t

// float
#define CCP_A_pressure_hPa 0x080
#define CCP_A_temperature_C 0x081
#define CCP_A_humidity_percent 0x082
#define CCP_A_altitude_m 0x083

#define CPP_B_pressure_altitude_m 0x086
#define CCP_B_temperature_C 0x087
#define CCP_B_humidity_percent 0x088
#define CCP_B_altitude_m 0x089

#define CCP_surface_pressure1_pressure_hPa 0x08A
#define CCP_surface_pressure2_pressure_hPa 0x08B
#define CCP_surface_pressure3_pressure_hPa 0x08C
#define CCP_surface_pressure4_pressure_hPa 0x08D
#define CCP_surface_pressure5_pressure_hPa 0x08E
#define CCP_surface_pressure6_pressure_hPa 0x08F
#define CCP_surface_pressure7_pressure_hPa 0x090
#define CCP_surface_pressure8_pressure_hPa 0x091

// fp16
#define CCP_A_accel_mss 0x720
#define CCP_A_gyro_rads 0x721
#define CCP_A_mag_uT 0x722
#define CCP_A_euler_rad 0x723
#define CCP_A_magnetic_Am 0x724
#define CCP_A_gravity_mss 0x725

#define CCP_B_accel_mss 0x730
#define CCP_B_gyro_rads 0x731
#define CCP_B_mag_uT 0x732
#define CCP_B_euler_rad 0x733
#define CCP_B_magnetic_Am 0x734
#define CCP_B_gravity_mss 0x735


#endif

