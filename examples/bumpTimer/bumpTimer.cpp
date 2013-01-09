//
//  bumpTimer.cpp
//  Bump
//
//  Created by Christian Noon on 12/4/12.
//  Copyright (c) 2012 Christian Noon. All rights reserved.
//

// Bump headers
#include <bump/Timer.h>

// C++ headers
#include <math.h>

void doSomeWork()
{
	// Perform some work that takes a bit
	for (unsigned long i = 0; i < 100000000; ++i)
	{
		double temp = sqrt(123.456);
		temp += 1.0f;
	}
}

/**
 * This example demonstrates how to use the Bump timer API.
 */
int main(int argc, char **argv)
{
	//=======================================================================
	//           Demonstrates how to use the singleton timer
	//=======================================================================

	// Start up the singleton timer
	std::cout << "============= Starting the singleton timer =============" << std::endl;
	bump::Timer::instance()->start();

	// Do some work
	std::cout << "\nDoing some work:" << std::endl;
	doSomeWork();

	// Ask the timer how much time has elapsed in seconds
	double elapsed_time_s = bump::Timer::instance()->secondsElapsed();
	double elapsed_time_ms = bump::Timer::instance()->millisecondsElapsed();
	double elapsed_time_us = bump::Timer::instance()->microsecondsElapsed();
	double elapsed_time_ns = bump::Timer::instance()->nanosecondsElapsed();
	std::cout << "- Elapsed Time (s):  " << elapsed_time_s << std::endl;
	std::cout << "- Elapsed Time (ms): " << elapsed_time_ms << std::endl;
	std::cout << "- Elapsed Time (us): " << elapsed_time_us << std::endl;
	std::cout << "- Elapsed Time (ns): " << elapsed_time_ns << std::endl;

	// Let's do some more work
	std::cout << "\nDoing some more work:" << std::endl;
	doSomeWork();

	// Let's ask the timer for the cumulative elapsed time
	elapsed_time_s = bump::Timer::instance()->secondsElapsed();
	elapsed_time_ms = bump::Timer::instance()->millisecondsElapsed();
	elapsed_time_us = bump::Timer::instance()->microsecondsElapsed();
	elapsed_time_ns = bump::Timer::instance()->nanosecondsElapsed();
	std::cout << "- Elapsed Time (s):  " << elapsed_time_s << std::endl;
	std::cout << "- Elapsed Time (ms): " << elapsed_time_ms << std::endl;
	std::cout << "- Elapsed Time (us): " << elapsed_time_us << std::endl;
	std::cout << "- Elapsed Time (ns): " << elapsed_time_ns << std::endl;

	// Now let's restart the timer
	std::cout << "\n============= Restarting the singleton timer =============" << std::endl;
	bump::Timer::instance()->restart();

	// Let's do some more work
	std::cout << "\nDoing lots of work:" << std::endl;
	doSomeWork();
	doSomeWork();
	doSomeWork();

	// Let's ask the timer once more for the cumulative elapsed time
	elapsed_time_s = bump::Timer::instance()->secondsElapsed();
	elapsed_time_ms = bump::Timer::instance()->millisecondsElapsed();
	elapsed_time_us = bump::Timer::instance()->microsecondsElapsed();
	elapsed_time_ns = bump::Timer::instance()->nanosecondsElapsed();
	std::cout << "- Elapsed Time (s):  " << elapsed_time_s << std::endl;
	std::cout << "- Elapsed Time (ms): " << elapsed_time_ms << std::endl;
	std::cout << "- Elapsed Time (us): " << elapsed_time_us << std::endl;
	std::cout << "- Elapsed Time (ns): " << elapsed_time_ns << std::endl;

	//=======================================================================
	//              Demonstrates how to use your own timers
	//=======================================================================

	// You can also use your own timers instead of the singleton timer
	std::cout << "\n============= Starting our custom timer =============" << std::endl;
	bump::Timer timer;
	timer.start();

	// Do some work
	std::cout << "\nDoing some work:" << std::endl;
	doSomeWork();

	// How much time elapsed with our custom timer?
	elapsed_time_s = timer.secondsElapsed();
	elapsed_time_ms = timer.millisecondsElapsed();
	elapsed_time_us = timer.microsecondsElapsed();
	elapsed_time_ns = timer.nanosecondsElapsed();
	std::cout << "- Elapsed Time (s):  " << elapsed_time_s << std::endl;
	std::cout << "- Elapsed Time (ms): " << elapsed_time_ms << std::endl;
	std::cout << "- Elapsed Time (us): " << elapsed_time_us << std::endl;
	std::cout << "- Elapsed Time (ns): " << elapsed_time_ns << std::endl;

    return 0;
}
