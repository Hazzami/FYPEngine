#include "EngineGUIContent.h"
#include <SDL2/SDL.h>
#include <memory>

namespace FYPEngine
{
	struct EngineGUIElement;

	struct EngineGUIButton : EngineGUIContent
	{
	private:
		friend struct EngineGUIElement;
		std::weak_ptr<EngineGUIButton> m_self;
	public:
		void onInitialize();
		void render();
		void onClick();
		void update();
		std::shared_ptr<EngineGUIButton>getButton();
	};
}