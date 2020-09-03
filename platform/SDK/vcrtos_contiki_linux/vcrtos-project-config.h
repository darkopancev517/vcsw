#ifndef VCRTOS_PROJECT_CONFIG_H
#define VCRTOS_PROJECT_CONFIG_H

#define VCRTOS_CONFIG_MULTIPLE_INSTANCE_ENABLE 0

#define VCRTOS_CONFIG_THREAD_FLAGS_ENABLE 1
#define VCRTOS_CONFIG_THREAD_EVENT_ENABLE 1

#define VCRTOS_CONFIG_MAIN_THREAD_STACK_SIZE 24576
#define VCRTOS_CONFIG_IDLE_THREAD_STACK_SIZE 12288
#define VCRTOS_CONFIG_CLI_UART_THREAD_STACK_SIZE 12288
#define VCRTOS_CONFIG_THREAD_EVENT_HIGHEST_STACK_SIZE 12288
#define VCRTOS_CONFIG_THREAD_EVENT_MEDIUM_STACK_SIZE 12288
#define VCRTOS_CONFIG_THREAD_EVENT_LOWEST_STACK_SIZE 12288

#define VCRTOS_CONFIG_ZTIMER_ENABLE 1
#define VCRTOS_CONFIG_ZTIMER_NOW64 0
#define VCRTOS_CONFIG_ZTIMER_USEC_BASE_FREQ (1000000LU)
#define VCRTOS_CONFIG_ZTIMER_USEC_DEV 0
#define VCRTOS_CONFIG_ZTIMER_USEC_MIN (64)
#define VCRTOS_CONFIG_ZTIMER_USEC_WIDTH (32)
#define VCRTOS_CONFIG_ZTIMER_EXTEND 1

#endif /* VCRTOS_PROJECT_CONFIG_H */
