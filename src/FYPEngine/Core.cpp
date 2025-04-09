#include "Core.h"
#include "Entity.h"
#include "Window.h"
#include "iostream"
#include "EngineGUI.h"
#include "EngineGUIElement.h"
#include "EngineGUIFrame.h"
#include "Keyboard.h"
#include "Mouse.h"
#include "EngineGUIButton.h"
#include "EngineGUIObject.h"
#include "EngineGUIAttrib.h"

#include <iostream>

namespace FYPEngine
{
	std::shared_ptr<Core> Core::initialize()
	{
		if (SDL_Init(SDL_INIT_VIDEO) != 0)
		{
			std::cerr << "SDL_Init failed: " << SDL_GetError() << std::endl;
			return nullptr;
		}

		if (TTF_Init() == -1)
		{
			std::cerr << "TTF_Init failed: " << TTF_GetError() << std::endl;
			return nullptr;
		}

		std::shared_ptr<Core> rtn = std::make_shared<Core>();
		rtn->m_self = rtn;
		std::shared_ptr<Window> wind = std::make_shared<Window>();
		wind->m_core = rtn;
		wind->initRenderer();
		rtn->m_window = wind;
		rtn->m_running = true;

		std::shared_ptr<Keyboard> key = std::make_shared<Keyboard>();
		rtn->m_keyboard = key;
		std::shared_ptr<Mouse> mouse = std::make_shared<Mouse>();
		rtn->m_mouse = mouse;

		std::shared_ptr<EngineGUI> EGUI = std::make_shared<EngineGUI>();
		EGUI->m_core = rtn;
		EGUI->m_self = EGUI;
		EGUI->addFrame();
		EGUI->setFrameColour(50, 50, 50, 255);
		rtn->m_engineGUI = EGUI;
		rtn->m_engineGUI->addElement();
		rtn->m_engineGUI->getElements()[0]->setBox(10, 70, 200, rtn->m_window->getWinH() - 210);
		rtn->m_engineGUI->getElements()[0]->setColour(100, 100, 120, 255);
		rtn->m_engineGUI->getElements()[0]->addContent<EngineGUIObject>(20, 80, 0, 0, "Assets/penj.bmp",0);
		rtn->m_engineGUI->getElements()[0]->addContent<EngineGUIObject>(110, 80, 0, 0, "Assets/box.bmp",0);
		rtn->m_engineGUI->getElements()[0]->addContent<EngineGUIObject>(20, 170, 0, 0, "Assets/platform.bmp",0);
		rtn->m_engineGUI->addElement();
		rtn->m_engineGUI->getElements()[1]->setBox(10, 10, rtn->m_window->getWinW() - 10, 50);
		rtn->m_engineGUI->getElements()[1]->setColour(100, 100, 120, 255);
		rtn->m_engineGUI->addElement();
		rtn->m_engineGUI->getElements()[2]->setBox(10, rtn->m_window->getWinH() - 130, rtn->m_window->getWinW() - 20, 120);
		rtn->m_engineGUI->getElements()[2]->setColour(100, 100, 120, 255);
		rtn->m_engineGUI->addElement();
		rtn->m_engineGUI->getElements()[3]->setBox(rtn->m_window->getWinW() - 200 - 10, 70, 200, rtn->m_window->getWinH() - 210);
		rtn->m_engineGUI->getElements()[3]->setColour(100, 100, 120, 255);
		rtn->m_engineGUI->getElements()[3]->addContent<EngineGUIAttrib>(770, 170, 0, 0, "Collision", 0);
		rtn->m_engineGUI->getElements()[3]->addContent<EngineGUIAttrib>(770, 200, 0, 0, "Player Controls", 1);
		rtn->m_engineGUI->getElements()[3]->addContent<EngineGUIAttrib>(770, 230, 0, 0, "Platform", 2);

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

				if (event.type == SDL_KEYDOWN)
				{
					m_keyboard->pressedKeys.push_back(event.key.keysym.sym);
					m_keyboard->keys.push_back(event.key.keysym.sym);
				}

				if (event.type == SDL_KEYUP)
				{
					m_keyboard->releasedKeys.push_back(event.key.keysym.sym);
					for (int i = 0; i < m_keyboard->keys.size(); ++i)
					{
						if (m_keyboard->keys[i] == event.key.keysym.sym)
						{
							m_keyboard->keys.erase(m_keyboard->keys.begin() + i);
							--i;
						}
					}
				}

				if (event.type == SDL_MOUSEBUTTONDOWN)
				{
					m_mouse->pressedKeys.push_back(event.button.button);
					m_mouse->keys.push_back(event.button.button);
				}

				if (event.type == SDL_MOUSEBUTTONUP)
				{
					m_mouse->releasedKeys.push_back(event.button.button);
					for (int i = 0; i < m_mouse->keys.size(); ++i)
					{
						if (m_mouse->keys[i] == event.button.button)
						{
							m_mouse->keys.erase(m_mouse->keys.begin() + i);
							--i;
						}
					}
				}
			}

			SDL_SetRenderDrawColor(m_window->getRenderer(), 150, 150, 255, 255);
			SDL_RenderClear(m_window->getRenderer());

			m_mouse->update();
			m_engineGUI->update();

			m_window->update();

			for (int i = 0; i < m_entities.size(); i++)
			{
				m_entities.at(i)->getTexture()->render();
			}

			m_engineGUI->getElements()[0]->setBox(10, 70, m_window->getWinW() / 5, m_window->getWinH() - (m_window->getWinH() / 4) - 90);
			m_engineGUI->getElements()[1]->setBox(10, 10, m_window->getWinW() - 20, 50);
			m_engineGUI->getElements()[2]->setBox(10, m_window->getWinH() - (m_window->getWinH() / 4) - 10, m_window->getWinW() - 20, m_window->getWinH() / 4);
			m_engineGUI->getElements()[3]->setBox(m_window->getWinW() - (m_window->getWinW() / 5) - 10, 70, m_window->getWinW() / 5, m_window->getWinH() - (m_window->getWinH() / 4) - 90);

			m_engineGUI->m_frame->setBox(m_window->getWinW() / 5 + 20, 70, m_window->getWinW() - (2 * (m_window->getWinW() / 5)) - 40, m_window->getWinH() - 70 - (m_window->getWinH() / 4) - 20);
			m_engineGUI->m_frame->render();

			for (int i = 0; i < m_engineGUI->getElements().size(); i++)
			{
				m_engineGUI->getElements().at(i)->render();
			}

			SDL_RenderPresent(m_window->getRenderer());
			m_keyboard->pressedKeys.clear();
			m_keyboard->releasedKeys.clear();
			m_mouse->pressedKeys.clear();
			m_mouse->releasedKeys.clear();
		}
	}

	std::shared_ptr<Keyboard> Core::getKeyboard()
	{
		return m_keyboard;
	}

	std::shared_ptr<Mouse> Core::getMouse()
	{
		return m_mouse;
	}

	std::shared_ptr<EngineGUI> Core::getEngineGUI()
	{
		return m_engineGUI;
	}
}