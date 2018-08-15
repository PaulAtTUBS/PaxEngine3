//
// Created by Paul on 13.08.2018.
//

#include "../include/Plugin.h"

#include <core/Engine.h>

namespace PAX {
    namespace Physics {
        void Plugin::initialize(PAX::Engine &engine) {
            std::cout << "[PAX::Physics::Plugin::initialize]" << std::endl;
        }

        void Plugin::postInitialize(PAX::Engine &engine) {
            std::cout << "[PAX::Physics::Plugin::postInitialize]" << std::endl;
        }

        void Plugin::registerFactories(PAX::FactoryService &factoryService) {
            std::cout << "[PAX::Physics::Plugin::registerFactories]" << std::endl;
        }

        void Plugin::registerResourceLoaders(PAX::Resources &resources) {
            std::cout << "[PAX::Physics::Plugin::registerResourceLoaders]" << std::endl;
        }

        void Plugin::registerServices(PAX::Services &services) {
            std::cout << "[PAX::Physics::Plugin::registerServices]" << std::endl;
        }
    }
}