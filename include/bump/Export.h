//
//  Export.h
//  Bump
//
//  Created by Christian Noon on 11/7/12.
//  Copyright (c) 2012 Christian Noon. All rights reserved.
//

#ifndef BUMP_EXPORT_H
#define BUMP_EXPORT_H

// Disable VisualStudio warnings
#if defined(_MSC_VER) && defined(BUMP_DISABLE_MSVC_WARNINGS)
    #pragma warning(disable:4244)
    #pragma warning(disable:4251)
    #pragma warning(disable:4275)
    #pragma warning(disable:4512)
    #pragma warning(disable:4267)
    #pragma warning(disable:4702)
    #pragma warning(disable:4511)
#endif

// Define the dllexport and dllimports for Windows
#if defined(_MSC_VER) || defined(__CYGWIN__) || defined(__MINGW32__) || defined( __BCPLUSPLUS__) || defined( __MWERKS__)
    #if defined(BUMP_LIBRARY_STATIC)
        #define BUMP_EXPORT
    #elif defined(BUMP_LIBRARY)
        #define BUMP_EXPORT __declspec(dllexport)
    #else
        #define BUMP_EXPORT __declspec(dllimport)
    #endif
#else
    #define BUMP_EXPORT
#endif

// Set up define for whether member templates are supported by VisualStudio compilers
#ifdef _MSC_VER
    #if (_MSC_VER >= 1300)
        #define __STL_MEMBER_TEMPLATES
    #endif
#endif

// Define NULL pointer value
#ifndef NULL
    #ifdef  __cplusplus
        #define NULL 0
    #else
        #define NULL ((void *)0)
    #endif
#endif

#endif  // End of BUMP_EXPORT_H
