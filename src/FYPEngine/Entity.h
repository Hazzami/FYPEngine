#include <memory>
#include <vector>
#include "Texture.h"

namespace FYPEngine
{
	struct Core;
	struct Component;

	struct Entity
	{
	private:
		friend struct FYPEngine::Core;
		std::vector<std::shared_ptr<Component>> m_components;
		std::weak_ptr<Core> m_core;
		std::weak_ptr<Entity> m_self;
		bool m_alive;
		std::shared_ptr<Texture> m_texture;


		void tick();
		void render();

	public:
		void setTexture(const char* _path);

		std::shared_ptr<Core> getCore();

		std::shared_ptr<Texture> Entity::getTexture();

		template<typename T>
		std::shared_ptr<T> addComponent();

		template <typename T>
		std::shared_ptr<T> getComponent();
	};



	template<typename T>
	std::shared_ptr<T> Entity::addComponent()
	{
		std::shared_ptr<T> rtn = std::make_shared<T>();
		rtn->m_entity = m_self;
		rtn->onInitialize();
		m_components.push_back(rtn);

		return rtn;
	}

	template <typename T>
	std::shared_ptr<T> Entity::getComponent()
	{
		for (size_t ci = 0; ci < m_components.size(); ++ci)
		{
			std::shared_ptr<T> rtn = std::dynamic_pointer_cast<T>(m_components.at(ci));

			if (rtn) return rtn;
		}

		throw std::runtime_error("Failed to find component");
	}
}