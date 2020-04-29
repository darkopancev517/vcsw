#include "gtest/gtest.h"

#include "core/instance.hpp"
#include "core/code_utils.hpp"
#include "core/locator-getters.hpp"

#include "test-helper.h"

using namespace mt;

class TestThread : public testing::Test
{
protected:
    virtual void SetUp()
    {
    }

    virtual void TearDown()
    {
    }
};

TEST_F(TestThread, singleThread)
{
    mtDEFINE_ALIGNED_VAR(buffer, sizeof(Instance), uint64_t);

    uint32_t size = mtARRAY_LENGTH(buffer);

    Instance instance = Instance::Init((void *)buffer, (size_t *)&size);

    EXPECT_TRUE(instance.IsInitialized());

    EXPECT_EQ(instance.Get<ThreadScheduler>().GetNumOfThreadsInScheduler(), 0);
    EXPECT_EQ(instance.Get<ThreadScheduler>().GetCurrentActiveThread(), nullptr);
    EXPECT_EQ(instance.Get<ThreadScheduler>().GetCurrentActivePid(), KERNEL_PID_UNDEF);

    /**
     * -------------------------------------------------------------------------
     * [TEST CASE] create single thread and run the thread scheduler, that
     * thread is expected to be in running state and become current active
     * thread
     * -------------------------------------------------------------------------
     **/

    char stack[128];

    Thread *thread = Thread::Init(instance, stack, sizeof(stack), 15,
                                  THREAD_FLAGS_CREATE_WOUT_YIELD | \
                                  THREAD_FLAGS_CREATE_STACKMARKER,
                                  NULL, NULL, "idle");

    EXPECT_NE(thread, nullptr);

    EXPECT_EQ(thread->GetPid(), 1);
    EXPECT_EQ(thread->GetPriority(), 15);
    EXPECT_EQ(thread->GetName(), "idle");
    EXPECT_EQ(thread->GetStatus(), THREAD_STATUS_PENDING);

    EXPECT_EQ(instance.Get<ThreadScheduler>().GetNumOfThreadsInScheduler(), 1);
    EXPECT_EQ(instance.Get<ThreadScheduler>().GetThreadFromScheduler(thread->GetPid()), thread);
    EXPECT_FALSE(instance.Get<ThreadScheduler>().IsContextSwitchRequested());
    EXPECT_EQ(instance.Get<ThreadScheduler>().GetCurrentActiveThread(), nullptr);
    EXPECT_EQ(instance.Get<ThreadScheduler>().GetCurrentActivePid(), KERNEL_PID_UNDEF);

    instance.Get<ThreadScheduler>().Run();

    EXPECT_EQ(thread->GetStatus(), THREAD_STATUS_RUNNING);

    EXPECT_EQ(instance.Get<ThreadScheduler>().GetCurrentActiveThread(), thread);
    EXPECT_EQ(instance.Get<ThreadScheduler>().GetCurrentActivePid(), thread->GetPid());
    EXPECT_EQ(instance.Get<ThreadScheduler>().GetNumOfThreadsInScheduler(), 1);
}

