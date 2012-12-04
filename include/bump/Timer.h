//
//  Timer.h
//  Bump
//
//  Created by Christian Noon on 12/4/12.
//  Copyright (c) 2012 Christian Noon. All rights reserved.
//

#ifndef BUMP_TIMER_H
#define BUMP_TIMER_H

// Boost headers
#include <boost/timer/timer.hpp>

namespace bump {

/**
 * Timer class used for measuring elapsed time between two events.
 */
class Timer
{
public:

	/**
	 * Constructor.
	 */
	Timer();

	/**
	 * Destructor.
	 */
	~Timer();

	/**
	 * Creates a singleton Timer instance.
	 */
	static Timer* instance() { static Timer s_timer; return &s_timer; }

	/**
	 * Starts the timer.
	 */
	void start();

	/**
	 * Restarts the timer by resetting the start time.
	 */
	void restart();

	/**
	 * Calculates the elapsed time in seconds between the start time and now.
	 *
	 * @return the elapsed time between the start time and now.
	 */
	double secondsElapsed() const;

	/**
	 * Calculates the elapsed time in milliseconds between the start time and now.
	 *
	 * @return the elapsed time between the start time and now.
	 */
	double millisecondsElapsed() const;

	/**
	 * Calculates the elapsed time in microseconds between the start time and now.
	 *
	 * @return the elapsed time between the start time and now.
	 */
	double microsecondsElapsed() const;

	/**
	 * Calculates the elapsed time in nanoseconds between the start time and now.
	 *
	 * @return the elapsed time between the start time and now.
	 */
	double nanosecondsElapsed() const;

protected:

	/** Instance member variables. */
	boost::timer::cpu_timer _timer;
};

}	// End of bump namespace

#endif	// End of BUMP_TIMER_H
