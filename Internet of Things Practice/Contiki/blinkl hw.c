//cooperate with serialtest
#include <stdio.h>
#include "contiki.h"
#include "dev/leds.h"

/* -------------------------------------------------------------------------- */
PROCESS(red_process, "Red light process");
PROCESS(blink_process, "Blink");
AUTOSTART_PROCESSES(&blink_process);
/*---------------------------------------------------------------------------*/
/* This process is started from the other process and blinks an LED fast.
*/
static struct etimer etr;
PROCESS_THREAD(red_process, ev, data)
{
  PROCESS_POLLHANDLER();
  PROCESS_EXITHANDLER();
  PROCESS_BEGIN();
  while(1) {
    leds_toggle(LEDS_RED);
    etimer_set(&etr, CLOCK_SECOND*4);
    PROCESS_WAIT_EVENT_UNTIL(etimer_expired(&etr));
  }
  PROCESS_END();
}

/*--------------------------------------------------------------------------*/
/* this process starts another process and then periodically blinks an LED */
static struct etimer et;

PROCESS_THREAD(blink_process, ev, data)
{
  PROCESS_BEGIN();

  etimer_set(&et, CLOCK_SECOND);
  PROCESS_WAIT_EVENT_UNTIL(etimer_expired(&et));
  process_start(&red_process, NULL);

  while(1) {
	printf("led off ->");
	etimer_set(&et,CLOCK_SECOND);
	PROCESS_WAIT_EVENT_UNTIL(etimer_expired(&et));

	printf("red led ->");
	etimer_set(&et,CLOCK_SECOND);
	PROCESS_WAIT_EVENT_UNTIL(etimer_expired(&et));

	printf("green led->");
	etimer_set(&et,CLOCK_SECOND);
	PROCESS_WAIT_EVENT_UNTIL(etimer_expired(&et));

	printf("led all ->");
	etimer_set(&et,CLOCK_SECOND*2);
	PROCESS_WAIT_EVENT_UNTIL(etimer_expired(&et));
  }
  PROCESS_END();
}