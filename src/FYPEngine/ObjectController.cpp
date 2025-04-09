#include "ObjectController.h"
#include "EngineGUIObject.h"
#include "EngineGUIElement.h"
#include "EngineGUI.h"
#include "Core.h"
#include "Keyboard.h"
#include <iostream>

namespace FYPEngine
{
	void ObjectController::affect()
	{
		if (getObject()->getElement()->getGUI()->getCore()->getKeyboard()->isKey(SDLK_d))
		{
			getObject()->setX(getObject()->getX() + 1);
			getObject()->getTexture()->flipTexture(0);
		}

		if (getObject()->getElement()->getGUI()->getCore()->getKeyboard()->isKey(SDLK_a))
		{
			getObject()->setX(getObject()->getX() - 1);
			getObject()->getTexture()->flipTexture(1);
		}

		if (getObject()->getY() + getObject()->getHeight() < getObject()->getFloor() - 3)
		{
			getObject()->setY(getObject()->getY() + 1);
		}

		if (getObject()->getElement()->getGUI()->getCore()->getKeyboard()->isKeyPressed(SDLK_SPACE) && m_jumping == false)
		{
			m_jumping = true;
		}

		else if (getObject()->getY() + getObject()->getHeight() >= getObject()->getFloor() - 3)
		{
			m_jumping = false;
		}

		if (m_jumping)
		{
			m_frameCount++;
			if (m_frameCount % 15 ==0)
			{
				m_jumpCoolDown--;
			}

			if (getObject()->getY() - m_jumpCoolDown +getObject()->getHeight() > getObject()->getFloor() - 3)
			{
				m_jumping = false;
				m_jumpCoolDown = 5;
				m_frameCount = 0;
			}

			if (m_frameCount > 160)
			{
				m_jumping = false;
				m_jumpCoolDown = 5;
				m_frameCount = 0;
			}

			else
			{
				getObject()->setY(getObject()->getY() - m_jumpCoolDown);
			}

			std::cout << getObject()->getY() << std::endl;

		}
		
	}
}