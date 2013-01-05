//
//	NotificationCenter.h
//	Bump
//
//	Created by Christian Noon on 12/3/12.
//	Copyright (c) 2012 Christian Noon. All rights reserved.
//

#ifndef BUMP_NOTIFICATION_CENTER_H
#define BUMP_NOTIFICATION_CENTER_H

// Boost headers
#include <boost/any.hpp>
#include <boost/bind.hpp>
#include <boost/function.hpp>

// Bump headers
#include <bump/Export.h>
#include <bump/NotificationError.h>
#include <bump/Singleton.h>
#include <bump/String.h>

namespace bump {

/**
 * The base observer class defines the notify() interface as well as contains the
 * observer pointer and the notification name. The notification center uses only
 * Observer objects to handle forwarding all notifications to the appropriate
 * Observer instances.
 */
class BUMP_EXPORT Observer
{
public:

	/**
	 * Defines what type of observer the observer is.
	 */
	enum ObserverType
	{
		KEY_OBSERVER,
		OBJECT_OBSERVER
	};

	/**
	 * Destructor.
	 */
	virtual ~Observer();

	/**
	 * Calls the function pointer on the observer instance.
	 */
	virtual void notify();

	/**
	 * Calls the function pointer on the observer instance with the given object.
	 *
	 * @param object The object to send to the notification's observer.
	 */
	virtual void notify(const boost::any& object);

	/**
	 * Returns the name of the notification that the observer is attached to.
	 *
	 * @return The name of the notification that the observer is attached to.
	 */
	const String& notificationName();

	/**
	 * Returns the type of the observer.
	 *
	 * @return The type of the observer.
	 */
	const ObserverType& observerType();

	/**
	 * Returns whether the given observer is the same as the internal observer.
	 *
	 * @param observer An observer pointer to match against the internal observer pointer.
	 * @return True if the internal observer matches the given observer, false otherwise.
	 */
	bool containsObserver(void* observer);

protected:

	/**
	 * @internal
	 * Constructor.
	 */
	Observer();

	// Instance member variables
	void*						_observer;			/**< @internal The observer instance used to send notifications. */
	bump::String				_notificationName;	/**< @internal The notification name the observer is observing. */
	ObserverType				_observerType;		/**< @internal The type of observer the observer is. */
};

/**
 * The KeyObserver subclass is used to send an observers notifications without objects based strictly
 * on the key. This subclass is used with the POST_NOIFICATION macro.
 */
template <class T>
class BUMP_EXPORT KeyObserver : public Observer
{
public:

	/**
	 * Constructor.
	 *
	 * @param observer The observer instance used to send notifications.
	 * @param functionPointer The function pointer called on the observer instance when notified.
	 * @param notificationName The name of the notification the observer is observing.
	 */
	inline KeyObserver(T* observer, void (T::*functionPointer)(), const String& notificationName);

	/**
	 * Calls the function pointer on the observer instance.
	 */
	inline void notify();

protected:

	/**
	 * @internal
	 * Destructor.
	 */
	inline ~KeyObserver();

	// Instance member variables
	boost::function<void ()> _functionPointer;	/**< @internal The function pointer called on the observer instance when notified. */
};

/**
 * The ObjectObserver subclass is used to send an observers notifications with objects based
 * on the key. This subclass is used with the POST_NOTIFICATION_WITH_OBJECT macro.
 */
template <class T1, class T2>
class BUMP_EXPORT ObjectObserver : public Observer
{
public:

	/**
	 * Constructor.
	 *
	 * @param observer The observer instance used to send notifications.
	 * @param functionPointer The function pointer called on the observer instance when notified.
	 * @param notificationName The name of the notification the observer is observing.
	 */
	inline ObjectObserver(T1* observer, void (T1::*functionPointer)(T2), const String& notificationName);

	/**
	 * Constructor.
	 *
	 * @param observer The observer instance used to send notifications.
	 * @param functionPointer The function pointer called on the observer instance when notified.
	 * @param notificationName The name of the notification the observer is observing.
	 */
	inline ObjectObserver(T1* observer, void (T1::*functionPointer)(const T2&), const String& notificationName);

	/**
	 * Constructor.
	 *
	 * @param observer The observer instance used to send notifications.
	 * @param functionPointer The function pointer called on the observer instance when notified.
	 * @param notificationName The name of the notification the observer is observing.
	 */
	inline ObjectObserver(T1* observer, void (T1::*functionPointer)(T2*), const String& notificationName);

	/**
	 * Constructor.
	 *
	 * @param observer The observer instance used to send notifications.
	 * @param functionPointer The function pointer called on the observer instance when notified.
	 * @param notificationName The name of the notification the observer is observing.
	 */
	inline ObjectObserver(T1* observer, void (T1::*functionPointer)(const T2*), const String& notificationName);

	/**
	 * Calls the function pointer on the observer instance with the given object.
	 *
	 * @throw bump::NotificationError When the object has an invalid type for the bound callback.
	 *
	 * @param object The object to send to the notification's observer.
	 */
	inline void notify(const boost::any& object);

protected:

