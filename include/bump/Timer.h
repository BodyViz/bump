//
//  Timer.h
//  Bump
//
//  Created by Christian Noon on 12/4/12.
//  Copyright (c) 2012 Christian Noon. All rights reserved.
//

#pragma once

#include <bump/Export.h>

#include <boost/timer/timer.hpp>

// MSVC C4251: Timer holds a boost::timer::cpu_timer by value.
// Scoped to this header so the suppression never reaches consumer code.
#if defined(_MSC_VER)
#pragma warning(push)
#pragma warning(disable : 4251)  // needs dll-interface to be used by clients
#endif

namespace bump {

/**
 * Timer class used for measuring elapsed time between two events.
 */
class BUMP_EXPORT Timer {
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
     * Creates a thread-safe singleton instance of the Timer object.
     *
     * @return The singleton instance.
     */
    static Timer* instance();

    /**
     * Starts the timer.
     */
    void start();

    /**
     * Pauses the timer.
     */
    void pause();

    /**
     * Unpauses the timer.
     */
    void unpause();

    /**
     * Restarts the timer by resetting the start time.
     */
    void restart();

    /**
     * Calculates the elapsed time in seconds between the start time and now.
     *
     * @return The elapsed time between the start time and now.
     */
    double secondsElapsed() const;

    /**
     * Calculates the elapsed time in milliseconds between the start time and
     * now.
     *
     * @return The elapsed time between the start time and now.
     */
    double millisecondsElapsed() const;

    /**
     * Calculates the elapsed time in microseconds between the start time and
     * now.
     *
     * @return The elapsed time between the start time and now.
     */
    double microsecondsElapsed() const;

    /**
     * Calculates the elapsed time in nanoseconds between the start time and
     * now.
     *
     * @return The elapsed time between the start time and now.
     */
    double nanosecondsElapsed() const;

protected:
    // Instance member variables
    boost::timer::cpu_timer _timer; /**< @internal The boost cpu timer used to
                                       compute the elapsed times. */
};

}  // namespace bump

#if defined(_MSC_VER)
#pragma warning(pop)
#endif
