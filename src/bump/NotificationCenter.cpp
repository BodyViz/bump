//
//	NotificationCenter.cpp
//	Bump
//
//	Created by Christian Noon on 12/3/12.
//	Copyright (c) 2012 Christian Noon. All rights reserved.
//

// Bump headers
#include <bump/NotificationCenter.h>

using namespace bump;

NotificationCenter::NotificationCenter()
{
	;
}

NotificationCenter::~NotificationCenter()
{
	if (!_observers.empty())
	{
		String msg = String("bump::NotificationCenter has %1 observers that were not properly destructed!").arg(_observers.size());
		throw NotificationError(msg, BUMP_LOCATION);
	}
}

bool NotificationCenter::containsObserver(void* observer)
{
	std::multimap<AbstractFunctor*, String>::iterator iter;
	for (iter = _observers.begin(); iter != _observers.end(); ++iter)
	{
		if (iter->first->isEqual(observer))
		{
			return true;
		}
	}

	return false;
}

unsigned int NotificationCenter::postNotification(const String& notificationName)
{
	unsigned int notification_count = 0;
	std::multimap<AbstractFunctor*, String>::iterator iter = _observers.begin();
	while (iter != _observers.end())
	{
		if (iter->second == notificationName)
		{
			iter->first->notify(notificationName);
			++notification_count;
		}

		++iter;
	}

	return notification_count;
}

unsigned int NotificationCenter::postNotificationWithObject(const String& notificationName, boost::any object)
{
	unsigned int notification_count = 0;
	std::multimap<AbstractFunctor*, String>::iterator iter;
	for (iter = _observers.begin(); iter != _observers.end(); ++iter)
	{
		if (iter->second == notificationName)
		{
			iter->first->notify(object, notificationName);
			++notification_count;
		}
	}

	return notification_count;
}

void NotificationCenter::removeObserver(void* observer)
{
	// First collect all the observers to remove
	std::vector<AbstractFunctor*> matches;
	std::multimap<AbstractFunctor*, String>::iterator iter;
	for (iter = _observers.begin(); iter != _observers.end(); ++iter)
	{
		if (iter->first->isEqual(observer))
		{
			matches.push_back(iter->first);
		}
	}

	// Now remove them
	for (unsigned int i = 0; i < matches.size(); ++i)
	{
		_observers.erase(_observers.find(matches.at(i)));
	}

	// Delete all the match pointers since they aren't reference counted
	for (unsigned int i = 0; i < matches.size(); ++i)
	{
		AbstractFunctor* f = matches.at(i);
		delete f;
		f = NULL;
	}
}