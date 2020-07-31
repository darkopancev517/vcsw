#include "gtest/gtest.h"

#include "core/instance.hpp"
#include "core/code_utils.hpp"
#include "core/mutex.hpp"
#include "core/msg.hpp"

#include "test-helper.h"

using namespace vc;

class TestMsg : public testing::Test
{
};

TEST_F(TestMsg, single_send_and_receive_msg)
{
    DEFINE_ALIGNED_VAR(buffer, sizeof(Instance), uint64_t);

    uint32_t size = ARRAY_LENGTH(buffer);

    Instance instance = Instance::init((void *)buffer, (size_t *)&size);

    EXPECT_TRUE(instance.is_initialized());

    EXPECT_EQ(instance.get<ThreadScheduler>().get_numof_threads_in_scheduler(), 0);
    EXPECT_EQ(instance.get<ThreadScheduler>().get_current_active_thread(), nullptr);
    EXPECT_EQ(instance.get<ThreadScheduler>().get_current_active_pid(), KERNEL_PID_UNDEF);

    char idle_stack[128];

    Thread *idle_thread = Thread::init(instance, idle_stack, sizeof(idle_stack), 15,
                                      THREAD_FLAGS_CREATE_WOUT_YIELD | \
                                      THREAD_FLAGS_CREATE_STACKMARKER,
                                      NULL, NULL, "idle");

    EXPECT_NE(idle_thread, nullptr);

    EXPECT_EQ(idle_thread->get_pid(), 1);
    EXPECT_EQ(idle_thread->get_priority(), 15);
    EXPECT_EQ(idle_thread->get_name(), "idle");
    EXPECT_EQ(idle_thread->get_status(), THREAD_STATUS_PENDING);

    char main_stack[128];

    Thread *main_thread = Thread::init(instance, main_stack, sizeof(main_stack), 7,
                                      THREAD_FLAGS_CREATE_WOUT_YIELD | \
                                      THREAD_FLAGS_CREATE_STACKMARKER,
                                      NULL, NULL, "main");

    EXPECT_NE(main_thread, nullptr);

    EXPECT_EQ(main_thread->get_pid(), 2);
    EXPECT_EQ(main_thread->get_priority(), 7);
    EXPECT_EQ(main_thread->get_name(), "main");
    EXPECT_EQ(main_thread->get_status(), THREAD_STATUS_PENDING);

    char task1_stack[128];

    Thread *task1_thread = Thread::init(instance, task1_stack, sizeof(task1_stack), 5,
                                       THREAD_FLAGS_CREATE_WOUT_YIELD | \
                                       THREAD_FLAGS_CREATE_STACKMARKER,
                                       NULL, NULL, "task1");

    EXPECT_NE(task1_thread, nullptr);

    EXPECT_EQ(task1_thread->get_pid(), 3);
    EXPECT_EQ(task1_thread->get_priority(), 5);
    EXPECT_EQ(task1_thread->get_name(), "task1");
    EXPECT_EQ(task1_thread->get_status(), THREAD_STATUS_PENDING);

    EXPECT_EQ(instance.get<ThreadScheduler>().get_numof_threads_in_scheduler(), 3);
    EXPECT_EQ(instance.get<ThreadScheduler>().get_thread_from_scheduler(idle_thread->get_pid()), idle_thread);
    EXPECT_EQ(instance.get<ThreadScheduler>().get_thread_from_scheduler(main_thread->get_pid()), main_thread);
    EXPECT_EQ(instance.get<ThreadScheduler>().get_thread_from_scheduler(task1_thread->get_pid()), task1_thread);
    EXPECT_FALSE(instance.get<ThreadScheduler>().is_context_switch_requested());
    EXPECT_EQ(instance.get<ThreadScheduler>().get_current_active_thread(), nullptr);
    EXPECT_EQ(instance.get<ThreadScheduler>().get_current_active_pid(), KERNEL_PID_UNDEF);

    EXPECT_EQ(main_thread->get_status(), THREAD_STATUS_PENDING);
    EXPECT_EQ(idle_thread->get_status(), THREAD_STATUS_PENDING);
    EXPECT_EQ(task1_thread->get_status(), THREAD_STATUS_PENDING);

    instance.get<ThreadScheduler>().run();

    EXPECT_EQ(main_thread->get_status(), THREAD_STATUS_PENDING);
    EXPECT_EQ(idle_thread->get_status(), THREAD_STATUS_PENDING);
    EXPECT_EQ(task1_thread->get_status(), THREAD_STATUS_RUNNING);

    EXPECT_EQ(instance.get<ThreadScheduler>().get_current_active_thread(), task1_thread);
    EXPECT_EQ(instance.get<ThreadScheduler>().get_current_active_pid(), task1_thread->get_pid());
    EXPECT_EQ(instance.get<ThreadScheduler>().get_numof_threads_in_scheduler(), 3);

    /**
     * -------------------------------------------------------------------------
     * [TEST CASE] make sure Msg class size is correct
     * -------------------------------------------------------------------------
     **/

    EXPECT_EQ(sizeof(Msg), sizeof(msg_t));

    /**
     * -------------------------------------------------------------------------
     * [TEST CASE] basic send and receive message
     * -------------------------------------------------------------------------
     **/

    Msg msg1 = Msg(instance);

    EXPECT_EQ(msg1.sender_pid, KERNEL_PID_UNDEF);
    EXPECT_EQ(msg1.type, 0);
    EXPECT_EQ(msg1.content.ptr, nullptr);
    EXPECT_EQ(msg1.content.value, 0);

    /* call msg.receive() in current thread (task1_thread), it expected to set
     * current thread status to receive blocking */

    msg1.receive();

    EXPECT_EQ(main_thread->get_status(), THREAD_STATUS_PENDING);
    EXPECT_EQ(idle_thread->get_status(), THREAD_STATUS_PENDING);
    EXPECT_EQ(task1_thread->get_status(), THREAD_STATUS_RECEIVE_BLOCKED);

    instance.get<ThreadScheduler>().run();

    EXPECT_EQ(main_thread->get_status(), THREAD_STATUS_RUNNING);
    EXPECT_EQ(idle_thread->get_status(), THREAD_STATUS_PENDING);
    EXPECT_EQ(task1_thread->get_status(), THREAD_STATUS_RECEIVE_BLOCKED);

    Msg msg2 = Msg(instance);

    EXPECT_EQ(msg2.sender_pid, KERNEL_PID_UNDEF);
    EXPECT_EQ(msg2.type, 0);
    EXPECT_EQ(msg2.content.ptr, nullptr);
    EXPECT_EQ(msg2.content.value, 0);

    uint32_t msgValue = 0xdeadbeef;

    msg2.type = 0x20;
    msg2.content.ptr = static_cast<void *>(&msgValue);

    EXPECT_EQ(msg2.send(task1_thread->get_pid()), 1);

    EXPECT_EQ(main_thread->get_status(), THREAD_STATUS_RUNNING);
    EXPECT_EQ(idle_thread->get_status(), THREAD_STATUS_PENDING);
    EXPECT_EQ(task1_thread->get_status(), THREAD_STATUS_PENDING);

    /* Note: at this point, msg2 is immediately received by task1_thread because
     * it was in RECEIVE_BLOCKED status */

    instance.get<ThreadScheduler>().run();

    EXPECT_EQ(main_thread->get_status(), THREAD_STATUS_PENDING);
    EXPECT_EQ(idle_thread->get_status(), THREAD_STATUS_PENDING);
    EXPECT_EQ(task1_thread->get_status(), THREAD_STATUS_RUNNING);

    EXPECT_EQ(msg1.sender_pid, main_thread->get_pid());
    EXPECT_EQ(msg1.type, 0x20);
    EXPECT_NE(msg1.content.ptr, nullptr);
    EXPECT_EQ(*static_cast<uint32_t *>(msg1.content.ptr), 0xdeadbeef);

    /**
     * -------------------------------------------------------------------------
     * [TEST CASE] send message to a thread that doesn't in receive blocked
     * -------------------------------------------------------------------------
     **/

    Msg msg3 = Msg(instance);

    EXPECT_EQ(msg3.sender_pid, KERNEL_PID_UNDEF);
    EXPECT_EQ(msg3.type, 0);
    EXPECT_EQ(msg3.content.ptr, nullptr);
    EXPECT_EQ(msg3.content.value, 0);

    msg3.type = 0x21;
    msg3.content.value = 0xdeadbeef;

    EXPECT_EQ(msg3.send(main_thread->get_pid()), 1);

    EXPECT_EQ(main_thread->get_status(), THREAD_STATUS_PENDING);
    EXPECT_EQ(idle_thread->get_status(), THREAD_STATUS_PENDING);
    EXPECT_EQ(task1_thread->get_status(), THREAD_STATUS_SEND_BLOCKED);

    instance.get<ThreadScheduler>().run();

    /* now we are in main_thread */

    EXPECT_EQ(main_thread->get_status(), THREAD_STATUS_RUNNING);
    EXPECT_EQ(idle_thread->get_status(), THREAD_STATUS_PENDING);
    EXPECT_EQ(task1_thread->get_status(), THREAD_STATUS_SEND_BLOCKED);

    Msg msg4 = Msg(instance);

    EXPECT_EQ(msg4.sender_pid, KERNEL_PID_UNDEF);
    EXPECT_EQ(msg4.type, 0);
    EXPECT_EQ(msg4.content.ptr, nullptr);
    EXPECT_EQ(msg4.content.value, 0);

    msg4.receive(); /* try to receive msg that was sent by task1_thread */

    EXPECT_EQ(msg4.sender_pid, task1_thread->get_pid());
    EXPECT_EQ(msg4.type, 0x21);
    EXPECT_EQ(msg4.content.value, 0xdeadbeef);

    EXPECT_EQ(main_thread->get_status(), THREAD_STATUS_RUNNING);
    EXPECT_EQ(idle_thread->get_status(), THREAD_STATUS_PENDING);
    EXPECT_EQ(task1_thread->get_status(), THREAD_STATUS_PENDING);

    /* Note: at this point msg3 already received by main_thread and because
     * task1_thread has higher priority than main_thread, kernel will context
     * switch to task1_thread */

    instance.get<ThreadScheduler>().run();

    EXPECT_EQ(main_thread->get_status(), THREAD_STATUS_PENDING);
    EXPECT_EQ(idle_thread->get_status(), THREAD_STATUS_PENDING);
    EXPECT_EQ(task1_thread->get_status(), THREAD_STATUS_RUNNING);

    /**
     * -------------------------------------------------------------------------
     * [TEST CASE] try send a message to a thread that doesn't in receive
     * blocked status
     * -------------------------------------------------------------------------
     **/

    Msg msg5 = Msg(instance);

    EXPECT_EQ(msg5.sender_pid, KERNEL_PID_UNDEF);
    EXPECT_EQ(msg5.type, 0);
    EXPECT_EQ(msg5.content.ptr, nullptr);
    EXPECT_EQ(msg5.content.value, 0);

    msg5.type = 0x22;
    msg5.content.value = 0xdeadbeef;

    EXPECT_EQ(main_thread->get_status(), THREAD_STATUS_PENDING);
    EXPECT_EQ(idle_thread->get_status(), THREAD_STATUS_PENDING);
    EXPECT_EQ(task1_thread->get_status(), THREAD_STATUS_RUNNING);

    EXPECT_EQ(msg5.try_send(main_thread->get_pid()), 0);

    EXPECT_EQ(main_thread->get_status(), THREAD_STATUS_PENDING);
    EXPECT_EQ(idle_thread->get_status(), THREAD_STATUS_PENDING);
    EXPECT_EQ(task1_thread->get_status(), THREAD_STATUS_RUNNING);

    /* Note: none of these try_send message will works unless the target thread
     * is in receive blocked status */

    EXPECT_EQ(msg5.try_send(main_thread->get_pid()), 0);
    EXPECT_EQ(msg5.try_send(main_thread->get_pid()), 0);
    EXPECT_EQ(msg5.try_send(main_thread->get_pid()), 0);
    EXPECT_EQ(msg5.try_send(main_thread->get_pid()), 0);
    EXPECT_EQ(msg5.try_send(main_thread->get_pid()), 0);
    EXPECT_EQ(msg5.try_send(main_thread->get_pid()), 0);

    EXPECT_EQ(main_thread->get_status(), THREAD_STATUS_PENDING);
    EXPECT_EQ(idle_thread->get_status(), THREAD_STATUS_PENDING);
    EXPECT_EQ(task1_thread->get_status(), THREAD_STATUS_RUNNING);

    instance.get<ThreadScheduler>().sleeping_current_thread();

    EXPECT_EQ(main_thread->get_status(), THREAD_STATUS_PENDING);
    EXPECT_EQ(idle_thread->get_status(), THREAD_STATUS_PENDING);
    EXPECT_EQ(task1_thread->get_status(), THREAD_STATUS_SLEEPING);

    instance.get<ThreadScheduler>().run();

    EXPECT_EQ(main_thread->get_status(), THREAD_STATUS_RUNNING);
    EXPECT_EQ(idle_thread->get_status(), THREAD_STATUS_PENDING);
    EXPECT_EQ(task1_thread->get_status(), THREAD_STATUS_SLEEPING);

    Msg msg6 = Msg(instance);

    EXPECT_EQ(msg6.sender_pid, KERNEL_PID_UNDEF);
    EXPECT_EQ(msg6.type, 0);
    EXPECT_EQ(msg6.content.ptr, nullptr);
    EXPECT_EQ(msg6.content.value, 0);

    msg6.receive();

    EXPECT_EQ(main_thread->get_status(), THREAD_STATUS_RECEIVE_BLOCKED);
    EXPECT_EQ(idle_thread->get_status(), THREAD_STATUS_PENDING);
    EXPECT_EQ(task1_thread->get_status(), THREAD_STATUS_SLEEPING);

    instance.get<ThreadScheduler>().run();

    EXPECT_EQ(main_thread->get_status(), THREAD_STATUS_RECEIVE_BLOCKED);
    EXPECT_EQ(idle_thread->get_status(), THREAD_STATUS_RUNNING);
    EXPECT_EQ(task1_thread->get_status(), THREAD_STATUS_SLEEPING);

    instance.get<ThreadScheduler>().wakeup_thread(task1_thread->get_pid());

    EXPECT_EQ(main_thread->get_status(), THREAD_STATUS_RECEIVE_BLOCKED);
    EXPECT_EQ(idle_thread->get_status(), THREAD_STATUS_RUNNING);
    EXPECT_EQ(task1_thread->get_status(), THREAD_STATUS_RUNNING);

    instance.get<ThreadScheduler>().run();

    EXPECT_EQ(main_thread->get_status(), THREAD_STATUS_RECEIVE_BLOCKED);
    EXPECT_EQ(idle_thread->get_status(), THREAD_STATUS_PENDING);
    EXPECT_EQ(task1_thread->get_status(), THREAD_STATUS_RUNNING);

    /* Note: now try_send() will succeed */

    EXPECT_EQ(msg5.try_send(main_thread->get_pid()), 1);

    EXPECT_EQ(main_thread->get_status(), THREAD_STATUS_PENDING);
    EXPECT_EQ(idle_thread->get_status(), THREAD_STATUS_PENDING);
    EXPECT_EQ(task1_thread->get_status(), THREAD_STATUS_RUNNING);

    /* message is successfully received */

    EXPECT_EQ(msg6.sender_pid, task1_thread->get_pid());
    EXPECT_EQ(msg6.type, 0x22);
    EXPECT_EQ(msg6.content.value, 0xdeadbeef);

    instance.get<ThreadScheduler>().run();

    EXPECT_EQ(main_thread->get_status(), THREAD_STATUS_PENDING);
    EXPECT_EQ(idle_thread->get_status(), THREAD_STATUS_PENDING);
    EXPECT_EQ(task1_thread->get_status(), THREAD_STATUS_RUNNING);

    EXPECT_EQ(msg5.send_to_self_queue(), 0); /* we dont use message queue yet */

    /**
     * -------------------------------------------------------------------------
     * [TEST CASE] send message from Isr
     * -------------------------------------------------------------------------
     **/

    msg6.receive();

    EXPECT_EQ(main_thread->get_status(), THREAD_STATUS_PENDING);
    EXPECT_EQ(idle_thread->get_status(), THREAD_STATUS_PENDING);
    EXPECT_EQ(task1_thread->get_status(), THREAD_STATUS_RECEIVE_BLOCKED);

    instance.get<ThreadScheduler>().run();

    EXPECT_EQ(main_thread->get_status(), THREAD_STATUS_RUNNING);
    EXPECT_EQ(idle_thread->get_status(), THREAD_STATUS_PENDING);
    EXPECT_EQ(task1_thread->get_status(), THREAD_STATUS_RECEIVE_BLOCKED);

    test_helper_set_cpu_in_isr();

    msg5.type = 0xff;
    msg5.content.value = 0x12345678;

    EXPECT_EQ(msg5.send(task1_thread->get_pid()), 1);

    EXPECT_EQ(main_thread->get_status(), THREAD_STATUS_RUNNING);
    EXPECT_EQ(idle_thread->get_status(), THREAD_STATUS_PENDING);
    EXPECT_EQ(task1_thread->get_status(), THREAD_STATUS_PENDING);

    EXPECT_TRUE(instance.get<ThreadScheduler>().is_context_switch_requested());

    cpu_end_of_isr((instance_t *)&instance);

    EXPECT_EQ(main_thread->get_status(), THREAD_STATUS_RUNNING);
    EXPECT_EQ(idle_thread->get_status(), THREAD_STATUS_PENDING);
    EXPECT_EQ(task1_thread->get_status(), THREAD_STATUS_PENDING);

    test_helper_reset_cpu_in_isr();

    instance.get<ThreadScheduler>().run();

    EXPECT_EQ(main_thread->get_status(), THREAD_STATUS_PENDING);
    EXPECT_EQ(idle_thread->get_status(), THREAD_STATUS_PENDING);
    EXPECT_EQ(task1_thread->get_status(), THREAD_STATUS_RUNNING);

    EXPECT_EQ(msg6.sender_pid, KERNEL_PID_ISR);
    EXPECT_EQ(msg6.type, 0xff);
    EXPECT_EQ(msg6.content.value, 0x12345678);

    /* Note: send message from Isr when the target is not in receive blocked */

    test_helper_set_cpu_in_isr();

    EXPECT_EQ(msg5.send(task1_thread->get_pid()), 0);

    cpu_end_of_isr((instance_t *)&instance);

    EXPECT_EQ(main_thread->get_status(), THREAD_STATUS_PENDING);
    EXPECT_EQ(idle_thread->get_status(), THREAD_STATUS_PENDING);
    EXPECT_EQ(task1_thread->get_status(), THREAD_STATUS_RUNNING);

    test_helper_reset_cpu_in_isr();

    instance.get<ThreadScheduler>().run();

    EXPECT_EQ(main_thread->get_status(), THREAD_STATUS_PENDING);
    EXPECT_EQ(idle_thread->get_status(), THREAD_STATUS_PENDING);
    EXPECT_EQ(task1_thread->get_status(), THREAD_STATUS_RUNNING);

    /**
     * -------------------------------------------------------------------------
     * [TEST CASE] send and then immediately set to receive state by calling
     * sendReceive function.
     * -------------------------------------------------------------------------
     **/

    Msg msg7 = Msg(instance);
    Msg msg7_reply = Msg(instance);

    EXPECT_EQ(msg7.sender_pid, KERNEL_PID_UNDEF);
    EXPECT_EQ(msg7.type, 0);
    EXPECT_EQ(msg7.content.ptr, nullptr);
    EXPECT_EQ(msg7.content.value, 0);

    EXPECT_EQ(msg7_reply.sender_pid, KERNEL_PID_UNDEF);
    EXPECT_EQ(msg7_reply.type, 0);
    EXPECT_EQ(msg7_reply.content.ptr, nullptr);
    EXPECT_EQ(msg7_reply.content.value, 0);

    uint32_t msg7_data = 0xdeeeaaad;

    msg7.type = 0xfe;
    msg7.content.ptr = static_cast<void *>(&msg7_data);

    EXPECT_EQ(msg7.send_receive(&msg7_reply, main_thread->get_pid()), 1);

    EXPECT_EQ(main_thread->get_status(), THREAD_STATUS_PENDING);
    EXPECT_EQ(idle_thread->get_status(), THREAD_STATUS_PENDING);
    EXPECT_EQ(task1_thread->get_status(), THREAD_STATUS_REPLY_BLOCKED);

    instance.get<ThreadScheduler>().run();

    EXPECT_EQ(main_thread->get_status(), THREAD_STATUS_RUNNING);
    EXPECT_EQ(idle_thread->get_status(), THREAD_STATUS_PENDING);
    EXPECT_EQ(task1_thread->get_status(), THREAD_STATUS_REPLY_BLOCKED);

    Msg msg8 = Msg(instance);
    Msg msg8_reply = Msg(instance);

    EXPECT_EQ(msg8.sender_pid, KERNEL_PID_UNDEF);
    EXPECT_EQ(msg8.type, 0);
    EXPECT_EQ(msg8.content.ptr, nullptr);
    EXPECT_EQ(msg8.content.value, 0);

    EXPECT_EQ(msg8_reply.sender_pid, KERNEL_PID_UNDEF);
    EXPECT_EQ(msg8_reply.type, 0);
    EXPECT_EQ(msg8_reply.content.ptr, nullptr);
    EXPECT_EQ(msg8_reply.content.value, 0);

    msg8.receive();

    EXPECT_EQ(msg8.sender_pid, task1_thread->get_pid());
    EXPECT_EQ(msg8.type, 0xfe);
    EXPECT_EQ(*static_cast<uint32_t *>(msg8.content.ptr), 0xdeeeaaad);

    /* Note: at this point msg7 is received */

    instance.get<ThreadScheduler>().run();

    EXPECT_EQ(main_thread->get_status(), THREAD_STATUS_RUNNING);
    EXPECT_EQ(idle_thread->get_status(), THREAD_STATUS_PENDING);
    EXPECT_EQ(task1_thread->get_status(), THREAD_STATUS_REPLY_BLOCKED);

    msg8_reply.type = 0xff;
    msg8_reply.content.value = 0xdeadbeef;

    EXPECT_EQ(msg8.reply(&msg8_reply), 1);

    EXPECT_EQ(main_thread->get_status(), THREAD_STATUS_RUNNING);
    EXPECT_EQ(idle_thread->get_status(), THREAD_STATUS_PENDING);
    EXPECT_EQ(task1_thread->get_status(), THREAD_STATUS_PENDING);

    instance.get<ThreadScheduler>().run();

    EXPECT_EQ(main_thread->get_status(), THREAD_STATUS_PENDING);
    EXPECT_EQ(idle_thread->get_status(), THREAD_STATUS_PENDING);
    EXPECT_EQ(task1_thread->get_status(), THREAD_STATUS_RUNNING);

    EXPECT_EQ(msg7_reply.type, 0xff);
    EXPECT_EQ(msg7_reply.content.value, 0xdeadbeef);

    /* Note: reply msg does not care who was replying the message */

    /**
     * -------------------------------------------------------------------------
     * [TEST CASE] send and then immediately set to receive state by calling
     * sendReceive function. reply function would be in Isr.
     * -------------------------------------------------------------------------
     **/

    msg7.type = 0xab;
    msg7.content.value = 0xaaaabbbb;

    EXPECT_EQ(msg7.send_receive(&msg7_reply, main_thread->get_pid()), 1);

    EXPECT_EQ(main_thread->get_status(), THREAD_STATUS_PENDING);
    EXPECT_EQ(idle_thread->get_status(), THREAD_STATUS_PENDING);
    EXPECT_EQ(task1_thread->get_status(), THREAD_STATUS_REPLY_BLOCKED);

    instance.get<ThreadScheduler>().run();

    EXPECT_EQ(main_thread->get_status(), THREAD_STATUS_RUNNING);
    EXPECT_EQ(idle_thread->get_status(), THREAD_STATUS_PENDING);
    EXPECT_EQ(task1_thread->get_status(), THREAD_STATUS_REPLY_BLOCKED);

    msg8.receive();

    EXPECT_EQ(msg8.sender_pid, task1_thread->get_pid());
    EXPECT_EQ(msg8.type, 0xab);
    EXPECT_EQ(msg8.content.value, 0xaaaabbbb);

    /* Note: at this point msg7 is received */

    instance.get<ThreadScheduler>().run();

    EXPECT_EQ(main_thread->get_status(), THREAD_STATUS_RUNNING);
    EXPECT_EQ(idle_thread->get_status(), THREAD_STATUS_PENDING);
    EXPECT_EQ(task1_thread->get_status(), THREAD_STATUS_REPLY_BLOCKED);

    msg8_reply.type = 0xcd;
    msg8_reply.content.value = 0xccccdddd;

    test_helper_set_cpu_in_isr(); /* ----------------- set cpu artificially in Isr */

    EXPECT_EQ(msg8.reply_in_isr(&msg8_reply), 1);

    EXPECT_EQ(main_thread->get_status(), THREAD_STATUS_RUNNING);
    EXPECT_EQ(idle_thread->get_status(), THREAD_STATUS_PENDING);
    EXPECT_EQ(task1_thread->get_status(), THREAD_STATUS_PENDING);

    cpu_end_of_isr(&instance);

    test_helper_reset_cpu_in_isr(); /* ---------------------------------- exit Isr */

    EXPECT_TRUE(instance.get<ThreadScheduler>().is_context_switch_requested());

    instance.get<ThreadScheduler>().run();

    EXPECT_EQ(main_thread->get_status(), THREAD_STATUS_PENDING);
    EXPECT_EQ(idle_thread->get_status(), THREAD_STATUS_PENDING);
    EXPECT_EQ(task1_thread->get_status(), THREAD_STATUS_RUNNING);

    EXPECT_EQ(msg7_reply.type, 0xcd);
    EXPECT_EQ(msg7_reply.content.value, 0xccccdddd);

    /* Note: reply message was sent from Isr */
}

