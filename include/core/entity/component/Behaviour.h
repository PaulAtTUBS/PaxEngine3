//
// Created by Paul on 05.06.2017.
//

#ifndef PAXENGINE3_BEHAVIOUR_H
#define PAXENGINE3_BEHAVIOUR_H

#include "../EntityComponent.h"

namespace PAX {
    PAX_ENTITYCOMPONENT(Behaviour, true)
    class Behaviour : public EntityComponent {
        PAX_ENTITYCOMPONENT_BODY(Behaviour)
    public:
        virtual void update() = 0;
    };
}

#endif //PAXENGINE3_BEHAVIOUR_H
