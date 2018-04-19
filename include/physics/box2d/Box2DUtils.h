//
// Created by Paul on 24.01.2018.
//

#ifndef PAXENGINE3_BOX2DUTILS_H
#define PAXENGINE3_BOX2DUTILS_H

#include <glm/vec2.hpp>
#include <Box2D/Common/b2Math.h>

namespace PAX {
    namespace Box2D {
        b2Vec2 toBox2D(const glm::vec2& glmvec) {
            return {glmvec.x, glmvec.y};
        }

        b2Vec2 toBox2D(const glm::vec3& glmvec) {
            return {glmvec.x, glmvec.y};
        }
    }
}

#endif //PAXENGINE3_BOX2DUTILS_H
