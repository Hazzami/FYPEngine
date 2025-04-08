#include "memory"
#include <vector>
#include <SDL2/SDL.h>


namespace FYPEngine
{
	struct Entity;
	struct Window;

	struct Core
	{
	private:
		std::vector<std::shared_ptr<Entity>> m_entities;
		bool m_running;
		std::weak_ptr<Core> m_self;
		std::shared_ptr<Window> m_window;

	public:
		static std::shared_ptr<Core> initialize();
		std::shared_ptr<Entity> addEntity();
		std::shared_ptr<Window> getWindow();
		void start();
	};
}