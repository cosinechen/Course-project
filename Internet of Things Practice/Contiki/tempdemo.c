#include <stdio.h>
#include "contiki.h"
#include "dev/leds.h"
#include "dev/adc.h"
#include "dev/button.h"
#include "dev/pwm.h"

/*---------------------------------------------------------------------------*/
#define MAVG_LEN  8
#define LED_PIN   0   // P1.0
#define TEMP_MIN  100 // minimum possible temp sensor reading
#define TEMP_MAX  500 // maximum possible temp sensor reading
/*---------------------------------------------------------------------------*/
static uint16_t temp_sense[MAVG_LEN];   /* ADC buffer for moving average */
static uint16_t temp_avg;               /* calculated average */
static uint8_t mavg_ix = 0;             /* index in buffer */
static uint8_t led_pwmdc;               /* LED PWM setting */
/*---------------------------------------------------------------------------*/
PROCESS(tempdemo_process, "My Process");
AUTOSTART_PROCESSES(&tempdemo_process);
/*---------------------------------------------------------------------------*/
static struct etimer et;
PROCESS_THREAD(tempdemo_process, ev, data)
{
  PROCESS_EXITHANDLER(pwm_off(0); leds_off(LEDS_ALL););
  PROCESS_BEGIN();
  /* pre-application mode: toggle LEDs */
  while(ev != button_event) {
    leds_toggle(LEDS_ALL);
    etimer_set(&et, CLOCK_SECOND/5);
    PROCESS_WAIT_EVENT_UNTIL(etimer_expired(&et));
  }

  /* application mode: get ADC of internal temp, showing avg (trend?) with LED */
  memset(temp_sense, 0, MAVG_LEN * sizeof(uint16_t));
  while(1) {
    uint8_t i;
    temp_sense[mavg_ix] = adc_get(TEMP);
    mavg_ix++;    /* mavg_ix = mavg_ix < (MAVG_LEN - 1) ? mavg_ix++ : 0; */
    if(mavg_ix == MAVG_LEN) {
      mavg_ix = 0;
    }

    temp_avg = 0;
    for(i = 0; i < MAVG_LEN; i += 1) {
      temp_avg += temp_sense[i];
    }
    temp_avg = temp_avg / MAVG_LEN;
    /* 100% duty cycle if full temp, 0% if lowest temp */
    led_pwmdc = (100 * (temp_avg - TEMP_MIN) / (TEMP_MAX - TEMP_MIN));
    pwm_on(0, LED_PIN, led_pwmdc);

    etimer_set(&et, CLOCK_SECOND/8);
    PROCESS_WAIT_EVENT_UNTIL(etimer_expired(&et));
  }
  PROCESS_END();
}