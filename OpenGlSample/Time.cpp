#include "Time.h"
#include <iostream>

Time::Time()
{
	_targetFrame = 60;

	QueryPerformanceFrequency(&_frameInfo);
	QueryPerformanceCounter(&_prevFrameCounter);

	_perFrame = _frameInfo.QuadPart / (double)_targetFrame;
	std::cout << "Target Frame : " << _targetFrame << std::endl;
}

bool Time::isRenderTiming()
{
	QueryPerformanceCounter(&_nowFrameCounter);

	double time_distance = _nowFrameCounter.QuadPart - _prevFrameCounter.QuadPart;

	if (time_distance > _perFrame)
	{
		_prevFrameCounter = _nowFrameCounter;

		static int count = 0;
		if (count++ > _targetFrame)
		{
			std::cout << "1 second" << std::endl;

			count = 0;
		}

		return true;
	}

	return false;
}