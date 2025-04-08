#include "Entity.h"
#include "Component.h"
#include "Texture.h"

namespace FYPEngine
{

	void Entity::tick()
	{
		for (size_t ci = 0; ci < m_components.size(); ++ci)
		{
			m_components.at(ci)->tick();
		}
	}

	void Entity::render()
	{
		for (size_t ci = 0; ci < m_components.size(); ++ci)
		{
			m_components.at(ci)->render();
		}
	}

	std::shared_ptr<Core> Entity::getCore()
	{
		return m_core.lock();
	}

	void Entity::setTexture(const char* _path)
	{
		std::shared_ptr<Texture> tex = std::make_shared<Texture>();
		tex->m_entity = m_self;
		tex->initialize();
		tex->loadImage(_path);
		m_texture = tex;
	}

	std::shared_ptr<Texture> Entity::getTexture()
	{
		return m_texture;
	}
}