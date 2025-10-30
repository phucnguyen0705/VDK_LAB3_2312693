#include "input_reading.h"

#define N0_OF_BUTTONS 3
#define BUTTON_IS_PRESSED GPIO_PIN_RESET
#define BUTTON_IS_RELEASED GPIO_PIN_SET

static GPIO_PinState buttonBuffer[N0_OF_BUTTONS];
static GPIO_PinState debounce1[N0_OF_BUTTONS];
static GPIO_PinState debounce2[N0_OF_BUTTONS];
static uint16_t buttonPin[N0_OF_BUTTONS] = {b1_Pin, b2_Pin, b3_Pin};

void button_reading_Init(void){
    for(int i = 0; i < N0_OF_BUTTONS; i++){
        debounce1[i] = BUTTON_IS_RELEASED;
        debounce2[i] = BUTTON_IS_RELEASED;
        buttonBuffer[i] = BUTTON_IS_RELEASED;
    }
}

void button_reading(void){
    for(int i = 0; i < N0_OF_BUTTONS; i++){
        debounce2[i] = debounce1[i];
        debounce1[i] = HAL_GPIO_ReadPin(GPIOB, buttonPin[i]);
        if(debounce1[i] == debounce2[i]){
            buttonBuffer[i] = debounce1[i];
        }
    }
}

unsigned char is_button_pressed(uint8_t index){
    if(index >= N0_OF_BUTTONS) return 0;
    return (buttonBuffer[index] == BUTTON_IS_PRESSED);
}
