#include <vcrtos/config.h>
#include <vcrtos/cpu.h>
#include <vcrtos/instance.h>
#include <vcrtos/thread.h>
#include <vcrtos/mutex.h>
#include <vcrtos/heap.h>
#include <vcrtos/sema.h>

#if VCRTOS_CONFIG_ZTIMER_ENABLE
#include <vcrtos/ztimer.h>
#endif

#include "pal.h"
#include "pal_plat_rtos.h"
#include <stdlib.h>

#define TRACE_GROUP "PAL"

#ifndef PAL_SEMAPHORE_MAX_COUNT
#define PAL_SEMAPHORE_MAX_COUNT 255
#endif

#ifndef PAL_RTOS_WAIT_FOREVER
#define PAL_RTOS_WAIT_FOREVER UINT_MAX
#endif

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
    int32_t maxCount;
} palSemaphore_t;

typedef struct palThreadData {
    palThreadID_t threadID;
    palThreadFuncPtr userFunction;
    void *userFunctionArgument;
} palThreadData_t;

void pal_plat_osReboot(void)
{

}

void pal_plat_osApplicationReboot(void)
{

}

palStatus_t pal_plat_RTOSInitialize(void* opaqueContext)
{
    palStatus_t status = PAL_SUCCESS;

    (void) opaqueContext;

    return status;
}

palStatus_t pal_plat_RTOSDestroy(void)
{
    palStatus_t status = PAL_SUCCESS;

    return status;
}

uint64_t pal_plat_osKernelSysTick(void)
{
    uint64_t result = ztimer_now(ZTIMER_USEC);
    return result;
}

uint64_t pal_plat_osKernelSysTickMicroSec(uint64_t microseconds)
{
    return microseconds;
}

uint64_t pal_plat_osKernelSysTickFrequency(void)
{
    return 1000000; /* 1 MHz */
}

#if 0
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

    palMutex_t *pal_mutex = (palMutex_t *)heap_malloc(sizeof(palMutex_t));

    mutex_t *mutex  = (mutex_t *)heap_malloc(sizeof(mutex_t));


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
    palMutex_t *pal_mutex = NULL;

    if (mutexID == NULLPTR)
    {
        return PAL_ERR_INVALID_ARGUMENT;
    }

    pal_mutex = (palMutex_t*)mutexID;

    if (cpu_is_in_isr())
    {
        status = PAL_ERR_GENERIC_FAILURE; /* can't wait mutex in ISR */
    }
    else
    {
        uint32_t us = millisec * 1000;

        uint32_t start = ztimer_now(ZTIMER_USEC);

        mutex_lock_timeout(instance_get(), (mutex_t *)pal_mutex->mutexID, us);

        uint32_t elapsed = ztimer_now(ZTIMER_USEC) - start;

        if (elapsed < us)
        {
            status = PAL_ERR_RTOS_TIMEOUT;
        }
    }

    return status;
}

palStatus_t pal_plat_osMutexRelease(palMutexID_t mutexID)
{
    palStatus_t status = PAL_SUCCESS;
    palMutex_t *pal_mutex = NULL;

    if (mutexID == NULLPTR)
    {
        return PAL_ERR_INVALID_ARGUMENT;
    }

    pal_mutex = (palMutex_t *)mutexID;

    mutex_unlock((mutex_t *)pal_mutex->mutexID);

    return status;
}

