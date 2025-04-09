#include "EngineGUIContent.h"
#include <SDL2/SDL.h>
#include <SDL_ttf/SDL_ttf.h>
#include <memory>

namespace FYPEngine
{
	struct EngineGUIElement;
	struct EngineGUIObject;

	struct EngineGUIAttrib : EngineGUIContent
	{
	private:
		friend struct EngineGUIElement;
		int m_initX;
		int m_initY;
		int m_initW;
		int m_initH;
		std::weak_ptr<EngineGUIAttrib> m_self;
		TTF_Font* m_font = nullptr;
		SDL_Color m_fontColour;
		SDL_Surface* m_surface;
		SDL_Texture* m_texture;
		const char* text;
		bool m_released;
		int m_spawn = 0;
		std::shared_ptr<EngineGUIObject> m_temp;
		int m_type;

	public:
		void onInitialize(int _x, int _y, int _w, int _h, const char* _text, int _type);
		void render();
		void update();
		std::shared_ptr<EngineGUIAttrib> getAttrib();
		bool collisionCheck();
		std::shared_ptr<EngineGUIObject> setTemp(std::shared_ptr<EngineGUIObject> _temp);
	};

}


