//
//	Log_impl.h
//	Bump
//
//	Created by Christian Noon on 1/4/13.
//	Copyright (c) 2013 Christian Noon. All rights reserved.
//

#ifndef BUMP_LOG_IMPL_H
#define BUMP_LOG_IMPL_H

/*

namespace bump {

inline std::ostream& fetchLogStream(const Log::LogLevel& level)
{
	if ((Log::instance()->isLogLevelEnabled(level)) && level <= Log::instance()->logLevel())
	{
		return Log::instance()->logStream();
	}

	return Log::instance()->nullLogStream();
}

inline std::ostream& fetchLogStreamWithPrefix(const Log::LogLevel& level, const String& prefix)
{
	if ((Log::instance()->isLogLevelEnabled(level)) && level <= Log::instance()->logLevel())
	{
		return Log::instance()->logStream(prefix);
	}

	return Log::instance()->nullLogStream();
}

}	// End of bump namespace

inline std::ostream& LOG_ALWAYS()
{
	return bump::fetchLogStream(bump::Log::ALWAYS_LVL);
}

inline std::ostream& LOG_ERROR()
{
	return bump::fetchLogStream(bump::Log::ERROR_LVL);
}

inline std::ostream& LOG_WARNING()
{
	return bump::fetchLogStream(bump::Log::WARNING_LVL);
}

inline std::ostream& LOG_INFO()
{
	return bump::fetchLogStream(bump::Log::INFO_LVL);
}

inline std::ostream& LOG_DEBUG()
{
	return bump::fetchLogStream(bump::Log::DEBUG_LVL);
}

inline std::ostream& LOG_ALWAYS_P(const bump::String& prefix)
{
	return bump::fetchLogStreamWithPrefix(bump::Log::ALWAYS_LVL, prefix);
}

inline std::ostream& LOG_ERROR_P(const bump::String& prefix)
{
	return bump::fetchLogStreamWithPrefix(bump::Log::ERROR_LVL, prefix);
}

inline std::ostream& LOG_WARNING_P(const bump::String& prefix)
{
	return bump::fetchLogStreamWithPrefix(bump::Log::WARNING_LVL, prefix);
}

inline std::ostream& LOG_INFO_P(const bump::String& prefix)
{
	return bump::fetchLogStreamWithPrefix(bump::Log::INFO_LVL, prefix);
}

inline std::ostream& LOG_DEBUG_P(const bump::String& prefix)
{
	return bump::fetchLogStreamWithPrefix(bump::Log::DEBUG_LVL, prefix);
}

*/

#endif	// End of BUMP_LOG_IMPL_H
