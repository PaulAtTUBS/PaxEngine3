//
// Created by Paul on 05.10.2017.
//

#ifndef PAXENGINE3_GRAPHICSSHADERCHANGEDEVENT_H
#define PAXENGINE3_GRAPHICSSHADERCHANGEDEVENT_H

#include "ShaderChangedEvent.h"

namespace PAX {
    class Graphics;

    class GraphicsShaderChangedEvent : public ShaderChangedEvent {
    public:
        Graphics *graphics;

        GraphicsShaderChangedEvent(Shader* oldShader, Shader *newShader, Graphics *graphics) :
                ShaderChangedEvent(oldShader, newShader), graphics(graphics) {}
    };
}

#endif //PAXENGINE3_GRAPHICSSHADERCHANGEDEVENT_H
