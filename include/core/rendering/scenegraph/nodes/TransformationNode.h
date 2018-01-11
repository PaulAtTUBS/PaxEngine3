//
// Created by Paul on 06.01.2018.
//

#ifndef PAXENGINE3_TRANSFORMATIONNODE_H
#define PAXENGINE3_TRANSFORMATIONNODE_H

#include <core/rendering/scenegraph/SceneGraph.h>

namespace PAX {
    class TransformationNode : public SceneGraph {
        glm::mat4 _transformation;

    public:
        TransformationNode(const glm::mat4& transformation = glm::mat4(1.0));

        void setTransformation(const glm::mat4& transformation);
        glm::mat4& getTransformation();

        virtual void render(RenderOptions& options) override;
    };
}

#endif //PAXENGINE3_TRANSFORMATIONNODE_H