TEST_F(TestThread, multipleThread)
{
    mtDEFINE_ALIGNED_VAR(buffer, sizeof(Instance), uint64_t);

    uint32_t size = mtARRAY_LENGTH(buffer);

    Instance instance = Instance::Init((void *)buffer, (size_t *)&size);

    EXPECT_TRUE(instance.IsInitialized());

    EXPECT_EQ(instance.Get<ThreadScheduler>().GetNumOfThreadsInScheduler(), 0);
    EXPECT_EQ(instance.Get<ThreadScheduler>().GetCurrentActiveThread(), nullptr);
    EXPECT_EQ(instance.Get<ThreadScheduler>().GetCurrentActivePid(), KERNEL_PID_UNDEF);

    /**
     * -------------------------------------------------------------------------
     * [TEST CASE] create multiple thread ("idle" and "main" thread) and make
     * sure the thread with higher priority will be in running state and the
     * thread with lower priority ("idle" thread) is in pending state
     * -------------------------------------------------------------------------
     **/

    char idleStack[128];

    Thread *idleThread = Thread::Init(instance, idleStack, sizeof(idleStack), 15,
                                      THREAD_FLAGS_CREATE_WOUT_YIELD | \
                                      THREAD_FLAGS_CREATE_STACKMARKER,
                                      NULL, NULL, "idle");

    EXPECT_NE(idleThread, nullptr);

    EXPECT_EQ(idleThread->GetPid(), 1);
    EXPECT_EQ(idleThread->GetPriority(), 15);
    EXPECT_EQ(idleThread->GetName(), "idle");
    EXPECT_EQ(idleThread->GetStatus(), THREAD_STATUS_PENDING);

    char mainStack[128];

    Thread *mainThread = Thread::Init(instance, mainStack, sizeof(mainStack), 7,
                                      THREAD_FLAGS_CREATE_WOUT_YIELD | \
                                      THREAD_FLAGS_CREATE_STACKMARKER,
                                      NULL, NULL, "main");

    EXPECT_NE(mainThread, nullptr);

    EXPECT_EQ(mainThread->GetPid(), 2);
    EXPECT_EQ(mainThread->GetPriority(), 7);
    EXPECT_EQ(mainThread->GetName(), "main");
    EXPECT_EQ(mainThread->GetStatus(), THREAD_STATUS_PENDING);

    EXPECT_EQ(instance.Get<ThreadScheduler>().GetNumOfThreadsInScheduler(), 2);
    EXPECT_EQ(instance.Get<ThreadScheduler>().GetThreadFromScheduler(idleThread->GetPid()), idleThread);
    EXPECT_EQ(instance.Get<ThreadScheduler>().GetThreadFromScheduler(mainThread->GetPid()), mainThread);
    EXPECT_FALSE(instance.Get<ThreadScheduler>().IsContextSwitchRequested());
    EXPECT_EQ(instance.Get<ThreadScheduler>().GetCurrentActiveThread(), nullptr);
    EXPECT_EQ(instance.Get<ThreadScheduler>().GetCurrentActivePid(), KERNEL_PID_UNDEF);

    instance.Get<ThreadScheduler>().Run();

    EXPECT_EQ(mainThread->GetStatus(), THREAD_STATUS_RUNNING);
    EXPECT_EQ(idleThread->GetStatus(), THREAD_STATUS_PENDING);

    EXPECT_EQ(instance.Get<ThreadScheduler>().GetCurrentActiveThread(), mainThread);
    EXPECT_EQ(instance.Get<ThreadScheduler>().GetCurrentActivePid(), mainThread->GetPid());
    EXPECT_EQ(instance.Get<ThreadScheduler>().GetNumOfThreadsInScheduler(), 2);

    /* Note: at this point "main" thread is in running state and "idle" thread
     * is in pending state */

    /**
     * -------------------------------------------------------------------------
     * [TEST CASE] set the higher priority thread ("main" thread) to blocked
     * state and lower priority thread ("idle" thread) should be in in running
     * state
     * -------------------------------------------------------------------------
     **/

    instance.Get<ThreadScheduler>().SetThreadStatusAndUpdateRunqueue(mainThread, THREAD_STATUS_RECEIVE_BLOCKED);

    EXPECT_EQ(mainThread->GetStatus(), THREAD_STATUS_RECEIVE_BLOCKED);
    EXPECT_EQ(idleThread->GetStatus(), THREAD_STATUS_PENDING);

    EXPECT_EQ(instance.Get<ThreadScheduler>().GetCurrentActiveThread(), mainThread);

    instance.Get<ThreadScheduler>().Run();

    EXPECT_EQ(mainThread->GetStatus(), THREAD_STATUS_RECEIVE_BLOCKED);
    EXPECT_EQ(idleThread->GetStatus(), THREAD_STATUS_RUNNING);

    EXPECT_EQ(instance.Get<ThreadScheduler>().GetCurrentActiveThread(), idleThread);
    EXPECT_EQ(instance.Get<ThreadScheduler>().GetCurrentActivePid(), idleThread->GetPid());
    EXPECT_EQ(instance.Get<ThreadScheduler>().GetNumOfThreadsInScheduler(), 2);

    /* Note: at this point "main" thread is in blocked state and "idle" thread
     * is in blocked state */

    /**
     * -----------------------------------------------------------------------------
     * [TEST CASE] create new thread with higher priority than main and idle thread
     * and yield immediately
     * -----------------------------------------------------------------------------
     **/

    char task1Stack[128];

    Thread *task1Thread = Thread::Init(instance, task1Stack, sizeof(task1Stack), 5,
                                       THREAD_FLAGS_CREATE_STACKMARKER,
                                       NULL, NULL, "task1");

    EXPECT_NE(task1Thread, nullptr);

    EXPECT_EQ(task1Thread->GetPid(), 3);
    EXPECT_EQ(task1Thread->GetPriority(), 5);
    EXPECT_EQ(task1Thread->GetName(), "task1");
    EXPECT_EQ(task1Thread->GetStatus(), THREAD_STATUS_PENDING);

    /* Note: at this point cpu should immediately yield the "task1" by
     * triggering the PendSV interrupt and context switch is not requested */

    EXPECT_TRUE(testHelperIsPendSVInterruptTriggered());
    EXPECT_FALSE(instance.Get<ThreadScheduler>().IsContextSwitchRequested());

    instance.Get<ThreadScheduler>().Run();

    /* Note: after run the scheduler current active thread is expected to be
     * "task1" */

    EXPECT_EQ(mainThread->GetStatus(), THREAD_STATUS_RECEIVE_BLOCKED);
    EXPECT_EQ(idleThread->GetStatus(), THREAD_STATUS_PENDING);
    EXPECT_EQ(task1Thread->GetStatus(), THREAD_STATUS_RUNNING);

    EXPECT_EQ(instance.Get<ThreadScheduler>().GetCurrentActiveThread(), task1Thread);
    EXPECT_EQ(instance.Get<ThreadScheduler>().GetCurrentActivePid(), task1Thread->GetPid());
    EXPECT_EQ(instance.Get<ThreadScheduler>().GetNumOfThreadsInScheduler(), 3);

    /**
     * -------------------------------------------------------------------------
     * [TEST CASE] try to context swithing to lower priority thread than current
     * running thread
     * -------------------------------------------------------------------------
     **/

    testHelperResetPendSVTrigger(); /* reset the PendSV state */

    EXPECT_FALSE(testHelperIsPendSVInterruptTriggered());

    EXPECT_EQ(idleThread->GetPriority(), 15);
    EXPECT_EQ(mainThread->GetPriority(), 7);
    EXPECT_EQ(task1Thread->GetPriority(), 5); /* highest priority thread */

    instance.Get<ThreadScheduler>().ContextSwitch(mainThread->GetPriority());

    /* Note: because "mainThread" priority is lower than current running thread
     * and current running thread is still in running status, nothing should
     * happened */

    EXPECT_FALSE(testHelperIsPendSVInterruptTriggered());

    EXPECT_FALSE(instance.Get<ThreadScheduler>().IsContextSwitchRequested());

    EXPECT_EQ(mainThread->GetStatus(), THREAD_STATUS_RECEIVE_BLOCKED);
    EXPECT_EQ(idleThread->GetStatus(), THREAD_STATUS_PENDING);
    EXPECT_EQ(task1Thread->GetStatus(), THREAD_STATUS_RUNNING);

    EXPECT_EQ(instance.Get<ThreadScheduler>().GetCurrentActiveThread(), task1Thread);
    EXPECT_EQ(instance.Get<ThreadScheduler>().GetCurrentActivePid(), task1Thread->GetPid());
    EXPECT_EQ(instance.Get<ThreadScheduler>().GetNumOfThreadsInScheduler(), 3);

    /**
     * ------------------------------------------------------------------------------
     * [TEST CASE] request context swicth inside ISR (Interrupt Service Routine) and
     * current running thread is not in running status, it expected to see context
     * switch is requested instead of yielding immediately to the next thread
     * ------------------------------------------------------------------------------
     **/

    /* Note: set "task1" at blocked state first and is expected to be the next thread to
     * run is "idle" thread */

    instance.Get<ThreadScheduler>().SetThreadStatusAndUpdateRunqueue(task1Thread, THREAD_STATUS_RECEIVE_BLOCKED);

    EXPECT_EQ(mainThread->GetStatus(), THREAD_STATUS_RECEIVE_BLOCKED);
    EXPECT_EQ(idleThread->GetStatus(), THREAD_STATUS_PENDING);
    EXPECT_EQ(task1Thread->GetStatus(), THREAD_STATUS_RECEIVE_BLOCKED);

    instance.Get<ThreadScheduler>().Run();

    EXPECT_EQ(mainThread->GetStatus(), THREAD_STATUS_RECEIVE_BLOCKED);
    EXPECT_EQ(idleThread->GetStatus(), THREAD_STATUS_RUNNING);
    EXPECT_EQ(task1Thread->GetStatus(), THREAD_STATUS_RECEIVE_BLOCKED);

    EXPECT_EQ(instance.Get<ThreadScheduler>().GetCurrentActiveThread(), idleThread);
    EXPECT_EQ(instance.Get<ThreadScheduler>().GetCurrentActivePid(), idleThread->GetPid());
    EXPECT_EQ(instance.Get<ThreadScheduler>().GetNumOfThreadsInScheduler(), 3);

    /* Note: at this point idle thread is run as expected, because other
     * higher priority threads is in blocked state */

    testHelperSetCpuInISR(); /* artificially set cpu in ISR */

    EXPECT_TRUE(mtCpuIsInISR());

    instance.Get<ThreadScheduler>().ContextSwitch(task1Thread->GetPriority());

    EXPECT_FALSE(testHelperIsPendSVInterruptTriggered());

    EXPECT_TRUE(instance.Get<ThreadScheduler>().IsContextSwitchRequested());

    /* Note: because it is in ISR at this point context switch is requested
     * instead of immediatelly yield to "task1" */

    /* Note: in real cpu implementation, before exiting the ISR function it will
     * check this flag and trigger the PendSV interrupt if context switch is
     * requested, therefore after exiting ISR function PendSV interrupt will be
     * triggered and run thread scheduler */

    testHelperResetCpuInISR(); /* artificially out from ISR */

    EXPECT_FALSE(mtCpuIsInISR());

    instance.Get<ThreadScheduler>().Run();

    EXPECT_EQ(mainThread->GetStatus(), THREAD_STATUS_RECEIVE_BLOCKED);
    EXPECT_EQ(idleThread->GetStatus(), THREAD_STATUS_RUNNING);
    EXPECT_EQ(task1Thread->GetStatus(), THREAD_STATUS_RECEIVE_BLOCKED);

    /* Note: at this point the current active thread is still "idle" because "task1"
     * is still in receive blocked state even though it was try to context
     * switch to "task1", now try set "task1" to pending state and
     * context switch to "task1" priority */

    instance.Get<ThreadScheduler>().SetThreadStatusAndUpdateRunqueue(task1Thread, THREAD_STATUS_PENDING);

    EXPECT_EQ(task1Thread->GetStatus(), THREAD_STATUS_PENDING);

    instance.Get<ThreadScheduler>().ContextSwitch(task1Thread->GetPriority());

    EXPECT_TRUE(testHelperIsPendSVInterruptTriggered());

    EXPECT_FALSE(instance.Get<ThreadScheduler>().IsContextSwitchRequested());

    instance.Get<ThreadScheduler>().Run();

    testHelperResetPendSVTrigger(); /* artificially reset PendSV state */

    EXPECT_EQ(mainThread->GetStatus(), THREAD_STATUS_RECEIVE_BLOCKED);
    EXPECT_EQ(idleThread->GetStatus(), THREAD_STATUS_PENDING);
    EXPECT_EQ(task1Thread->GetStatus(), THREAD_STATUS_RUNNING);

    /* Note: at this point it succesfully switched to "task1" */

    EXPECT_EQ(instance.Get<ThreadScheduler>().GetCurrentActiveThread(), task1Thread);
    EXPECT_EQ(instance.Get<ThreadScheduler>().GetCurrentActivePid(), task1Thread->GetPid());
    EXPECT_EQ(instance.Get<ThreadScheduler>().GetNumOfThreadsInScheduler(), 3);
}
