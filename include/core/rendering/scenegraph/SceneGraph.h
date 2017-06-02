//
// Created by Paul on 02.05.2017.
//

#ifndef PAXENGINE3_SCENEGRAPH_H
#define PAXENGINE3_SCENEGRAPH_H

#include <vector>
#include "sort/RenderableSort.h"

namespace PAX {
    class SceneGraph : private Renderable {
        std::vector<SceneGraph*> _parents;
        std::vector<Renderable*> _children;
        Sort::RenderableSort _sorter;

    public:
        SceneGraph();
        ~SceneGraph();

        const std::vector<SceneGraph*>& getParents();

        void addRenderable(Renderable* renderable);
        bool removeRenderable(Renderable* renderable);
        void addChild(SceneGraph* child);
        bool removeChild(SceneGraph* child);

        bool isEmpty();

        virtual void render() override;
        virtual float getZ() override;

        void prettyPrint();
    };
}

#endif //PAXENGINE3_SCENEGRAPH_H
