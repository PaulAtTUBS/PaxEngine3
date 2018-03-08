//
// Created by Paul on 09.01.2018.
//

#include <core/rendering/graphics/SpriteGraphics.h>
#include <glm/gtc/matrix_transform.hpp>
#include <core/io/resources/Resources.h>
#include <core/service/Services.h>
#include <core/entity/component/Size.h>

namespace PAX {
    Mesh *SpriteGraphics::QuadMesh = nullptr;

    Mesh* SpriteGraphics::GetMesh() {
        if (!QuadMesh) {
            std::vector<glm::vec3> vertices = {
                    {-0.5f,  0.5f, 0},  // V0
                    {-0.5f, -0.5f, 0},  // V1
                    { 0.5f, -0.5f, 0},  // V2
                    { 0.5f,  0.5f, 0}   // V3
            };

            std::vector<std::vector<int>> indices = {
                    {0, 1, 3},  // Top    left  triangle (V0,V1,V3)
                    {3, 1, 2}   // Bottom right triangle (V3,V1,V2)
            };

            std::vector<glm::vec2> texCoords = {
                    {0, 0},
                    {0, 1},
                    {1, 1},
                    {1, 0}
            };

            QuadMesh = Services::GetRenderFactory()->createMesh(vertices, indices);
            QuadMesh->addAttribute(texCoords);
            QuadMesh->finalize();
            QuadMesh->upload();
        }

        return QuadMesh;
    }

    SpriteGraphics::SpriteGraphics(const std::shared_ptr<Texture> &texture) : SceneGraphGraphics(),
                                                                              _texture(texture),
                                                                              _trafoNode(),
                                                                              _textureNode(texture),
                                                                              _meshNode(GetMesh())
    {
        _scenegraph <<= _trafoNode <<= _textureNode <<= &_meshNode;
    }

    const glm::vec2& SpriteGraphics::getSpriteSize() const {
        return glm::vec2(_texture->getWidth(), _texture->getHeight());
    }

    void SpriteGraphics::onSizeChanged(SizeChangedEvent &event) {
        _trafoNode.setTransformation(
                glm::scale(glm::mat4(1), event.size->getSizeUnscaled())
        );
    }

    void SpriteGraphics::registerFlags(Shader::Flags &flags) {
        _meshNode.registerFlags(flags);
    }

    void SpriteGraphics::setShader(std::shared_ptr<Shader> &shader) {
        _meshNode.cacheUniformsFor(shader);
        Graphics::setShader(shader);
    }

    void SpriteGraphics::attached(Entity *entity) {
        SceneGraphGraphics::attached(entity);

        entity->getEventService().add<SizeChangedEvent, SpriteGraphics, &SpriteGraphics::onSizeChanged>(this);

        glm::vec3 spriteSize = glm::vec3(getSpriteSize(), 0);
        Size* size = entity->get<Size>();
        if (size) {
            size->setSize(spriteSize);
        } else {
            size = Services::GetEntityComponentService().create<Size>(spriteSize);
            entity->add(size);
        }
    }

    void SpriteGraphics::detached(Entity *entity) {
        SceneGraphGraphics::detached(entity);
        entity->getEventService().remove<SizeChangedEvent, SpriteGraphics, &SpriteGraphics::onSizeChanged>(this);
    }
}