#include <memory>

namespace FYPEngine
{
	struct EngineGUI;

	struct EngineGUIFrame
	{
	private:
		friend struct EngineGUI;
		int m_colourRGBA[4];
		int m_holeX;
		int m_holeY;
		int m_holeW;
		int m_holeH;
		std::weak_ptr<EngineGUI> m_GUI;

	public:
		void render();
		void setBox(int _x, int _y, int _w, int _h);
		std::shared_ptr<EngineGUI> getGUI();
		int getX();
		int getY();
		int getW();
		int getH();
	};
}