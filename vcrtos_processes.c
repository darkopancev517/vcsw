#include <stdio.h>
#include <inttypes.h>

#include <vcrtos/instance.h>
#include <vcrtos/thread.h>
#include <vcrtos/ztimer.h>
#include <vcrtos/cli.h>

#include "contiki.h"

PROCESS(app_process, "app-process", VCRTOS_CONFIG_MAIN_THREAD_STACK_SIZE);

AUTOSTART_PROCESSES(&app_process);

#if 0
static uint32_t _ctimer_counter = 0;
static void _ctimer_handler(void *arg)
{
    struct ctimer *ct = (struct ctimer *)arg;
    _ctimer_counter += 1;
    ctimer_reset(ct);
}
#endif

PROCESS_THREAD(app_process, ev, data)
{
    //static struct etimer timer_etimer;
    //static struct ctimer timer_ctimer;

    PROCESS_BEGIN();

    //uint32_t etimer_counter = 0;

    //ctimer_set(&timer_ctimer, CLOCK_SECOND / 2, _ctimer_handler, &timer_ctimer);

    while (1)
    {
        //etimer_set(&timer_etimer, CLOCK_SECOND);
        //PROCESS_WAIT_EVENT_UNTIL(ev == PROCESS_EVENT_TIMER);
        //printf("e: %" PRIu32 "\r\n", etimer_counter++);
        //printf("c: %" PRIu32 "\r\n", _ctimer_counter);

        thread_sleep(p->instance);
    }

    PROCESS_END();
}
