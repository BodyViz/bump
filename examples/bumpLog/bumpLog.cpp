//
//  bumpLog.cpp
//  Bump
//
//  Created by Christian Noon on 12/3/12.
//  Copyright (c) 2012 Christian Noon. All rights reserved.
//

// Boost headers
#include <boost/thread.hpp>

// Bump headers
#include <bump/Log.h>

// Custom prefixes for logging
#define customPrefix			"[bump] "
#define customDashPrefix		"- [bump] "

/**
 * Simple function that prints out a message on all log levels.
 */
void pushAllLogMessageLevels()
{
	bumpALWAYS("- ALWAYS Message");
	bumpERROR("- ERROR Message");
	bumpWARNING("- WARNING Message");
	bumpINFO("- INFO Message");
	bumpDEBUG("- DEBUG Message");
}

/**
 * Helper callable to demonstrate the bump::Log's thread-safety.
 */
struct Callable
{
	// Instance member variables
	bump::String name;
	uint64_t counter = 0;

	// Constructor
	Callable(const bump::String& callableName) { name = callableName; }

	// Callback
    void operator()()
	{
		for (uint64_t i = 0; i < 10; ++i)
		{
			bumpALWAYS(bump::String("- %1: %2").arg(name, counter));
			++counter;
		}
	}
};

/**
 * Runs the bump::Log in parallel across two different threads to demonstrate the
 * thread-safety of the logging system.
 */
void runThreadSafetyDemo()
{
    Callable x("Callable X");
	Callable y("Callable Y");
	boost::thread thread_x(x);
	boost::thread thread_y(y);
	thread_x.join();
	thread_y.join();
}

/**
 * This example demonstrates how to use the Bump logging system API.
 *
 * This logging system supports the following:
 *
 *	  - Five different log levels
 *	  - Output redirection to files (a custom std::ofstream)
 *	  - Thread-safe access to the stream buffer and thread-safe logging functions
 *    - Timestamp formatting
 *	  - Disabling the log altogether
 *
 * The following environment variables can be used to configure the log at runtime:
 *
 *	  - BUMP_LOG_ENABLED: Disables the log system if set to any of the following:
 *		  * [ NO | FALSE | NOPE | DISABLE ]
 *	  - BUMP_LOG_FILE: Redirects the output from the log to a specified file:
 *		  * /home/username/output.txt
 *	  - BUMP_LOG_LEVEL: Defines the maximum output level for the log:
 *		  * [ ALWAYS_LVL | ERROR_LVL | WARNING_LVL | INFO_LVL | DEBUG_LVL ]
 *
 * Using the log is straight-forward. There are several different convenience functions
 * provided to make this as simple as possible. The easiest way to use the log is with
 * the following functions:
 *
 *    - bumpALWAYS(message);
 *    - bumpERROR(message);
 *    - bumpWARNING(message);
 *    - bumpINFO(message);
 *    - bumpDEBUG(message);
 *
 * Here is a simple example using the bumpDEBUG() function:
 *
 *    - bumpDEBUG("this is my output");
 *
 * Sometimes, it is useful to be able to prefix your output with something like a
 * namespace, application name, error message, etc. For this purpose, the following
 * functions exist:
 *
 *	  - bumpALWAYS_P(prefix, message);
 *	  - bumpERROR_P(prefix, message);
 *	  - bumpWARNING_P(prefix, message);
 *	  - bumpINFO_P(prefix, message);
 *	  - bumpDEBUG_P(prefix, message);
 *
 * Here are some common examples of different logging messages:
 *
 *	  - bumpERROR_P("[bump] ", "ERROR: We have a problem here");
 *	  - bumpALWAYS_P("[bump] ", "Initializing the logging system");
 *
 * As you can see, it is just like using std::cout, except with a bunch of extra benefits!
 */
