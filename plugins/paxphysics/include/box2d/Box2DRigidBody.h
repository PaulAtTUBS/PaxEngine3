//
// Created by Paul on 21.01.2018.
//

#ifndef PAXENGINE3_BOX2DPHYSICS_H
#define PAXENGINE3_BOX2DPHYSICS_H

#include "../RigidBody.h"
#include <Box2D/Box2D.h>

namespace PAX {
    namespace Physics {
        namespace Box2D {
            class RigidBody : public PAX::Physics::RigidBody {
                PAX_PROPERTY(PAX::Physics::Box2D::RigidBody, PAX_PROPERTY_IS_CONCRETE)
                PAX_PROPERTY_DERIVES(PAX::Physics::RigidBody)
                PAX_PROPERTY_IS_MULTIPLE

                b2BodyDef _bodyDef;
                b2FixtureDef _fixtureDef;

                b2Body *_body;
                b2Fixture *_fixture;

            public:
                explicit RigidBody(const b2BodyDef &bodyDef);

                void createFor(b2World &world);

                void attached(Entity &entity) override;
            };
        }
    }
}

#endif //PAXENGINE3_BOX2DPHYSICS_H
