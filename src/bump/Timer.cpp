//
//  Timer.cpp
//  Bump
//
//  Created by Christian Noon on 12/4/12.
//  Copyright (c) 2012 Christian Noon. All rights reserved.
//

// Boost headers
#include <boost/thread/mutex.hpp>

// Bump headers
#include <bump/String.h>
#include <bump/Timer.h>

// Global singleton mutex
boost::mutex gTimerSingletonMutex;

namespace bump {

Timer::Timer() :
	_timer()
{
	;
}

Timer::~Timer()
{
	;
}

Timer* Timer::instance()
{
	boost::mutex::scoped_lock lock(gTimerSingletonMutex);
	static Timer timer;
	return &timer;
}

void Timer::start()
{
	_timer.start();
}

void Timer::pause()
{
	_timer.stop();
}

void Timer::unpause()
{
	_timer.resume();
}

void Timer::restart()
{
	_timer.start();
}

double Timer::secondsElapsed() const
{
	String elapsed_time = boost::timer::format(_timer.elapsed(), boost::timer::default_places, "%w");
	return elapsed_time.toDouble();
}

double Timer::millisecondsElapsed() const
{
	String elapsed_time = boost::timer::format(_timer.elapsed(), boost::timer::default_places, "%w");
	return elapsed_time.toDouble() * 1e3;
}

double Timer::microsecondsElapsed() const
{
	String elapsed_time = boost::timer::format(_timer.elapsed(), boost::timer::default_places, "%w");
	return elapsed_time.toDouble() * 1e6;
}

double Timer::nanosecondsElapsed() const
{
	String elapsed_time = boost::timer::format(_timer.elapsed(), boost::timer::default_places, "%w");
	return elapsed_time.toDouble() * 1e9;
}

}	// End of bump namespace