palStatus_t pal_plat_osMutexDelete(palMutexID_t* mutexID)
{
    palStatus_t status = PAL_SUCCESS;
    palMutex_t *pal_mutex = NULL;

    if (mutexID == NULL || *mutexID == NULLPTR)
    {
        return PAL_ERR_INVALID_ARGUMENT;
    }

    pal_mutex = (palMutex_t *)*mutexID;

    if (pal_mutex->mutexID != NULLPTR)
    {
        heap_free(pal_mutex);
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

palStatus_t pal_plat_osSemaphoreCreate(uint32_t count, palSemaphoreID_t* semaphoreID)
{
    palStatus_t status = PAL_SUCCESS;
    palSemaphore_t *pal_semaphore = NULL;

    if (semaphoreID == NULL)
    {
        return PAL_ERR_INVALID_ARGUMENT;
    }

    pal_semaphore = (palSemaphore_t *)heap_malloc(sizeof(palSemaphore_t));

    sema_t *sema = (sema_t *)heap_malloc(sizeof(sema_t));

    if (pal_semaphore == NULL || sema == NULL)
    {
        status = PAL_ERR_NO_MEMORY;
    }

    if (status == PAL_SUCCESS)
    {
        sema_create(instance_get(), sema, count);
        pal_semaphore->semaphoreID = (uintptr_t)sema;
        pal_semaphore->maxCount = PAL_SEMAPHORE_MAX_COUNT;
        if (pal_semaphore->semaphoreID == NULLPTR)
        {
            heap_free(pal_semaphore);
            pal_semaphore = NULLPTR;
            PAL_LOG_ERR("RTOS semaphore create error");
            status = PAL_ERR_GENERIC_FAILURE;
        }
        else
        {
            *semaphoreID = (palSemaphoreID_t)pal_semaphore;
        }
    }

    return status;
}

palStatus_t pal_plat_osSemaphoreWait(palSemaphoreID_t semaphoreID, uint32_t millisec, int32_t* countersAvailable)
{
    palStatus_t status = PAL_SUCCESS;
    palSemaphore_t *pal_semaphore = NULL;
    int32_t tmpCounters = 0;
    int res = 0;

    if (semaphoreID == NULLPTR)
    {
        return PAL_ERR_INVALID_ARGUMENT;
    }

    pal_semaphore = (palSemaphore_t *)semaphoreID;

    if (cpu_is_in_isr())
    {
        status = PAL_ERR_GENERIC_FAILURE; /* can't wait semaphore is ISR */
        res = -1;
    }
    else
    {
        if (millisec == PAL_RTOS_WAIT_FOREVER)
        {
            res = sema_wait((sema_t *)pal_semaphore->semaphoreID);
        }
        else
        {
            res = sema_wait_timed((sema_t *)pal_semaphore->semaphoreID, millisec * 1000);
        }
    }

    if (res == 0)
    {
        tmpCounters = ((sema_t *)pal_semaphore->semaphoreID)->value;
    }
    else
    {
        tmpCounters = 0;
        status = PAL_ERR_RTOS_TIMEOUT;
    }

    if (countersAvailable != NULL)
    {
        *countersAvailable = tmpCounters;
    }
    return status;
}

palStatus_t pal_plat_osSemaphoreRelease(palSemaphoreID_t semaphoreID)
{
    palStatus_t status = PAL_SUCCESS;
    palSemaphore_t *pal_semaphore = NULL;
    int32_t tmpCounters = 0;
    int res = 0;

    if (semaphoreID == NULLPTR)
    {
        return PAL_ERR_INVALID_ARGUMENT;
    }

    pal_semaphore = (palSemaphore_t *)semaphoreID;

    tmpCounters = ((sema_t *)pal_semaphore->semaphoreID)->value;

    if (tmpCounters < pal_semaphore->maxCount)
    {
        res = sema_post((sema_t *)pal_semaphore->semaphoreID);

        if (res != 0)
        {
            status = PAL_ERR_GENERIC_FAILURE;
        }
    }
    else
    {
        status = PAL_ERR_RTOS_RESOURCE;
    }

    return status;
}

palStatus_t pal_plat_osSemaphoreDelete(palSemaphoreID_t* semaphoreID)
{
    palStatus_t status = PAL_SUCCESS;
    palSemaphore_t *pal_semaphore = NULL;

    if (semaphoreID == NULL || *semaphoreID == NULLPTR)
    {
        return PAL_ERR_INVALID_ARGUMENT;
    }

    pal_semaphore = (palSemaphore_t *)*semaphoreID;

    if (pal_semaphore->semaphoreID != NULLPTR)
    {
        heap_free(pal_semaphore);
        *semaphoreID = NULLPTR;
        status = PAL_SUCCESS;
    }
    else
    {
        PAL_LOG_ERR("RTOS semaphore destroy error");
        status = PAL_ERR_GENERIC_FAILURE;
    }

    return status;
}

#if 0
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
