#include "EngineGUIElement.h"
#include "EngineGUI.h"
#include "Core.h"
#include "Window.h"
#include "EngineGUIContent.h"

#include <iostream>

namespace FYPEngine
{
    void EngineGUIElement::render()
    {
        SDL_SetRenderDrawColor(getGUI()->getCore()->getWindow()->getRenderer(), m_colourRGBA[0], m_colourRGBA[1], m_colourRGBA[2], m_colourRGBA[3]);

        SDL_Rect rect1 = { m_x + 18, m_y, m_width - 36, m_height };
        SDL_Rect rect2 = { m_x, m_y + 18, m_width, m_height - 36 };
        drawCircle(m_x + 18, m_y + 18, 18);
        drawCircle(m_x + m_width - 18, m_y + 18, 18);
        drawCircle(m_x + 18, m_y + m_height - 18, 18);
        drawCircle(m_x + m_width - 18, m_y + m_height - 18, 18);
        SDL_RenderFillRect(getGUI()->getCore()->getWindow()->getRenderer(), &rect1);
        SDL_RenderFillRect(getGUI()->getCore()->getWindow()->getRenderer(), &rect2);

        for (int i = 0; i < m_content.size(); i++)
        {
            if (m_content.at(i)->getDeleteMe())
            {
                m_content.erase(m_content.begin() + i);
                --i;
            }
            else
            {
                m_content.at(i)->render();
            }
        }
    }

    void EngineGUIElement::drawCircle(int _x, int _y, int _r) {
        for (int w = 0; w < _r * 2; w++) {
            for (int h = 0; h < _r * 2; h++) {
                int dx = _r - w;
                int dy = _r - h;
                if ((dx * dx + dy * dy) <= (_r * _r)) {
                    SDL_RenderDrawPoint(getGUI()->getCore()->getWindow()->getRenderer(), _x + dx, _y + dy);
                }
            }
        }
    }

    std::vector<std::shared_ptr<EngineGUIContent>> EngineGUIElement::getContent()
    {
        return m_content;
    }

    std::shared_ptr<EngineGUI> EngineGUIElement::getGUI()
    {
        return m_GUI.lock();
    }

    void EngineGUIElement::setBox(int _x, int _y, int _w, int _h)
    {
        m_x = _x;
        m_y = _y;
        m_width = _w;
        m_height = _h;
    }

    void EngineGUIElement::setColour(int _r, int _g, int _b, int _a)
    {
        m_colourRGBA[0] = _r;
        m_colourRGBA[1] = _g;
        m_colourRGBA[2] = _b;
        m_colourRGBA[3] = _a;
    }

    void EngineGUIElement::update()
    {
        for (int i = 0; i < m_content.size(); i++)
        {
            m_content.at(i)->update();
        }
    }
}
