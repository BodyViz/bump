//
//	NotificationError.h
//	Bump
//
//	Created by Christian Noon on 12/10/12.
//	Copyright (c) 2012 Christian Noon. All rights reserved.
//

#ifndef BUMP_NOTIFICATION_ERROR_H
#define BUMP_NOTIFICATION_ERROR_H

// Bump headers
#include <bump/Exception.h>

namespace bump {

/**
 * A public runtime error class which is used when the notification center is used incorrectly. This can
 * either involve shutting down the notification center without properly removing all the observers as well
 * as incorrectly posting notifications.
 */
class BUMP_EXPORT NotificationError : public RuntimeError
{
public:

	/**
	 * Constructor.
	 *
	 * @param description The description of the exception.
	 * @param location The file path, line number and function name of where the exception was thrown.
	 */
	NotificationError(const String& description, const String& location) throw();

	/**
	 * Destructor.
	 */
	~NotificationError() throw();
};

}	// End of bump namespace

#endif	// End of BUMP_NOTIFICATION_ERROR_H
