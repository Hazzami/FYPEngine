#include "Core.h"
#include "Entity.h"
#include "Window.h"
#include "iostream"

namespace FYPEngine
{
	std::shared_ptr<Core> Core::initialize()
	{
		if (SDL_Init(SDL_INIT_VIDEO) != 0)
		{
			std::cerr << "SDL_Init failed: " << SDL_GetError() << std::endl;
			return nullptr;
		}

		std::shared_ptr<Core> rtn = std::make_shared<Core>();
		rtn->m_self = rtn;
		std::shared_ptr<Window> wind = std::make_shared<Window>();
		wind->m_core = rtn;
		wind->initRenderer();
		rtn->m_window = wind;
		rtn->m_running = true;

		return rtn;
	}

	std::shared_ptr<Entity> Core::addEntity()
	{
		std::shared_ptr<Entity> rtn = std::make_shared<Entity>();
		rtn->m_self = rtn;
		rtn->m_core = m_self;
		m_entities.push_back(rtn);
		return rtn;
	}

	std::shared_ptr<Window> Core::getWindow()
	{
		return m_window;
	}

	void Core::start()
	{
		SDL_Event event;

		while (m_running)
		{
			while (SDL_PollEvent(&event))
			{
				if (event.type == SDL_QUIT)
				{
					m_running = false;
				}
			}

			//SDL_SetRenderDrawColor(m_window->getRenderer(), 0, 0, 0, 255);
			//SDL_RenderClear(m_window->getRenderer());

			for (int i = 0; i < m_entities.size(); i++)
			{
				m_entities.at(i)->getTexture()->render();
			}

			SDL_RenderPresent(m_window->getRenderer());
		}
	}
}