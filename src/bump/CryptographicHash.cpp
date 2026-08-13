//
//  CryptographicHash.cpp
//  Bump
//
//  Created by Christian Noon on 1/4/13.
//  Copyright (c) 2013 Christian Noon. All rights reserved.
//

#include <bump/CryptographicHash.h>
#include <smallsha1/sha1.h>

namespace bump {

CryptographicHash::CryptographicHash(const Algorithm& algorithm)
    : _algorithm(algorithm), _hasData(false), _hash() {
    ;
}

void CryptographicHash::setData(const String& data) {
    setData(data.data(), static_cast<int>(data.size()));
}

void CryptographicHash::setData(const char* data, int length) {
    _hasData = length > 0;
    if (_hasData) {
        sha1::calc(data, length, _hash);
    }
}

void CryptographicHash::reset() { _hasData = false; }

String CryptographicHash::result() {
    if (!_hasData) {
        return String();
    }

    char hexstring[41];
    sha1::toHexString(_hash, hexstring);

    return String(hexstring);
}

}  // namespace bump
