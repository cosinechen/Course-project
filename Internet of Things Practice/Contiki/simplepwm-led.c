/**
 * \file
 *         Simple-PWM example application,
 *          Demonstrates using the simple_pwm API to eg dim LED.
 * \author
 *         Marcus Linderoth <linderoth.marcus@gmail.com>
 */

#include <stdio.h>
#include "contiki.h"
#include "dev/leds.h"
#include "dev/button.h"
#include "simple-pwm.h"

/* pins I want to use for PWM (only one is used) at a time with this */
#define LEDRED_PIN       (0)   // P1.0
#define LEDGRN_PIN       (6)   // P1.6
#define LEDBIG_PIN       (7)   // P1.7

/* the PWM duty cycle will step back and forth between these limits, with this step */
#define PWM_MIN           0
#define PWM_MAX           255
#define PWM_STEP          1

/* wait this long between setting a new PWM setting */
#define INTERVAL          CLOCK_SECOND/64
/*---------------------------------------------------------------------------*/
PROCESS(pwmled_process, "PWM LED process");
AUTOSTART_PROCESSES(&pwmled_process);
/*---------------------------------------------------------------------------*/
/* PWM process; finds and sets the PWM. */
static struct etimer etr;
static uint8_t i = 1;     /* counter */
static uint8_t up = 1;    /* counting up or down? */

PROCESS_THREAD(pwmled_process, ev, data)
{
  PROCESS_POLLHANDLER();
  PROCESS_EXITHANDLER(simple_pwm_off(););
  PROCESS_BEGIN();

  simple_pwm_confpin(LEDBIG_PIN);

  while(1) {
    simple_pwm_on(i);

    /* find next PWM setting */
    if(up) {
      if(i < PWM_MAX - PWM_STEP) {
        i += PWM_STEP;
      } else {
        i = PWM_MAX;
        up = 0;
      }
    } else {
      if(i > PWM_MIN + PWM_STEP) {
        i -= PWM_STEP;
      } else {
        i = PWM_MIN ;
        up = 1;
      }
    }

    /* wait a little while */
    etimer_set(&etr, INTERVAL);
    PROCESS_WAIT_EVENT_UNTIL(etimer_expired(&etr));
  }
  PROCESS_END();
}
/*--------------------------------------------------------------------------.*/
