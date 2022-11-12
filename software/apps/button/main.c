// Breadboard example app
//
// Read from multiple analog sensors and control an RGB LED

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <math.h>

#include "app_timer.h"
#include "nrf_delay.h"
#include "nrfx_saadc.h"
#include "microbit_v2.h"

// Digital outputs
// Breakout pins 13, 14, and 15
// These are GPIO pin numbers that can be used in nrf_gpio_* calls
#define BUTTON_LED EDGE_P13
#define BUTTON_IN EDGE_P16

// Global variables
APP_TIMER_DEF(sample_timer);

// Function prototypes
static void gpio_init(void);

static void sample_timer_callback(void* _unused) {
  // Do things periodically here
  int button_val = nrf_gpio_pin_read(BUTTON_IN);
  
  printf("Button value: %d\n", button_val);

  // control the button LED with the switch
  if (button_val == 1) {
    nrf_gpio_pin_clear(BUTTON_LED);
    printf("Button pressed!\n");
  } else {
    nrf_gpio_pin_set(BUTTON_LED);
    
  }
}

static void gpio_init(void) {
  // Initialize output pins
  nrf_gpio_pin_dir_set(BUTTON_LED, NRF_GPIO_PIN_DIR_OUTPUT);

  // Set LED off initially
  nrf_gpio_pin_set(BUTTON_LED);

  // Initialize input pin
  nrf_gpio_pin_dir_set(BUTTON_IN, NRF_GPIO_PIN_DIR_INPUT);
  nrf_gpio_cfg_input(BUTTON_IN, NRF_GPIO_PIN_PULLDOWN);
}

int main(void) {
  printf("Board started!\n");
  
  // initialize GPIO
  gpio_init();

  // initialize app timer
  app_timer_init();
  app_timer_create(&sample_timer, APP_TIMER_MODE_REPEATED, sample_timer_callback);

  // start timer (change the rate to whatever you want)
  app_timer_start(sample_timer, 10000, NULL);

  // loop forever
  while (1) {
    // Don't put any code in here. Instead put periodic code in `sample_timer_callback()`
    nrf_delay_ms(1000);
  }
}

