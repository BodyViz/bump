//
//  Timeline.h
//  Bump
//
//  Created by Christian Noon on 12/4/12.
//  Copyright (c) 2012 Christian Noon. All rights reserved.
//

#ifndef BUMP_TIMELINE_H
#define BUMP_TIMELINE_H

// Bump headers
#include <bump/Export.h>
#include <bump/Timer.h>

namespace bump {

/**
 * The Timeline class is used for controlling animations.
 *
 * It is most commonly used for controlling GUI element animations. In order to use
 * the timeline, you create one, set the parameters such as direction, output range
 * and curve shape, then start the timeline. You then need to periodically call the
 * update method. After the timeline has been updated, use the stepValue or
 * stepIncrement values to update the animations.
 */
class BUMP_EXPORT Timeline
{
public:

	/**
	 * Defines the different timeline states.
	 */
	enum State
	{
		RUNNING,				/**< Timeline timer is running. */
		NOT_RUNNING,			/**< Timeline timer is NOT running. */
		PAUSED,					/**< Timeline timer is paused. */
		FINISHED				/**< Timeline timer is NOT running and is finished. */
	};

	/**
	 * Defines the direction of the timeline.
	 */
	enum Direction
	{
		FORWARDS,				/**< Timeline value moves from start to end output values. */
		BACKWARDS				/**< Timeline value moves from end to start output values. */
	};

	/**
	 * Defines the curve shape for the timeline.
	 */
	enum CurveShape
	{
		LINEAR_CURVE,			/**< Timeline moves from start to end output linearly. */
		EASE_IN_CURVE,			/**< Timeline moves slow at first, then increases in speed. */
		EASE_OUT_CURVE,			/**< Timeline moves fast at first, then slows down steadily. */
		EASE_IN_AND_OUT_CURVE	/**< Timeline starts slow, increases in speed, peaks in the middle, then eases out. */
	};

	/**
	 * Default constructor.
	 */
	Timeline();

	/**
	 * Convenience constructor.
	 *
	 * @param duration The duration of timeline execution.
	 * @param direction The direction of the timeline output.
	 * @param curveShape The curve shape defining the acceleration of the timeline output.
	 */
	Timeline(double duration, const Direction& direction = FORWARDS, const CurveShape& curveShape = LINEAR_CURVE);

	/**
	 * Destructor.
	 */
	~Timeline();

	/**
	 * Starts the timeline.
	 */
	void start();

	/**
	 * Restarts the timeline.
	 */
	void restart();

	/**
	 * Stops the timeline.
	 */
	void stop();

	/**
	 * Pauses the timeline.
	 */
	void pause();

	/**
	 * Unpauses the timeline.
	 */
	void unpause();

	/**
	 * Updates the timeline.
	 *
	 * This method needs to be called each time you wish to update the step value
	 * of the timeline. After the timeline has been updated, you will use either
	 * the stepValue or stepIncrement functions to update your animations.
	 */
	void update();

	/**
	 * Sets the range of output values from the timeline.
	 *
	 * @param startOutput The starting output value for the timeline.
	 * @param endOutput The ending output value for the timeline.
	 */
	void setOutputRange(double startOutput, double endOutput);

	/**
	 * Sets the direction of the timeline.
	 *
	 * @param direction The direction to set for the timeline.
	 */
	void setDirection(const Direction& direction);

	/**
	 * Determines the direction of the timeline.
	 *
	 * @return The direction of the timeline.
	 */
	Direction direction();

	/**
	 * Sets the curve shape of the timeline.
	 *
	 * @param curveShape The curve shape to set for the timeline.
	 */
	void setCurveShape(const CurveShape& curveShape);

	/**
	 * Returns the curve shape for the timeline.
	 *
	 * @return The curve shape for the timeline.
	 */
	CurveShape curveShape();

	/**
	 * Sets the duration of the timeline.
	 *
	 * @param duration The duration to set for the timeline.
	 */
	void setDuration(double duration);

	/**
	 * Returns the duration of the timeline.
	 *
	 * @return The duration of the timeline.
	 */
	double duration();

	/**
	 * Returns the state of the timeline.
	 *
	 * @return The state of the timeline.
	 */
	State state();

	/**
	 * Returns the step value of the timeline.
	 *
	 * The step value is the actual value within the start and end
	 * outputs. This value moves along the curve shape between the
	 * start and end output values as the timeline is run.
	 *
	 * @return The step value of the timeline.
	 */
	double stepValue();

	/**
	 * Returns the step increment of the timeline.
	 *
	 * The step increment is the difference between the value previous
	 * step value and the current step value.
	 *
	 * @return The step increment of the timeline.
	 */
	double stepIncrement();

protected:

	/**
	 * @internal
	 * Calculates the acceleration for the step.
	 */
	void calculateAcceleration();

	/**
	 * @internal
	 * Updates the timeline step value.
	 */
	void generateStep();

	// Instance member variables
	State			_state;				/**< @internal Timeline run-time status. */
	Direction		_direction;			/**< @internal Timeline forwards or backwards direction. */
	CurveShape		_curveShape;		/**< @internal Timeline curve shape interpolation. */
	double			_duration;			/**< @internal How long the timeline will run. */
	double			_halfDuration;		/**< @internal Half the time the timeline will run. */
	double			_runTime;			/**< @internal How long the timeline has been running. */
	double			_acceleration;		/**< @internal How fast or slow the timeline accelerates. */
	double			_stepValue;			/**< @internal The step output value generated from start to end. */
	double			_stepIncrement;		/**< @internal The step output increment between each update. */
	double			_startOutput;		/**< @internal The starting point step value. */
	double			_endOutput;			/**< @internal The ending point step value. */
	Timer			_timer;				/**< @internal The timer used to keep track of time. */
};

}	// End of bump namespace

#endif	// End of BUMP_TIMELINE_H
