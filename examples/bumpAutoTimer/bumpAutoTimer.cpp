//
//  bumpAutoTimer.cpp
//  Bump
//
//  Created by Christian Noon on 12/4/12.
//  Copyright (c) 2012 Christian Noon. All rights reserved.
//

// Bump headers
#include <bump/AutoTimer.h>

// C++ headers
#include <iostream>
#include <math.h>

void doSomeWork()
{
	// Create an auto timer
	bump::AutoTimer timer;

	// Perform some work that takes a bit
	for (unsigned long i = 0; i < 100000000; ++i)
	{
		double temp = sqrt(123.456);
		temp += 1.0f;
	}
}

void doSomeMoreWork(const bump::AutoTimer::OutputType& outputType)
{
	// Create an auto timer
	bump::AutoTimer timer(outputType);

	// Perform some work that takes a bit
	for (unsigned long i = 0; i < 100000000; ++i)
	{
		double temp = sqrt(123.456);
		temp += 1.0f;
	}
}

void massiveMethod()
{
	// Create a heap allocated auto timer
	bump::AutoTimer* timer = new bump::AutoTimer();

	// Chunk 1 of work
	std::cout << "Starting Chunk 1:" << std::endl;
	for (unsigned long i = 0; i < 300000000; ++i)
	{
		double temp = sqrt(123.456);
		temp += 1.0f;
	}
	delete timer;
	timer = new bump::AutoTimer();

	// Chunk 2 of work
	std::cout << "Starting Chunk 2:" << std::endl;
	for (unsigned long i = 0; i < 100000000; ++i)
	{
		double temp = sqrt(123.456);
		temp += 1.0f;
	}
	delete timer;
	timer = new bump::AutoTimer();

	// Chunk 3 of work
	std::cout << "Starting Chunk 3:" << std::endl;
	for (unsigned long i = 0; i < 400000000; ++i)
	{
		double temp = sqrt(123.456);
		temp += 1.0f;
	}
	delete timer;
	timer = new bump::AutoTimer();

	// Chunk 4 of work
	std::cout << "Starting Chunk 4:" << std::endl;
	for (unsigned long i = 0; i < 200000000; ++i)
	{
		double temp = sqrt(123.456);
		temp += 1.0f;
	}
	delete timer;
}

/**
 * This example demonstrates how to use the Bump auto timer API.
 *
 * The AutoTimer class is used for easily measuring elapsed time in a particular
 * scope. When the AutoTimer is destructed, it will print out the elapsed
 * time to std::cout.
 */
int main(int argc, char **argv)
{
	// Using an auto timer is super simple. You add it to a scope that you want timed,
	// and once it is destructed, it will print out the elapsed time. For example,
	// let's run the "doSomeWork" method and see what happens.
	std::cout << "Starting up the \"doSomeWork\" method" << std::endl;
	doSomeWork();

	// You can also modify the output type of the auto timer. Let's run the
	// "doSomeMoreWork" method with different output types to see the different
	// types.
	std::cout << "\nStarting up the \"doSomeMoreWork\" method with a seconds auto timer" << std::endl;
	doSomeMoreWork(bump::AutoTimer::SECONDS);
	std::cout << "\nStarting up the \"doSomeMoreWork\" method with a milliseconds auto timer" << std::endl;
	doSomeMoreWork(bump::AutoTimer::MILLISECONDS);
	std::cout << "\nStarting up the \"doSomeMoreWork\" method with a microseconds auto timer" << std::endl;
	doSomeMoreWork(bump::AutoTimer::MICROSECONDS);
	std::cout << "\nStarting up the \"doSomeMoreWork\" method with a nanoseconds auto timer" << std::endl;
	doSomeMoreWork(bump::AutoTimer::NANOSECONDS);

	// If you have a massive method that is all in the same scope, and you need to
	// break down the performance into chunks, you could use heap allocated auto timers
	// to figure it out. Here's an example of doing this.
	std::cout << "\n============ Starting up the massiveMethod ============\n" << std::endl;
	massiveMethod();

    return 0;
}
