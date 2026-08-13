//
//	LaunchDirectoryGuard.cpp
//	Bump
//

#include <gtest/gtest.h>

#include <filesystem>

namespace bumpTest {
namespace {

/** The directory every filesystem fixture builds its tree under. */
constexpr const char* kFixtureTree = "unittest";

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

        // A precondition rather than a result: finding it here means an earlier
        // run already built its tree in this directory.
        EXPECT_FALSE(std::filesystem::exists(_directory / kFixtureTree))
            << _directory << " already contains a '" << kFixtureTree
            << "' directory before any test has run. Remove it: a previous run "
               "built its tree there.";
    }

    void TearDown() override {
        EXPECT_FALSE(std::filesystem::exists(_directory / kFixtureTree))
            << "Running this suite left a '" << kFixtureTree
            << "' directory in " << _directory
            << ", the directory it was launched from. A fixture is building "
               "its tree there rather than in one it owns.";
    }

private:
    std::filesystem::path _directory;
};

[[maybe_unused]] const ::testing::Environment* const kLaunchDirectoryGuard =
    ::testing::AddGlobalTestEnvironment(new LaunchDirectoryGuard);

}  // namespace
}  // namespace bumpTest
