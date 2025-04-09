#include <vector>
#include <memory>
#include <SDL2/SDL.h>

namespace FYPEngine
{
	struct EngineGUI;
	struct EngineGUIContent;

	struct EngineGUIElement
	{
	private:
		friend struct EngineGUI;
		int m_x;
		int m_y;
		int m_width;
		int m_height;
		int m_colourRGBA[4];
		std::vector<std::shared_ptr<EngineGUIContent>> m_content;
		std::weak_ptr<EngineGUI> m_GUI;
		std::weak_ptr<EngineGUIElement> m_self;
		bool m_rounded;

	public:
		void render();
		void drawCircle(int _x, int _y, int _r);
		void update();

		template <typename T>
		std::shared_ptr<T> addContent(int _x, int _y, int _w, int _h, const char* _path, int _type);

		std::vector<std::shared_ptr<EngineGUIContent>> getContent();
		std::shared_ptr<EngineGUI> getGUI();
		void setBox(int _x, int _y, int _w, int _h);
		void setColour(int _r, int _g, int _b, int _a);
	};

	template <typename T>
	std::shared_ptr<T> EngineGUIElement::addContent(int _x, int _y, int _w, int _h, const char* _path, int _type)
	{
		std::shared_ptr<T> rtn = std::make_shared<T>();
		rtn->m_element = m_self;
		rtn->m_self = rtn;
		rtn->onInitialize(_x, _y, _w, _h, _path, _type);
		m_content.push_back(rtn);

		return rtn;
	}

}