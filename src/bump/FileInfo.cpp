//
//  FileInfo.cpp
//  Bump
//
//  Created by Christian Noon on 12/4/12.
//  Copyright (c) 2012 Christian Noon. All rights reserved.
//

#include <bump/Environment.h>
#include <bump/FileInfo.h>
#include <bump/FileSystem.h>
#include <bump/FileSystemError.h>

#include <boost/config.hpp>
#include <boost/filesystem.hpp>

namespace bump {

FileInfo::FileInfo(const String& path) {
    _path = boost::filesystem::path(path.c_str()).make_preferred();
}

//=============================================================================
//                              Path Query Methods
//=============================================================================

bool FileInfo::exists() const {
    return boost::filesystem::exists(_path) ||
           boost::filesystem::is_symlink(_path);
}

unsigned long long FileInfo::fileSize() const {
    // Throw a FileSystemError if the path is not valid
    validatePath();

    // Expand the symlink path if necessary
    boost::filesystem::path path = _path;
    if (boost::filesystem::is_symlink(path)) {
        path = boost::filesystem::canonical(
            boost::filesystem::system_complete(path));
    }

    // Throw a FileSystemError if the path is not a file
    if (!boost::filesystem::is_regular_file(path)) {
        String msg =
            String("The following path is not a file: %1").arg(_path.string());
        throw FileSystemError(msg, BUMP_LOCATION);
    }

    return boost::filesystem::file_size(path);
}

bool FileInfo::isAbsolute() const { return _path.has_root_path(); }

bool FileInfo::isRelative() const { return !_path.has_root_path(); }

bool FileInfo::isDirectory() const {
    return boost::filesystem::is_directory(_path);
}

bool FileInfo::isFile() const {
    return boost::filesystem::is_regular_file(_path);
}

bool FileInfo::isSymbolicLink() const {
    return boost::filesystem::is_symlink(_path);
}

bool FileInfo::isEmpty() const {
    // Make sure the path is valid
    validatePath();

    // Try to check if the path is empty. This can fail in the event that we
    // don't have the proper permissions to read the file system object.
    try {
        boost::filesystem::path temp = boost::filesystem::canonical(_path);
        return boost::filesystem::is_empty(temp);
    } catch (const boost::filesystem::filesystem_error& /*e*/) {
        // Boost 1.91 made is_empty() throw on a file we lack read permission
        // for, where earlier releases returned a value. A regular file's
        // emptiness is still knowable without reading it: stat() reports the
        // size through a readable parent directory.
        boost::system::error_code error;
        boost::filesystem::path resolved =
            boost::filesystem::canonical(_path, error);
        if (!error) {
            const bool is_file =
                boost::filesystem::is_regular_file(resolved, error);
            if (!error && is_file) {
                const boost::uintmax_t size =
                    boost::filesystem::file_size(resolved, error);
                if (!error) {
                    return size == 0;
                }
            }
        }

        throw FileSystemError("Do not have permission to check if empty",
                              BUMP_LOCATION);
    }
}

bool FileInfo::isHidden() const {
    // It is not a hidden file if it isn't even a file
    if (exists()) {
        String filename = _path.filename().string();
        return filename.startsWith(".");
    }

    return false;
}

//=============================================================================
//                          Path Decomposition Methods
//=============================================================================

String FileInfo::absolutePath() const {
    String path = boost::filesystem::absolute(_path).string();
    return bump::FileSystem::convertToUnixPath(path);
}

String FileInfo::canonicalPath() const {
    validatePath();
    String path = boost::filesystem::canonical(_path).string();
    return bump::FileSystem::convertToUnixPath(path);
}

String FileInfo::parentPath() const {
    String path = _path.parent_path().string();
    return bump::FileSystem::convertToUnixPath(path);
}

String FileInfo::path() const {
    return bump::FileSystem::convertToUnixPath(_path.string());
}

String FileInfo::basename() const {
    if (isDirectory()) {
        return filename();
    } else {
        String basename = _path.stem().string();
        if (basename.startsWith(".")) {
            String temp = basename.right(basename.length() - 1);
            if (temp.contains(".")) {
                basename = basename.left(temp.indexOf(".") + 1);
            }
        } else {
            if (basename.contains(".")) {
                basename = basename.left(basename.indexOf("."));
            }
        }

        return basename;
    }
}

String FileInfo::completeBasename() const {
    if (isDirectory()) {
        return filename();
    } else {
        return _path.stem().string();
    }
}

String FileInfo::extension() const {
    if (isDirectory()) {
        return String();
    } else {
        String extension = _path.extension().string();
        if (extension.startsWith(".")) {
            extension = extension.section(1);
        }

        return extension;
    }
}

String FileInfo::completeExtension() const {
    if (isDirectory()) {
        return String();
    } else {
        String filename = this->filename();
        if (filename.contains(".")) {
            String basename = this->basename() << ".";
            return filename.remove(basename);
        } else {
            return String();
        }
    }
}

String FileInfo::filename() const { return _path.filename().string(); }

//=============================================================================
//                              Date Query Methods
//=============================================================================

std::time_t FileInfo::modifiedDate() const {
    validatePath();
    return boost::filesystem::last_write_time(_path);
}

void FileInfo::validatePath() const {
    try {
        boost::filesystem::canonical(_path);
    } catch (const boost::filesystem::filesystem_error& /*e*/) {
        String msg =
            String("The following path is invalid: %1").arg(_path.string());
        throw FileSystemError(msg, BUMP_LOCATION);
    }
}

}  // namespace bump
