//
//	NotificationCenter.cpp
//	Bump
//
//	Created by Christian Noon on 12/3/12.
//	Copyright (c) 2012 Christian Noon. All rights reserved.
//

// Boost headers
#include <boost/foreach.hpp>

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
	;
}

NotificationCenter* NotificationCenter::instance()
{
	boost::mutex::scoped_lock lock(gNotificationCenterSingletonMutex);
	static NotificationCenter notification_center;
	return &notification_center;
}

void NotificationCenter::addObserver(Observer* observer)
{
	boost::mutex::scoped_lock lock(_mutex);

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
	boost::mutex::scoped_lock lock(_mutex);

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
	boost::mutex::scoped_lock lock(_mutex);

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
	boost::mutex::scoped_lock lock(_mutex);

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
	boost::mutex::scoped_lock lock(_mutex);

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

void ADD_OBSERVER(bump::Observer* observer)
{
	bump::NotificationCenter::instance()->addObserver(observer);
}

void REMOVE_OBSERVER(void* observer)
{
	bump::NotificationCenter::instance()->removeObserver(observer);
}

unsigned int POST_NOTIFICATION(const bump::String& notificationName)
{
	return bump::NotificationCenter::instance()->postNotification(notificationName);
}

unsigned int POST_NOTIFICATION_WITH_OBJECT(const bump::String& notificationName, const boost::any& object)
{
	return bump::NotificationCenter::instance()->postNotificationWithObject(notificationName, object);
}
