#ifndef CRUISE_IO_H
#define CRUISE_IO_H

#ifdef __cplusplus
extern "C" {
#endif

/* State machine inputs */
extern unsigned char enable_button;
extern unsigned char set_decrease_button;
extern unsigned char resume_increase_button;
extern unsigned char brake_button;
extern unsigned char accelerator;
extern unsigned char decrease_distance_button;
extern unsigned char increase_distance_button;
extern unsigned char actual_distance;
extern unsigned char actual_kph;
extern unsigned short engine_speed;

/* State machine outputs */
extern unsigned char speed_setting;
extern unsigned char distance_setting;
extern unsigned char cruise_status;
extern unsigned char cruise_accelerator;
extern unsigned char internal_state;

#ifdef __cplusplus
}
#endif

#endif
