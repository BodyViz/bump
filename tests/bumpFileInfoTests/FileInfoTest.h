//
//	FileInfoTest.h
//	Bump
//
//	Created by Christian Noon on 12/12/12.
//	Copyright (c) 2012 Christian Noon. All rights reserved.
//

// Bump headers
#include <bump/FileSystem.h>
#include <bump/String.h>

// bumpTest headers
#include "../bumpTest/BaseTest.h"

namespace bumpTest {

/**
 * This is our main file info testing class. The SetUp and TearDown methods are
 * executed before the test runs and after it completes. This is where we can
 * add any custom set up for each test without having to add this to "every"
 * test individually.
 */
class FileInfoTest : public BaseTest
{
protected:

	/**
	 * Run immediately before a test starts. Starts the timer.
	 */
	void SetUp();

	/**
	 * Invoked immediately after a test finishes. Stops the timer.
	 */
	void TearDown();

	/** Instance member variables. */
	bump::String _unittestDirectory;
	bump::String _emptyDirectory;
	bump::String _emptySymlinkDirectory;
	bump::String _filesDirectory;
	bump::String _regularDirectory;
	bump::String _symlinkDirectory;
	bump::String _symlinkFilesDirectory;
	bump::String _currentPath;
};

}	// End of bumpTest namespace
