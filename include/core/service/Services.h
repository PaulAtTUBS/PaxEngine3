//
// Created by Paul on 04.10.2017.
//

#ifndef PAXENGINE3_SERVICES_H
#define PAXENGINE3_SERVICES_H

#include <core/io/resources/Resources.h>
#include <utility/datastructures/TypeMap.h>
#include <core/entity/EntityComponentService.h>

#include "core/rendering/RenderFactory.h"
#include "core/event/EventService.h"
#include "core/io/InputSystem.h"

#include "Paths.h"
#include "FactoryService.h"

namespace PAX {
    class Engine;

    class Services {
        friend class Engine;

        static Services* _instance;

        TypeMap<void*> _registeredServices;

        EntityComponentService _entityComponentService;
        EventService _eventService;
        FactoryService _factoryService;
        Resources _resources;

        std::shared_ptr<InputSystem> _inputSystem = nullptr;

        Paths _paths;

    protected:
        Services();
        ~Services();

        void initialize();

    public:
        template<typename Service>
        bool registerService(Service *service) {
            return _registeredServices.put<Service>(service);
        }

        template<typename Service>
        size_t unregisterService() {
            return _registeredServices.erase<Service>();
        }

        template<typename Service>
        Service* get() {
            if (_registeredServices.contains<Service>())
                return static_cast<Service*>(_registeredServices.get<Service>());
            return nullptr;
        }

        static Services& Instance();

        static InputSystem* GetInput();

        static Resources& GetResources();
        static FactoryService& GetFactory();
        static EntityComponentService& GetEntityComponentService();
        static EventService& GetEventService();

        static Paths& GetPaths();

        void update();
    };
}

#endif //PAXENGINE3_SERVICES_H
