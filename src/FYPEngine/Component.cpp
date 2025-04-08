#include "Component.h"
#include "Entity.h"

namespace FYPEngine
{
	void Component::tick()
	{
		onTick();
	}

	void Component::render()
	{
		onRender();
	}

	void Component::onInitialize() {}	
	void Component::onTick() {}	
	void Component::onRender() {}

	std::shared_ptr<Entity> Component::getEntity()
	{
		return m_entity.lock();
	}
}