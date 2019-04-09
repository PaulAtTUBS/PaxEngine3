//
// Created by Bittner on 08.04.2019.
//

#ifndef PAXENGINE3_RENDERPASSFACTORY_H
#define PAXENGINE3_RENDERPASSFACTORY_H

#include <memory>
#include "RenderPass.h"

namespace PAX {
    class RenderPassFactory {
    public:
        virtual std::shared_ptr<RenderPass> create() = 0;
    };
}

#endif //PAXENGINE3_RENDERPASSFACTORY_H
