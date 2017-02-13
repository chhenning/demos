#pragma once

#include "win32_headers.h"

#include <mmsystem.h>


static LONGLONG processor_frequency = {};
static bool sleep_is_granular = false;

inline 
void init_diagnostics()
{
	LARGE_INTEGER frequency;
	QueryPerformanceFrequency(&frequency);
	processor_frequency = frequency.QuadPart;

	// set the OS scheduler granularity
	UINT period = 1;
	auto result = timeBeginPeriod(period);

	if (result == TIMERR_NOCANDO)
	{
		OutputDebugString("Cannot set scheduler granularity.");
	}
	else
	{
		sleep_is_granular = true;
	}
}

inline 
LONGLONG get_wall_clock()
{
	LARGE_INTEGER counter;
	QueryPerformanceCounter(&counter);

	return counter.QuadPart;
}


inline
float elapsed_time(const LONGLONG& start, const LONGLONG& end)
{
	return (float)(end - start) / (float)processor_frequency;
}

