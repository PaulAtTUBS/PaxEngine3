//
// Created by paul on 07.01.19.
//

#ifndef PAXENGINE3_VIEWPORTFACTORY_H
#define PAXENGINE3_VIEWPORTFACTORY_H

#include <memory>
#include <paxcore/rendering/Viewport.h>

namespace PAX {
    class ViewportFactory {
    public:
        virtual std::shared_ptr<Viewport> create() = 0;
        virtual std::shared_ptr<Viewport> create(int x, int y, int w, int h, Viewport::ResizePolicy resizePolicy) = 0;
    };
}

#endif //PAXENGINE3_VIEWPORTFACTORY_H