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
		RUNNING,
		NOT_RUNNING,
		PAUSED,
		FINISHED
	};

	/**
	 * Defines the direction of the timeline.
	 */
	enum Direction
	{
		FORWARDS,
		BACKWARDS
	};

	/**
	 * Defines the curve shape for the timeline.
	 */
	enum CurveShape
	{
		LINEAR_CURVE,
		EASE_IN_CURVE,
		EASE_OUT_CURVE,
		EASE_IN_AND_OUT_CURVE
	};

	/**
	 * Default constructor.
	 */
	Timeline();

	/**
	 * Convenience constructor.
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
	 * @param startOutput the starting output value for the timeline.
	 * @param endOutput the ending output value for the timeline.
	 */
	inline void setOutputRange(double startOutput, double endOutput)
	{
		_startOutput = startOutput;
		_endOutput = endOutput;
	}

	/**
	 * Sets the direction of the timeline.
	 *
	 * @param direction the direction to set for the timeline.
	 */
	inline void setDirection(const Direction& direction) { _direction = direction; }

	/**
	 * Determines the direction of the timeline.
	 *
	 * @return the direction of the timeline.
	 */
	inline Direction direction() { return _direction; }

	/**
	 * Sets the curve shape of the timeline.
	 *
	 * @param curveShape the curve shape to set for the timeline.
	 */
	inline void setCurveShape(const CurveShape& curveShape) { _curveShape = curveShape; }

	/**
	 * Returns the curve shape for the timeline.
	 *
	 * @return the curve shape for the timeline.
	 */
	inline CurveShape curveShape() { return _curveShape; }

	/**
	 * Sets the duration of the timeline.
	 *
	 * @param duration the duration to set for the timeline.
	 */
	inline void setDuration(double duration) { _duration = duration; }

	/**
	 * Returns the duration of the timeline.
	 *
	 * @return the duration of the timeline.
	 */
	inline double duration() { return _duration; }

	/**
	 * Returns the state of the timeline.
	 *
	 * @return the state of the timeline.
	 */
	inline State state() { return _state; }

	/**
	 * Returns the step value of the timeline.
	 *
	 * The step value is the actual value within the start and end
	 * outputs. This value moves along the curve shape between the
	 * start and end output values as the timeline is run.
	 *
	 * @return the step value of the timeline.
	 */
	inline double stepValue() { return _stepValue; }

	/**
	 * Returns the step increment of the timeline.
	 *
	 * The step increment is the difference between the value previous
	 * step value and the current step value.
	 *
	 * @return the step increment of the timeline.
	 */
	inline double stepIncrement() { return _stepIncrement; }

protected:

	/**
	 * Calculates the acceleration for the step.
	 */
	void _calculateAcceleration();

	/**
	 * Updates the timeline step value.
	 */
	void _generateStep();

	// Instance member variables
	State			_state;				/**< Timeline run-time status. */
	Direction		_direction;			/**< Timeline forwards or backwards direction. */
	CurveShape		_curveShape;		/**< Timeline curve shape interpolation. */
	double			_duration;			/**< How long the timeline will run. */
	double			_halfDuration;		/**< Half the time the timeline will run. */
	double			_runTime;			/**< How long the timeline has been running. */
	double			_acceleration;		/**< How fast or slow the timeline accelerates. */
	double			_stepValue;			/**< The step output value generated from start to end. */
	double			_stepIncrement;		/**< The step output increment between each update. */
	double			_startOutput;		/**< The starting point step value. */
	double			_endOutput;			/**< The ending point step value. */
	Timer			_timer;				/**< The timer used to keep track of time. */
};

}	// End of bump namespace

#endif	// End of BUMP_TIMELINE_H
