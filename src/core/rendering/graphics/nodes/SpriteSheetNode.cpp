//
// Created by Paul on 11.01.2018.
//

#include <core/rendering/graphics/nodes/SpriteSheetNode.h>

namespace PAX {
    SpriteSheetNode::SpriteSheetNode(int columns, int rows) : SceneGraph(), _size(columns, rows) {
        setOffset(0, 0);
    }

    void SpriteSheetNode::setOffset(int xOffset, int yOffset) {
        _offset = {xOffset, yOffset};
    }

    glm::ivec2 SpriteSheetNode::getOffset() {
        return _offset;
    }

    glm::ivec2 SpriteSheetNode::getSize() {
        return _size;
    }

    void SpriteSheetNode::registerFlags(Shader::Flags &flags) {
        flags.VertexFlags += "\n#define SPRITE_SHEET\n";
    }

    void SpriteSheetNode::cacheUniformsFor(std::shared_ptr<Shader> &shader) {
        shader->cacheUniforms({
                                      "spriteSheet.offset",
                                      "spriteSheet.size",
                              });
    }

    void SpriteSheetNode::render(RenderOptions &options) {
        Shader* shader = options.getShaderOptions().getShader();
        shader->setUniform("spriteSheet.offset", _offset);
        shader->setUniform("spriteSheet.size", _size);
        SceneGraph::render(options);
    }
}