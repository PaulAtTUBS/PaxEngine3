//
// Created by Paul on 21.01.2018.
//

#ifndef PAXENGINE3_BOX2DPHYSICSSYSTEM_H
#define PAXENGINE3_BOX2DPHYSICSSYSTEM_H

#include <paxcore/system/entity/EntityPropertySystem.h>

#include "Box2DHitbox.h"

namespace PAX::Physics {
    class Box2DPhysicsSystem : public EntityPropertySystem<PAX::Physics::Box2DHitbox> {
        float pixelsPerMeter = 1;
        float metersPerPixel = 1;

    public:
        explicit Box2DPhysicsSystem(float pixelsPerMeter);

        void initialize(Game *game) override;
        void update(UpdateOptions & options) override;

        void setPixelsPerMeter(float pixelsPerMeter);
        float getMetersPerPixel();
        float getPixelsPerMeter();
    };
}

#endif //PAXENGINE3_BOX2DPHYSICSSYSTEM_H