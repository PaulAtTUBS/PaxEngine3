//
// Created by Paul on 29.04.2017.
//

#include <typeindex>
#include "../../../include/core/entity/Entity.h"
#include "../../../include/lib/easylogging++.h"

namespace PAX {
    Entity::Entity() {
        OnParentChanged.add<EventService, &EventService::fire<EntityParentChangedEvent>>(&LocalEventService);
    }

    Entity::~Entity() {

    }

    Transform& Entity::getTransform() {
        return _transform;
    }

    void Entity::setParent(Entity *parent) {
        Entity *oldParent = _parent;//#PRANT

        _parent = parent;
        LOG(WARNING) << "Entity::setParent: event not implemented!";
        Transform *parentTransform = nullptr;
        if (_parent)
            parentTransform = &_parent->_transform;
        _transform.setParent(parentTransform);

        EntityParentChangedEvent e(this, oldParent, parent);
        OnParentChanged(e);
    }

    Entity* Entity::getParent() {
        return _parent;
    }

    const std::vector<Entity*>& Entity::getChildren() {
        return _children;
    }

    WorldLayer* Entity::getWorldLayer() {
        return _worldLayer;
    }
}