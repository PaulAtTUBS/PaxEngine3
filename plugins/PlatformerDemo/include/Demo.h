//
// Created by Paul on 06.01.2018.
//

#ifndef PAXENGINE3_JUMPNRUNDEMO_H
#define PAXENGINE3_JUMPNRUNDEMO_H

#include <core/Game.h>
#include <core/Engine.h>

#include <core/entity/component/Size.h>
#include <core/io/resources/Path.h>
#include <core/rendering/camera/FullPixelScreenProjection.h>
#include <core/rendering/resource/SpriteSheet.h>
#include <core/rendering/graphics/SpriteGraphics.h>
#include <core/rendering/graphics/SpriteSheetGraphics.h>

#include <opengl/include/OpenGLViewport.h>

#include "behaviour/PlayerControls.h"
#include "behaviour/PlayerSpriteAnimation.h"
#include "behaviour/FollowEntityBehaviour.h"

namespace PAX {
    namespace PlatformerDemo {
        class Demo : public Game {
            World *_world = nullptr;
            Entity *_player = nullptr;
            Entity* _camera = nullptr;

            SpriteSheetGraphics* playerGraphics;

            std::shared_ptr<Texture> centerBlockTexture;
            std::shared_ptr<Texture> leftBlockTexture;
            std::shared_ptr<Texture> rightBlockTexture;
            std::shared_ptr<Texture> spriteTest;

            std::shared_ptr<Shader> spriteShader, spriteSheetShader;


            void gatherResources() {
                LOG(INFO) << "Demo: gatherResources";

                EntityComponentService& s = Services::GetEntityComponentService();

                spriteTest = Services::GetResources().loadOrGet<Texture>(
                        Services::GetPaths().RelativeResourcePath() + "img/Platformer/GreenBot16.png"
                );

                spriteShader = Services::GetResources().loadOrGet<Shader>(
                        Services::GetPaths().RelativeResourcePath() + "shader/sprite/sprite.vert",
                        Services::GetPaths().RelativeResourcePath() + "shader/sprite/sprite.frag"
                );

                playerGraphics = s.create<SpriteSheetGraphics>(spriteTest, 7, 4);
                spriteSheetShader = Services::GetResources().loadOrGet<Shader>(
                        playerGraphics->getShaderFlags(),
                        Services::GetPaths().RelativeResourcePath() + "shader/sprite/sprite.vert",
                        Services::GetPaths().RelativeResourcePath() + "shader/sprite/sprite.frag"
                );

                spriteShader->upload();
                spriteSheetShader->upload();

                playerGraphics->setShader(spriteSheetShader);
            }

            Entity* createPlayer() {
                LOG(INFO) << "Demo: create Player";
                EntityComponentService& s = Services::GetEntityComponentService();

                Entity* player = new Entity();
                player->add(playerGraphics);
                LOG(INFO) << "Demo: Player add VelocityBehaviour";
                player->add(s.create<VelocityBehaviour>());
                LOG(INFO) << "Demo: Player add PlayerControls";
                player->add(s.create<PlayerControls>());
                LOG(INFO) << "Demo: Player add PlayerSpriteAnimation";
                player->add(s.create<PlayerSpriteAnimation>());

                player->getTransform().setScale(5, 5);

                return player;
            }

            Entity* createCamera(Entity *player) {
                LOG(INFO) << "Demo: create Camera";
                EntityComponentService& s = Services::GetEntityComponentService();

                Entity *cam = new Entity();
                cam->add(s.create<Camera>(
                        new OpenGL::OpenGLViewport(),
                        new FullPixelScreenProjection()
                ));
                cam->getTransform().z() = 1;
                cam->add(s.create<FollowEntityBehaviour>(player));

                return cam;
            }

            Entity* createPlatform(int span) {
                LOG(INFO) << "Demo: createPlatform of size " << span;

                int scale = 5;
                EntityComponentService& s = Services::GetEntityComponentService();

                Entity* platform = new Entity();
                int w = centerBlockTexture->getWidth() * scale;
                int xMax = (span-1)*(w/2);

                std::shared_ptr<Texture> tex = leftBlockTexture;
                for (int x = -xMax; x <= xMax; x += w) {
                    if (x >= xMax)
                        tex = rightBlockTexture;

                    Entity *block = new Entity();
                    SpriteGraphics* g = s.create<SpriteGraphics>(tex);
                    g->setShader(spriteShader);
                    block->add(g);

                    block->getTransform().x() = x;
                    block->getTransform().setScale(scale, scale);

                    block->setParent(platform);

                    tex = centerBlockTexture;
                }

                platform->add(s.create<Size>(glm::vec3(0, 0, 1)));
                FloatBoundingBox3D platformBoundingBox = platform->get<Size>()->toAbsoluteBoundingBox();
                platformBoundingBox.print();

                return platform;
            }

            void createEnvironment() {
                LOG(INFO) << "Demo: create Environment";
                EntityComponentService& s = Services::GetEntityComponentService();
                glm::ivec2 resolution = Engine::Instance().getWindow()->getResolution();
                Resources &r = Services::GetResources();
                std::string imgPath = Services::GetPaths().RelativeResourcePath() + "img/Platformer/";

                centerBlockTexture = r.loadOrGet<Texture>(imgPath + "Block/Center.png");
                leftBlockTexture   = r.loadOrGet<Texture>(imgPath + "Block/Left.png");
                rightBlockTexture  = r.loadOrGet<Texture>(imgPath + "Block/Right.png");

                int w = centerBlockTexture->getWidth();
                int h = centerBlockTexture->getHeight();
                int y = resolution.y - 2*h;

                Entity *p1 = createPlatform(5);
                p1->getTransform().position2D() = {0, -200};
                _world->getMainLayer()->spawn(p1);

                Entity *p2 = createPlatform(2);
                p2->getTransform().position2D() = {300, 100};
                _world->getMainLayer()->spawn(p2);

                {
                    Entity *background = new Entity();
                    SpriteGraphics* backgroundGraphics = s.create<SpriteGraphics>(
                            r.loadOrGet<Texture>(imgPath + "bg.png")
                    );
                    backgroundGraphics->setShader(spriteShader);
                    background->add(backgroundGraphics);

                    Entity *backgroundCam = new Entity();
                    backgroundCam->add(s.create<Camera>(
                            new OpenGL::OpenGLViewport(),
                            new FullPixelScreenProjection()
                    ));
                    backgroundCam->getTransform().z() = 1;

                    WorldLayer *bg = new WorldLayer("Background", -10);
                    bg->spawn(background);
                    bg->spawn(backgroundCam);
                    _world->addLayer(bg);
                }
            }

        public:
            Demo() : Game()
            {

            }

            ~Demo() {
                if (unregisterWorld(_world)) {
                    delete _world;
                } else {
                    LOG(ERROR) << "The world of JumpNRun could not be deleted!";
                }
            }

            virtual void initialize() override {
                Game::initialize();

                LOG(INFO) << "Demo: initialize";

                gatherResources();

                _world = new World();
                _player = createPlayer();
                _camera = createCamera(_player);
                LOG(INFO) << "Demo: spawn Player";
                _world->getMainLayer()->spawn(_player);
                LOG(INFO) << "Demo: spawn Camera";
                _world->getMainLayer()->spawn(_camera);
                createEnvironment();

                setActiveWorld(_world);
            }
        };
    }
}

#endif //PAXENGINE3_JUMPNRUNDEMO_H