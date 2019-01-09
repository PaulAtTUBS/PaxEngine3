//
// Created by paul on 07.01.19.
//

#include <behaviour/FollowEntityBehaviour.h>
#include <paxcore/time/Time.h>

namespace PAX {
    PAX_PROPERTY_SOURCE(PAX::FollowEntityBehaviour)

    void FollowEntityBehaviour::update() {
        if (target) {
            Transformation &me = getOwner()->getTransformation();
            Transformation &he = target->getTransformation();
            me.position2D() = me.position2D() + (he.position2D() - me.position2D()) * speed * Time::DeltaF;
        }
    }
}