	/**
	 * @internal
	 * Destructor.
	 */
	inline ~ObjectObserver();

	// Instance member variables
	boost::function<void (T2)>	_functionPointerWithObject;		/**< @internal The function pointer that has an object signature. */
	boost::function<void (T2*)>	_functionPointerWithPointer;	/**< @internal The function pointer that has a pointer signature. */
};

/**
 * Central messaging system for passing abstract messages with objects through Bump.
 *
 * The NotificationCenter is a notification system that allows you to send notifications abstractly
 * when events occur in your application. For example, if you're work on an event system, and your event
 * completes, sometimes it would be nice to notify multiple parts of your application that that event
 * was completed. The bump::NotificationCenter makes this type of notification very easy to do. In order
 * to create such a notification, follow these steps:
 *
 * 1) Register all objects as observers with the NotificationCenter
 *
 * @code
 *   bump::AbstractObserver* observer = new bump::ObjectObserver<ObjectType, Event*>(this, &ObjectType::eventCompleted, "EventCompleted");
 *   bump::NotificationCenter::instance()->addObserver(observer);
 *   ADD_OBSERVER(observer); // convenience macro
 * @endcode
 *
 * 2) Make sure to remove the observer from the NotificationCenter in its destructor
 *
 * @code
 *   bump::NotificationCenter::instance()->removeObserver(this);
 *   REMOVE_OBSERVER(observer); // convenience macro
 * @endcode
 *
 * 3) When the event completes, post a notification that the event completed with a matching name
 *
 * @code
 *   bump::NotificationCenter::instance()->postNotificationWithObject("EventCompleted", event);
 *   POST_NOTIFICATION_WITH_OBJECT("EventCompleted", event); // convenience macro
 * @endcode
 *
 * And that's all there is to it! For more information, please see the bumpNotificationCenter example.
 */
class BUMP_EXPORT NotificationCenter : public Singleton<NotificationCenter>
{
public:

	// Declare the singleton to be a friend class to call the constructor/destructors
	friend class Singleton<NotificationCenter>;

	/**
	 * Adds the observer to the list of observers to send notifications.
	 *
	 * @param observer The observer to add to the list of observers to send notifications.
	 */
	void addObserver(Observer* observer);

	/**
	 * Determines whether the notification center contains the observer.
	 *
	 * @param observer The observer pointer to check against the list of internal observers stored.
	 * @return True if the observer is registered with the notification center, false otherwise.
	 */
	bool containsObserver(void* observer);

	/**
	 * Calls all observer's function pointers that have registered for the posted notification.
	 *
	 * @param notificationName The notification to post to registered observers.
	 * @return The number of observers that received the notification.
	 */
	unsigned int postNotification(const String& notificationName);

	/**
	 * Calls all observer's function pointers that have registered for the posted notification
	 * with the given object.
	 *
	 * @param notificationName The notification to post to registered observers.
	 * @param object The object to send to the registered observers.
	 * @return The number of observers that received the notification.
	 */
	unsigned int postNotificationWithObject(const String& notificationName, const boost::any& object);

	/**
	 * Removes the observer from the notification center.
	 *
	 * @param observer The observer instance to remove from the notification center.
	 */
	void removeObserver(void* observer);

protected:

	/**
	 * @internal
	 * Constructor.
	 */
	NotificationCenter();

	/**
	 * @internal
	 * Destructor.
	 */
	~NotificationCenter();

	// Instance member variables
	std::vector<Observer*> _keyObservers;		/**< @internal The list of key observers registered with the NotificationCenter. */
	std::vector<Observer*> _objectObservers;	/**< @internal The list of object observers registered with the NotificationCenter. */
};

}	// End of bump namespace

/**
 * Convenience function for accessing the NotificationCenter singleton's addObserver() method.
 *
 * @param observer The object or key observer to add to the NotificationCenter.
 */
inline void ADD_OBSERVER(bump::Observer* observer);

/**
 * Convenience method for accessing the NotificationCenter singleton's removeObserver() method.
 *
 * @param observer The observer instance to remove from the NotificationCenter.
 */
inline void REMOVE_OBSERVER(void* observer);

/**
 * Convenience method for accessing the NotificationCenter singleton's postNotification() method.
 *
 * @param notificationName The notification to post to registered observers.
 * @return The number of observers that received the notification.
 */
inline unsigned int POST_NOTIFICATION(const bump::String& notificationName);

/**
 * Convenience method for accessing the NotificationCenter singleton's postNotificationWithObject() method.
 *
 * @param notificationName The notification to post to registered observers.
 * @param object The object to send to the registered observers.
 * @return The number of observers that received the notification.
 */
inline unsigned int POST_NOTIFICATION_WITH_OBJECT(const bump::String& notificationName, const boost::any& object);

// Pull in the KeyObserver and ObjectObserver template implementations
#include <bump/NotificationCenter_impl.h>

#endif	// End of BUMP_NOTIFICATION_CENTER_H
