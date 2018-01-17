//
// Created by bittner on 11/20/17.
//

#ifndef PAXENGINE3_TERRAIN_H
#define PAXENGINE3_TERRAIN_H

#include <core/rendering/graphics/nodes/MeshNode.h>
#include <core/rendering/Graphics.h>

namespace PAX {
    PAX_ENTITYCOMPONENT_DERIVED(Terrain, Graphics)
    class Terrain : public Graphics {
        PAX_ENTITYCOMPONENT_BODY(Terrain)
    private:
        Mesh* mesh;

    public:
        Terrain(Mesh* mesh);

        void render(RenderOptions& renderOptions) override;
    };
}

#endif //PAXENGINE3_TERRAIN_H
