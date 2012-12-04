//
//  AutoTimer.cpp
//  Bump
//
//  Created by Christian Noon on 12/4/12.
//  Copyright (c) 2012 Christian Noon. All rights reserved.
//

// Bump headers
#include <bump/AutoTimer.h>

using namespace bump;

AutoTimer::AutoTimer(const OutputType& outputType) :
	_outputType(outputType)
{
	_timer.start();
}

AutoTimer::~AutoTimer()
{
	if (_outputType == SECONDS)
	{
		std::cout << "Elapsed Time: " << _timer.secondsElapsed() << " secs" << std::endl;
	}
	else if (_outputType == MILLISECONDS)
	{
		std::cout << "Elapsed Time: " << _timer.millisecondsElapsed() << " msecs" << std::endl;
	}
	else if (_outputType == MICROSECONDS)
	{
		std::cout << "Elapsed Time: " << _timer.microsecondsElapsed() << " usecs" << std::endl;
	}
	else // _outputType == NANOSECONDS
	{
		std::cout << "Elapsed Time: " << _timer.nanosecondsElapsed() << " nsecs" << std::endl;
	}
}