int main(int argc, char **argv)
{
	//=======================================================================
	//          Demonstrates how to use the environment variables
	//=======================================================================

	// If you want to use any of the environment variables to configure the
	// Log instance, then go ahead and set them before running this example.
	// Here are the environment variables that can be configured:
	//    - BUMP_LOG_ENABLED
	//        - if you set this to "no", then the output is disabled
	//    - BUMP_LOG_LEVEL
	//        - this automatically sets the log level for the log instance
	//    - BUMP_LOG_FILE
	//        - redirects all output to the filepath

	//=======================================================================
	//           Demonstrates how to use the different log levels
	//=======================================================================

	// Set the log level to "ALWAYS"
	bump::Log::instance()->setLogLevel(bump::Log::ALWAYS_LVL);
	bumpALWAYS("Setting LogLevel to ALWAYS:");
	pushAllLogMessageLevels();

	// Set the log level to "ERROR"
	bump::Log::instance()->setLogLevel(bump::Log::ERROR_LVL);
	bumpNEWLINE();
	bumpALWAYS("Setting LogLevel to ERROR:");
	pushAllLogMessageLevels();

	// Set the log level to "WARNING"
	bump::Log::instance()->setLogLevel(bump::Log::WARNING_LVL);
	bumpNEWLINE();
	bumpALWAYS("Setting LogLevel to WARNING:");
	pushAllLogMessageLevels();

	// Set the log level to "INFO"
	bump::Log::instance()->setLogLevel(bump::Log::INFO_LVL);
	bumpNEWLINE();
	bumpALWAYS("Setting LogLevel to INFO:");
	pushAllLogMessageLevels();

	// Set the log level to "DEBUG"
	bump::Log::instance()->setLogLevel(bump::Log::DEBUG_LVL);
	bumpNEWLINE();
	bumpALWAYS("Setting LogLevel to DEBUG:");
	pushAllLogMessageLevels();

	//=======================================================================
	//              Demonstrates how to use prefix logging
	//=======================================================================

	// Push some messages using the prefix logging functions
	bumpALWAYS(bump::String("\nPushing messages with a custom prefix: \"") << customDashPrefix << "\"");
	bumpALWAYS_P(customDashPrefix, "ALWAYS Message");
	bumpERROR_P(customDashPrefix, "ERROR Message");
	bumpWARNING_P(customDashPrefix, "WARNING Message");
	bumpINFO_P(customDashPrefix, "WARNING Message");
	bumpDEBUG_P(customDashPrefix, "DEBUG Message");

	//=======================================================================
	//            Demonstrates how to use timestamp formatting
	//=======================================================================

	// By default, the timestamp formatting is disabled. To enable it, just turn it on.
	bumpNEWLINE();
	bump::Log::instance()->setIsTimestampingEnabled(true);
	bump::Log::instance()->setTimestampFormat(bump::Log::DATE_TIME_TIMESTAMP);
	bumpALWAYS("Example message with \"DATE_TIME_TIMESTAMP\" timestamp formatting");
	bumpALWAYS_P(customPrefix, "Example prefix message with \"DATE_TIME_TIMESTAMP\" timestamp formatting\n");

	// From here, you can customize the timestamp format as you wish
	bump::Log::instance()->setTimestampFormat(bump::Log::DATE_TIME_WITH_AM_PM_TIMESTAMP);
	bumpALWAYS("Example message with \"DATE_TIME_WITH_AM_PM_TIMESTAMP\" timestamp formatting");
	bumpALWAYS_P(customPrefix, "Example prefix message with \"DATE_TIME_WITH_AM_PM_TIMESTAMP\" timestamp formatting\n");

	bump::Log::instance()->setTimestampFormat(bump::Log::TIME_TIMESTAMP);
	bumpALWAYS("Example message with \"TIME_TIMESTAMP\" timestamp formatting");
	bumpALWAYS_P(customPrefix, "Example prefix message with \"TIME_TIMESTAMP\" timestamp formatting\n");

	bump::Log::instance()->setTimestampFormat(bump::Log::TIME_WITHOUT_AM_PM_TIMESTAMP);
	bumpALWAYS("Example message with \"TIME_WITHOUT_AM_PM_TIMESTAMP\" timestamp formatting");
	bumpALWAYS_P(customPrefix, "Example prefix message with \"TIME_WITHOUT_AM_PM_TIMESTAMP\" timestamp formatting\n");

	// Then to turn it back off, simply disable it.
	bump::Log::instance()->setIsTimestampingEnabled(false);
	bumpALWAYS("The timestamps should now be disabled and not visible");
	bumpNEWLINE();

	//=======================================================================
	//               Demonstrates the log's thread-safety
	//=======================================================================

	// Run the thread safety demo to show that the bump::Log is thread-safe
	bumpALWAYS("Thread Saftey Demo:");
	runThreadSafetyDemo();

    return 0;
}
