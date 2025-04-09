#include "EngineGUIFrame.h"
#include "EngineGUI.h"
#include "Core.h"
#include "Window.h"

namespace FYPEngine
{
	void EngineGUIFrame::render()
	{
		SDL_Rect m_rectL = { 0, 0, m_holeX, getGUI()->getCore()->getWindow()->getWinH() };
		SDL_Rect m_rectT = { 0,0,getGUI()->getCore()->getWindow()->getWinW(), m_holeY };
		SDL_Rect m_rectR = { m_holeX + m_holeW, 0, m_holeX, getGUI()->getCore()->getWindow()->getWinH() };
		SDL_Rect m_rectB = { 0, m_holeY + m_holeH, getGUI()->getCore()->getWindow()->getWinW(), getGUI()->getCore()->getWindow()->getWinH() - (m_holeY + m_holeH) };
		
		SDL_SetRenderDrawColor(getGUI()->getCore()->getWindow()->getRenderer(), m_colourRGBA[0], m_colourRGBA[1], m_colourRGBA[2], m_colourRGBA[3]);
		SDL_RenderFillRect(getGUI()->getCore()->getWindow()->getRenderer(), &m_rectL);
		SDL_RenderFillRect(getGUI()->getCore()->getWindow()->getRenderer(), &m_rectT);
		SDL_RenderFillRect(getGUI()->getCore()->getWindow()->getRenderer(), &m_rectR);
		SDL_RenderFillRect(getGUI()->getCore()->getWindow()->getRenderer(), &m_rectB);
	}

	void EngineGUIFrame::setBox(int _x, int _y, int _w, int _h)
	{
		m_holeX = _x;
		m_holeY = _y;
		m_holeW = _w;
		m_holeH = _h;
	}

	std::shared_ptr<EngineGUI> EngineGUIFrame::getGUI()
	{
		return m_GUI.lock();
	}

	int EngineGUIFrame::getX()
	{
		return m_holeX;
	}

	int EngineGUIFrame::getY()
	{
		return m_holeY;
	}

	int EngineGUIFrame::getW()
	{
		return m_holeW;
	}

	int EngineGUIFrame::getH()
	{
		return m_holeH;
	}
}