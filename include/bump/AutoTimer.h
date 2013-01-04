//
//  AutoTimer.h
//  Bump
//
//  Created by Christian Noon on 12/4/12.
//  Copyright (c) 2012 Christian Noon. All rights reserved.
//

#ifndef BUMP_AUTO_TIMER_H
#define BUMP_AUTO_TIMER_H

// Bump headers
#include <bump/Export.h>
#include <bump/Timer.h>

namespace bump {

/**
 * The AutoTimer class used for easily measuring elapsed time in a particular
 * scope. When the AutoTimer is destructed, it will print out the elapsed
 * time to std::cout.
 */
class BUMP_EXPORT AutoTimer
{
public:

	/**
	 * Defines the possible types of output formatting to be printed to std::cout.
	 */
	enum OutputType
	{
		SECONDS,		/**< Output type is in seconds. */
		MILLISECONDS,	/**< Output type is in milliseconds (10e3). */
		MICROSECONDS,	/**< Output type is in microseconds (10e6). */
		NANOSECONDS		/**< Output type is in nanoseconds (10e9). */
	};

	/**
	 * Constructor.
	 *
	 * @param outputType The output format of the time printed to std::cout.
	 */
	AutoTimer(const OutputType& outputType = SECONDS);

	/**
	 * Destructor.
	 */
	~AutoTimer();

protected:

	// Instance member variables
	OutputType		_outputType;	/**< The output format to be printed to std::cout. */
	Timer			_timer;			/**< The timer used to print out the elapsed time. */
};

}	// End of bump namespace

#endif	// End of BUMP_AUTO_TIMER_H
