#include "EngineGUIButton.h"
#include "EngineGUIElement.h"
#include "EngineGUI.h"
#include "Core.h"
#include "Window.h"

namespace FYPEngine
{
	void EngineGUIButton::onInitialize()
	{
		setHeight(30);
		setWidth(50);
		setX(20);
		setY(20);
	}

	void EngineGUIButton::render()
	{
		SDL_SetRenderDrawColor(getElement()->getGUI()->getCore()->getWindow()->getRenderer(), getR(), getG(), getB(), getA());
		SDL_Rect button = { getX(), getY(), getWidth(), getHeight() };
		SDL_RenderFillRect(getElement()->getGUI()->getCore()->getWindow()->getRenderer(), &button);
	}

	void EngineGUIButton::onClick()
	{

	}

	void EngineGUIButton::update()
	{
		setCurrentColour();
	}

	std::shared_ptr<EngineGUIButton> EngineGUIButton::getButton()
	{
		return m_self.lock();
	}
}