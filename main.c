#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/timer.h"

#include "modules/led.h"

uint8_t led_idx = 0; // determine wich LED will be on
uint8_t leds[] = {PIN_RED_LED,PIN_BLUE_LED,PIN_GREEN_LED}; // matrix of LEDs pin
void init_gpio(){
    // inicia o LED RGB
    init_rgb_led();
}
bool repeating_timer_callback(struct repeating_timer * t) {
    led_idx++;
    if (led_idx >= 3) led_idx = 0;
    for (int i = 0; i < 3; i++) {
        if ( i == led_idx) led_manipulate(leds[i], true);
        else led_manipulate(leds[i], false);
    }
}

int main() {
    stdio_init_all();
    init_gpio();

    struct repeating_timer timer;

    add_repeating_timer_ms(3000, repeating_timer_callback, NULL, &timer);
    led_manipulate(PIN_RED_LED, true);
    while(1) {
        sleep_ms(1000);
        printf("repetition routine\n");
    }
}