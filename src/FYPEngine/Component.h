#pragma once
#include <memory>
#include <vector>

namespace FYPEngine
{
	struct Entity;

	struct Component
	{
	private:
		friend struct FYPEngine::Entity;
		std::weak_ptr<Entity> m_entity;

		void tick();
		void render();

	public:
		virtual void onInitialize();
		virtual void onTick();
		virtual void onRender();
		std::shared_ptr<Entity> getEntity();

		template <typename T>
		void find(std::vector<std::shared_ptr<T> >& _out);

		template <typename T>
		std::shared_ptr<T> getComponent();

	};



	template <typename T>
	void Component::find(std::vector<std::shared_ptr<T> >& _out)
	{
		getEntity()->getCore()->find<T>(_out);
	}

	template <typename T>
	std::shared_ptr<T> Component::getComponent()
	{
		return getEntity()->getComponent<T>();
	}

}