//
// Created by Paul on 19.01.2018.
//

#ifndef PAXENGINE3_VELOCITYBEHAVIOUR_H
#define PAXENGINE3_VELOCITYBEHAVIOUR_H


#include <paxcore/entity/EntityComponent.h>
#include <paxcore/entity/component/Behaviour.h>
#include <paxcore/time/Time.h>

namespace PAX {
    class VelocityBehaviour : public Behaviour {
        PAX_ENTITYCOMPONENT_BODY(PAX::Behaviour, false)

    public:
        glm::vec2 velocity = glm::vec2(0);

        virtual void update() override {
            Transform& t = getOwner()->getTransform();
            t.position2D() += velocity * Time::DeltaF;
        }
    };
}
#endif //PAXENGINE3_VELOCITYBEHAVIOUR_H
