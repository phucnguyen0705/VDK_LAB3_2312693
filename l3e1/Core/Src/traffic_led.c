#include "traffic_led.h"
#include "timer.h"
#include "seven_segment.h"

static int red_time = 5, yellow_time = 2, green_time = 3;
int counter_NS = 0;
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
    yellow_time = y;
    green_time = g;
    red_time = r;
    if (red_time<green_time + yellow_time)
    {red_time = yellow_time + green_time;}
    if (red_time > green_time + yellow_time) {
    	green_time = red_time - yellow_time;
    };
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
void traffic_init(void){  // ĐẢM BẢO CÓ ĐỊNH NGHĨA HÀM NÀY
    counter_NS = green_time;
    state = 0;
    setNS(0,0,1);
    setWE(1,0,0);
}

void traffic_update(void){
    if(timer0_flag == 1){
        timer0_flag = 0;

        counter_NS--;
        switch(state){
            case 0:
                setNS(0,0,1);
                setWE(1,0,0);
                if(counter_NS == 0){
                    state = 1;
                    counter_NS = yellow_time;
                }
                break;

            case 1:
                setNS(0,1,0);
                setWE(1,0,0);
                if(counter_NS == 0){
                    state = 2;
                    counter_NS = red_time;
                }
                break;

            case 2:
                if(counter_NS > yellow_time){
                    setNS(1,0,0);
                    setWE(0,0,1);
                } else {
                    setNS(1,0,0);
                    setWE(0,1,0);
                }

                if(counter_NS == 0){
                    state = 0;
                    counter_NS = green_time;
                }
                break;
            default: // CASE DEFAULT - RESET VỀ STATE 0
                          state = 0;
            break;
        }
        setTimer0(100);
    }
}
