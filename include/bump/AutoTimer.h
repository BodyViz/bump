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
	 * Defines the types of output.
	 */
	enum OutputType
	{
		SECONDS,
		MILLISECONDS,
		MICROSECONDS,
		NANOSECONDS
	};

	/**
	 * Constructor.
	 */
	AutoTimer(const OutputType& outputType = SECONDS);

	/**
	 * Destructor.
	 */
	~AutoTimer();

protected:

	/** Instance member variables. */
	OutputType		_outputType;
	Timer			_timer;
};

}	// End of bump namespace

#endif	// End of BUMP_AUTO_TIMER_H
