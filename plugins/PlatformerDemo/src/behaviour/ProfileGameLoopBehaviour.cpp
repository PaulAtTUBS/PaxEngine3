//
// Created by paul on 07.01.19.
//

#include <behaviour/ProfileGameLoopBehaviour.h>

namespace PAX {
    PAX_PROPERTY_SOURCE(PAX::ProfileGameLoopBehaviour, PAX_PROPERTY_IS_CONCRETE)

    ProfileGameLoopBehaviour * ProfileGameLoopBehaviour::createFromProvider(ContentProvider & provider) {
        return new ProfileGameLoopBehaviour();
    }

    void ProfileGameLoopBehaviour::initializeFromProvider(ContentProvider & provider) {
        Super::initializeFromProvider(provider);
    }
}