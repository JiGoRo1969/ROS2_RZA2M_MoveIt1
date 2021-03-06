#include <uxr/client/util/time.h>
#include <uxr/client/config.h>
#if defined(PLATFORM_NAME_FREERTOS)
#include "FreeRTOS.h"
#include "task.h"
extern unsigned long ulGetRunTimeCounterValue( void );

#else
#include <time.h>
#endif

#ifdef WIN32
#include <Windows.h>
#endif

//==================================================================
//                             PUBLIC
//==================================================================
int64_t uxr_millis(void)
{
    return uxr_nanos() / ( 1000 * 1000 );
}

int64_t uxr_nanos(void)
{
#if defined(PLATFORM_NAME_FREERTOS)
    TimeOut_t tick_count;

    /* Get the current tick count. */
    vTaskSetTimeOutState(&tick_count);

    /* Pack the current tick count in int64_t. */
    int64_t total_tick = (int64_t) tick_count.xOverflowCount;
#if( configUSE_16_BIT_TICKS == 1 )    /* Use 16-bit tick type. */
    total_tick <<= 16;
#else                                 /* Use 32-bit tick type. */
    total_tick <<= 32;
#endif
    total_tick |= (int64_t) tick_count.xTimeOnEntering;
    return ( ( total_tick / (int64_t) portTICK_PERIOD_MS ) * ( 1000 * 1000 ) );
#else
#ifdef WIN32
    SYSTEMTIME epoch_tm = {1970, 1, 4, 1, 0, 0, 0, 0};
    FILETIME epoch_ft;
    SystemTimeToFileTime(&epoch_tm, &epoch_ft);
    uint64_t epoch_time = (((uint64_t) epoch_ft.dwHighDateTime) << 32) + epoch_ft.dwLowDateTime;

    SYSTEMTIME tm;
    FILETIME ft;
    GetSystemTime(&tm);
    SystemTimeToFileTime(&tm, &ft);
    uint64_t current_time = (((uint64_t) ft.dwHighDateTime) << 32) + ft.dwLowDateTime;

    return (current_time - epoch_time) * 100;
#else
    struct timespec ts;
    clock_gettime(CLOCK_REALTIME, &ts);
    return (((int64_t)ts.tv_sec) * 1000000000) + ts.tv_nsec;
#endif
#endif
}
