#include "cruise_io.h"

/* State machine inputs */
unsigned char enable_button;  // On/Off
unsigned char set_decrease_button;  // On/Off
unsigned char resume_increase_button;  // On/Off
unsigned char brake_button;  // On/Off
unsigned char accelerator;  // percent
unsigned char decrease_distance_button;
unsigned char increase_distance_button;
unsigned char actual_distance;  // meters
unsigned char actual_kph;  // kph
unsigned short engine_speed;  // rpm

/* State machine outputs */
unsigned char speed_setting;  // kph
unsigned char distance_setting;  // meters
unsigned char cruise_status;  // On/Off
unsigned char cruise_accelerator;  // percent
unsigned char internal_state;


