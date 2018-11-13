//
// Created by Paul on 06.01.2018.
//

#ifndef PAXENGINE3_PLAYGROUNDDEMO_H
#define PAXENGINE3_PLAYGROUNDDEMO_H

#include <paxcore/Game.h>

#include <paxcore/rendering/camera/Camera.h>
#include <paxcore/rendering/camera/PerspectiveProjection.h>
#include <paxutil/rendering/Cube.h>
#include <paxcore/rendering/graphics/SceneGraphGraphics.h>
#include <paxcore/rendering/data/Texture.h>
#include <paxcore/entity/component/behaviours/NoClipControls.h>
#include <paxcore/rendering/graphics/AssetGraphics.h>
#include <paxcore/rendering/data/Material.h>
#include <paxcore/rendering/light/DirectionalLight.h>
#include <paxcore/rendering/light/AmbientLight.h>
#include <paxcore/system/LightSystem.h>

#include "TestBehaviour.h"

namespace PAX {
    namespace PlaygroundDemo {
        class Demo : public Game {
            World *_world = nullptr;

            std::shared_ptr<Shader> redShader;
            std::shared_ptr<Shader> texShader;
            std::shared_ptr<Shader> simpleMatShader;

            std::shared_ptr<Mesh> cube;

            std::shared_ptr<Material> cubeMaterial;

            void prepareAssets() {
                texShader = Services::GetResources().loadOrGet<Shader>(
                        Services::GetPaths().getResourcePath() + "/shader/test/PlainTexture.vert",
                        Services::GetPaths().getResourcePath() + "/shader/test/PlainTexture.frag"
                );
                simpleMatShader = Services::GetResources().loadOrGet<Shader>(
                        Services::GetPaths().getResourcePath() + "/shader/material/simple/simplemat.vert",
                        Services::GetPaths().getResourcePath() + "/shader/material/simple/simplemat.frag"
                );
                redShader = Services::GetResources().loadOrGet<Shader>(
                        Services::GetPaths().getResourcePath() + "/shader/test/red/red.vert",
                        Services::GetPaths().getResourcePath() + "/shader/test/red/red.frag"
                );

                texShader->upload();
                simpleMatShader->upload();
                redShader->upload();

                cube = Util::createCube(true /*with tex coords*/);
                cube->upload();

                std::shared_ptr<Texture> texture = Services::GetResources().loadOrGet<Texture>(
                        Services::GetPaths().getResourcePath() + "/img/PaxEngine3_128.png"
                );
                cubeMaterial = std::make_shared<Material>("CubeMaterial_createdInCode");
                cubeMaterial->diffuse.texture = texture;
            }

            Entity* createCube(std::shared_ptr<Shader> & shader) {
                Entity* cubeEntity = new Entity();
                AllocationService& es = Services::GetDefaultAllocationService();
                std::shared_ptr<Asset> a = std::make_shared<Asset>(std::vector<Asset::Part>{
                        Asset::Part(cube, cubeMaterial)
                });
                const std::shared_ptr<AssetGraphics>& g = es.create<AssetGraphics>(a);
                g->setShader(shader);
                cubeEntity->add(g);
                return cubeEntity;
            }

            Entity* createFromFile(const std::string & relativeResourcePath, std::shared_ptr<Shader> & shader) {
                AllocationService& es = Services::GetDefaultAllocationService();
                std::shared_ptr<Asset> tree = Services::GetResources().load<Asset>(
                        Services::GetPaths().getResourcePath() + relativeResourcePath
                );
                Entity* treeEntity = new Entity();
                const std::shared_ptr<AssetGraphics>& g = es.create<AssetGraphics>(tree);
                g->setShader(shader);
                treeEntity->add(g);
                return treeEntity;
            }

        public:
            Demo() : Game()
            {

            }

            ~Demo() override {

            }

            virtual void initialize() override {
                Game::initialize();
                this->addSystem(new LightSystem());

                prepareAssets();

                bool withCube = true;
                bool withTree = true;
                bool withTank = true;

                _world = new World();
                WorldLayer* mainLayer = new WorldLayer(PAX_WORLDLAYERNAME_MAIN, 3);


                AllocationService& es = Services::GetDefaultAllocationService();
                Entity* cam = new Entity();
                {
                    std::shared_ptr<PerspectiveProjection> proj = std::make_shared<PerspectiveProjection>();
                    proj->setFOV(90);
                    cam->add(es.create<Camera>(Services::GetFactory().create<Viewport>(), proj));
                    cam->add(es.create<NoClipControls>());
                    mainLayer->spawn(cam);
                }

                cam->getTransformation().position() = {0, 0, 0};

                if (withCube) {
                    Entity* cube = createCube(redShader);
                    cube->getTransformation().position() = {0, 0, -2};
                    mainLayer->spawn(cube);
                }

                if (withTree) {
                    Entity* tree  = createFromFile("mesh/lowpolytree/lowpolytree.obj", simpleMatShader);
                    tree->getTransformation().position() = {-3, 0, -5};
                    mainLayer->spawn(tree);
                }

                if (withTank) {
                    Entity* tank  = createFromFile("mesh/ltp/LTP.obj", simpleMatShader);
                    tank->getTransformation().position() = {1, -2, -5};
                    mainLayer->spawn(tank);
                }

                // Spawn a light
                Entity* lightEntity = new Entity();
                lightEntity->add(es.create<DirectionalLight>(glm::vec3(1, 0, 0), glm::vec4(1, 0.5f, 0, 1)));
                mainLayer->spawn(lightEntity);

                mainLayer->add(es.create<AmbientLight>());

                _world->addLayer(mainLayer);
                setActiveWorld(_world);
            }
        };
    }
}

#endif //PAXENGINE3_PLAYGROUNDDEMO_H
