//
//	NotificationCenter_impl.h
//	Bump
//
//	Created by Christian Noon on 1/4/13.
//	Copyright (c) 2013 Christian Noon. All rights reserved.
//

#ifndef BUMP_NOTIFICATION_CENTER_IMPL_H
#define BUMP_NOTIFICATION_CENTER_IMPL_H

namespace bump {

//====================================================================================
//                                    KeyObserver
//====================================================================================

template <class T>
inline KeyObserver<T>::KeyObserver(T* observer, void (T::*functionPointer)(), const String& notificationName)
{
	_observer = observer;
	_functionPointer = boost::bind(functionPointer, observer);
	_notificationName = notificationName;
	_observerType = KEY_OBSERVER;
}

template <class T>
inline KeyObserver<T>::~KeyObserver()
{
	;
}

template <class T>
inline void KeyObserver<T>::notify()
{
	_functionPointer();
}

template <class T>
inline void KeyObserver<T>::notify(const boost::any& /*object*/)
{
	// No-op
}

//====================================================================================
//                                   ObjectObserver
//====================================================================================

template <class T1, class T2>
inline ObjectObserver<T1, T2>::ObjectObserver(T1* observer, void (T1::*functionPointer)(T2), const String& notificationName)
{
	_observer = observer;
	_functionPointerWithObject = boost::bind(functionPointer, observer, _1);
	_functionPointerWithPointer = NULL;
	_notificationName = notificationName;
	_observerType = OBJECT_OBSERVER;
}

template <class T1, class T2>
inline ObjectObserver<T1, T2>::ObjectObserver(T1* observer, void (T1::*functionPointer)(const T2&), const String& notificationName)
{
	_observer = observer;
	_functionPointerWithObject = boost::bind(functionPointer, observer, _1);
	_functionPointerWithPointer = NULL;
	_notificationName = notificationName;
	_observerType = OBJECT_OBSERVER;
}

template <class T1, class T2>
inline ObjectObserver<T1, T2>::ObjectObserver(T1* observer, void (T1::*functionPointer)(T2*), const String& notificationName)
{
	_observer = observer;
	_functionPointerWithObject = NULL;
	_functionPointerWithPointer = boost::bind(functionPointer, observer, _1);
	_notificationName = notificationName;
	_observerType = OBJECT_OBSERVER;
}

template <class T1, class T2>
inline ObjectObserver<T1, T2>::ObjectObserver(T1* observer, void (T1::*functionPointer)(const T2*), const String& notificationName)
{
	_observer = observer;
	_functionPointerWithObject = NULL;
	_functionPointerWithPointer = boost::bind(functionPointer, observer, _1);
	_notificationName = notificationName;
	_observerType = OBJECT_OBSERVER;
}

template <class T1, class T2>
inline ObjectObserver<T1, T2>::~ObjectObserver()
{
	;
}

template <class T1, class T2>
inline void ObjectObserver<T1, T2>::notify()
{
	// No-op
}

template <class T1, class T2>
inline void ObjectObserver<T1, T2>::notify(const boost::any& object)
{
	try
	{
		if (_functionPointerWithObject)
		{
			const T2& castObject = boost::any_cast<T2>(object);
			_functionPointerWithObject(castObject);
		}
		else // _functionPointerWithPointer
		{
			T2* castObject = boost::any_cast<T2*>(object);
			_functionPointerWithPointer(castObject);
		}
	}
	catch (const boost::bad_any_cast& /*e*/)
	{
		String msg = String("Notification object for \"%1\" has invalid type for bound callback.").arg(_notificationName);
		throw NotificationError(msg, BUMP_LOCATION);
	}
}

}	// End of bump namespace

#endif	// End of BUMP_NOTIFICATION_CENTER_IMPL_H
