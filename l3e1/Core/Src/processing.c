#include "processing.h"
#include "traffic_led.h"
#include "seven_segment.h"
#include "input_reading.h"
#include "timer.h"

static int mode = 1;
static int button_flag[3] = {0};
static int sync_blink = 0;
static int temp_red, temp_yellow, temp_green;
void processing_init(void){
    traffic_init();

    temp_red = get_red();
    temp_yellow = get_yellow();
    temp_green = get_green();
}

void blink_leds_mode(void){
    static int blink_state = 0;

    if(timer2_flag){
        timer2_flag = 0;
        blink_state = !blink_state;
        setTimer0(250);
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
        if(sync_blink > 0){
            HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, blink_state);
            sync_blink--;
            if(sync_blink == 0){
                HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, 0);
            }
        }
    }
}

void processing_run(void){
	  if(timer1_flag){
		        timer1_flag = 0;
		        scan7SEG();
		        setTimer1(250);
		    }
	    if(timer3_flag){
	        timer3_flag = 0;
	        button_reading();
	        setTimer3(10);
	    }
    if(is_button_pressed(0)){
        if(!button_flag[0]){
            button_flag[0] = 1;
            mode = mode + 1;
            if(mode > 4) mode = 1;
            turnOffTraffic();

            if(mode == 1){
                traffic_init();
            } else {
                temp_red = get_red();
                temp_yellow = get_yellow();
                temp_green = get_green();
            }
        }
    } else {
        button_flag[0] = 0;
    }

    // Xử lý button TĂNG GIÁ TRỊ (BUTTON 2) - CHỈ TĂNG TRONG BIẾN TẠM
    if(is_button_pressed(1)){
        if(!button_flag[1]){
            button_flag[1] = 1;

            switch(mode){
                case 2:  // Tăng thời gian đỏ TẠM THỜI
                    temp_red++;
                    if(temp_red > 99) temp_red = 1;
                    break;

                case 3:  // Tăng thời gian vàng TẠM THỜI
                    temp_yellow++;
                    if(temp_yellow > 99) temp_yellow = 1;
                    break;

                case 4:  // Tăng thời gian xanh TẠM THỜI
                    temp_green++;
                    if(temp_green > 99) temp_green = 1;
                    break;

                default:
                    break;
            }
        }
    } else {
        button_flag[1] = 0;
    }

    // Xử lý button LƯU GIÁ TRỊ (BUTTON 3) - DÙNG set_traffic_time ĐỂ LƯU
    if(is_button_pressed(2)){
        if(!button_flag[2]){
            button_flag[2] = 1;

            // LƯU GIÁ TRỊ bằng hàm set_traffic_time
            set_traffic_time(temp_red, temp_yellow, temp_green);

            // Nếu đang ở mode 1, khởi động lại traffic
            if(mode == 1){
                traffic_init();
            }
        }
    } else {
        button_flag[2] = 0;
    }

    switch(mode){
        case 1:
            traffic_update();
            upclock(counter_NS);
            upmode(1);
            break;

        case 2:
            blink_leds_mode();
            upclock(temp_red);
            upmode(2);
            break;

        case 3:
            blink_leds_mode();
            upclock(temp_yellow);
            upmode(3);
            break;

        case 4:
            blink_leds_mode();
            upclock(temp_green);
            upmode(4);
            break;

        default:
            mode = 1;
            traffic_init();
            break;
    }
}
