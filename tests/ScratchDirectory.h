//
//	ScratchDirectory.h
//	Bump
//

#pragma once

#include <filesystem>
#include <random>
#include <sstream>
#include <stdexcept>
#include <string>
#include <system_error>

namespace bumpTest {

/**
 * A uniquely named directory under the system temporary location, made current
 * for the lifetime of the object and removed with its contents afterwards.
 *
 * The filesystem fixtures build a tree named "unittest" from paths relative to
 * the working directory and remove it recursively when they finish. Owning that
 * directory is what confines both halves: without it a suite builds -- and then
 * deletes -- whatever sits beside the binary when it is launched.
 *
 * Held by value in a fixture, so it is established before SetUp and unwound
 * after TearDown.
 */
class ScratchDirectory {
public:
    ScratchDirectory()
        : _previousPath(std::filesystem::current_path()), _path(create()) {
        std::filesystem::current_path(_path);
    }

    ~ScratchDirectory() {
        // Leaves before removing, since a directory cannot be removed while it
        // is current on Windows. Errors are swallowed: a destructor cannot
        // report, and a leftover directory under the temp location is not worth
        // terminating a test run over.
        std::error_code ec;
        std::filesystem::current_path(_previousPath, ec);
        std::filesystem::remove_all(_path, ec);
    }

    ScratchDirectory(const ScratchDirectory&) = delete;
    ScratchDirectory& operator=(const ScratchDirectory&) = delete;

    const std::filesystem::path& path() const { return _path; }

private:
    /**
     * temp_directory_path() is the location the platform designates, honouring
     * TMPDIR, TMP and TEMP, and it throws rather than guessing if there is
     * none. Only a freshly created subdirectory of it is ever returned, so an
     * existing directory is never adopted.
     *
     * create_directory() reports true only when this call created the
     * directory, and it is one mkdir underneath, so two processes racing on the
     * same name cannot both be told they succeeded. Retrying past a taken name
     * is therefore enough to own what comes back, whatever else is running.
     */
    static std::filesystem::path create() {
        const std::filesystem::path base =
            std::filesystem::temp_directory_path();
        std::random_device entropy;

        for (int attempt = 0; attempt < 64; ++attempt) {
            std::ostringstream name;
            name << "bump-tests-" << std::hex << entropy() << entropy();
            const std::filesystem::path candidate = base / name.str();

            std::error_code ec;
            if (std::filesystem::create_directory(candidate, ec)) {
                return candidate;
            }
            if (ec) {
                throw std::runtime_error("Could not create a scratch directory "
                                         "under " +
                                         base.string() + ": " + ec.message());
            }
        }

        throw std::runtime_error("Could not find an unused scratch directory "
                                 "name under " +
                                 base.string());
    }

    std::filesystem::path _previousPath;
    std::filesystem::path _path;
};

}  // namespace bumpTest