TEST_F(TestMsg, multiple_send_and_receive_msg)
{
    DEFINE_ALIGNED_VAR(buffer, sizeof(Instance), uint64_t);

    uint32_t size = ARRAY_LENGTH(buffer);

    Instance instance = Instance::init((void *)buffer, (size_t *)&size);

    EXPECT_TRUE(instance.is_initialized());

    EXPECT_EQ(instance.get<ThreadScheduler>().get_numof_threads_in_scheduler(), 0);
    EXPECT_EQ(instance.get<ThreadScheduler>().get_current_active_thread(), nullptr);
    EXPECT_EQ(instance.get<ThreadScheduler>().get_current_active_pid(), KERNEL_PID_UNDEF);

    char idle_stack[128];

    Thread *idle_thread = Thread::init(instance, idle_stack, sizeof(idle_stack), 15,
                                       THREAD_FLAGS_CREATE_WOUT_YIELD | THREAD_FLAGS_CREATE_STACKMARKER,
                                       NULL, NULL, "idle");

    EXPECT_NE(idle_thread, nullptr);

    EXPECT_EQ(idle_thread->get_pid(), 1);
    EXPECT_EQ(idle_thread->get_priority(), 15);
    EXPECT_EQ(idle_thread->get_name(), "idle");
    EXPECT_EQ(idle_thread->get_status(), THREAD_STATUS_PENDING);

    char main_stack[128];

    Thread *main_thread = Thread::init(instance, main_stack, sizeof(main_stack), 7,
                                       THREAD_FLAGS_CREATE_WOUT_YIELD | THREAD_FLAGS_CREATE_STACKMARKER,
                                       NULL, NULL, "main");

    EXPECT_NE(main_thread, nullptr);

    EXPECT_EQ(main_thread->get_pid(), 2);
    EXPECT_EQ(main_thread->get_priority(), 7);
    EXPECT_EQ(main_thread->get_name(), "main");
    EXPECT_EQ(main_thread->get_status(), THREAD_STATUS_PENDING);

    char task1_stack[128];

    Thread *task1_thread = Thread::init(instance, task1_stack, sizeof(task1_stack), 5,
                                        THREAD_FLAGS_CREATE_WOUT_YIELD | THREAD_FLAGS_CREATE_STACKMARKER,
                                        NULL, NULL, "task1");

    EXPECT_NE(task1_thread, nullptr);

    EXPECT_EQ(task1_thread->get_pid(), 3);
    EXPECT_EQ(task1_thread->get_priority(), 5);
    EXPECT_EQ(task1_thread->get_name(), "task1");
    EXPECT_EQ(task1_thread->get_status(), THREAD_STATUS_PENDING);

    EXPECT_EQ(instance.get<ThreadScheduler>().get_numof_threads_in_scheduler(), 3);
    EXPECT_EQ(instance.get<ThreadScheduler>().get_thread_from_scheduler(idle_thread->get_pid()), idle_thread);
    EXPECT_EQ(instance.get<ThreadScheduler>().get_thread_from_scheduler(main_thread->get_pid()), main_thread);
    EXPECT_EQ(instance.get<ThreadScheduler>().get_thread_from_scheduler(task1_thread->get_pid()), task1_thread);
    EXPECT_FALSE(instance.get<ThreadScheduler>().is_context_switch_requested());
    EXPECT_EQ(instance.get<ThreadScheduler>().get_current_active_thread(), nullptr);
    EXPECT_EQ(instance.get<ThreadScheduler>().get_current_active_pid(), KERNEL_PID_UNDEF);

    EXPECT_EQ(main_thread->get_status(), THREAD_STATUS_PENDING);
    EXPECT_EQ(idle_thread->get_status(), THREAD_STATUS_PENDING);
    EXPECT_EQ(task1_thread->get_status(), THREAD_STATUS_PENDING);

    instance.get<ThreadScheduler>().run();

    EXPECT_EQ(main_thread->get_status(), THREAD_STATUS_PENDING);
    EXPECT_EQ(idle_thread->get_status(), THREAD_STATUS_PENDING);
    EXPECT_EQ(task1_thread->get_status(), THREAD_STATUS_RUNNING);

    EXPECT_EQ(instance.get<ThreadScheduler>().get_current_active_thread(), task1_thread);
    EXPECT_EQ(instance.get<ThreadScheduler>().get_current_active_pid(), task1_thread->get_pid());
    EXPECT_EQ(instance.get<ThreadScheduler>().get_numof_threads_in_scheduler(), 3);

    /**
     * -------------------------------------------------------------------------
     * [TEST CASE] create msg queue in current active thread
     * -------------------------------------------------------------------------
     **/

    EXPECT_EQ(task1_thread->has_msg_queue(), 0);

    Msg task1_msg_array[16];

    for (int i = 0; i < 16; i++)
    {
        task1_msg_array[i].init(instance);
    }

    task1_thread->init_msg_queue(task1_msg_array, ARRAY_LENGTH(task1_msg_array));

    EXPECT_EQ(task1_thread->has_msg_queue(), 1);
    EXPECT_EQ(task1_thread->get_numof_msg_in_queue(), 0);

    /**
     * -------------------------------------------------------------------------
     * [TEST CASE] set current active thread to sleep status and send msg to it,
     * it expected to queued the msg.
     * -------------------------------------------------------------------------
     **/

    instance.get<ThreadScheduler>().set_thread_status(task1_thread, THREAD_STATUS_SLEEPING);

    EXPECT_EQ(main_thread->get_status(), THREAD_STATUS_PENDING);
    EXPECT_EQ(idle_thread->get_status(), THREAD_STATUS_PENDING);
    EXPECT_EQ(task1_thread->get_status(), THREAD_STATUS_SLEEPING);

    instance.get<ThreadScheduler>().run();

    EXPECT_EQ(main_thread->get_status(), THREAD_STATUS_RUNNING);
    EXPECT_EQ(idle_thread->get_status(), THREAD_STATUS_PENDING);
    EXPECT_EQ(task1_thread->get_status(), THREAD_STATUS_SLEEPING);

    Msg msg1 = Msg(instance);
    Msg msg2 = Msg(instance);
    Msg msg3 = Msg(instance);
    Msg msg4 = Msg(instance);

    msg1.type = 0xff;
    msg1.content.value = 0x1;

    msg2.type = 0xff;
    msg2.content.value = 0x2;

    msg3.type = 0xff;
    msg3.content.value = 0x3;

    msg4.type = 0xff;
    msg4.content.value = 0x4;

    EXPECT_EQ(msg1.send(task1_thread->get_pid()), 1);
    EXPECT_EQ(msg2.send(task1_thread->get_pid()), 1);
    EXPECT_EQ(msg3.send(task1_thread->get_pid()), 1);
    EXPECT_EQ(msg4.send(task1_thread->get_pid()), 1);

    /* Note: task1_thread is in sleeping status and has message queue, so the
     * message sent to task1_thread should be queued */

    EXPECT_EQ(task1_thread->get_numof_msg_in_queue(), 4);

    /* Note: set task1_thread to running status and dequeque the message */

    instance.get<ThreadScheduler>().set_thread_status(task1_thread, THREAD_STATUS_PENDING);

    EXPECT_EQ(main_thread->get_status(), THREAD_STATUS_RUNNING);
    EXPECT_EQ(idle_thread->get_status(), THREAD_STATUS_PENDING);
    EXPECT_EQ(task1_thread->get_status(), THREAD_STATUS_PENDING);

    instance.get<ThreadScheduler>().run();

    EXPECT_EQ(main_thread->get_status(), THREAD_STATUS_PENDING);
    EXPECT_EQ(idle_thread->get_status(), THREAD_STATUS_PENDING);
    EXPECT_EQ(task1_thread->get_status(), THREAD_STATUS_RUNNING);

    EXPECT_EQ(task1_thread->get_numof_msg_in_queue(), 4);

    Msg msg_intask1 = Msg(instance);

    EXPECT_EQ(msg_intask1.receive(), 1);

    EXPECT_EQ(msg_intask1.sender_pid, main_thread->get_pid());
    EXPECT_EQ(msg_intask1.type, 0xff);
    EXPECT_EQ(msg_intask1.content.value, 0x01); /* get msg1 */

    EXPECT_EQ(msg_intask1.receive(), 1);

    EXPECT_EQ(msg_intask1.sender_pid, main_thread->get_pid());
    EXPECT_EQ(msg_intask1.type, 0xff);
    EXPECT_EQ(msg_intask1.content.value, 0x02); /* get msg2 */

     EXPECT_EQ(msg_intask1.receive(), 1);

    EXPECT_EQ(msg_intask1.sender_pid, main_thread->get_pid());
    EXPECT_EQ(msg_intask1.type, 0xff);
    EXPECT_EQ(msg_intask1.content.value, 0x03); /* get msg3 */

    EXPECT_EQ(msg_intask1.receive(), 1);

    EXPECT_EQ(msg_intask1.sender_pid, main_thread->get_pid());
    EXPECT_EQ(msg_intask1.type, 0xff);
    EXPECT_EQ(msg_intask1.content.value, 0x04); /* get msg4 */

    EXPECT_EQ(main_thread->get_status(), THREAD_STATUS_PENDING);
    EXPECT_EQ(idle_thread->get_status(), THREAD_STATUS_PENDING);
    EXPECT_EQ(task1_thread->get_status(), THREAD_STATUS_RUNNING);

    EXPECT_EQ(task1_thread->get_numof_msg_in_queue(), 0);

    /* Note: at this point we already got all the message from queue */

    /**
     * -------------------------------------------------------------------------
     * [TEST CASE] send message to itself
     * -------------------------------------------------------------------------
     **/

    EXPECT_EQ(msg1.send(task1_thread->get_pid()), 1);
    EXPECT_EQ(msg2.try_send(task1_thread->get_pid()), 1);
    EXPECT_EQ(msg3.send(task1_thread->get_pid()), 1);
    EXPECT_EQ(msg4.try_send(task1_thread->get_pid()), 1);

    EXPECT_EQ(task1_thread->get_numof_msg_in_queue(), 4);

    EXPECT_EQ(msg_intask1.receive(), 1);

    EXPECT_EQ(msg_intask1.sender_pid, task1_thread->get_pid());
    EXPECT_EQ(msg_intask1.type, 0xff);
    EXPECT_EQ(msg_intask1.content.value, 0x01); /* get msg1 */

    EXPECT_EQ(msg_intask1.receive(), 1);

    EXPECT_EQ(msg_intask1.sender_pid, task1_thread->get_pid());
    EXPECT_EQ(msg_intask1.type, 0xff);
    EXPECT_EQ(msg_intask1.content.value, 0x02); /* get msg2 */

     EXPECT_EQ(msg_intask1.receive(), 1);

    EXPECT_EQ(msg_intask1.sender_pid, task1_thread->get_pid());
    EXPECT_EQ(msg_intask1.type, 0xff);
    EXPECT_EQ(msg_intask1.content.value, 0x03); /* get msg3 */

    EXPECT_EQ(msg_intask1.receive(), 1);

    EXPECT_EQ(msg_intask1.sender_pid, task1_thread->get_pid());
    EXPECT_EQ(msg_intask1.type, 0xff);
    EXPECT_EQ(msg_intask1.content.value, 0x04); /* get msg4 */

    EXPECT_EQ(main_thread->get_status(), THREAD_STATUS_PENDING);
    EXPECT_EQ(idle_thread->get_status(), THREAD_STATUS_PENDING);
    EXPECT_EQ(task1_thread->get_status(), THREAD_STATUS_RUNNING);

    EXPECT_EQ(task1_thread->get_numof_msg_in_queue(), 0);
}
