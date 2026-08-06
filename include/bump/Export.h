//
//	Export.h
//	Bump
//
//	Created by Christian Noon on 11/7/12.
//	Copyright (c) 2012 Christian Noon. All rights reserved.
//

#pragma once

#include <boost/config.hpp>

// Define the symbol import/export
#if defined(Bump_LIBRARY_STATIC)
#define BUMP_EXPORT
#elif defined(Bump_LIBRARY)
#define BUMP_EXPORT BOOST_SYMBOL_EXPORT
#else
#define BUMP_EXPORT BOOST_SYMBOL_IMPORT
#endif
