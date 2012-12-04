//
//  Timer.cpp
//  Bump
//
//  Created by Christian Noon on 12/4/12.
//  Copyright (c) 2012 Christian Noon. All rights reserved.
//

// Bump headers
#include <bump/String.h>
#include <bump/Timer.h>

using namespace bump;

Timer::Timer() :
	_timer()
{
	;
}

Timer::~Timer()
{
	;
}

void Timer::start()
{
	_timer.start();
}

void Timer::restart()
{
	_timer = boost::timer::cpu_timer();
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
