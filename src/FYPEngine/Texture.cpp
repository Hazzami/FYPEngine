#include "Texture.h"
#include "Entity.h"
#include "Core.h"
#include "Window.h"
#include "iostream"

namespace FYPEngine
{
	void Texture::initialize()
	{

		m_x = 0;
		m_y = 0;
		m_width = 100;
		m_height = 100;
		m_path = "build/Debug/default.bmp";

	}

	void Texture::render()
	{
		SDL_Rect dstrect = { 5, 5, 100, 100};
		SDL_RenderCopyEx(getEntity()->getCore()->getWindow()->getRenderer(), m_texture, NULL, &dstrect, m_angle, m_center, m_flip);
	}

	void Texture::setTexture()
	{
		m_texture = SDL_CreateTextureFromSurface(getEntity()->getCore()->getWindow()->getRenderer(), m_image);
	}

	void Texture::loadImage(const char* _path)
	{
		m_path = _path;
		m_image = SDL_LoadBMP(m_path);
		if (!m_image)
		{
			std::cout << "Trying to load image from: " << m_path << std::endl;
			return;
		}
		setTexture();
	}

	const char* Texture::getPath()
	{
		return m_path;
	}

	std::shared_ptr<Entity> Texture::getEntity()
	{
		return m_entity.lock();
	}

	void Texture::setBox(int _x, int _y, int _w, int _h)
	{
		m_x = _x;
		m_y = _y;
		m_width = _w;
		m_height = _h;
	}

}