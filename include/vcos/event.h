#ifndef VCOS_EVENT_H
#define VCOS_EVENT_H

#include <vcos/config.h>
#include <vcos/thread.h>

#ifdef __cplusplus
extern "C" {
#endif

#define THREAD_FLAG_EVENT (0x1)

#define THREAD_EVENT_STACK_SIZE 128
#define THREAD_EVENT_PRIORITY (KERNEL_THREAD_PRIORITY_MAIN - 1)

typedef struct event event_t;

typedef void (*event_handler_func_t)(event_t *);

struct event
{
    clist_node_t list_node;
    event_handler_func_t handler;
};

#ifdef __cplusplus
}
#endif

#endif /* VCOS_EVENT_H */
