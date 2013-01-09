//
//	Log.cpp
//	Bump
//
//	Created by Christian Noon on 12/3/12.
//	Copyright (c) 2012 Christian Noon. All rights reserved.
//

// C++ headers
#include <fstream>

// Boost headers
#include <boost/date_time/posix_time/posix_time.hpp>

// Bump headers
#include <bump/Environment.h>
#include <bump/Log.h>

namespace bump {

Log::Log() :
	_isEnabled(true),
	_logLevel(WARNING_LVL),
	_isDateTimeFormatEnabled(false),
	_timestampFormat(DATE_TIME_WITH_AM_PM_TIMESTAMP),
	_logStream(&std::cout),
	_nullLogStream(NULL)
{
	// Attempt to disable the entire log system based on the "BUMP_LOG_ENABLED" environment variable
	String logEnabled = bump::Environment::environmentVariable(BUMP_LOG_ENABLED);
	logEnabled.toLowerCase();
	if (logEnabled == "no" || logEnabled == "false" || logEnabled == "nope" || logEnabled == "disable")
	{
		_isEnabled = false;
		std::cout << "[bump] Setting LOG_ENABLED to NO" << std::endl;
		return;
	}

	// Attempt to set the log level based on the "BUMP_LOG_LEVEL" environment variable
	String logLevel = bump::Environment::environmentVariable(BUMP_LOG_LEVEL);
	if (logLevel == "ALWAYS_LVL")
	{
		_logLevel = ALWAYS_LVL;
		std::cout << "[bump] Setting BUMP_LOG_LEVEL to ALWAYS" << std::endl;
	}
	else if (logLevel == "ERROR_LVL")
	{
		_logLevel = ERROR_LVL;
		std::cout << "[bump] Setting BUMP_LOG_LEVEL to ERROR" << std::endl;
	}
	else if (logLevel == "WARNING_LVL")
	{
		_logLevel = WARNING_LVL;
		std::cout << "[bump] Setting BUMP_LOG_LEVEL to WARNING" << std::endl;
	}
	else if (logLevel == "INFO_LVL")
	{
		_logLevel = INFO_LVL;
		std::cout << "[bump] Setting BUMP_LOG_LEVEL to INFO" << std::endl;
	}
	else if (logLevel == "DEBUG_LVL")
	{
		_logLevel = DEBUG_LVL;
		std::cout << "[bump] Setting BUMP_LOG_LEVEL to DEBUG" << std::endl;
	}
	else if (!logLevel.empty())
	{
		std::cout << "[bump] WARNING: Your BUMP_LOG_LEVEL environment variable: [" << logLevel
			<< "] does not match any of the possible options: [ ALWAYS_LVL | ERROR_LVL | WARNING_LVL "
			<< "| INFO_LVL | DEBUG_LVL ]" << std::endl;
	}
	else
	{
		// DO NOTHING
	}

	// Attempt to set the log file based on the "BUMP_LOG_FILE" environment variable
	String logFile = bump::Environment::environmentVariable(BUMP_LOG_FILE);
	if (!logFile.empty())
	{
		if (logFile == "stderr")
		{
			_logStream = &std::cerr;
		}
		else if (logFile != "stdout")
		{
			bool success = setLogFile(logFile);
			if (success)
			{
				std::cout << "[bump] Setting BUMP_LOG_FILE to " << logFile << std::endl;
			}
			else
			{
				std::cout << "[bump] WARNING: Your BUMP_LOG_FILE environment variable: ["
					<< logFile << "] could not be created or opened" << std::endl;
			}
		}
	}
}

Log::~Log()
{
	;
}

void Log::setIsLogEnabled(bool enabled)
{
	boost::mutex::scoped_lock lock(_mutex);
	_isEnabled = enabled;
}

bool Log::isLogEnabled()
{
	boost::mutex::scoped_lock lock(_mutex);
	return _isEnabled;
}

bool Log::isLogLevelEnabled(LogLevel logLevel)
{
	boost::mutex::scoped_lock lock(_mutex);

	// Returning false if disabled
	if (!_isEnabled)
	{
		return false;
	}

	return logLevel <= _logLevel;
}

void Log::setLogLevel(LogLevel logLevel)
{
	std::cout << "bump::String Log Instance: " << instance() << std::endl;

	boost::mutex::scoped_lock lock(_mutex);
	_logLevel = logLevel;
}

Log::LogLevel Log::logLevel()
{
	boost::mutex::scoped_lock lock(_mutex);
	return _logLevel;
}

void Log::setIsTimestampingEnabled(bool enabled)
{
	boost::mutex::scoped_lock lock(_mutex);
	_isDateTimeFormatEnabled = enabled;
}

bool Log::isTimestampingEnabled()
{
	boost::mutex::scoped_lock lock(_mutex);
	return _isDateTimeFormatEnabled;
}

void Log::setTimestampFormat(const TimestampFormat& format)
{
	boost::mutex::scoped_lock lock(_mutex);
	_timestampFormat = format;
}

Log::TimestampFormat Log::timestampFormat()
{
	boost::mutex::scoped_lock lock(_mutex);
	return _timestampFormat;
}

bool Log::setLogFile(const String& filepath)
{
	boost::mutex::scoped_lock lock(_mutex);

	// First try to open the file
	std::ofstream* logFile = new std::ofstream(filepath.c_str());
	if ( !(*logFile) )
	{
		delete logFile;
		logFile = NULL;
		return false;
	}

	// We successfully opened the file for writing, so switch log streams
	_logStream = logFile;
	return true;
}

void Log::setLogStream(std::ostream& stream)
{
	boost::mutex::scoped_lock lock(_mutex);
	_logStream = &stream;
}

std::ostream& Log::logStream(const String& prefix)
{
	boost::mutex::scoped_lock lock(_mutex);

	// The generic stream to "buffer" output to for the output handler. This allows us to
	// avoid pointer dereferences until necessary.
	std::ostream& ostream = *_logStream;

	// Append the date time if necessary
	if (_isDateTimeFormatEnabled)
	{
		ostream << convertTimeToString() << " ";
	}

	// Append the prefix if necessary
	if (!prefix.empty())
	{
		ostream << prefix;
	}

	return *_logStream;
}

String Log::convertTimeToString()
{
	// Get the time using boost
	boost::posix_time::ptime now = boost::posix_time::second_clock::local_time();

	// Build strings for each time value from the boost ptime value
	String year = static_cast<long>(now.date().year());
	String month = static_cast<long>(now.date().month());
	String day = static_cast<long>(now.date().day());
	String hours = static_cast<long>(now.time_of_day().hours());
	String minutes = static_cast<long>(now.time_of_day().minutes());
	String seconds = static_cast<long>(now.time_of_day().seconds());

	// Figure out if we're AM or PM
	String am_pm = hours.toInt() < 13 ? "AM" : "PM";

	// Correct the hours if larger than 12
	if (hours.toInt() > 12)
	{
		hours = hours.toInt() - 12;
	}

	// Pad the month, day, hours, minutes and seconds
	month.padWithString("0", 2);
	day.padWithString("0", 2);
	hours.padWithString("0", 2);
	minutes.padWithString("0", 2);
	seconds.padWithString("0", 2);

	// Now create a string representation of the timestamp based on the timestamp format
	if (_timestampFormat == DATE_TIME_TIMESTAMP)
	{
		return String("%1-%2-%3 %4:%5:%6:").arg(year, month, day, hours, minutes, seconds);
	}
	else if (_timestampFormat == DATE_TIME_WITH_AM_PM_TIMESTAMP)
	{
		return String("%1-%2-%3 %4:%5:%6 %7:").arg(year, month, day, hours, minutes, seconds, am_pm);
	}
	else if (_timestampFormat == DATE_TIME_TIMESTAMP)
	{
		return String("%1:%2:%3:").arg(hours, minutes, seconds);
	}
	else // _timestampFormat == TIME_WITH_AM_PM_TIMESTAMP
	{
		return String("%1:%2:%3 %4:").arg(hours, minutes, seconds, am_pm);
	}
}

std::ostream& Log::nullLogStream()
{
	return _nullLogStream;
}

std::ostream& fetchLogStream(const Log::LogLevel& level)
{
	if ((Log::instance()->isLogLevelEnabled(level)) && level <= Log::instance()->logLevel())
	{
		return Log::instance()->logStream();
	}
	
	return Log::instance()->nullLogStream();
}

std::ostream& fetchLogStreamWithPrefix(const Log::LogLevel& level, const String& prefix)
{
	if ((Log::instance()->isLogLevelEnabled(level)) && level <= Log::instance()->logLevel())
	{
		return Log::instance()->logStream(prefix);
	}
	
	return Log::instance()->nullLogStream();
}

}	// End of bump namespace

