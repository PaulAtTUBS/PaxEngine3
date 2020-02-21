//
// Created by Bittner on 21/06/2019.
//

#include <paxcore/world/property/WorldLayerSize.h>

namespace PAX {
    PAX_PROPERTY_IMPL(PAX::WorldLayerSize)

    ClassMetadata WorldLayerSize::getMetadata() {
        ClassMetadata m = Super::getMetadata();
        m.add(paxfieldof(size));
        return m;
    }

    WorldLayerSize::WorldLayerSize(const glm::vec3 &size) : size(size) {}

    const glm::vec3 & WorldLayerSize::getSize() const {
        return size;
    }

    const glm::vec2 & WorldLayerSize::getSize2D() const {
        return size2D;
    }

    void WorldLayerSize::setSize(const glm::vec3& size) {
        this->size = size;
    }

    void WorldLayerSize::setSize2D(const glm::vec2& size) {
        this->size2D = size;
    }
}