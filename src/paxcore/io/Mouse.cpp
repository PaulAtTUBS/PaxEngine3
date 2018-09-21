//
// Created by Paul on 29.04.2017.
//

#include <easylogging++.h>
#include <paxcore/io/Mouse.h>

namespace PAX {
    int Mouse::getX() {
        return x;
    }

    int Mouse::getY() {
        return y;
    }

    bool Mouse::isButtonDown(MouseButton button) {
        LOG(WARNING) << "Mouse::isButtonDown not implemented";
        return false;
    }
}