//
// Created by Paul on 10.09.2018.
//

#ifndef PAXENGINE3_ANGLES_H
#define PAXENGINE3_ANGLES_H

#include "MathDefines.h"
#include "../lib/GlmIncludes.h"

namespace PAX {
    namespace Math {
        template<typename T>
        constexpr T toRadians(T degrees) {
            return T(degrees * M_PI / 180.0);
        }

        template<typename T>
        constexpr T toDegrees(T radians) {
            return T(radians * 180 / M_PI);
        }

        glm::vec3 sphericalCoordinatesToDirection(float theta, float phi);
        glm::vec2 lookDirToSphericalCoordinates(const glm::vec3 & lookdir);
        glm::vec3 sphericalCoordinatesToUpDirection(float theta, float phi);
    }
}

#endif //PAXENGINE3_ANGLES_H
