//
// Created by paul on 07.01.19.
//

#include "platformerdemo/behaviour/PlayerSpriteAnimation.h"

namespace PAX {
    PAX_PROPERTY_IMPL(PAX::PlayerSpriteAnimation, PAX_PROPERTY_IS_CONCRETE)

    PlayerSpriteAnimation * PlayerSpriteAnimation::createFromProvider(ContentProvider & provider) {
        return new PlayerSpriteAnimation();
    }

    void PlayerSpriteAnimation::initializeFromProvider(ContentProvider & provider) {
        Super::initializeFromProvider(provider);
    }
}