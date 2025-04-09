#include "EngineGUIObject.h"
#include "EngineGUIElement.h"
#include "EngineGUI.h"
#include "Core.h"
#include "Window.h"
#include "Mouse.h"
#include "EngineGUIFrame.h"
#include "Attribute.h"

namespace FYPEngine
{
	void EngineGUIObject::onInitialize(int _x, int _y, int _w, int _h, const char* _path, int _type)
	{
		setX(_x);
		setY(_y);
		setHeight(getElement()->getGUI()->getCore()->getWindow()->getWinH() / 5 - 30);
		setWidth(getElement()->getGUI()->getCore()->getWindow()->getWinH() / 5 - 30);
		setPath(_path);

		m_initX = getX();
		m_initY = getY();
		m_initW = getWidth();
		m_initH = getHeight();

		std::shared_ptr<EngineGUITexture> tex = std::make_shared<EngineGUITexture>();
		tex->m_object = getObject();
		tex->initialize();
		m_texture = tex;
		m_texture->loadImage(_path);
	}

	void EngineGUIObject::render()
	{
		m_texture->setBox(getX(), getY(), getWidth(), getHeight());
		m_texture->render();
	}

	void EngineGUIObject::update()
	{
		m_texture->setBox(getX(), getY(), getElement()->getGUI()->getFrame()->getX() - 30, getElement()->getGUI()->getFrame()->getX() - 30);
		for (int i = 0; i < m_attributes.size(); i++)
		{
			m_attributes.at(i)->affect();
		}

		if (mouseOver())
		{
			isBeingHeld();
			if (isHeld() && getTargetHeld())
			{
				if (getElement()->getGUI()->getCore()->getMouse()->isKey(SDL_BUTTON_RIGHT) && getWidth() > 10)
				{
					setWidth(getWidth() - 1);
					setHeight(getHeight() - 1);

				}
				else if (getElement()->getGUI()->getCore()->getMouse()->isKey(SDL_BUTTON_MIDDLE))
				{
					setWidth(getWidth() + 1);
					setHeight(getHeight() + 1);
				}

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

			else if (getElement()->getGUI()->getCore()->getMouse()->isKeyReleased(SDL_BUTTON_LEFT) && m_spawn < 1 && getIsHeld())
			{
				getElement()->addContent<EngineGUIObject>(m_initX, m_initY, m_initW, m_initH, getPath(),0);
				m_released = true;
				setIsHeld(false);
				m_spawn++;
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

	std::shared_ptr<EngineGUIObject> EngineGUIObject::getObject()
	{
		return m_self.lock();
	}

	std::shared_ptr<EngineGUITexture> EngineGUIObject::getTexture()
	{
		return m_texture;
	}

	int EngineGUIObject::getFloor()
	{
		return getElement()->getGUI()->getFrame()->getY() + getElement()->getGUI()->getFrame()->getH();
	}

	std::vector<std::shared_ptr<Attribute>> EngineGUIObject::getAttributes()
	{
		return m_attributes;
	}

	bool EngineGUIObject::getRigid()
	{
		return m_rigid;
	}

	void EngineGUIObject::setRigid(bool _r)
	{
		m_rigid = _r;
	}
}