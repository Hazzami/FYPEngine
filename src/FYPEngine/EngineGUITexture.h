#pragma once
#include <string>
#include <SDL2/SDL.h>
#include <memory>

namespace FYPEngine
{
	struct EngineGUIObject;


	struct EngineGUITexture
	{
	private:
		friend struct EngineGUIObject;
		const char* m_path;
		SDL_Surface* m_image;
		SDL_Texture* m_texture;
		std::weak_ptr<EngineGUIObject> m_object;
		int m_width;
		int m_height;
		int m_x;
		int m_y;
		double m_angle;
		SDL_Point* m_center = nullptr;
		SDL_RendererFlip m_flip = SDL_FLIP_NONE;

	public:
		void initialize();
		void render();
		void setTexture();
		void loadImage(const char* _path);
		const char* getPath();
		void setBox(int _x, int _y, int _w, int _h);
		std::shared_ptr<EngineGUIObject> getObject();
		void flipTexture(int _dir);
	};
}
