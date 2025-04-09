#include "EngineGUIAttrib.h"
#include "EngineGUIElement.h"
#include "EngineGUI.h"
#include "Core.h"
#include "Mouse.h"
#include "Window.h"
#include "EngineGUIFrame.h"
#include "EngineGUIObject.h"
#include "ObjectController.h"
#include "CollisionBox.h"
#include <iostream>

namespace FYPEngine
{
	void EngineGUIAttrib::onInitialize(int _x, int _y, int _w, int _h, const char* _text, int _type)
	{
		m_type = _type;
		setAttrib(true);
		setX(_x);
		setY(_y);
		setWidth(_w);
		setHeight(_h);
		setPath(_text);

		m_initX = _x;
		m_initY = _y;
		m_initW = _w;
		m_initH = _h;

		TTF_Font* font = TTF_OpenFont("Assets/Lexend.ttf",20);
		if (!font) 
		{
			std::cout << "Failed to load font: " << TTF_GetError() << "\n";
			SDL_DestroyRenderer(getElement()->getGUI()->getCore()->getWindow()->getRenderer());
			SDL_DestroyWindow(getElement()->getGUI()->getCore()->getWindow()->getWindow());
			TTF_Quit();
			SDL_Quit();
		}
		m_font = font;
		
		SDL_Color textColour = { 255, 255, 255 };
		m_fontColour = textColour;

		SDL_Surface* textSurface = TTF_RenderText_Solid(m_font, _text, m_fontColour);
		if (!textSurface) 
		{
			std::cerr << "Text render error: " << TTF_GetError() << "\n";
			TTF_CloseFont(font);
			SDL_DestroyRenderer(getElement()->getGUI()->getCore()->getWindow()->getRenderer());
			SDL_DestroyWindow(getElement()->getGUI()->getCore()->getWindow()->getWindow());
			TTF_Quit();
			SDL_Quit();
		}
		m_surface = textSurface;

		SDL_Texture* textTexture = SDL_CreateTextureFromSurface(getElement()->getGUI()->getCore()->getWindow()->getRenderer(), m_surface);
		SDL_FreeSurface(m_surface);
		if (!textTexture) {
			std::cerr << "CreateTexture Error: " << SDL_GetError() << "\n";
			TTF_CloseFont(font);
			SDL_DestroyRenderer(getElement()->getGUI()->getCore()->getWindow()->getRenderer());
			SDL_DestroyWindow(getElement()->getGUI()->getCore()->getWindow()->getWindow());
			TTF_Quit();
			SDL_Quit();
		}
		m_texture = textTexture;

		int width, height;
		SDL_QueryTexture(m_texture, NULL, NULL, &width, &height);
		setWidth(width);
		setHeight(height);
		isBeingHeld();
	}

	void EngineGUIAttrib::render()
	{

		SDL_Rect dstRect = { getX(), getY(), getWidth(), getHeight()};
		SDL_RenderCopy(getElement()->getGUI()->getCore()->getWindow()->getRenderer(), m_texture, NULL, &dstRect);
	}

