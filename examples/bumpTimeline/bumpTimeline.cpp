//
//  bumpTimeline.cpp
//  Bump
//
//  Created by Christian Noon on 12/4/12.
//  Copyright (c) 2012 Christian Noon. All rights reserved.
//

// Boost headers
#include <boost/thread/thread.hpp>

// Bump headers
#include <bump/Timeline.h>

// STL headers
#include <iostream>

#define ANIMATION_DURATION				4.0
#define TOTAL_ANIMATION_CHARACTERS		81

/**
 * Renders out asterisks as an animation to std::cout based on the timeline properties.
 */
void executeAnimation(bump::Timeline* timeline, bool pauseAtMiddle)
{
	// First start up the timeline
	timeline->start();

	// Now continuously keep updating the timeline and render an asterisk each time
	// the timeline hits a 1/80th increment
	int current_index = 1;
	while (timeline->state() == bump::Timeline::RUNNING)
	{
		// Update the timeline
		timeline->update();

		// Render the asterisk if we hit another increment
		if (timeline->stepValue() >= (double)current_index / TOTAL_ANIMATION_CHARACTERS)
		{
			std::cout << "*" << std::flush;
			++current_index;

			// Pause the animation in the middle if specified
			if (pauseAtMiddle && current_index == TOTAL_ANIMATION_CHARACTERS / 2)
			{
				timeline->pause();
				boost::this_thread::sleep(boost::posix_time::milliseconds(2000));
				timeline->unpause();
			}
		}
	}

	// Add some new lines since we're finished
	std::cout << std::endl << std::endl;
}

/**
 * This example demonstrates how to use the Bump timeline API.
 *
 * The Timeline class is used for controlling animations. It is most commonly used
 * for controlling GUI element animations. In order to use the timeline, you create
 * one, set the parameters such as direction, output range and curve shape, then start
 * the timeline. You then need to periodically call the update method. After the
 * timeline has been updated, use the stepValue or stepIncrement values to update
 * the animations.
 */
int main(int argc, char **argv)
{
	// Demonstrates how to create a linear animation
	std::cout << "================================== LINEAR_CURVE =================================" << std::endl;
	boost::this_thread::sleep(boost::posix_time::milliseconds(1000));
	bump::Timeline linear_timeline;
	linear_timeline.setCurveShape(bump::Timeline::LINEAR_CURVE);
	linear_timeline.setDirection(bump::Timeline::FORWARDS);
	linear_timeline.setDuration(ANIMATION_DURATION);
	linear_timeline.setOutputRange(0.0, 1.0);
	executeAnimation(&linear_timeline, false);

	// Demonstrates how to create an ease in animation
	boost::this_thread::sleep(boost::posix_time::milliseconds(1000));
	std::cout << "\n================================== EASE_IN_CURVE ================================" << std::endl;
	boost::this_thread::sleep(boost::posix_time::milliseconds(1000));
	bump::Timeline ease_in_timeline;
	ease_in_timeline.setCurveShape(bump::Timeline::EASE_IN_CURVE);
	ease_in_timeline.setDirection(bump::Timeline::FORWARDS);
	ease_in_timeline.setDuration(ANIMATION_DURATION);
	ease_in_timeline.setOutputRange(0.0, 1.0);
	executeAnimation(&ease_in_timeline, false);

	// Demonstrates how to create an ease out animation
	boost::this_thread::sleep(boost::posix_time::milliseconds(1000));
	std::cout << "\n================================== EASE_OUT_CURVE ===============================" << std::endl;
	boost::this_thread::sleep(boost::posix_time::milliseconds(1000));
	bump::Timeline ease_out_timeline;
	ease_out_timeline.setCurveShape(bump::Timeline::EASE_OUT_CURVE);
	ease_out_timeline.setDirection(bump::Timeline::FORWARDS);
	ease_out_timeline.setDuration(ANIMATION_DURATION);
	ease_out_timeline.setOutputRange(0.0, 1.0);
	executeAnimation(&ease_out_timeline, false);

	// Demonstrates how to create an ease in and out animation
	boost::this_thread::sleep(boost::posix_time::milliseconds(1000));
	std::cout << "\n=============================== EASE_IN_AND_OUT_CURVE ===========================" << std::endl;
	boost::this_thread::sleep(boost::posix_time::milliseconds(1000));
	bump::Timeline ease_in_and_out_timeline;
	ease_in_and_out_timeline.setCurveShape(bump::Timeline::EASE_IN_AND_OUT_CURVE);
	ease_in_and_out_timeline.setDirection(bump::Timeline::FORWARDS);
	ease_in_and_out_timeline.setDuration(ANIMATION_DURATION);
	ease_in_and_out_timeline.setOutputRange(0.0, 1.0);
	executeAnimation(&ease_in_and_out_timeline, false);

	// Demonstrates how to pause an animation in the middle if you wish
	boost::this_thread::sleep(boost::posix_time::milliseconds(1000));
	std::cout << "\n=========================== EASE_IN_AND_OUT_CURVE with a pause ==================" << std::endl;
	boost::this_thread::sleep(boost::posix_time::milliseconds(1000));
	executeAnimation(&ease_in_and_out_timeline, true);

    return 0;
}
