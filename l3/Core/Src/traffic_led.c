#include "traffic_led.h"
#include "timer.h"
#include "seven_segment.h"

static int red_time = 5, yellow_time = 2, green_time = 3;
int counter_NS = 0;
int counter_WE = 0;  // Add counter for WE direction
static int state = 0;

static void setNS(int R, int Y, int G){
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_8, !R);
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_9, !Y);
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_10, !G);
}

static void setWE(int R, int Y, int G){
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_11, !R);
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_12, !Y);
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_13, !G);
}

void set_traffic_time(int r, int y, int g){
    if ((g + y) > 99 || (r - g) < 0 || (r - y) < 0 ||
        r < 1 || y < 1 || g < 1) {
        red_time = 5;
        yellow_time = 2;
        green_time = 3;
        return;
    }
    yellow_time = y;
    green_time = g;
    red_time = r;

    if (red_time < green_time + yellow_time) {
        red_time = yellow_time + green_time;
    }
    if (red_time > green_time + yellow_time) {
        green_time = red_time - yellow_time;
    }
}

int get_red(void){ return red_time; }
int get_yellow(void){ return yellow_time; }
int get_green(void){ return green_time; }

void turnOffTraffic(void){
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_8, 1);
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_9, 1);
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_10, 1);
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_11, 1);
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_12, 1);
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_13, 1);
}

void traffic_init(void){
    state = 0;
    counter_NS = green_time;
    counter_WE = red_time;
    setNS(0,0,1);
    setWE(1,0,0);
    upclock(counter_NS);
}

int get_counter_NS(void){
    return counter_NS;
}

void traffic_update(void){
    if(timer0_flag == 1){
        timer0_flag = 0;
        setTimer0(1000);

        counter_NS--;
        counter_WE--;

        switch(state){
            case 0:  // NS: Green, WE: Red
                setNS(0,0,1);
                setWE(1,0,0);
                if(counter_NS == 0){
                    state = 1;
                    counter_NS = yellow_time;
                }
                break;

            case 1:  // NS: Yellow, WE: Red
                setNS(0,1,0);
                setWE(1,0,0);
                if(counter_NS == 0){
                    state = 2;
                    counter_NS = red_time;
                    counter_WE = green_time;
                }
                break;

            case 2:
                         setNS(1,0,0);

                         if(counter_NS > yellow_time){
                             setWE(0,0,1);  // WE: Xanh
                         } else {
                             setWE(0,1,0);  // WE: Vàng
                         }

                         if(counter_NS <= 0){
                             state = 0;
                             counter_NS = green_time;
                         }
                         break;
            default:
                state = 0;
                counter_NS = green_time;
                counter_WE = red_time;
                break;
        }
        // DON'T call upclock() here - it's called in processing_run()
    }
}
