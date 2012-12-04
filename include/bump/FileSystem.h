//
//  FileSystem.h
//  Bump
//
//  Created by Christian Noon on 12/4/12.
//  Copyright (c) 2012 Christian Noon. All rights reserved.
//

#ifndef BUMP_FILE_SYSTEM_H
#define BUMP_FILE_SYSTEM_H

// Bump headers
#include <bump/Export.h>
#include <bump/String.h>

namespace bump {

/**
 * TODO
 */
class BUMP_EXPORT FileSystem
{
public:

	/**
	 * Constructor.
	 */
	FileSystem();

	/**
	 * Destructor.
	 */
	~FileSystem();

	/**
	 * Sets the current working directory path.
	 *
	 * @param the path to set the current working directory to.
	 */
	static void setCurrentPath(const String& path);

	/**
	 * Returns the current working directory path.
	 *
	 * @return the absolute path of the current working directory.
	 */
	static String currentPath();
};

}	// End of bump namespace

#endif	// End of BUMP_FILE_SYSTEM_H
