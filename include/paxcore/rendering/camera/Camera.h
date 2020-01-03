//
// Created by Gordon on 16.05.2017.
//

#ifndef PAXENGINE3_CAMERA_H
#define PAXENGINE3_CAMERA_H

#include <paxutil/lib/GlmIncludes.h>
#include <glm/detail/type_mat4x4.hpp>

#include "PerspectiveProjection.h"

#include "paxcore/gameentity/GameEntityProperty.h"
#include "../scenegraph/SceneGraph.h"
#include "../Viewport.h"
#include "../RenderOptions.h"

namespace PAX {
    class Camera : public GameEntityProperty, public SceneGraph {
        PAX_PROPERTY(Camera, PAX_PROPERTY_IS_CONCRETE)
        PAX_PROPERTY_DERIVES(GameEntityProperty)
        PAX_PROPERTY_IS_SINGLE

        glm::mat4 viewMatrix = glm::mat4();
        std::shared_ptr<Viewport> viewport;
        std::shared_ptr<Projection> projection;

        bool syncProjectionResolutionToViewportResolution = false;

        void onViewportWidthChanged(int oldWidth, int newWidth);
        void onViewportHeightChanged(int oldHeight, int newHeight);

    public:
        explicit Camera(const std::shared_ptr<Viewport> & viewport, const std::shared_ptr<Projection> & projection = std::make_shared<PerspectiveProjection>());

        void render(RenderOptions &renderOptions) override;

        const glm::mat4 &getViewTransform();
        PAX_NODISCARD std::shared_ptr<Viewport> getViewport() const;
        PAX_NODISCARD std::shared_ptr<Projection> getProjection() const;

        void setSyncProjectionResolutionToViewportResolution(bool sync);
        PAX_NODISCARD bool areProjectionResolutionToViewportResolutionSynced() const;

        PAX_NODISCARD ClassMetadata getMetadata() override;
    };
}

#endif //PAXENGINE3_CAMERA_H
