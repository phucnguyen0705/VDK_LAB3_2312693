#include "seven_segment.h"

int led_buffer[4] = {0, 0, 0, 0};

static const uint8_t segment_code[10] = {
    0xC0, 0xF9, 0xA4, 0xB0, 0x99,  // 0, 1, 2, 3, 4
    0x92, 0x82, 0xF8, 0x80, 0x90   // 5, 6, 7, 8, 9
};

static const uint16_t led_select[4] = {
    GPIO_PIN_12, GPIO_PIN_13, GPIO_PIN_14, GPIO_PIN_15
};

void upclock(uint8_t time){
    led_buffer[0] = time / 10;
    led_buffer[1] = time % 10;
}

void upmode(uint8_t mode){
    led_buffer[2] = 0;
    led_buffer[3] = mode;
}

static void display7SEG(int num){
    uint8_t seg = segment_code[num];
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_0, ((seg >> 0) & 1));
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_1, ((seg >> 1) & 1));
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_2, ((seg >> 2) & 1));
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_3, ((seg >> 3) & 1));
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, ((seg >> 4) & 1));
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, ((seg >> 5) & 1));
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_6, ((seg >> 6) & 1));
}
void scan7SEG(void){
    static int index = 0;

    // TẮT TẤT CẢ LED TRƯỚC
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, 1);
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_13, 1);
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_14, 1);
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_15, 1);

    // HIỂN THỊ SỐ
    display7SEG(led_buffer[index]);

    // BẬT LED HIỆN TẠI (ACTIVE LOW: 0 = ON)
    HAL_GPIO_WritePin(GPIOB, led_select[index], 0);

    // TĂNG INDEX
    index++;
    if(index >= 4) index = 0;
}
