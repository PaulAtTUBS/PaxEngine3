//
// Created by Paul on 28.05.2017.
//

#include "../../../include/core/rendering/Graphics.h"
#include "../../../include/core/entity/Entity.h"

namespace PAX {
    float Graphics::getZ() {
        return getOwner()->getTransform().z();
    }

    Shader *Graphics::getShader() const {
        return _shader;
    }

    void Graphics::setShader(Shader *shader) {
        GraphicsShaderChangedEvent e(_shader, shader, this);
        Graphics::_shader = shader;
        OnShaderChanged(e);
    }
}