//
//	HeaderHygiene.cpp
//	Bump
//
// Asserts properties of the public headers that bump's own build cannot see,
// because they only show up in a consumer. Nothing here is meant to run; the
// point is that it compiles, and under which flags. See tests/CMakeLists.txt.

#include <bump/bump.h>

#include <functional>

// What a consumer writes for its own std::bind calls. It only compiles if no
// bump header has put boost::placeholders into the global namespace, which
// would make every _1 through _9 ambiguous in code that has nothing to do with
// bump -- and unfixable without editing bump.
using namespace std::placeholders;

namespace {

int add(int a, int b) { return a + b; }

[[maybe_unused]] int bindsWithoutAmbiguity() {
    const auto addFive = std::bind(add, 5, _1);
    return addFive(3);
}

}  // namespace
