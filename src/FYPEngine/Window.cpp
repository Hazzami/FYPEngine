#include "Window.h"
#include "Core.h"
#include <stdexcept>

namespace FYPEngine
{
	Window::Window()
	{
		int winw = 960;
		int winh = 540;

		m_raw = SDL_CreateWindow("EngineDemo",
			SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
			winw, winh, SDL_WINDOW_RESIZABLE);

		if (!m_raw)
		{
			throw std::runtime_error("Failed to create window");
		}
	}

	Window::~Window()
	{
		SDL_DestroyWindow(m_raw);
		SDL_Quit();
	}

	SDL_Window* Window::getWindow()
	{
		return m_raw;
	}

	std::shared_ptr<Core> Window::getCore()
	{
		return m_core.lock();
	}

	SDL_Renderer* Window::getRenderer()
	{
		return m_renderer;
	}

	void Window::initRenderer()
	{
		m_renderer = SDL_CreateRenderer(m_raw, -1, 0);
	}
}