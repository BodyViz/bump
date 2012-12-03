//
//	NotificationCenter.h
//	Bump
//
//	Created by Christian Noon on 12/3/12.
//	Copyright (c) 2012 Christian Noon. All rights reserved.
//

#ifndef BUMP_NOTIFICATION_CENTER_H
#define BUMP_NOTIFICATION_CENTER_H

// C++ headers
#include <iostream>
#include <map>
#include <vector>

// Boost headers
#include <boost/any.hpp>
#include <boost/function.hpp>

// Bump headers
#include <bump/Exception.h>
#include <bump/String.h>

namespace bump {

/**
 * Functor abstract base class.
 */
class AbstractFunctor
{
public:

	/**
	 * Destructor.
	 */
	virtual ~AbstractFunctor() {}

	/**
	 * Notification callback for the functor with no object.
	 *
	 * @param notificationName the name of the notification being sent.
	 */
	virtual void notify(const String& notificationName) = 0;

	/**
	 * Notification callback for the functor with an object.
	 *
	 * @param object the object to send to the notification's observers.
	 * @param notificationName the name of the notification being sent.
	 */
	virtual void notify(const boost::any& object, const String& notificationName) = 0;

	/**
	 * Checks whether the given object is equal to the functor's internal object pointer.
	 *
	 * @param object the object to check whether it is equal to the functor's internal object pointer.
	 * @return true if the given object equals the functor's internal object pointer, otherwise returns false.
	 */
	virtual bool isEqual(void* object) = 0;

protected:

	/**
	 * Constructor.
	 */
	AbstractFunctor() {}
};

/**
 * The notification functor class stores the observer object along with its function pointer to be
 * executed when a matching notification is posted. The notification functor class does not support
 * notifications with objects.
 */
template <class T>
class NotificationFunctor : public AbstractFunctor
{
public:

	/**
	 * Constructor.
	 *
	 * @param objectPointer the observer instance associated with the function pointer.
	 * @param functionPointer the function to call on the observer instance.
	 */
	NotificationFunctor(T* objectPointer, boost::function<void (T*)> functionPointer) :
		_objectPointer(objectPointer),
		_functionPointer(functionPointer)
	{
		;
	}

	/**
	 * Notification callback for the functor with no object.
	 *
	 * @param notificationName the name of the notification being sent.
	 */
	void notify(const String& notificationName)
	{
		_functionPointer(_objectPointer);
	}

	/**
	 * Notification callback for the functor with an object.
	 *
	 * @param object the object to send to the notification's observers.
	 * @param notificationName the name of the notification being sent.
	 */
	void notify(const boost::any& /*object*/, const String& notificationName)
	{
		String msg = String("Notification callback for \"%1\" was sent notification object "
							"but should not have been.").arg(notificationName);
		throw NotificationError(msg, BUMP_LOCATION);
	}

	/**
	 * Checks whether the given object is equal to the functor's internal object pointer.
	 *
	 * @param object the object to check whether it is equal to the functor's internal object pointer.
	 * @return true if the given object equals the functor's internal object pointer, otherwise returns false.
	 */
	virtual bool isEqual(void* object)
	{
		return object == _objectPointer;
	}

protected:

	/** Instance member variables. */
	T* _objectPointer;
	boost::function<void (T*)> _functionPointer;
};

/**
 * The notification with object functor class stores the observer object along with its function pointer to be
 * executed when a matching notification is posted. This functor allows notifications with objects to be
 * passed through the notification center.
 */
template <class T1, class T2>
class NotificationWithObjectFunctor : public AbstractFunctor
{
public:

	/**
	 * Constructor.
	 */
	NotificationWithObjectFunctor(T1* objectPointer, boost::function<void (T1*, T2)> functionPointer) :
		_objectPointer(objectPointer),
		_functionPointer(functionPointer)
	{
		;
	}

	/**
	 * Notification callback for the functor with no object.
	 *
	 * @param notificationName the name of the notification being sent.
	 */
	void notify(const String& notificationName)
	{
		String msg = String("Notification callback for \"%1\" takes an object but was not sent one.").arg(notificationName);
		throw NotificationError(msg, BUMP_LOCATION);
	}

	/**
	 * Notification callback for the functor with an object.
	 *
	 * @param object the object to send to the notification's observers.
	 * @param notificationName the name of the notification being sent.
	 */
	void notify(const boost::any& object, const String& notificationName)
	{
		try
		{
			const T2& castObject = boost::any_cast<T2>(object);
			_functionPointer(_objectPointer, castObject);
		}
		catch (const boost::bad_any_cast& /*e*/)
		{
			String msg = String("Notification object for \"%1\" has invalid type for bound callback.").arg(notificationName);
			throw NotificationError(msg, BUMP_LOCATION);
		}
	}

	/**
	 * Checks whether the given object is equal to the functor's internal object pointer.
	 *
	 * @param object the object to check whether it is equal to the functor's internal object pointer.
	 * @return true if the given object equals the functor's internal object pointer, otherwise returns false.
	 */
	virtual bool isEqual(void* object)
	{
		return object == _objectPointer;
	}

protected:

	/** Instance member variables. */
	T1* _objectPointer;
	boost::function<void (T1*, T2)> _functionPointer;
};


/**
 * The notification with pointer functor class stores the observer object along with its function pointer to be
 * executed when a matching notification is posted. This functor allows notifications with pointers to be
 * passed through the notification center.
 */
template <class T1, class T2>
class NotificationWithPointerFunctor : public AbstractFunctor
{
public:

	/**
	 * Constructor.
	 */
	NotificationWithPointerFunctor(T1* objectPointer, boost::function<void (T1*, T2*)> functionPointer) :
		_objectPointer(objectPointer),
		_functionPointer(functionPointer)
	{
		;
	}

