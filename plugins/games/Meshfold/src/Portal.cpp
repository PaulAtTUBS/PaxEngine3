//
// Created by Paul Bittner on 21.03.2020.
//

#include <meshfold/Portal.h>

namespace PAX {
    Portal::Portal() : from(0), to(0), target(nullptr) {}

    Portal::Portal(const glm::vec2 &from, const glm::vec2 &to, PAX::Portal *target)
    : from(from), to(to), target(target) {

    }

    static inline float cross2d(const glm::vec2 & a, const glm::vec2 & b) {
        return a.x * b.y - a.y * b.x;
    }

    float Portal::getIntersection(const glm::vec2 &p, const glm::vec2 &d, bool& parallel) {
        float down = cross2d(to - from, d);

        if (down == 0) {
            parallel = true;
            return 0;
        }

        parallel = false;
        return cross2d(p - from, d) / down;
    }

    glm::vec2 Portal::normal() {
        auto axis = glm::vec2(to - from);
        return {axis.y, -axis.x};
    }
}