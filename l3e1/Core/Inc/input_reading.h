#ifndef INC_INPUT_READING_H_
#define INC_INPUT_READING_H_

#include "main.h"

void button_reading_Init(void);
void button_reading(void);
unsigned char is_button_pressed(uint8_t index);
unsigned char is_button_pressed_1s(uint8_t index);

#endif
