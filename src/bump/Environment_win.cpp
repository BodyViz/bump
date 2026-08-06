//
//	Enviroment_win.cpp
//	Bump
//
//	Created by Christian Noon on 12/12/12.
//	Copyright (c) 2012 Christian Noon. All rights reserved.
//

#include <bump/Environment.h>
#include <bump/String.h>

#include <cstdlib>

// Order is load-bearing: Lmcons.h uses Windows types without including
// windows.h itself, so windows.h must come first.
// clang-format off
#include <windows.h>
#include <Lmcons.h>
// clang-format on

namespace bump {

namespace Environment {

bool setEnvironmentVariable(const String& name, const String& value,
                            bool overwrite) {
    int result = 0;
    bool exists = !environmentVariable(name).isEmpty();
    if (overwrite || !exists) {
        result = _putenv_s(name.c_str(), value.c_str());
    }

    return result == 0;
}

bool unsetEnvironmentVariable(const String& name) {
    int result = _putenv_s(name.c_str(), "");
    return result == 0;
}

String currentUsername() {
    // GetUserNameA explicitly, not the GetUserName A/W macro: if UNICODE is
    // ever defined the macro resolves to GetUserNameW and this stops compiling.
    char username[UNLEN + 1] = {};
    DWORD size = UNLEN + 1;
    if (!GetUserNameA(username, &size)) {
        return String();
    }

    return username;
}

}  // namespace Environment

}  // namespace bump
