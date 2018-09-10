//
// Created by Paul on 14.01.2018.
//

#ifndef PAXENGINE3_PLAYERSPRITEANIMATION_H
#define PAXENGINE3_PLAYERSPRITEANIMATION_H

#include <paxcore/entity/component/Behaviour.h>
#include <paxcore/rendering/graphics/SpriteSheetGraphics.h>
#include <paxcore/animation/Animation.h>
#include <paxutil/math/Functions.h>

namespace PAX {
    class PlayerSpriteAnimation : public Behaviour {
        PAX_ENTITYCOMPONENT_BODY(PAX::Behaviour, false)
        PAX_ENTITYCOMPONENT_DEPENDS_ON(SpriteSheetGraphics, VelocityBehaviour)

        Animation<int> walkingAnimation;
        Animation<int> idleAnimation;
        Animation<int>* activeAnimation;

        int xIndex;
        int yIndex;

        int moving = 0;

        VelocityBehaviour *v;
        SpriteSheetGraphics *spriteSheet;

    public:
        PlayerSpriteAnimation() :
                walkingAnimation(1, 7, 0.8, &xIndex),
                idleAnimation(0, 2, 0.6, &xIndex),
                xIndex(0),
                yIndex(2),
                activeAnimation(&idleAnimation)
        {

        }

        virtual void attached(Entity *entity) override {
            Behaviour::attached(entity);
            v = entity->get<VelocityBehaviour>();
            spriteSheet = entity->get<SpriteSheetGraphics>();
            idleAnimation.start();
        }

        virtual void update() override {
            int oldMoving = moving;
            moving = Math::sign(v->velocity.x);
            if (oldMoving != moving) {
                if (moving) {
                    idleAnimation.stop();
                    walkingAnimation.start();
                    activeAnimation = &walkingAnimation;
                    getOwner()->getTransform().setScaleX(getOwner()->getTransform().getScaleX() * moving);
                    yIndex = 1;
                } else {
                    walkingAnimation.stop();
                    idleAnimation.start();
                    activeAnimation = &idleAnimation;
                    getOwner()->getTransform().setScaleX(abs(getOwner()->getTransform().getScaleX()));
                    yIndex = 2;
                }
            }

            activeAnimation->update();
            spriteSheet->setSpritePosition(xIndex, yIndex);
        }
    };
}

#endif //PAXENGINE3_PLAYERSPRITEANIMATION_H
