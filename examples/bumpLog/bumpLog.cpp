//
//  bumpLog.cpp
//  Bump
//
//  Created by Christian Noon on 12/3/12.
//  Copyright (c) 2012 Christian Noon. All rights reserved.
//

// Bump headers
#include <bump/Log.h>

#define customPrefix			"[bump] "
#define customDashPrefix		"- [bump] "

void pushAllLogMessageTypes()
{
	LOG_ALWAYS() << "- ALWAYS Message" << std::endl;
	LOG_ERROR() << "- ERROR Message" << std::endl;
	LOG_WARNING() << "- WARNING Message" << std::endl;
	LOG_INFO() << "- WARNING Message" << std::endl;
	LOG_DEBUG() << "- DEBUG Message" << std::endl;
}

/**
 * This example demonstrates how to use the Bump logging system API.
 *
 * This logging system supports the following:
 *
 *	  - Five different log levels
 *	  - Output redirection to files (a custom std::ofstream)
 *	  - Thread-safe access to the stream buffer
 *    - Date time formatting
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
 * Using the log is straight-forward. There are several different convenience macros
 * provided to make this as simple as possible. The easiest way to use the log is with
 * the following macros:
 *
 *    - LOG_ALWAYS()
 *    - LOG_ERROR()
 *    - LOG_WARNING()
 *    - LOG_INFO()
 *    - LOG_DEBUG()
 *
 * Here is a simple example using the LOG_DEBUG() macro:
 *
 *    - LOG_DEBUG() << "this is my output" << std::endl;
 *
 * Sometimes, it is useful to be able to prefix your output with something like a
 * namespace, application name, error message, etc. For this purpose, the following
 * macros exist:
 *
 *	  - LOG_ALWAYS_P(prefix)
 *	  - LOG_ERROR_P(prefix)
 *	  - LOG_WARNING_P(prefix)
 *	  - LOG_INFO_P(prefix)
 *	  - LOG_DEBUG_P(prefix)
 *
 * Here are some common examples of different logging messages:
 *
 *	  - LOG_ERROR_P("[bump] ") << "ERROR: We have a problem here" << std::endl;
 *	  - LOG_ALWAYS_P("[bump] ") << "Initializing the logging system" << std::endl;
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
	LOG_ALWAYS() << "Setting LogLevel to ALWAYS:" << std::endl;
	pushAllLogMessageTypes();

	// Set the log level to "ERROR"
	bump::Log::instance()->setLogLevel(bump::Log::ERROR_LVL);
	LOG_ALWAYS() << "\nSetting LogLevel to ERROR:" << std::endl;
	pushAllLogMessageTypes();

	// Set the log level to "WARNING"
	bump::Log::instance()->setLogLevel(bump::Log::WARNING_LVL);
	LOG_ALWAYS() << "\nSetting LogLevel to WARNING:" << std::endl;
	pushAllLogMessageTypes();

	// Set the log level to "INFO"
	bump::Log::instance()->setLogLevel(bump::Log::INFO_LVL);
	LOG_ALWAYS() << "\nSetting LogLevel to INFO:" << std::endl;
	pushAllLogMessageTypes();

	// Set the log level to "DEBUG"
	bump::Log::instance()->setLogLevel(bump::Log::DEBUG_LVL);
	LOG_ALWAYS() << "\nSetting LogLevel to DEBUG:" << std::endl;
	pushAllLogMessageTypes();

	//=======================================================================
	//              Demonstrates how to use prefix logging
	//=======================================================================

	// Push some messages using the prefix logging functions
	LOG_ALWAYS() << "\nPushing messages with a custom prefix: \"" << customDashPrefix << "\"" << std::endl;
	LOG_ALWAYS_P(customDashPrefix) << "ALWAYS Message" << std::endl;
	LOG_ERROR_P(customDashPrefix) << "ERROR Message" << std::endl;
	LOG_WARNING_P(customDashPrefix) << "WARNING Message" << std::endl;
	LOG_INFO_P(customDashPrefix) << "WARNING Message" << std::endl;
	LOG_DEBUG_P(customDashPrefix) << "DEBUG Message" << std::endl;

	//=======================================================================
	//            Demonstrates how to use date time formatting
	//=======================================================================

	// By default, the date time formatting is disabled. To enable it, just
	// turn it on.
	LOG_ALWAYS() << std::endl;
	LOG()->setIsDateTimeFormattingEnabled(true);
	LOG_ALWAYS() << "Example message with \"DATE_TIME_DEFAULT\" date time formatting" << std::endl;
	LOG_ALWAYS_P(customPrefix) << "Example prefix message with \"DATE_TIME_DEFAULT\" date time formatting\n" << std::endl;

	// From here, you can customize the output format using the date time format enumeration
	LOG()->setDateTimeFormat(bump::Log::DATE_TIME_WITH_AM_PM);
	LOG_ALWAYS() << "Example message with \"DATE_TIME_WITH_AM_PM\" date time formatting" << std::endl;
	LOG_ALWAYS_P(customPrefix) << "Example prefix message with \"DATE_TIME_WITH_AM_PM\" date time formatting\n" << std::endl;

	LOG()->setDateTimeFormat(bump::Log::TIME_DEFAULT);
	LOG_ALWAYS() << "Example message with \"TIME_DEFAULT\" date time formatting" << std::endl;
	LOG_ALWAYS_P(customPrefix) << "Example prefix message with \"TIME_DEFAULT\" date time formatting\n" << std::endl;

	LOG()->setDateTimeFormat(bump::Log::TIME_WITH_AM_PM);
	LOG_ALWAYS() << "Example message with \"TIME_WITH_AM_PM\" date time formatting" << std::endl;
	LOG_ALWAYS_P(customPrefix) << "Example prefix message with \"TIME_WITH_AM_PM\" date time formatting\n" << std::endl;

	// Then to turn it back off, simply disable it.
	LOG()->setIsDateTimeFormattingEnabled(false);
	LOG_ALWAYS() << "The date time formatting should now be disabled and not visible" << std::endl;

    return 0;
}
