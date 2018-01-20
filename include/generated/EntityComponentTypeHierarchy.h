#ifndef PAXENGINE3_GENERATED_ENTITYCOMPONENTTYPEHIERARCHYCREATOR_H
#define PAXENGINE3_GENERATED_ENTITYCOMPONENTTYPEHIERARCHYCREATOR_H

#include <typeindex>
#include <utility/datastructures/TypeMap.h>

namespace PAX {
    class Entity;
    class EntityComponent;

    namespace Generated {
        class EntityComponentTypeHierarchy {
            friend class PAX::Entity;
            static TypeMap<void (*)(Entity*, EntityComponent*)> OnEntityComponentAttached;
            static TypeMap<void (*)(Entity*, EntityComponent*)> OnEntityComponentDetached;
            static TypeMap<bool> IsMultiple;

            static bool checkMultiplicity(const std::type_index& type, TypeMap<bool> &isTypeMultiple);
            static void createEntityComponentTypeHierarchy();

        public:
            static void initialize();
        };
    }
}

#endif