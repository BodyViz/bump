//
//  main.cpp
//  Bump package smoke test
//
//  Exercises one symbol per category that could plausibly break at a module
//  boundary, rather than sampling the API broadly. The unit tests already cover
//  behaviour; what is under test here is whether the installed package hands a
//  consumer everything it needs.
//

#include <bump/CryptographicHash.h>
#include <bump/FileSystem.h>
#include <bump/NotificationCenter.h>
#include <bump/String.h>
#include <bump/Timer.h>
#include <bump/TypeCastError.h>
#include <bump/Uuid.h>
#include <bump/Version.h>

#include <boost/any.hpp>
#include <iostream>
#include <type_traits>

// Regression guard for the five empty destructors deleted in 2.0.0. A
// user-declared destructor suppresses the implicit move operations, so before
// that change every "move" of a bump::String was a deep copy. This lives in the
// consumer because that is where the cost was paid.
static_assert(std::is_nothrow_move_constructible<bump::String>::value,
              "bump::String lost its move constructor");
static_assert(std::is_nothrow_move_assignable<bump::String>::value,
              "bump::String lost its move assignment operator");

// The package must raise the consumer to C++20 through
// INTERFACE_COMPILE_FEATURES without the consumer setting CMAKE_CXX_STANDARD.
static_assert(__cplusplus >= 202002L,
              "Bump::bump did not propagate cxx_std_20");

namespace {

int gFailures = 0;

void check(bool passed, const char* what) {
    std::cout << (passed ? "  ok    " : "  FAIL  ") << what << std::endl;
    if (!passed) {
        ++gFailures;
    }
}

/**
 * Receives a notification posted by the library's singleton. Defined in the
 * consumer so that bump::ObjectObserver -- a template whose base holds
 * boost::function and boost::shared_mutex members -- is instantiated on this
 * side of the boundary. That is the case the C4275/C4251 suppressions exist
 * for, and the one a consumer hits first on MSVC.
 */
class Listener {
public:
    void onNotified(const bump::String& object) { _received = object; }

    const bump::String& received() const { return _received; }

private:
    bump::String _received;
};

}  // namespace

int main() {
    std::cout << "Bump " << BUMP_MAJOR_VERSION << "." << BUMP_MINOR_VERSION
              << "." << BUMP_PATCH_VERSION << " package smoke test"
              << std::endl;

    // Derives from std::string, so its base crosses the boundary.
    bump::String text = "bump";
    text << "-smoke";
    check(text == "bump-smoke", "bump::String inherits and appends");
    check(bump::String(42).toInt() == 42, "bump::String numeric round trip");

    // Derives from a Boost type, which means Boost::headers has to have been
    // re-resolved by find_dependency for this to even compile.
    const bump::Uuid uuid = bump::Uuid::generateRandom();
    check(!uuid.isNull(), "bump::Uuid::generateRandom");
    check(uuid.toString().length() == 36, "bump::Uuid::toString");

    // Compiled from the vendored smallsha1 object library. Fails to link if
    // those objects did not make it into the installed archive or dylib.
    //
    // NOTE: `hash_input` has to outlive the result() call. setData(const
    // String&) stores a borrowed const char* into the argument rather than
    // copying it, so passing a temporary here reads freed memory and returns a
    // wrong hash. That is a real defect in bump, not a quirk of this test; see
    // the phase 7 report.
    bump::CryptographicHash hash;
    const bump::String hash_input =
        "This is a simple string that I'm going to hash";
    hash.setData(hash_input);
    check(hash.result() == "364fd3e0c0c454cb0c0fb393ede75f7f66b28eb6",
          "bump::CryptographicHash reaches vendored smallsha1");

    // Free function in a nested namespace, one of the 91 per-function
    // BUMP_EXPORT annotations that hidden visibility makes load-bearing.
    check(!bump::FileSystem::currentPath().isEmpty(),
          "bump::FileSystem::currentPath");

    // A singleton has to resolve to one instance across the boundary.
    check(bump::Timer::instance() != nullptr &&
              bump::Timer::instance() == bump::Timer::instance(),
          "bump::Timer::instance is stable");

    // Observer instantiated here, notification dispatched by the library.
    // Heap-allocated because ~ObjectObserver is protected: the notification
    // centre owns its observers and destroys them through the virtual
    // ~Observer, so removeObserver takes the *observed object* and deletes the
    // observer wrapping it. That makes this a boundary test in both directions
    // -- constructed here, destroyed inside the library through its vtable.
    Listener listener;
    bump::NotificationCenter::instance()->addObserver(
        new bump::ObjectObserver<Listener, bump::String>(
            &listener, &Listener::onNotified, "bump/smoke"));
    const unsigned int notified =
        bump::NotificationCenter::instance()->postNotificationWithObject(
            "bump/smoke", boost::any(bump::String("delivered")));
    check(notified == 1 && listener.received() == "delivered",
          "bump::ObjectObserver instantiated in the consumer");

    bump::NotificationCenter::instance()->removeObserver(&listener);
    check(!bump::NotificationCenter::instance()->containsObserver(&listener),
          "bump::NotificationCenter deletes a consumer-built observer");

    // Thrown inside the library, caught here by type. This is the check that
    // hidden visibility did not strip the typeinfo and vtable for the exception
    // hierarchy -- if it had, this catch would not match and the process would
    // terminate rather than report a failure.
    bool caught_by_type = false;
    try {
        bump::String("not a number").toInt();
    } catch (const bump::TypeCastError&) {
        caught_by_type = true;
    } catch (...) {
        caught_by_type = false;
    }
    check(caught_by_type, "bump::TypeCastError caught by type across boundary");

    // Static and shared packages are both valid; what matters is that the
    // consumer never had to say which one it got.
#ifdef BUMP_STATIC_DEFINE
    std::cout << "  note  BUMP_STATIC_DEFINE arrived from the imported target"
              << std::endl;
#else
    std::cout << "  note  linked against a shared Bump" << std::endl;
#endif

    if (gFailures == 0) {
        std::cout << "PASS" << std::endl;
        return 0;
    }

    std::cout << "FAIL (" << gFailures << ")" << std::endl;
    return 1;
}