std::ostream& LOG_ALWAYS()
{
	return bump::fetchLogStream(bump::Log::ALWAYS_LVL);
}

std::ostream& LOG_ERROR()
{
	return bump::fetchLogStream(bump::Log::ERROR_LVL);
}

std::ostream& LOG_WARNING()
{
	return bump::fetchLogStream(bump::Log::WARNING_LVL);
}

std::ostream& LOG_INFO()
{
	return bump::fetchLogStream(bump::Log::INFO_LVL);
}

std::ostream& LOG_DEBUG()
{
	return bump::fetchLogStream(bump::Log::DEBUG_LVL);
}

std::ostream& LOG_ALWAYS_P(const bump::String& prefix)
{
	return bump::fetchLogStreamWithPrefix(bump::Log::ALWAYS_LVL, prefix);
}

std::ostream& LOG_ERROR_P(const bump::String& prefix)
{
	return bump::fetchLogStreamWithPrefix(bump::Log::ERROR_LVL, prefix);
}

std::ostream& LOG_WARNING_P(const bump::String& prefix)
{
	return bump::fetchLogStreamWithPrefix(bump::Log::WARNING_LVL, prefix);
}

std::ostream& LOG_INFO_P(const bump::String& prefix)
{
	return bump::fetchLogStreamWithPrefix(bump::Log::INFO_LVL, prefix);
}

std::ostream& LOG_DEBUG_P(const bump::String& prefix)
{
	return bump::fetchLogStreamWithPrefix(bump::Log::DEBUG_LVL, prefix);
}