	/**
	 * Notification callback for the functor with no object.
	 *
	 * @param notificationName the name of the notification being sent.
	 */
	void notify(const String& notificationName)
	{
		String msg = String("Notification object for \"%1\" takes an object but was not sent one.").arg(notificationName);
		throw NotificationError(msg, BUMP_LOCATION);
	}

	/**
	 * Notification callback for the functor with a pointer.
	 *
	 * @param object the object to send to the notification's observers.
	 * @param notificationName the name of the notification being sent.
	 */
	void notify(const boost::any& object, const String& notificationName)
	{
		try
		{
			T2* castObject = boost::any_cast<T2*>(object);
			_functionPointer(_objectPointer, castObject);
		}
		catch (const boost::bad_any_cast& /*e*/)
		{
			String msg = String("Notification object for \"%1\" has invalid type for bound callback.").arg(notificationName);
			throw NotificationError(msg, BUMP_LOCATION);
		}
	}

	/**
	 * Checks whether the given object is equal to the functor's internal object pointer.
	 *
	 * @param object the object to check whether it is equal to the functor's internal object pointer.
	 * @return true if the given object equals the functor's internal object pointer, otherwise returns false.
	 */
	virtual bool isEqual(void* object)
	{
		return object == _objectPointer;
	}

protected:

	/** Instance member variables. */
	T1* _objectPointer;
	boost::function<void (T1*, T2*)> _functionPointer;
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
 *		 - boost::function<void (ObjectType1*) Event*> eventCompletedCallback(&ObjectType1::eventCompleted);
 *		 - bump::NotificationCenter::instance()->addObserver(this, eventCompletedCallback, "EventCompleted");
 *
 * 2) Make sure to remove the observer from the NotificationCenter in its destructor
 *		 - bump::NotificationCenter::instance()->removeObserver(this);
 *
 * 3) When the event completes, post a notification that the event completed with a matching name
 *		 - bump::NotificationCenter::instance()->postNotificationWithObject("EventCompleted", event);
 *
 * And that's all there is to it! For more information, please see the bumpNotificationCenter example.
 */
class NotificationCenter
{
public:

	/**
	 * Creates a singleton instance.
	 *
	 * @return the singleton NotificationCenter instance.
	 */
	static NotificationCenter* instance() { static NotificationCenter nc; return &nc; }

	/**
	 * Registers the observer's function pointer without an object with the notification name.
	 *
	 * @param observer the observer instance being registered to receive notifications.
	 * @param function the function pointer to be called on observer.
	 * @param notificationName the identifying string used to trigger the function pointer on observer.
	 */
	template<typename T>
	void addObserver(T* observer, boost::function<void (T*)> function, const String& notificationName)
	{
		NotificationFunctor<T>* functor = new NotificationFunctor<T>(observer, function);
		_observers.insert(std::pair<AbstractFunctor*, String>(functor, notificationName));
	}

	/**
	 * Registers the observer's function pointer with an object with the notification name.
	 *
	 * @param observer the observer instance being registered to receive notifications.
	 * @param function the function pointer to be called on observer.
	 * @param notificationName the identifying string used to trigger the function pointer on observer.
	 */
	template<typename T1, typename T2>
	void addObserver(T1* observer, boost::function<void (T1*, T2)> function, const String& notificationName)
	{
		NotificationWithObjectFunctor<T1, T2>* functor = new NotificationWithObjectFunctor<T1, T2>(observer, function);
		_observers.insert(std::pair<AbstractFunctor*, String>(functor, notificationName));
	}

	/**
	 * Registers the observer's function pointer with a pointer object with the notification name.
	 *
	 * @param observer the observer instance being registered to receive notifications.
	 * @param function the function pointer to be called on observer.
	 * @param notificationName the identifying string used to trigger the function pointer on observer.
	 */
	template<typename T1, typename T2>
	void addObserver(T1* observer, boost::function<void (T1*, T2*)> function, const String& notificationName)
	{
		NotificationWithPointerFunctor<T1, T2>* functor = new NotificationWithPointerFunctor<T1, T2>(observer, function);
		_observers.insert(std::pair<AbstractFunctor*, String>(functor, notificationName));
	}

	/**
	 * Calls all observer's function pointers that have registered for the posted notification.
	 *
	 * @param notificationName the notification to post to registered observers.
	 */
	void postNotification(const String& notificationName);

	/**
	 * Calls all observer's function pointers that have registered for the posted notification
	 * with the given object.
	 *
	 * @param notificationName the notification to post to registered observers.
	 * @param object the object to send to the registered observers.
	 */
	void postNotificationWithObject(const String& notificationName, boost::any object);

	/**
	 * Removes the observer from the notification center.
	 *
	 * @param observer the observer instance to remove from the notification center.
	 */
	void removeObserver(void* observer);

protected:

	/**
	 * Constructor.
	 */
	NotificationCenter();

	/**
	 * Destructor.
	 */
	~NotificationCenter();

	/** Instance member variables. */
	std::multimap<AbstractFunctor*, String> _observers;
};

/** Convenience macros for posting notifications. */
#define ADD_OBSERVER(o, c, k) bump::NotificationCenter::instance()->addObserver(o, c, k)
#define NOTIFICATION_CENTER() bump::NotificationCenter::instance()
#define REMOVE_OBSERVER(o) bump::NotificationCenter::instance()->removeObserver(o)
#define POST_NOTIFICATION(k) bump::NotificationCenter::instance()->postNotification(k)
#define POST_NOTIFICATION_WITH_OBJECT(k, o) bump::NotificationCenter::instance()->postNotificationWithObject(k, o)

}	// End of bump namespace

#endif	// End of BUMP_NOTIFICATION_CENTER_H
