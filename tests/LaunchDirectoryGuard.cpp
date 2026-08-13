//
//	LaunchDirectoryGuard.cpp
//	Bump
//

#include <gtest/gtest.h>

#include <algorithm>
#include <filesystem>
#include <iterator>
#include <string>
#include <system_error>
#include <vector>

namespace bumpTest {
namespace {

/** The directory every filesystem fixture builds its tree under. */
constexpr const char* kFixtureTree = "unittest";

/**
 * The immediate entries of a directory, sorted. Not recursive: what this is
 * looking for is a fixture creating its tree beside the binary, which shows up
 * as a new top-level entry. Recursing would mean walking the whole build tree
 * on every one of the couple of hundred process launches a ctest run makes.
 */
std::vector<std::string> listing(const std::filesystem::path& directory) {
    std::vector<std::string> entries;
    std::error_code ec;

    for (const auto& entry :
         std::filesystem::directory_iterator(directory, ec)) {
        entries.push_back(entry.path().filename().string());
    }

    std::sort(entries.begin(), entries.end());
    return entries;
}

/** The entries of the first sorted listing that are absent from the second. */
std::string difference(const std::vector<std::string>& from,
                       const std::vector<std::string>& without) {
    std::vector<std::string> only;
    std::set_difference(from.begin(), from.end(), without.begin(),
                        without.end(), std::back_inserter(only));

    std::string joined;
    for (const std::string& entry : only) {
        joined += joined.empty() ? entry : ", " + entry;
    }
    return joined;
}

/**
 * Asserts that running a suite leaves the directory it was launched from alone.
 *
 * The filesystem fixtures build a tree named "unittest" from paths relative to
 * the working directory, so a fixture that does not own that directory operates
 * on the caller's. ScratchDirectory is what keeps that from happening; this is
 * what notices if it stops.
 */
class LaunchDirectoryGuard : public ::testing::Environment {
public:
    void SetUp() override {
        _directory = std::filesystem::current_path();
        _before = listing(_directory);

        // A precondition rather than a result. Finding the tree here means an
        // earlier run already built it in this directory -- and it would then
        // be in the baseline below, leaving the comparison with nothing to
        // report however badly a fixture misbehaves.
        EXPECT_FALSE(std::filesystem::exists(_directory / kFixtureTree))
            << _directory << " already contains a '" << kFixtureTree
            << "' directory before any test has run. Remove it: a previous run "
               "built its tree there, and leaving it defeats this check.";
    }

    void TearDown() override {
        // By name as well as by comparison. The comparison catches a stray
        // entry of any name, but only against a clean baseline; this one holds
        // whatever state the directory was already in.
        EXPECT_FALSE(std::filesystem::exists(_directory / kFixtureTree))
            << "Running this suite left a '" << kFixtureTree
            << "' directory in " << _directory
            << ", the directory it was launched from. A fixture is building "
               "its tree there rather than in one it owns.";

        const std::vector<std::string> after = listing(_directory);
        if (after == _before) {
            return;
        }

        // The difference rather than EXPECT_EQ on the two listings, which would
        // print every entry of a build directory twice to report one stray one.
        ADD_FAILURE() << "Running this suite changed " << _directory
                      << ", the directory it was launched from. A fixture is "
                         "building its tree there rather than in one it owns."
                      << "\n  created: " << difference(after, _before)
                      << "\n  removed: " << difference(_before, after);
    }

private:
    std::filesystem::path _directory;
    std::vector<std::string> _before;
};

[[maybe_unused]] const ::testing::Environment* const kLaunchDirectoryGuard =
    ::testing::AddGlobalTestEnvironment(new LaunchDirectoryGuard);

}  // namespace
}  // namespace bumpTest
