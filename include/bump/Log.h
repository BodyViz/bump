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
 *	  - Five different log levels
 *	  - Output redirection to files (a custom std::ofstream)
 *	  - Thread-safe access to the stream buffer
 *    - Timestamp formatting
 *	  - Disabling the log altogether
 *
 * The following environment variables can be used to configure the log at runtime:
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
 *    - LOG_ALWAYS()
 *    - LOG_ERROR()
 *    - LOG_WARNING()
 *    - LOG_INFO()
 *    - LOG_DEBUG()
 *
 * Here is a simple example using the LOG_DEBUG() macro:
 *
 * @code
 *   LOG_DEBUG() << "this is my output" << std::endl;
 * @endcode
 *
 * Sometimes, it is useful to be able to prefix your output with something like a
 * namespace, application name, error message, etc. For this purpose, the following
 * macros exist:
 *	  - LOG_ALWAYS_P(prefix)
 *	  - LOG_ERROR_P(prefix)
 *	  - LOG_WARNING_P(prefix)
 *	  - LOG_INFO_P(prefix)
 *	  - LOG_DEBUG_P(prefix)
 *
 * Here are some common examples of different logging messages:
 *
 * @code
 *   LOG_ERROR_P("[bump] ") << "ERROR: We have a problem here" << std::endl;
 *   LOG_ALWAYS_P("[bump] ") << "Initializing the logging system" << std::endl;
 * @endcode
 *
 * As you can see, it is just like using std::cout, except with a bunch of extra benefits!
 */
class BUMP_EXPORT Log
{
public:

	/** The various levels of log message verbosity. */
	enum LogLevel
	{
		ALWAYS_LVL,		/**< These will always be shown if the log is enabled. */
		ERROR_LVL,		/**< Used for errors that the application cannot recover from. */
		WARNING_LVL,	/**< For warnings that the application can recover from. */
		INFO_LVL,		/**< Information that can be useful to the user. */
		DEBUG_LVL		/**< Designed purely for the lowest level debugging. */
	};

	/** The various timestamp formats. */
	enum TimestampFormat
	{
		DATE_TIME_TIMESTAMP,				/**< Date and time with format: 2013-01-14 10:51:33. */
		DATE_TIME_WITH_AM_PM_TIMESTAMP,		/**< Date and time with format: 2013-01-14 10:51:33 AM. */
		TIME_TIMESTAMP,						/**< Time with format: 2013-01-14 10:51:33. */
		TIME_WITHOUT_AM_PM_TIMESTAMP		/**< Time with format: 2013-01-14 10:51:33 AM. */
	};

	/**
	 * Creates a singleton instance.
	 *
	 * @return The singleton Log instance.
	 */
	static Log* instance() { static Log log; return &log; }

	/**
	 * Sets whether the log is enabled.
	 *
	 * @param enabled Whether the log is enabled.
	 */
	void setIsLogEnabled(bool enabled);

	/**
	 * Returns whether the log is enabled.
	 *
	 * @return True if the log is enabled, false otherwise.
	 */
	bool isLogEnabled();

	/**
	 * Returns whether the log level is enabled.
	 *
	 * @param logLevel The log level to determine if enabled.
	 * @return Whether the given logLevel is enabled.
	 */
	bool isLogLevelEnabled(LogLevel logLevel);

	/**
	 * Sets the log level.
	 *
	 * @param logLevel The log level to set the Log instance to.
	 */
	void setLogLevel(LogLevel logLevel);

	/**
	 * Returns the log level.
	 *
	 * @return The log level for the Log instance.
	 */
	LogLevel logLevel();

	/**
	 * Sets whether the timestamp display is enabled.
	 *
	 * @param enabled Whether to display timestamps in the log messages.
	 */
	void setIsTimestampingEnabled(bool enabled);

	/**
	 * Returns whether timestamps are displayed in the log messages.
	 *
	 * @return True if timestamps are displayed in the log messages, false otherwise.
	 */
	bool isTimestampingEnabled();

	/**
	 * Sets the timestamp format.
	 *
	 * @param format The timestamp format to set the Log instance to.
	 */
	void setTimestampFormat(const TimestampFormat& format);

	/**
	 * Returns the timestamp format.
	 *
	 * @return The timestamp format.
	 */
	TimestampFormat timestampFormat();

	/**
	 * Sets the output stream to a std::ofstream created from the provided filepath.
	 *
	 * NOTE: This will not change the current log stream if the file cannot be opened successfully.
	 *
	 * @param filepath The filepath of the file to write all the log output to.
	 * @return True if the stream was replaced, false otherwise.
	 */
	bool setLogFile(const String& filepath);

	/**
	 * Switches the current output stream to the provided stream.
	 *
	 * @param stream The output stream to start using for the Log instance.
	 */
	void setLogStream(std::ostream& stream);

