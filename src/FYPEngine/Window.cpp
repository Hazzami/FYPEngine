#include "Window.h"
#include "Core.h"
#include <stdexcept>

namespace FYPEngine
{
	Window::Window()
	{
		m_raw = SDL_CreateWindow("EngineDemo",
			SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
			m_winw, m_winh, NULL);

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

	int Window::getWinW()
	{
		return m_winw;
	}

	int Window::getWinH()
	{
		return m_winh;
	}

	void Window::update()
	{
		SDL_GetWindowSize(m_raw, &m_winw, &m_winh);
	}
}