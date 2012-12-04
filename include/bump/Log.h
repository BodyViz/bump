//
//	Log.h
//	Bump
//
//	Created by Christian Noon on 12/3/12.
//	Copyright (c) 2012 Christian Noon. All rights reserved.
//

#ifndef BUMP_LOG_H
#define BUMP_LOG_H

// Boost headers
#include <boost/thread.hpp>

// Bump headers
#include <bump/Export.h>
#include <bump/String.h>

// Environment variable name definitions
#define BUMP_LOG_ENABLED	"BUMP_LOG_ENABLED"
#define BUMP_LOG_FILE		"BUMP_LOG_FILE"
#define BUMP_LOG_LEVEL		"BUMP_LOG_LEVEL"

// Defines the bump prefix for logging
#define bumpPrefix			"[bump] "

namespace bump {

/**
 * The Log class handles all logging.
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
class BUMP_EXPORT Log
{
public:

	/** The various levels of log message verbosity. */
	enum LogLevel
	{
		ALWAYS_LVL,
		ERROR_LVL,
		WARNING_LVL,
		INFO_LVL,
		DEBUG_LVL
	};

	/** The various date time formats. */
	enum DateTimeFormat
	{
		DATE_TIME_DEFAULT,
		DATE_TIME_WITH_AM_PM,
		DATE_TIME_PRECISE,
		TIME_DEFAULT,
		TIME_WITH_AM_PM,
		TIME_PRECISE
	};

	/**
	 * Creates a singleton instance.
	 *
	 * @return the singleton Log instance.
	 */
	static Log* instance() { static Log log; return &log; }

	/**
	 * Sets whether the log is enabled.
	 *
	 * @param enabled whether the log is enabled.
	 */
	void setIsLogEnabled(bool enabled);

	/**
	 * Returns whether the log is enabled.
	 *
	 * @return true if the log is enabled, false otherwise.
	 */
	bool isLogEnabled();

	/**
	 * Determines whether the log level is enabled.
	 *
	 * @param logLevel the log level to determine if enabled.
	 * @return whether the given logLevel is enabled.
	 */
	bool isLogLevelEnabled(LogLevel logLevel);

	/**
	 * Sets the log level.
	 *
	 * @param logLevel the log level to set the Log instance to.
	 */
	void setLogLevel(LogLevel logLevel);

	/**
	 * Determines the log level.
	 *
	 * @return the log level for the Log instance.
	 */
	LogLevel logLevel();

	/**
	 * Sets whether the date time formatting display is enabled.
	 *
	 * @param enabled whether the date time formatting display is enabled.
	 */
	void setIsDateTimeFormattingEnabled(bool enabled);

	/**
	 * Determines whether the date time formatting display is enabled.
	 *
	 * @return true if the date time formatting display is enabled, false otherwise.
	 */
	bool isDateTimeFormattingEnabled();

	/**
	 * Sets the date time format.
	 *
	 * @param format the date time format to set the Log instance to.
	 */
	void setDateTimeFormat(const DateTimeFormat& format);

	/**
	 * Determines the date time format.
	 *
	 * @return the date time format.
	 */
	DateTimeFormat dateTimeFormat();

	/**
	 * Sets the output stream to a std::ofstream created from the provided filepath.
	 *
	 * NOTE: This will not change the current log stream if the file cannot be opened successfully.
	 *
	 * @param filepath the filepath of the file to write all the log output to.
	 * @return true if the stream was replaced, false otherwise.
	 */
	bool setLogFile(const String& filepath);

	/**
	 * Switches the current output stream to the provided stream.
	 *
	 * @param stream the output stream to start using for the Log instance.
	 */
	void setLogStream(std::ostream& stream);

	/**
	 * Returns the log output stream (use like std::cout).
	 *
	 * @param logLevel the log level of the stream being requested.
	 * @param prefix the string to tack onto the front of the message.
	 * @return the output stream to write to.
	 */
	std::ostream& logStream(LogLevel level, const String& prefix = "");

protected:

	/**
	 * Constructor.
	 *
	 * Initializes the log level by attempting to grab the BUMP_LOG_LEVEL environment
	 * variables from the user's environment.
	 */
	Log();

	/**
	 * Destructor.
	 */
	~Log();

public:

	/**
	 * Returns the current time as a formatted string.
	 *
	 * @return the current time as a formatted string.
	 */
	String	_convertTimeToString();

	/** Instance member variables. */
	bool					_isEnabled;
	LogLevel				_logLevel;
	bool					_isDateTimeFormatEnabled;
	DateTimeFormat			_dateTimeFormat;
	std::ostream*			_logStream;
	boost::mutex			_mutex;
};

/**
 * Convenience macro for accessing the Log singleton.
 */
#define LOG() bump::Log::instance()

/**
 * Log messages with levels. Below are a couple examples:
 *
 * LOG_WARNING() << "This is an example of a WARNING message" << std::endl;
 * - Would log: "This is an example of a WARNING message"
 *
 * LOG_ERROR() << "ERROR: Look at what happened!" << std::endl;
 * - Would log: "ERROR: Look at what happened!" << std::endl;
 */
#define LOG_ALWAYS() log(bump::Log::ALWAYS_LVL)
#define LOG_ERROR() log(bump::Log::ERROR_LVL)
#define LOG_WARNING() log(bump::Log::WARNING_LVL)
#define LOG_INFO() log(bump::Log::INFO_LVL)
#define LOG_DEBUG() log(bump::Log::DEBUG_LVL)

/**
 * Logs a message with the defined prefix. Below are a couple examples:
 *
 * LOG_ERROR_P(bumpPrefix) << "ERROR: Look at what happened!" << std::endl;
 * - Would log: "[bump] ERROR: Look at what happened!"
 *
 * LOG_ERROR_P(bumpPrefix) << "This output uses the preprocessor definition bumpPrefix" << std::endl;
 * - Would log: "[bump] This output uses the preprocessor definition bumpPrefix"
 */
#define LOG_ALWAYS_P(prefix) logWithPrefix(bump::Log::ALWAYS_LVL, prefix)
#define LOG_ERROR_P(prefix) logWithPrefix(bump::Log::ERROR_LVL, prefix)
#define LOG_WARNING_P(prefix) logWithPrefix(bump::Log::WARNING_LVL, prefix)
#define LOG_INFO_P(prefix) logWithPrefix(bump::Log::INFO_LVL, prefix)
#define LOG_DEBUG_P(prefix) logWithPrefix(bump::Log::DEBUG_LVL, prefix)

/**
 * DO NOT USE THESE MACROS!!!
 *
 * Only for internal use, please use the methods above for logging.
 */
#define log(level) if ((LOG()->isLogLevelEnabled(level)) && level <= LOG()->logLevel()) LOG()->logStream(level)
#define logWithPrefix(level, prefix) if ((LOG()->isLogLevelEnabled(level)) && level <= LOG()->logLevel()) LOG()->logStream(level, prefix)

}	// End of bump namespace

#endif	// End of BUMP_LOG_H
