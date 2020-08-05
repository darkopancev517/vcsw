#ifndef VCOS_THREAD_H
#define VCOS_THREAD_H

#include <vcos/config.h>
#include <vcos/kernel.h>
#include <vcos/cib.h>
#include <vcos/clist.h>
#include <vcos/msg.h>
#include <vcos/instance.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef void *(*thread_handler_func_t)(void *arg);

typedef enum
{
    THREAD_STATUS_STOPPED,
    THREAD_STATUS_SLEEPING,
    THREAD_STATUS_MUTEX_BLOCKED,
    THREAD_STATUS_RECEIVE_BLOCKED,
    THREAD_STATUS_SEND_BLOCKED,
    THREAD_STATUS_REPLY_BLOCKED,
    THREAD_STATUS_FLAG_BLOCKED_ANY,
    THREAD_STATUS_FLAG_BLOCKED_ALL,
    THREAD_STATUS_MBOX_BLOCKED,
    THREAD_STATUS_COND_BLOCKED,
    THREAD_STATUS_RUNNING,
    THREAD_STATUS_PENDING,
    THREAD_STATUS_NUMOF
} thread_status_t;

#define THREAD_STATUS_NOT_FOUND ((thread_status_t)-1)

#if VCOS_CONFIG_THREAD_FLAGS_ENABLE
typedef uint16_t thread_flags_t;
#endif

typedef struct thread
{
    char *stack_pointer;
    thread_status_t status;
    uint8_t priority;
    kernel_pid_t pid;
#if VCOS_CONFIG_THREAD_FLAGS_ENABLE
    thread_flags_t flags;
    thread_flags_t waited_flags;
#endif
    list_node_t runqueue_entry;
    void *wait_data;
    list_node_t msg_waiters;
    cib_t msg_queue;
    msg_t *msg_array;
    char *stack_start;
    const char *name;
    int stack_size;
#if VCOS_CONFIG_MULTIPLE_INSTANCE_ENABLE
    void *instance;
#endif
} thread_t;

#define THREAD_FLAGS_CREATE_SLEEPING (0x1)
#define THREAD_FLAGS_CREATE_WOUT_YIELD (0x2)
#define THREAD_FLAGS_CREATE_STACKMARKER (0x4)

void thread_scheduler_run(instance_t *instance);

void thread_task_exit(void);

int thread_pid_is_valid(kernel_pid_t pid);

void thread_yield(void);

thread_t *thread_current(instance_t *instance);

kernel_pid_t thread_current_pid(void);

char *thread_arch_stack_init(thread_handler_func_t func, void *arg, void *stack_start, int stack_size);

void thread_arch_stack_print(void);

int thread_arch_stack_usage(void);

void *thread_arch_isr_stack_pointer(void);

void *thread_arch_stack_start(void);

#ifdef __cplusplus
}
#endif

#endif /* VCOS_THREAD_H */
