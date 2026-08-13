//
//	FileSystemError.h
//	Bump
//
//	Created by Christian Noon on 12/10/12.
//	Copyright (c) 2012 Christian Noon. All rights reserved.
//

#pragma once

#include <bump/Exception.h>

namespace bump {

/**
 * A public runtime error class which is used when the file system tries to
 * access a resource which is not valid. This can happen in situations such as
 * trying to remove a file that doesn't exist or setting the current path to an
 * invalid path.
 */
class BUMP_EXPORT FileSystemError : public RuntimeError {
public:
    /**
     * Constructor.
     *
     * @param description The description of the exception.
     * @param location The file path, line number and function name of where the
     * exception was thrown.
     */
    FileSystemError(const String& description, const String& location);

    /**
     * Destructor.
     */
    ~FileSystemError() override = default;
};

}  // namespace bump
