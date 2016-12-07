//
//  Timeline.cpp
//  Bump
//
//  Created by Christian Noon on 12/4/12.
//  Copyright (c) 2012 Christian Noon. All rights reserved.
//

// C++ headers
#include <iostream>

// Bump headers
#include <bump/Timeline.h>

namespace bump {

Timeline::Timeline() :
	_state(NOT_RUNNING),
	_direction(FORWARDS),
	_curveShape(LINEAR_CURVE),
	_duration(10.0),
	_halfDuration(0.0),
	_runTime(0.0),
	_acceleration(0.0),
	_stepValue(0.0),
	_stepIncrement(0.0),
	_startOutput(0.0),
	_endOutput(100.0),
	_timer()
{
	;
}

Timeline::Timeline(double duration, const Direction& direction, const CurveShape& curveShape) :
	_state(NOT_RUNNING),
	_direction(direction),
	_curveShape(curveShape),
	_duration(duration),
	_halfDuration(0.0),
	_runTime(0.0),
	_acceleration(0.0),
	_stepValue(0.0),
	_stepIncrement(0.0),
	_startOutput(0.0),
	_endOutput(100.0),
	_timer()
{
	;
}

Timeline::~Timeline()
{
	;
}

void Timeline::start()
{
	if (_state == NOT_RUNNING || _state == FINISHED)
	{
		// Start the timer and set State to RUNNING
		_timer.start();
		_state = RUNNING;

		// Calculate the interpolation coefficients
		calculateAcceleration();
		_halfDuration = _duration / 2.0;

		// Reset the step value and step increment
		_stepValue = 0.0;
		_stepIncrement = 0.0;
	}
	else if (_state == PAUSED)
	{
		unpause();
	}
	else // _state == RUNNING
	{
		// Simply ignore if we're already running
	}
}

void Timeline::restart()
{
	_state = NOT_RUNNING;
	start();
}

void Timeline::stop()
{
	_state = NOT_RUNNING;
}

void Timeline::pause()
{
	_state = PAUSED;
	_timer.pause();
}

void Timeline::unpause()
{
	_state = RUNNING;
	_timer.unpause();
}

void Timeline::update()
{
	// Check to make sure we are in a state to be running
	if (_state == PAUSED)
	{
		std::cout << "Timeline update() is returning because it is PAUSED." << std::endl;
		return;
	}
	else if (_state == FINISHED)
	{
		std::cout << "Timeline update() is returning because it is FINISHED.\n" << std::endl;
		return;
	}
	else if (_state == NOT_RUNNING)
	{
		std::cout << "Timeline update() is returning because it is NOT_RUNNING.\n" << std::endl;
		return;
	}

	// Set the runTime
	_runTime = _timer.secondsElapsed();

	// Determine if we have reached the goal value or not
	if (_runTime >= _duration)
		_state = FINISHED;

	// Generate the new step value
	generateStep();
}

void Timeline::setOutputRange(double startOutput, double endOutput)
{
	_startOutput = startOutput;
	_endOutput = endOutput;
}

void Timeline::setDirection(const Direction& direction)
{
	_direction = direction;
}

Timeline::Direction Timeline::direction()
{
	return _direction;
}

void Timeline::setCurveShape(const CurveShape& curveShape)
{
	_curveShape = curveShape;
}

Timeline::CurveShape Timeline::curveShape()
{
	return _curveShape;
}

void Timeline::setDuration(double duration)
{
	_duration = duration;
}

double Timeline::duration()
{
	return _duration;
}

Timeline::State Timeline::state()
{
	return _state;
}

double Timeline::stepValue()
{
	return _stepValue;
}

double Timeline::stepIncrement()
{
	return _stepIncrement;
}

void Timeline::calculateAcceleration()
{
	if (_curveShape == EASE_IN_AND_OUT_CURVE)
	{
		_acceleration = (_endOutput - _startOutput) / ((_duration / 2) * (_duration / 2));
	}
	else
	{
		_acceleration = 2.0 * (_endOutput - _startOutput) / (_duration * _duration);
	}
}

void Timeline::generateStep()
{
	// Return the EXACT value if this is the last iteration
	if (_state == FINISHED && _direction == FORWARDS)
	{
		_stepIncrement = _endOutput - _stepValue;
		_stepValue = _endOutput;
		return;
	}
	else if (_state == FINISHED && _direction == BACKWARDS)
	{
		_stepIncrement = _startOutput - _stepValue;
		_stepValue = _startOutput;
		return;
	}

	//===================================================================
	// Process the step value for each velocity type and each direction
	//===================================================================

	double inverseDuration = _duration - _runTime;

	// EASE_IN_CURVE
	double newStepValue;
	if (_curveShape == EASE_IN_CURVE)
	{
		if (_direction == FORWARDS)
		{
			newStepValue = ((_acceleration * _runTime * _runTime) / 2.0) + _startOutput;
			_stepIncrement = newStepValue - _stepValue;
			_stepValue = newStepValue;
		}
		else
		{
			newStepValue = _endOutput - ((_acceleration * _runTime * _runTime) / 2.0);
			_stepIncrement = newStepValue - _stepValue;
			_stepValue = newStepValue;
		}
	}
	else if (_curveShape == EASE_OUT_CURVE) // EASE_OUT_CURVE
	{
		if (_direction == FORWARDS)
		{
			newStepValue = ((-_acceleration * inverseDuration * inverseDuration) / 2.0) + _endOutput;
			_stepIncrement = newStepValue - _stepValue;
			_stepValue = newStepValue;
		}
		else
		{
			newStepValue = _startOutput - ((-_acceleration * inverseDuration * inverseDuration) / 2.0);
			_stepIncrement = newStepValue - _stepValue;
			_stepValue = newStepValue;
		}
	}
	else if (_curveShape == EASE_IN_AND_OUT_CURVE) // EASE_IN_AND_OUT_CURVE
	{
		// The gap between linear in and out still needs to be investigated
		if (_runTime < _halfDuration)
		{
			if (_direction == FORWARDS)
			{
				newStepValue = ((_acceleration * _runTime * _runTime) / 2.0) + _startOutput;
				_stepIncrement = newStepValue - _stepValue;
				_stepValue = newStepValue;
			}
			else
			{
				newStepValue = _endOutput - ((_acceleration * _runTime * _runTime) / 2.0);
				_stepIncrement = newStepValue - _stepValue;
				_stepValue = newStepValue;
			}
		}
		else
		{
			if (_direction == FORWARDS)
			{
				newStepValue = ((-_acceleration * inverseDuration * inverseDuration) / 2.0) + _endOutput;
				_stepIncrement = newStepValue - _stepValue;
				_stepValue = newStepValue;
			}
			else
			{
				newStepValue = _startOutput - ((-_acceleration * inverseDuration * inverseDuration) / 2.0);
				_stepIncrement = newStepValue - _stepValue;
				_stepValue = newStepValue;
			}
		}
	}
	else // LINEAR_CURVE
	{
		if (_direction == FORWARDS)
		{
			newStepValue = (_runTime / _duration) * (_endOutput - _startOutput) + _startOutput;
			_stepIncrement = newStepValue - _stepValue;
			_stepValue = newStepValue;
		}
		else
		{
			newStepValue = ((_duration - _runTime) / _duration) * (_endOutput - _startOutput) + _startOutput;
			_stepIncrement = newStepValue - _stepValue;
			_stepValue = newStepValue;
		}
	}
}

}	// End of bump namespace