	/**
	 * Returns the log output stream (use like std::cout).
	 *
	 * @param prefix The string to tack onto the front of the message.
	 * @return The output stream to write to.
	 */
	std::ostream& logStream(const String& prefix = "");

	/**
	 * Returns a null log stream that won't push any output through it.
	 *
	 * @param prefix The string to tack onto the front of the message.
	 * @return The output stream to write to.
	 */
	std::ostream& nullLogStream();

protected:

	/**
	 * @internal
	 * Constructor.
	 *
	 * Initializes the log level by attempting to grab the BUMP_LOG_LEVEL environment
	 * variables from the user's environment.
	 */
	Log();

	/**
	 * @internal
	 * Destructor.
	 */
	~Log();

	/**
	 * @internal
	 * Returns the current time as a formatted string.
	 *
	 * @return The current time as a formatted string.
	 */
	String convertTimeToString();

	// Instance member variables
	bool					_isEnabled;					/**< @internal Whether the log is enabled for output. */
	LogLevel				_logLevel;					/**< @internal The log level the log instance is set to. */
	bool					_isDateTimeFormatEnabled;	/**< @internal Whether the date/time are tacked onto the log output. */
	TimestampFormat			_timestampFormat;			/**< @internal The timestamp format when enabled. */
	std::ostream*			_logStream;					/**< @internal The log stream to output to. */
	std::ostream			_nullLogStream;				/**< @internal A null log stream that won't push output. */
	boost::mutex			_mutex;						/**< @internal A boost mutex used to make the log streamm access thread-safe. */
};

}	// End of bump namespace

/**
 * Logs the message no matter what level is set.
 *
 * @code
 *   LOG_ALWAYS() << "This is an ALWAYS message" << std::endl; // outputs "This is an ALWAYS message"
 * @endcode
 */
std::ostream& LOG_ALWAYS();

/**
 * Logs the message when the log level is set to ERROR_LVL or higher.
 *
 * @code
 *   LOG_ERROR() << "This is an ERROR message" << std::endl; // outputs "This is an ERROR message"
 * @endcode
 */
std::ostream& LOG_ERROR();

/**
 * Logs the message when the log level is set to WARNING_LVL or higher.
 *
 * @code
 *   LOG_WARNING() << "This is a WARNING message" << std::endl; // outputs "This is a WARNING message"
 * @endcode
 */
std::ostream& LOG_WARNING();

/**
 * Logs the message when the log level is set to INFO_LVL or higher.
 *
 * @code
 *   LOG_INFO() << "This is an INFO message" << std::endl; // outputs "This is an INFO message"
 * @endcode
 */
std::ostream& LOG_INFO();

/**
 * Logs the message only when the log level is set to DEBUG_LVL.
 *
 * @code
 *   LOG_DEBUG() << "This is a DEBUG message" << std::endl; // outputs "This is a DEBUG message"
 * @endcode
 */
std::ostream& LOG_DEBUG();

/**
 * Logs the message with the given prefix no matter what level is set.
 *
 * @code
 *   LOG_ALWAYS_P(bumpPrefix) << "This is an ALWAYS message" << std::endl; // outputs "[bump] This is an ALWAYS message"
 * @endcode
 */
std::ostream& LOG_ALWAYS_P(const bump::String& prefix);

/**
 * Logs the message with the given prefix when the log level is set to ERROR_LVL or higher.
 *
 * @code
 *   LOG_ERROR_P(bumpPrefix) << "This is an ERROR message" << std::endl; // outputs "[bump] This is an ERROR message"
 * @endcode
 */
std::ostream& LOG_ERROR_P(const bump::String& prefix);

/**
 * Logs the message with the given prefix when the log level is set to WARNING_LVL or higher.
 *
 * @code
 *   LOG_WARNING_P(bumpPrefix) << "This is a WARNING message" << std::endl; // outputs "[bump] This is a WARNING message"
 * @endcode
 */
std::ostream& LOG_WARNING_P(const bump::String& prefix);

/**
 * Logs the message with the given prefix when the log level is set to INFO_LVL or higher.
 *
 * @code
 *   LOG_INFO_P(bumpPrefix) << "This is an INFO message" << std::endl; // outputs "[bump] This is an INFO message"
 * @endcode
 */
std::ostream& LOG_INFO_P(const bump::String& prefix);

/**
 * Logs the message with the given prefix only when the log level is set to DEBUG_LVL.
 *
 * @code
 *   LOG_DEBUG_P(bumpPrefix) << "This is a DEBUG message" << std::endl; // outputs "[bump] This is a DEBUG message"
 * @endcode
 */
std::ostream& LOG_DEBUG_P(const bump::String& prefix);

#endif	// End of BUMP_LOG_H
