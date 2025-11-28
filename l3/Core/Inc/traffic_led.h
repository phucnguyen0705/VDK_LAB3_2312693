#ifndef INC_TRAFFIC_LED_H_
#define INC_TRAFFIC_LED_H_

#include "main.h"

extern int counter_NS;

void set_traffic_time(int r, int y, int g);
int get_red(void);
int get_yellow(void);
int get_green(void);
void turnOffTraffic(void);
void traffic_init(void);
void traffic_update(void);
int get_counter_NS(void);
#endif
