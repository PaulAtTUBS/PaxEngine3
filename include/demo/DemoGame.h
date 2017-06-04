//
// Created by paul on 01.06.17.
//

#ifndef PAXENGINE3_DEMOGAME_H
#define PAXENGINE3_DEMOGAME_H

#include <iostream>
#include "../core/Game.h"
#include "../test/SDLTestApplication2.h"
#include "../sdl/test/SDLSprite.h"
#include "../sdl/SDLRenderPass.h"
#include "../sdl/utitlity/Path.h"

namespace PAX {
    namespace Demo {
        class DemoGame : public Game {
            Entity testEntity;

        public:
            virtual void initialize() override {
                Game::initialize();

                SDLRenderPass *renderpass = new SDLRenderPass();
                Renderer &renderer = Engine::GetInstance()->getRenderer();
                renderer.setSceneGraphRoot(renderpass);
                renderer.setSceneGraphGenerationEntryPoint(renderpass);

                renderpass->initialize();

                World *testWorld = new World();
                setActiveWorld(testWorld);

                SDLSprite *sprite = new SDLSprite(renderpass->getSDLRenderer(), getResourcePath() + "img/test/Gilgamesh.bmp");
                testEntity.add<Graphics>(sprite);

                testEntity.add<Camera>(new Camera);

                testEntity.getTransform().setPosition(300, 200);

                testWorld->getMainLayer()->spawn(&testEntity);
                //*/
            }
        };
    }
}

#endif //PAXENGINE3_DEMOGAME_H
