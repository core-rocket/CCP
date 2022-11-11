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

#define CCP_A_control 0x018
#define CCP_A_state 0x019
#define CCP_B_control 0x01A
#define CCP_B_state 0x01B
#define CCP_C_control 0x01C
#define CCP_C_state 0x01D
#define CCP_D_control 0x01E
#define CCP_D_state 0x01F
#define CCP_E_control 0x020
#define CCP_E_state 0x021
#define CCP_F_control 0x022
#define CCP_F_state 0x023

#define CCP_camera_control 0x024
#define CCP_camera_state 0x025

#define CCP_A_flash_control 0x028
#define CCP_A_flash_state 0x029
#define CCP_B_flash_control 0x02A
#define CCP_B_flash_state 0x02B
#define CCP_C_flash_control 0x02C
#define CCP_C_flash_state 0x02D
#define CCP_D_flash_control 0x02E
#define CCP_D_flash_state 0x02F
#define CCP_E_flash_control 0x030
#define CCP_E_flash_state 0x031

// uint32_t
#define CCP_lift_off_time_ms 0x410
#define CCP_open_time_ms 0x411

#define CCP_A_GNSS_latitude_udeg 0x420
#define CCP_A_GNSS_longitude_udeg 0x421
#define CCP_A_GNSS_altitude_mm 0x422
#define CCP_A_GNSS_time_ms 0x423
#define CCP_B_GNSS_latitude_udeg 0x424
#define CCP_B_GNSS_longitude_udeg 0x425
#define CCP_B_GNSS_altitude_mm 0x426
#define CCP_B_GNSS_time_ms 0x427
#define CCP_C_GNSS_latitude_udeg 0x428
#define CCP_C_GNSS_longitude_udeg 0x429
#define CCP_C_GNSS_altitude_mm 0x42A
#define CCP_buzzer_ring_reserveation_h 0x42B


// uint16_t


// float
#define CCP_open_time_s 0x610
#define CCP_open_time_repeat_s 0x611

#define CCP_A_pressure_altitude_m 0x620
#define CCP_A_pressure_hPa 0x621
#define CCP_A_temperature_C 0x622
#define CCP_A_humidity_percent 0x623
#define CCP_A_chamber_pressure_V 0x624

#define CCP_voltage_main_V 0x62C

#define CCP_B_pressure_altitude_m 0x630
#define CCP_B_pressure_hPa 0x631
#define CCP_B_temperature_C 0x632
#define CCP_B_humidity_percent 0x633

#define CCP_voltage_actuator_V 0x63C
#define CCP_current_actuator_mA 0x63D
#define CCP_voltage_valve_V 0x63E
#define CCP_voltage_drain_V 0x63F

#define CCP_C_pressure_altitude_m 0x640
#define CCP_C_pressure_hPa 0x641
#define CCP_C_temperature_C 0x642
#define CCP_C_humidity_percent 0x643

#define CCP_C_differential_pressure_Pa 0x648
#define CCP_C_airspeed_ms 0x649
#define CCP_C_differential_pressure_raw_V 0x64A

#define CCP_D_pressure_altitude_m 0x650
#define CCP_D_pressure_hPa 0x651
#define CCP_D_temperature_C 0x652
#define CCP_D_humidity_percent 0x653

#define CCP_E_pressure_altitude_m 0x660
#define CCP_E_pressure_hPa 0x661
#define CCP_E_temperature_C 0x662
#define CCP_E_humidity_percent 0x663

#define CCP_F_precise_accel_x_mss 0x674
#define CCP_F_precise_accel_y_mss 0x675
#define CCP_F_precise_accel_z_mss 0x676
#define CCP_F_precise_accel_mss 0x677

// fp16
#define CCP_A_accel_mss 0x720
#define CCP_A_accel_G_cancel_mss 0x721
#define CCP_A_gyro_rads 0x722
#define CCP_A_mag_uT 0x724
#define CCP_A_euler_rad 0x726

#define CCP_B_accel_mss 0x730
#define CCP_B_accel_G_cancel_mss 0x731
#define CCP_B_gyro_rads 0x732
#define CCP_B_mag_uT 0x734
#define CCP_B_euler_rad 0x736

#define CCP_C_accel_mss 0x740
#define CCP_C_accel_G_cancel_mss 0x741
#define CCP_C_gyro_rads 0x742
#define CCP_C_mag_uT 0x744
#define CCP_C_euler_rad 0x746

#define CCP_D_accel_mss 0x750
#define CCP_D_accel_G_cancel_mss 0x751
#define CCP_D_gyro_rads 0x752
#define CCP_D_mag_uT 0x754
#define CCP_D_euler_rad 0x756

#define CCP_E_accel_mss 0x760
#define CCP_E_accel_G_cancel_mss 0x761
#define CCP_E_gyro_rads 0x762
#define CCP_E_mag_uT 0x764
#define CCP_E_euler_rad 0x766

#define CCP_F_accel_mss 0x770
#define CCP_F_accel_G_cancel_mss 0x771
#define CCP_F_gyro_rads 0x772
#define CCP_F_mag_uT 0x774
#define CCP_F_euler_rad 0x776

#endif