	void EngineGUIAttrib::update()
	{
		if (mouseOver())
		{
			isBeingHeld();
			if (isHeld() && getTargetHeld())
			{
				setX(getElement()->getGUI()->getCore()->getMouse()->getMouseX() - (getWidth() / 2));
				setY(getElement()->getGUI()->getCore()->getMouse()->getMouseY() - (getHeight() / 2));
			}

			else if (!(getX() > getElement()->getGUI()->getCore()->getEngineGUI()->getFrame()->getX()
				&& getX() + getWidth() < getElement()->getGUI()->getCore()->getEngineGUI()->getFrame()->getX() + getElement()->getGUI()->getCore()->getEngineGUI()->getFrame()->getW()
				&& getY() > getElement()->getGUI()->getCore()->getEngineGUI()->getFrame()->getY()
				&& getY() + getHeight() < getElement()->getGUI()->getCore()->getEngineGUI()->getFrame()->getY() + getElement()->getGUI()->getCore()->getEngineGUI()->getFrame()->getH())
				&& m_released)
			{
				setDeleteMe(true);
				m_spawn--;
			}

			else if (getElement()->getGUI()->getCore()->getMouse()->isKeyReleased(SDL_BUTTON_LEFT) && m_spawn < 1 && getIsHeld() && collisionCheck())
			{
				getElement()->addContent<EngineGUIAttrib>(m_initX, m_initY, m_initW, m_initH, getPath(), m_type);
				m_released = true;
				setIsHeld(false);
				m_spawn++;

				switch (m_type)
				{
				case 0:
					m_temp->addAttribute<CollisionBox>();
					break;

				case 1:
					m_temp->addAttribute<ObjectController>();
					break;

				case 2:
					m_temp->addAttribute<CollisionBox>();
					m_temp->setRigid(true);
					break;
				}

				setDeleteMe(true);
				m_spawn--;
			}

			else if (getElement()->getGUI()->getCore()->getMouse()->isKeyReleased(SDL_BUTTON_LEFT) && m_spawn < 1 && getIsHeld())
			{
				getElement()->addContent<EngineGUIAttrib>(m_initX, m_initY, m_initW, m_initH, getPath(), m_type);
				m_released = true;
				setIsHeld(false);
				m_spawn++;
				setDeleteMe(true);
				m_spawn--;
			}
		}

		else if (!(getX() > getElement()->getGUI()->getCore()->getEngineGUI()->getFrame()->getX()
			&& getX() + getWidth() < getElement()->getGUI()->getCore()->getEngineGUI()->getFrame()->getX() + getElement()->getGUI()->getCore()->getEngineGUI()->getFrame()->getW()
			&& getY() > getElement()->getGUI()->getCore()->getEngineGUI()->getFrame()->getY()
			&& getY() + getHeight() < getElement()->getGUI()->getCore()->getEngineGUI()->getFrame()->getY() + getElement()->getGUI()->getCore()->getEngineGUI()->getFrame()->getH())
			&& m_released)
		{
			setDeleteMe(true);
			m_spawn--;
		}

		

	}
	std::shared_ptr<EngineGUIAttrib> EngineGUIAttrib::getAttrib()
	{
		return m_self.lock();
	}

	bool EngineGUIAttrib::collisionCheck()
	{
		bool rtn = false;

		for (int i = 0; i < getElement()->getGUI()->getElements().size(); i++)
		{
			for (int x = 0; x < getElement()->getGUI()->getElements().at(i)->getContent().size(); x++)
			{
				if (getElement()->getGUI()->getElements().at(i)->getContent().at(x)->getAttrib() == false)
				{
					if (getX() + getWidth() < getElement()->getGUI()->getElements().at(i)->getContent().at(x)->getX())
					{
						
					}
					else if (getX() > getElement()->getGUI()->getElements().at(i)->getContent().at(x)->getX() + getElement()->getGUI()->getElements().at(i)->getContent().at(x)->getWidth())
					{
						
					}
					else if (getY() + getHeight() < getElement()->getGUI()->getElements().at(i)->getContent().at(x)->getY())
					{
						
					}
					else if (getY() > getElement()->getGUI()->getElements().at(i)->getContent().at(x)->getY() + getElement()->getGUI()->getElements().at(i)->getContent().at(x)->getHeight())
					{
					
					}
					else
					{
						rtn = true;
						setTemp(std::dynamic_pointer_cast<EngineGUIObject>(getElement()->getGUI()->getElements().at(i)->getContent().at(x)));
					}
				}
			}
		}
		return rtn;
	}

	std::shared_ptr<EngineGUIObject> EngineGUIAttrib::setTemp(std::shared_ptr<EngineGUIObject> _temp)
	{
		m_temp = _temp;
		return m_temp;
	}

}