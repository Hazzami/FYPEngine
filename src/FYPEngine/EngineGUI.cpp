#include "EngineGUI.h"
#include "EngineGUIElement.h"
#include "EngineGUIFrame.h"

namespace FYPEngine
{
	void EngineGUI::addFrame()
	{
		std::shared_ptr<EngineGUIFrame> frame = std::make_shared<EngineGUIFrame>();
		m_frame = frame;
		frame->m_GUI = m_self;
	}

	void EngineGUI::setFrameColour(int _r, int _g, int _b, int _a)
	{
		m_frame->m_colourRGBA[0] = _r;
		m_frame->m_colourRGBA[1] = _g;
		m_frame->m_colourRGBA[2] = _b;
		m_frame->m_colourRGBA[3] = _a;
	}

	void EngineGUI::update()
	{
		for (int i = 0; i < m_elements.size(); i++)
		{
			m_elements.at(i)->update();
		}
	}

	std::shared_ptr<EngineGUIElement> EngineGUI::addElement()
	{
		std::shared_ptr<EngineGUIElement> _element = std::make_shared<EngineGUIElement>();
		_element->m_GUI = m_self;
		_element->m_self = _element;
		m_elements.push_back(_element);
		return _element;
	}

	std::vector<std::shared_ptr<EngineGUIElement>> EngineGUI::getElements()
	{
		return m_elements;
	}

	std::shared_ptr<Core> EngineGUI::getCore()
	{
		return m_core.lock();
	}

	std::shared_ptr<EngineGUIFrame> EngineGUI::getFrame()
	{
		return m_frame;
	}

}