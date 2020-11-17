#pragma once
#include <Windows.h>

class Time
{
public:
	Time();
	LARGE_INTEGER _nowFrameCounter;
	LARGE_INTEGER _prevFrameCounter;
	LARGE_INTEGER _frameInfo;

	double _perFrame;
	int count;
	int _targetFrame;

	bool isRenderTiming();
};