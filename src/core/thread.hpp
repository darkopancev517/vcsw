#ifndef CORE_THREAD_HPP
#define CORE_THREAD_HPP

#include <vcos/config.h>
#include <vcos/thread.h>
#include <vcos/stat.h>
#include <vcos/cpu.h>

#if VCOS_CONFIG_THREAD_EVENT_ENABLE
#include <vcos/event.h>
#endif

#include "core/msg.hpp"
#include "core/cib.hpp"
#include "core/clist.hpp"

namespace vc {

class ThreadScheduler;
class Instance;

#if !VCOS_CONFIG_MULTIPLE_INSTANCE_ENABLE
extern uint64_t instance_raw[];
#endif

class Thread : public thread_t
{
public:
    static Thread *init(Instance &instances, char *stack, int stack_size, unsigned priority, int flags,
                        thread_handler_func_t handler_func, void *arg, const char *name);

    kernel_pid_t get_pid(void) { return pid; }

    void set_pid(kernel_pid_t pids) { pid = pids; }

    thread_status_t get_status(void) { return status; }

    void set_status(thread_status_t new_status) { status = new_status; }

    uint8_t get_priority(void) { return priority; }

    void set_priority(uint8_t new_priority) { priority = new_priority; }

    list_node_t *get_runqueue_entry(void) { return &runqueue_entry; }

    const char *get_name(void) { return name; }

    void add_to_list(List *list);

    static Thread *get_thread_pointer_from_list_member(List *list);

    static int is_pid_valid(kernel_pid_t pid);

    void init_msg_queue(Msg *msg, int num);

    int queued_msg(Msg *msg);

    int get_numof_msg_in_queue(void);

    int has_msg_queue(void);

private:
    void init_runqueue_entry(void) { runqueue_entry.next = NULL; }

    void init_msg(void);

#if VCOS_CONFIG_THREAD_FLAGS_ENABLE
    void init_flags(void);
#endif

    void set_stack_start(char *ptr) { stack_start = ptr; }

    void set_stack_size(int size) { stack_size = size; }

    void set_name(const char *new_name) { name = new_name; }

    void set_stack_pointer(char *ptr) { stack_pointer = ptr; }

    void stack_init(thread_handler_func_t func, void *arg, void *stack_start, int stack_size);

    template <typename Type> inline Type &get(void) const;

#if VCOS_CONFIG_MULTIPLE_INSTANCE_ENABLE
    Instance &get_instance(void) const { return *static_cast<Instance *>(instance); }
#else
    Instance &get_instance(void) const { return *reinterpret_cast<Instance *>(&instance_raw); }
#endif
};

#if VCOS_CONFIG_THREAD_EVENT_ENABLE
class Event : public event_t
{
public:
    explicit Event(event_handler_func_t func)
    {
        list_node.next = NULL;
        handler = func;
    }
};
#endif

class ThreadScheduler : public Clist
{
public:
    ThreadScheduler(void)
        : numof_threads_in_scheduler(0)
        , context_switch_request(0)
        , current_active_thread(NULL)
        , current_active_pid(KERNEL_PID_UNDEF)
        , runqueue_bitcache(0)
#if VCOS_CONFIG_THREAD_EVENT_ENABLE
        , event_waiter(NULL)
#endif
    {
        for (kernel_pid_t i = KERNEL_PID_FIRST; i <= KERNEL_PID_LAST; ++i)
        {
            scheduled_threads[i] = NULL;
        }
    }

    Thread *get_thread_from_scheduler(kernel_pid_t pid) { return scheduled_threads[pid]; }

    void set_thread_to_scheduler(Thread *thread, kernel_pid_t pid) { scheduled_threads[pid] = thread; }

    unsigned int is_context_switch_requested(void) { return context_switch_request; }

    void enable_context_switch_request(void) { context_switch_request = 1; }

    void disable_context_switch_request(void) { context_switch_request = 0; }

    int get_numof_threads_in_scheduler(void) { return numof_threads_in_scheduler; }

    void increment_numof_threads_in_scheduler(void) { numof_threads_in_scheduler++; }

    void decrement_numof_threads_in_scheduler(void) { numof_threads_in_scheduler--; }

    Thread *get_current_active_thread(void) { return current_active_thread; }

    void set_current_active_thread(Thread *thread) { current_active_thread = thread; }

    kernel_pid_t get_current_active_pid(void) { return current_active_pid; }

    void set_current_active_pid(kernel_pid_t pid) { current_active_pid = pid; }

    void run(void);

    void set_thread_status(Thread *thread, thread_status_t status);

    void context_switch(uint8_t priority_to_switch);

    void sleeping_current_thread(void);

    int wakeup_thread(kernel_pid_t pid);

    void yield(void);

    static void yield_higher_priority_thread(void);

    static const char *thread_status_to_string(thread_status_t status);

#if VCOS_CONFIG_THREAD_FLAGS_ENABLE
    void thread_flags_set(Thread *thread, thread_flags_t mask);

    thread_flags_t thread_flags_clear(thread_flags_t mask);

    thread_flags_t thread_flags_wait_any(thread_flags_t mask);

    thread_flags_t thread_flags_wait_all(thread_flags_t mask);

    thread_flags_t thread_flags_wait_one(thread_flags_t mask);

    int thread_flags_wake(Thread *thread);
#endif

#if VCOS_CONFIG_THREAD_EVENT_ENABLE
    void event_claim(void);

    void event_post(Event *event);

    void event_cancel(Event *event);

    Event *event_get(void);

    Event *event_wait(void);

    void event_loop(void);
#endif

private:
    uint32_t get_runqueue_bitcache(void) { return runqueue_bitcache; }

    void set_runqueue_bitcache(uint8_t priority) { runqueue_bitcache |= 1 << priority; }

    void reset_runqueue_bitcache(uint8_t priority) { runqueue_bitcache &= ~(1 << priority); }

    Thread *get_next_thread_from_runqueue(void);

    uint8_t get_lsb_index_from_runqueue(void);

#if VCOS_CONFIG_THREAD_FLAGS_ENABLE
    thread_flags_t thread_flags_clear_atomic(Thread *thread, thread_flags_t mask);

    void thread_flags_wait(thread_flags_t mask, Thread *thread, thread_status_t thread_status, unsigned irqstate);

    void thread_flags_wait_any_blocked(thread_flags_t mask);
#endif

    int numof_threads_in_scheduler;

    unsigned int context_switch_request;

    Thread *scheduled_threads[KERNEL_PID_LAST + 1];

    Thread *current_active_thread;

    kernel_pid_t current_active_pid;

    Clist scheduler_runqueue[VCOS_CONFIG_THREAD_PRIORITY_LEVELS];

    uint32_t runqueue_bitcache;

    scheduler_stat_t scheduler_stats[KERNEL_PID_LAST + 1];

#if VCOS_CONFIG_THREAD_EVENT_ENABLE
    Clist event_list;

    Thread *event_waiter;
#endif
};

} // namespace vc

#endif /* CORE_THREAD_HPP */
