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
		int m_winw = 960;
		int m_winh = 540;

	public:
		Window();
		~Window();
		SDL_Window* getWindow();
		std::shared_ptr<Core> getCore();
		SDL_Renderer* getRenderer();
		void initRenderer();
		int getWinW();
		int getWinH();
		void update();
	};
}