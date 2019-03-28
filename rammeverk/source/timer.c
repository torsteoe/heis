#include "timer.h"

static time_t time_var;

void timer_init() {
    time_var = time(NULL);
}
void timer_reset() {
    time_var = time(NULL);
}
int timer_is_timeout() {
    time_t time_now = time(NULL);

    return ((time_now-time_var)>=3);
}