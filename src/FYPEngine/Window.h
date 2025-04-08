#include <SDL2/SDL.h>
#include <memory>

namespace FYPEngine
{
	struct Core;

	struct Window
	{
	private:
		friend struct FYPEngine::Core;
		SDL_Window* m_raw;
		SDL_Renderer* m_renderer;
		std::weak_ptr<Core> m_core;

	public:
		Window();
		~Window();
		SDL_Window* getWindow();
		std::shared_ptr<Core> getCore();
		SDL_Renderer* getRenderer();
		void initRenderer();
	};
}