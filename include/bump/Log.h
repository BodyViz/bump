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
#include <boost/thread/mutex.hpp>

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
 *	  - Thread-safe access to the stream buffer and thread-safe logging functions
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
 * Using the log is straight-forward. There are several different convenience functions
 * provided to make this as simple as possible. The easiest way to use the log is with
 * the following functions:
 *    - bumpALWAYS(message);
 *    - bumpERROR(message);
 *    - bumpWARNING(message);
 *    - bumpINFO(message);
 *    - bumpDEBUG(message);
 *
 * Here is a simple example using the bumpDEBUG() function:
 *    - bumpDEBUG("this is my output");
 *
 * Sometimes, it is useful to be able to prefix your output with something like a
 * namespace, application name, error message, etc. For this purpose, the following
 * functions exist:
 *	  - bumpALWAYS_P(prefix, message);
 *	  - bumpERROR_P(prefix, message);
 *	  - bumpWARNING_P(prefix, message);
 *	  - bumpINFO_P(prefix, message);
 *	  - bumpDEBUG_P(prefix, message);
 *
 * Here are some common examples of different logging messages:
 *
 * @code
 *   bumpERROR_P("[bump] ", "ERROR: We have a problem here");
 *   bumpALWAYS_P("[bump] ", "Initializing the logging system");
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
	 * Creates a thread-safe singleton instance of the Log object.
	 *
	 * @return The singleton instance.
	 */
	static Log* instance();

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

protected:

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
	boost::mutex			_mutex;						/**< @internal A boost mutex used to make the log stream access thread-safe. */

private:

	/**
	 * @internal
	 * Constructor.
	 *
	 * Initializes the log level by attempting to grab the BUMP_LOG_LEVEL environment
	 * variables from the user's environment. Needs to be private to ensure you can
	 * only create a single instance.
	 */
	Log();

	/**
	 * @internal
	 * Copy constructor.
	 *
	 * No-op to support the singleton.
	 */
	Log(const Log& log);

	/**
	 * @internal
	 * Overloaded assignment operator.
	 *
	 * No-op to support the singleton.
	 */
	void operator=(const Log& log);
};

}	// End of bump namespace

/**
 * Default log functions.
 *
 * These are the most commonly used logging functions. They automatically use the
 * appropriate log level for the message. The log stream is retrieved, then the message
 * is appended into it, then std::endl is appended onto the stream flushing the buffer.
 */
BUMP_EXPORT void bumpALWAYS(const bump::String& message);
BUMP_EXPORT void bumpERROR(const bump::String& message);
BUMP_EXPORT void bumpWARNING(const bump::String& message);
BUMP_EXPORT void bumpINFO(const bump::String& message);
BUMP_EXPORT void bumpDEBUG(const bump::String& message);
BUMP_EXPORT void bumpNEWLINE();

/**
 * Log functions that only flush the buffer.
 *
 * These functions set the appropriate log level for the message, retrieve the stream,
 * append the message into the stream, then flush the stream. This is useful for when
 * you need to generate multiple log messages on a single line.
 */
BUMP_EXPORT void bumpALWAYS_F(const bump::String& message);
BUMP_EXPORT void bumpERROR_F(const bump::String& message);
BUMP_EXPORT void bumpWARNING_F(const bump::String& message);
BUMP_EXPORT void bumpINFO_F(const bump::String& message);
BUMP_EXPORT void bumpDEBUG_F(const bump::String& message);

/** Default log functions that only call std::flush on the std::ostream without adding a newline. */

/**
 * Log functions that append a prefix to the output message.
 *
 * It can sometimes be useful to tack on a prefix to your logging messages. These
 * functions are for exactly that. They automatically set the approprate log level
 * for the message and retrieve the stream. First, the prefix is appended to the
 * stream and then the message. Finally, std::endl is appended onto the stream
 * flushing the buffer with a newline character.
 */
BUMP_EXPORT void bumpALWAYS_P(const bump::String& prefix, const bump::String& message);
BUMP_EXPORT void bumpERROR_P(const bump::String& prefix, const bump::String& message);
BUMP_EXPORT void bumpWARNING_P(const bump::String& prefix, const bump::String& message);
BUMP_EXPORT void bumpINFO_P(const bump::String& prefix, const bump::String& message);
BUMP_EXPORT void bumpDEBUG_P(const bump::String& prefix, const bump::String& message);
BUMP_EXPORT void bumpNEWLINE_P(const bump::String& prefix);

/**
 * Log functions that append a prefix to the output message and only flush the buffer.
 *
 * It can sometimes be useful to tack on a prefix to your logging messages. These
 * functions are for exactly that. They automatically set the approprate log level
 * for the message and retrieve the stream. First, the prefix is appended to the
 * stream and then the message. Finally, the stream's buffer is flushed without
 * adding a newline character to the end. This is useful for when you need to
 * generate multiple log messages on a single line.
 */
BUMP_EXPORT void bumpALWAYS_PF(const bump::String& prefix, const bump::String& message);
BUMP_EXPORT void bumpERROR_PF(const bump::String& prefix, const bump::String& message);
BUMP_EXPORT void bumpWARNING_PF(const bump::String& prefix, const bump::String& message);
BUMP_EXPORT void bumpINFO_PF(const bump::String& prefix, const bump::String& message);
BUMP_EXPORT void bumpDEBUG_PF(const bump::String& prefix, const bump::String& message);

#endif	// End of BUMP_LOG_H
