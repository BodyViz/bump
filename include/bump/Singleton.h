//
//  Singleton.h
//  Bump
//
//  Created by Christian Noon on 1/4/13.
//  Copyright (c) 2013 Christian Noon. All rights reserved.
//

#ifndef BUMP_SINGLETON_H
#define BUMP_SINGLETON_H

// Boost headers
#include <boost/thread/mutex.hpp>

// Bump headers
#include <bump/Export.h>
#include <bump/SingletonError.h>

namespace bump {

/**
 * A thread-safe templated singleton class allowing only a single instance of
 * an object to be created.
 */
template<class T>
class BUMP_EXPORT Singleton
{
public:

	/**
	 * Creates a single thread-safe instance of the templated object.
	 *
	 * @return The single instance of the templated object.
	 */
	static T* instance()
	{
		// Throw an exception if the instance has already been destructed
		if (_isDestructed)
		{
			throw SingletonError("Tried to access the singleton after it was destructed", BUMP_LOCATION);
		}

		// Make sure the _isDestructed check is not removed in the Release build
		(void)_isDestructed;

		// Lock the mutex and create the instance
		boost::mutex::scoped_lock lock(mutex());
		static T instance;

		return &instance;
	}

protected:

	/**
	 * @internal
	 * Constructor.
	 */
	Singleton()
	{
		;
	}

	/**
	 * @internal
	 * Destructor.
	 */
	~Singleton()
	{
		_isDestructed = true;
	}

private:

	/**
	 * @internal
	 * Returns the mutex for locking the instance creation.
	 *
	 * @return The mutex for locking the instance creation.
	 */
	static boost::mutex& mutex()
	{
		static boost::mutex mutex;
		return mutex;
	}

	// Instance member variables
	static bool _isDestructed;	/**< @internal Whether the singleton instance has been destructed. */
};

// Forces the creation of the mutex before main() is called
template<class T>
bool Singleton<T>::_isDestructed = (Singleton<T>::mutex(), false);

}	// End of bump namespace

#endif	// End of BUMP_SINGLETON_H
