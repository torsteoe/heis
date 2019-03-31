#include "timer.h"
const double SECONDS = 3; //change to three
static clock_t clock_var;
void timer_init() {
    clock_var = clock();
}
void timer_reset() {
    clock_var = clock();
}
int timer_is_timeout() {
    clock_t clock_now = clock();
    return ((clock_now-clock_var)>=SECONDS*CLOCKS_PER_SEC); 
}