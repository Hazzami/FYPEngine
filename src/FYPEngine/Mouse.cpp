#include "Mouse.h"
#include "Core.h"
#include "Window.h"

namespace FYPEngine
{
	bool Mouse::isKey(int key)
	{
		for (int i = 0; i < keys.size(); ++i)
		{
			if (keys[i] == key)
			{
				return true;
			}
		}
		return false;
	}

	bool Mouse::isKeyPressed(int key)
	{
		for (int i = 0; i < pressedKeys.size(); ++i)
		{
			if (pressedKeys[i] == key)
			{
				return true;
			}
		}
		return false;
	}

	bool Mouse::isKeyReleased(int key)
	{
		for (int i = 0; i < releasedKeys.size(); ++i)
		{
			if (releasedKeys[i] == key)
			{
				return true;
			}
		}
		return false;
	}

	void Mouse::update()
	{
		SDL_GetMouseState(&m_x, &m_y);
	}

	int Mouse::getMouseX()
	{
		return m_x;
	}

	int Mouse::getMouseY()
	{
		return m_y;
	}

	void Mouse::setMouse(int _x, int _y)
	{
		SDL_WarpMouseInWindow(getCore()->getWindow()->getWindow(), _x, _y);
	}

	std::shared_ptr<Core> Mouse::getCore()
	{
		return m_core.lock();
	}
}