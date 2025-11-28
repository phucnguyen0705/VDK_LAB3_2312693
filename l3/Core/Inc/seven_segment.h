#ifndef INC_SEVEN_SEGMENT_H_
#define INC_SEVEN_SEGMENT_H_

#include "main.h"

extern int led_buffer[4];

void upclock(uint8_t time);
void upmode(uint8_t mode);
void scan7SEG(void);

#endif
