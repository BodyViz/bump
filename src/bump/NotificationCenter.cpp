//
//	NotificationCenter.cpp
//	Bump
//
//	Created by Christian Noon on 12/3/12.
//	Copyright (c) 2012 Christian Noon. All rights reserved.
//

// Boost headers
#include <boost/foreach.hpp>
#include <boost/thread/mutex.hpp>

// Bump headers
#include <bump/NotificationCenter.h>

// Global singleton mutex
boost::mutex gNotificationCenterSingletonMutex;

namespace bump {

//====================================================================================
//                                     Observer
//====================================================================================

Observer::Observer()
{
	;
}

Observer::~Observer()
{
	;
}

void Observer::notify()
{
	;
}

void Observer::notify(const boost::any& object)
{
	;
}

const String& Observer::notificationName()
{
	return _notificationName;
}

const Observer::ObserverType& Observer::observerType()
{
	return _observerType;
}

bool Observer::containsObserver(void* observer)
{
	return observer == _observer;
}

//====================================================================================
//                                    KeyObserver
//====================================================================================

// Implemented in NotificationCenter_impl.h

//====================================================================================
//                                   ObjectObserver
//====================================================================================

// Implemented in NotificationCenter_impl.h

//====================================================================================
//                                 NotificationCenter
//====================================================================================

NotificationCenter::NotificationCenter()
{
	;
}

NotificationCenter::~NotificationCenter()
{
	if (!_keyObservers.empty() || !_objectObservers.empty())
	{
		// Collect all the keys that are registered
		StringList keys;
		BOOST_FOREACH (Observer* observer, _keyObservers)
		{
			String key = String("\"%1\"").arg(observer->notificationName());
			keys.push_back(key);
		}
		BOOST_FOREACH (Observer* observer, _objectObservers)
		{
			String key = String("\"%1\"").arg(observer->notificationName());
			keys.push_back(key);
		}

		// Create a key string
		String key_string = String::join(keys, ", ");

		// Throw a notification error listing the number of observer still registered along with the keys
		unsigned int total_observers = _keyObservers.size() + _objectObservers.size();
		String msg = String("bump::NotificationCenter has %1 observers left with keys: %2").arg(total_observers, key_string);
		throw NotificationError(msg, BUMP_LOCATION);
	}
}

NotificationCenter* NotificationCenter::instance()
{
	boost::mutex::scoped_lock lock(gNotificationCenterSingletonMutex);
	static NotificationCenter notification_center;
	return &notification_center;
}

void NotificationCenter::addObserver(Observer* observer)
{
	boost::mutex::scoped_lock lock(gNotificationCenterSingletonMutex);

	if (observer->observerType() == bump::Observer::KEY_OBSERVER)
	{
		_keyObservers.push_back(observer);
	}
	else
	{
		_objectObservers.push_back(observer);
	}
}

bool NotificationCenter::containsObserver(void* observer)
{
	boost::mutex::scoped_lock lock(gNotificationCenterSingletonMutex);

	// Iterate through the observers
	BOOST_FOREACH (Observer* abs_observer, _keyObservers)
	{
		if (abs_observer->containsObserver(observer))
		{
			return true;
		}
	}

	// Iterate through the object observers
	BOOST_FOREACH (Observer* abs_observer, _objectObservers)
	{
		if (abs_observer->containsObserver(observer))
		{
			return true;
		}
	}

	return false;
}

unsigned int NotificationCenter::postNotification(const String& notificationName)
{
	boost::mutex::scoped_lock lock(gNotificationCenterSingletonMutex);

	unsigned int notification_count = 0;
	BOOST_FOREACH (Observer* abs_observer, _keyObservers)
	{
		if (abs_observer->notificationName() == notificationName)
		{
			abs_observer->notify();
			++notification_count;
		}
	}

	return notification_count;
}

unsigned int NotificationCenter::postNotificationWithObject(const String& notificationName, const boost::any& object)
{
	boost::mutex::scoped_lock lock(gNotificationCenterSingletonMutex);

	unsigned int notification_count = 0;
	BOOST_FOREACH (Observer* abs_observer, _objectObservers)
	{
		if (abs_observer->notificationName() == notificationName)
		{
			abs_observer->notify(object);
			++notification_count;
		}
	}

	return notification_count;
}

void NotificationCenter::removeObserver(void* observer)
{
	boost::mutex::scoped_lock lock(gNotificationCenterSingletonMutex);

	// Remove all the observers that match observer
	std::vector<Observer*> key_observers_to_keep;
	BOOST_FOREACH (Observer* abs_observer, _keyObservers)
	{
		if (abs_observer->containsObserver(observer))
		{
			delete abs_observer;
			abs_observer = NULL;
		}
		else
		{
			key_observers_to_keep.push_back(abs_observer);
		}
	}
	_keyObservers = key_observers_to_keep;

	// Remove all the object observers that match observer
	std::vector<Observer*> object_observers_to_keep;
	BOOST_FOREACH (Observer* abs_observer, _objectObservers)
	{
		if (abs_observer->containsObserver(observer))
		{
			delete abs_observer;
			abs_observer = NULL;
		}
		else
		{
			object_observers_to_keep.push_back(abs_observer);
		}
	}
	_objectObservers = object_observers_to_keep;
}

}	// End of bump namespace
