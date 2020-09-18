#include <vcrtos/config.h>
#include <vcrtos/cpu.h>
#include <vcrtos/instance.h>
#include <vcrtos/thread.h>
#include <vcrtos/mutex.h>
#include <vcrtos/heap.h>

#if VCRTOS_CONFIG_ZTIMER_ENABLE
#include <vcrtos/ztimer.h>
#endif

#include "pal.h"
#include "pal_plat_rtos.h"
#include <stdlib.h>

#define TRACE_GROUP "PAL"

//! Timer structure
typedef struct palTimer {
    palTimerID_t timerID;
    palTimerFuncPtr function;
    void *functionArgs;
    uint32_t timerType;
} palTimer_t;

typedef struct palMutex {
    palMutexID_t mutexID;
} palMutex_t;

typedef struct palSemaphore {
    palSemaphoreID_t semaphoreID;
    uint32_t maxCount;
} palSemaphore_t;

typedef struct palThreadData {
    palThreadID_t threadID;
    palThreadFuncPtr userFunction;
    void *userFunctionArgument;
} palThreadData_t;

#if 0
void pal_plat_osReboot(void)
{

}

void pal_plat_osApplicationReboot(void)
{

}

palStatus_t pal_plat_RTOSInitialize(void* opaqueContext)
{

}

palStatus_t pal_plat_RTOSDestroy(void);

uint64_t pal_plat_osKernelSysTick(void);

uint64_t pal_plat_osKernelSysTickMicroSec(uint64_t microseconds);

uint64_t pal_plat_osKernelSysTickFrequency(void);

palStatus_t pal_plat_osThreadCreate(palThreadFuncPtr function, void* funcArgument, palThreadPriority_t priority, uint32_t stackSize, palThreadID_t* threadID);

palStatus_t pal_plat_osThreadTerminate(palThreadID_t* threadID);

palThreadID_t pal_plat_osThreadGetId(void);

palStatus_t pal_plat_osDelay(uint32_t milliseconds);

palStatus_t pal_plat_osTimerCreate(palTimerFuncPtr function, void* funcArgument, palTimerType_t timerType, palTimerID_t* timerID);

palStatus_t pal_plat_osTimerStart(palTimerID_t timerID, uint32_t millisec);

palStatus_t pal_plat_osTimerStop(palTimerID_t timerID);

palStatus_t pal_plat_osTimerDelete(palTimerID_t* timerID);
#endif


palStatus_t pal_plat_osMutexCreate(palMutexID_t* mutexID)
{
    palStatus_t status = PAL_SUCCESS;

    if (mutexID == NULL)
    {
        return PAL_ERR_INVALID_ARGUMENT;
    }

    mutex_t *mutex  = (mutex_t *)heap_malloc(sizeof(mutex_t));

    palMutex_t *pal_mutex = (palMutex_t *)heap_malloc(sizeof(palMutex_t));

    if (mutex == NULL || pal_mutex == NULL)
    {
        status = PAL_ERR_NO_MEMORY;
    }

    if (status == PAL_SUCCESS)
    {
        mutex_init(instance_get(), mutex);
        pal_mutex->mutexID = (uintptr_t)mutex;
        *mutexID = (palMutexID_t)pal_mutex;
    }

    return status;
}

palStatus_t pal_plat_osMutexWait(palMutexID_t mutexID, uint32_t millisec)
{
    palStatus_t status = PAL_SUCCESS;
    palMutex_t *mutex = NULL;

    if (mutexID == NULLPTR)
    {
        return PAL_ERR_INVALID_ARGUMENT;
    }

    mutex = (palMutex_t*)mutexID;

    if (!cpu_is_in_isr())
    {
        uint32_t us = millisec * 1000;

        uint32_t start = ztimer_now(ZTIMER_USEC);

        mutex_lock_timeout(instance_get(), (mutex_t *)mutex, us);

        uint32_t elapsed = ztimer_now(ZTIMER_USEC) - start;

        if (elapsed <= us)
        {
            status = PAL_ERR_RTOS_TIMEOUT;
        }
    }

    return status;
}

palStatus_t pal_plat_osMutexRelease(palMutexID_t mutexID)
{
    palStatus_t status = PAL_SUCCESS;
    palMutex_t *mutex = NULL;

    if (mutexID == NULLPTR)
    {
        return PAL_ERR_INVALID_ARGUMENT;
    }

    mutex = (palMutex_t *)mutexID;

    mutex_unlock((mutex_t *)mutex);

    return status;
}

palStatus_t pal_plat_osMutexDelete(palMutexID_t* mutexID)
{
    palStatus_t status = PAL_SUCCESS;
    palMutex_t *mutex = NULL;

    if (mutexID == NULL || *mutexID == NULLPTR)
    {
        return PAL_ERR_INVALID_ARGUMENT;
    }

    mutex = (palMutex_t *)*mutexID;

    if (mutex->mutexID != NULLPTR)
    {
        heap_free(mutex);
        *mutexID = NULLPTR;
        status = PAL_SUCCESS;
    }
    else
    {
        PAL_LOG_ERR("RTOS mutex delete failure");
        status = PAL_ERR_GENERIC_FAILURE;
    }
    return status;
}

#if 0
palStatus_t pal_plat_osSemaphoreCreate(uint32_t count, palSemaphoreID_t* semaphoreID);

palStatus_t pal_plat_osSemaphoreWait(palSemaphoreID_t semaphoreID, uint32_t millisec, int32_t* countersAvailable);

palStatus_t pal_plat_osSemaphoreRelease(palSemaphoreID_t semaphoreID);

palStatus_t pal_plat_osSemaphoreDelete(palSemaphoreID_t* semaphoreID);

int32_t pal_plat_osAtomicIncrement(int32_t* valuePtr, int32_t increment);
#endif

void *pal_plat_malloc(size_t len)
{
    return heap_malloc(len);
}

void pal_plat_free(void * buffer)
{
    heap_free(buffer);
}

#if 0
palStatus_t pal_plat_osGetRoTFromHW(uint8_t *keyBuf, size_t keyLenBytes);

palStatus_t pal_plat_osSetRtcTime(uint64_t rtcSetTime);

palStatus_t pal_plat_osGetRtcTime(uint64_t *rtcGetTime);

palStatus_t pal_plat_rtcDeInit(void);

palStatus_t pal_plat_rtcInit(void);
#endif
