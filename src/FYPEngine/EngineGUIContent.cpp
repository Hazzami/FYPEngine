#include "EngineGUIContent.h"
#include "EngineGUIElement.h"
#include "EngineGUI.h"
#include "Core.h"
#include "Mouse.h"

#include <iostream>

namespace FYPEngine
{
	bool EngineGUIContent::getDeleteMe()
	{
		return m_deleteMe;
	}

	void EngineGUIContent::setDeleteMe(bool _deleteMe)
	{
		m_deleteMe = _deleteMe;
	}

	bool EngineGUIContent::isClicked()
	{
		if (mouseOver() && getElement()->getGUI()->getCore()->getMouse()->isKeyPressed(SDL_BUTTON_LEFT))
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	bool EngineGUIContent::mouseOver()
	{
		bool rtn = false;
		rtn = (getElement()->getGUI()->getCore()->getMouse()->getMouseX() > m_x 
			&& getElement()->getGUI()->getCore()->getMouse()->getMouseX() < m_x + m_width 
			&& getElement()->getGUI()->getCore()->getMouse()->getMouseY() > m_y 
			&& getElement()->getGUI()->getCore()->getMouse()->getMouseY() < m_y + m_height);
		return rtn;
	}

	bool EngineGUIContent::isHeld()
	{
		if (mouseOver() && getElement()->getGUI()->getCore()->getMouse()->isKey(SDL_BUTTON_LEFT))
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	void EngineGUIContent::isBeingHeld()
	{
		if (mouseOver())
		{
			if (getElement()->getGUI()->getCore()->getMouse()->isKeyPressed(SDL_BUTTON_LEFT) && mouseOver())
			{
				m_targetHeld = true;
				m_isHeldCurrent = true;
			}

			else if (getElement()->getGUI()->getCore()->getMouse()->isKeyReleased(SDL_BUTTON_LEFT) && mouseOver())
			{
				m_targetHeld = false;
			}

			else if (!mouseOver())
			{
				m_targetHeld = false;
			}
		}

		else
		{
			m_targetHeld = false;
		}
	}


	std::shared_ptr<EngineGUIElement> EngineGUIContent::getElement()
	{
		return m_element.lock();
	}

	int EngineGUIContent::getX()
	{
		return m_x;
	}

	int EngineGUIContent::getY()
	{
		return m_y;
	}

	int EngineGUIContent::getWidth()
	{
		return m_width;
	}

	int EngineGUIContent::getHeight()
	{
		return m_height;
	}

	int EngineGUIContent::getR()
	{
		return m_currentColour[0];
	}

	int EngineGUIContent::getG()
	{
		return m_currentColour[1];

	}

	int EngineGUIContent::getB()
	{
		return m_currentColour[2];

	}

	int EngineGUIContent::getA()
	{
		return m_currentColour[3];
	}

	bool EngineGUIContent::getAttrib()
	{
		return m_attrib;
	}

	void EngineGUIContent::setAttrib(bool _attrib)
	{
		m_attrib = _attrib;
	}


	bool EngineGUIContent::getTargetHeld()
	{
		return m_targetHeld;
	}

	void EngineGUIContent::setTargetHeld(bool _held)
	{
		m_targetHeld = _held;
	}

	bool EngineGUIContent::getIsHeld()
	{
		return m_isHeldCurrent;
	}

	void EngineGUIContent::setIsHeld(bool _held)
	{
		m_isHeldCurrent = _held;
	}

	const char* EngineGUIContent::getPath()
	{
		return m_path;
	}

	void EngineGUIContent::setPath(const char* _path)
	{
		m_path = _path;
	}

	void EngineGUIContent::setCurrentColour()
	{
		if (mouseOver() && isClicked())
		{
			for (int i = 0; i < 4; i++)
			{
				m_currentColour[i] = m_bgColourClickedRGBA[i];
			}
		}
		else if (mouseOver() && !isClicked())
		{
			for (int i = 0; i < 4; i++)
			{
				m_currentColour[i] = m_bgColourHoverRGBA[i];
			}
		}
		else
		{
			for (int i = 0; i < 4; i++)
			{
				m_currentColour[i] = m_bgColourRGBA[i];
			}
		}
	}

	void EngineGUIContent::setX(int _x)
	{
		m_x = _x;
	}

	void EngineGUIContent::setY(int _y)
	{
		m_y = _y;
	}

	void EngineGUIContent::setWidth(int _w)
	{
		m_width = _w;
	}

	void EngineGUIContent::setHeight(int _h)
	{
		m_height = _h;
	}
}