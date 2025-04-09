#pragma once
#include <memory>

namespace FYPEngine
{
	struct EngineGUIElement;

	struct EngineGUIContent
	{
	private:
		friend struct EngineGUIElement;
		int m_x;
		int m_y;
		int m_width;
		int m_height;
		std::weak_ptr<EngineGUIElement> m_element;
		int m_bgColourRGBA[4] = { 0,255,0,255 };
		int m_bgColourHoverRGBA[4] = { 255,255,255,255 };
		int m_bgColourClickedRGBA[4] = { 255,0,0,255 };
		int m_textColourRGBA[4];
		int m_currentColour[4];
		bool m_targetHeld = false;
		bool m_isHeldCurrent = false;
		const char* m_path;
		bool m_deleteMe = false;
		bool m_attrib = false;

	public:
		virtual void onInitialize() {}
		virtual void render() {}
		virtual void onClick(){}
		virtual void update() {}
		bool getDeleteMe();
		void setDeleteMe(bool _deleteMe);
		bool isClicked();
		bool mouseOver();
		bool isHeld();
		void isBeingHeld();
		std::shared_ptr<EngineGUIElement> getElement();
		int getX();
		int getY();
		int getWidth();
		int getHeight();
		int getR();
		int getG();
		int getB();
		int getA();
		bool getAttrib();
		void setAttrib(bool _attrib);
		bool getTargetHeld();
		void setTargetHeld(bool _held);
		bool getIsHeld();
		void setIsHeld(bool _held);
		const char* getPath();
		void setPath(const char* _path);
		void setCurrentColour();
		void setX(int _x);
		void setY(int _y);
		void setWidth(int _w);
		void setHeight(int _h);
	};

}