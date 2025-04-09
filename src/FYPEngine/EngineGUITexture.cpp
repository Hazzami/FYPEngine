#include "EngineGUITexture.h"
#include "EngineGUIObject.h"
#include "EngineGUIElement.h"
#include "EngineGUITexture.h"
#include "EngineGUI.h"
#include "EngineGUIFrame.h"
#include "Core.h"
#include "Window.h"
#include "iostream"

namespace FYPEngine
{
	void EngineGUITexture::initialize()
	{

		m_x = 0;
		m_y = 0;
		m_width = getObject()->getElement()->getGUI()->getFrame()->getX() - 30;
		m_height = getObject()->getElement()->getGUI()->getFrame()->getX() - 30;
		m_path = "build/Debug/default.bmp";

	}

	void EngineGUITexture::render()
	{
		SDL_Rect dstrect = { m_x, m_y, m_width, m_width };
		SDL_RenderCopyEx(getObject()->getElement()->getGUI()->getCore()->getWindow()->getRenderer(), m_texture, NULL, &dstrect, m_angle, m_center, m_flip);
	}

	void EngineGUITexture::setTexture()
	{
		m_texture = SDL_CreateTextureFromSurface(getObject()->getElement()->getGUI()->getCore()->getWindow()->getRenderer(), m_image);
	}

	void EngineGUITexture::loadImage(const char* _path)
	{
		m_path = _path;
		m_image = SDL_LoadBMP(m_path);
		if (!m_image)
		{
			std::cout << "failed to load image from: " << m_path << std::endl;
			return;
		}
		setTexture();
	}

	const char* EngineGUITexture::getPath()
	{
		return m_path;
	}

	std::shared_ptr<EngineGUIObject> EngineGUITexture::getObject()
	{
		return m_object.lock();
	}

	void EngineGUITexture::setBox(int _x, int _y, int _w, int _h)
	{
		m_x = _x;
		m_y = _y;
		m_width = _w;
		m_height = _h;
	}

	void EngineGUITexture::flipTexture(int _dir)
	{
		if (_dir == 1)
		{
			m_flip = SDL_FLIP_HORIZONTAL;
		}

		else
		{
			m_flip = SDL_FLIP_NONE;
		}
	}

}