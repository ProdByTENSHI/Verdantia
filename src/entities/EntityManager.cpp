#include "entities/EntityManager.hpp"

#include <spdlog/spdlog.h>
#include <algorithm>

EntityManager::EntityManager() {
}

EntityManager::~EntityManager() {
    m_EntityIdLUT.clear();
    for (i32 i = 0; i < m_Entities.size(); i++) {
        delete m_Entities[i];
        m_Entities.erase(m_Entities.begin() + i);
    }
}

void EntityManager::DestroyEntity(u32 entityId) {
    if (!IsValidEntity(entityId)) {
        return;
    }
}

void EntityManager::UpdateEntities() {
}

void EntityManager::RenderEntities() {
}

void EntityManager::AfterEntitiesFinished() {
    // -- Deferred Deletion
    for (i32 i = 0; i < m_EntityDeletionBuffer.size(); i++) {
        std::swap(m_Entities[i], m_Entities.back());

        delete m_Entities.back();
        m_Entities.pop_back();
    }

    m_EntityDeletionBuffer.clear();
}

Entity *EntityManager::GetEntityById(u32 entityId) {
    if (!IsValidEntity(entityId)) {
        return nullptr;
    }

    return m_Entities[m_EntityIdLUT[entityId]];
}

bool EntityManager::IsValidEntity(u32 entityId) {
    if (entityId >= m_Entities.size()) {
        spdlog::error("Entity {} is not valid because it is out of bounds", entityId);
        return false;
    }

    // Check if Entity is planned for deletion
    if (m_EntityIdLUT.find(entityId) != m_EntityIdLUT.end()) {
        spdlog::error("Entity {} was destroyed and is not valid", entityId);
        return false;
    }

    return true;
}
