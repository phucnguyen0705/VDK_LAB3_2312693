#include "processing.h"
#include "traffic_led.h"
#include "seven_segment.h"
#include "input_reading.h"
#include "timer.h"

static int mode = 1;
static int button_flag[3] = {0};

void processing_init(void){
    traffic_init();
    setTimer0(50);
    setTimer1(25);
    setTimer2(10);
}

void blink_leds_mode(void){
    static int blink_state = 0;

    if(timer2_flag){
        timer2_flag = 0;
        blink_state = !blink_state;
        setTimer2(100);

        switch(mode){
            case 2:
                HAL_GPIO_WritePin(GPIOA, GPIO_PIN_8, !blink_state);
                HAL_GPIO_WritePin(GPIOA, GPIO_PIN_11, !blink_state);
                break;
            case 3:
                HAL_GPIO_WritePin(GPIOA, GPIO_PIN_9, !blink_state);
                HAL_GPIO_WritePin(GPIOA, GPIO_PIN_12, !blink_state);
                break;
            case 4:
                HAL_GPIO_WritePin(GPIOA, GPIO_PIN_10, !blink_state);
                HAL_GPIO_WritePin(GPIOA, GPIO_PIN_13, !blink_state);
                break;
            default:
                break;
        }
    }
}
void processing_run(void){
    // Quét LED7
    if(timer1_flag){
        timer1_flag = 0;
        scan7SEG();
        setTimer1(25);
    }

    // Đọc button
    if(timer3_flag){
        timer3_flag = 0;
        button_reading();
        setTimer3(10);
    }

    // Xử lý button chuyển mode
    if(is_button_pressed(0)){
        if(!button_flag[0]){
            button_flag[0] = 1;
            mode = mode + 1;
            if(mode > 4) mode = 1;
            turnOffTraffic();
            if(mode == 1){
                traffic_init();
            }
        }
    } else {
        button_flag[0] = 0;
    }

    // XỬ LÝ TỪNG MODE
    switch(mode){
        case 1:
            traffic_update();
            upclock(counter_NS);
            upmode(1);
            break;

        case 2:
            blink_leds_mode();
            if(is_button_pressed(1)){
                if(!button_flag[1]){
                    button_flag[1] = 1;
                    int new_red = (get_red() % 99) + 1;
                    set_traffic_time(new_red, get_yellow(), get_green());
                }
            } else {
                button_flag[1] = 0;
            }
            upclock(get_red());
            upmode(2);
            break;

        case 3:
            blink_leds_mode();
            if(is_button_pressed(1)){
                if(!button_flag[1]){
                    button_flag[1] = 1;
                    int new_yellow = (get_yellow() % 99) + 1;
                    set_traffic_time(get_red(), new_yellow, get_green());
                }
            } else {
                button_flag[1] = 0;
            }
            upclock(get_yellow());
            upmode(3);
            break;

        case 4:
            blink_leds_mode();
            if(is_button_pressed(1)){
                if(!button_flag[1]){
                    button_flag[1] = 1;
                    int new_green = (get_green() % 99) + 1;
                    set_traffic_time(get_red(), get_yellow(), new_green);
                }
            } else {
                button_flag[1] = 0;
            }
            upclock(get_green());
            upmode(4);
            break;

        default:
            mode = 1;
            traffic_init();
            break;
    }
}
