#include <memory>
#include <vector>

namespace FYPEngine
{
	struct EngineGUIElement;
	struct Core;
	struct EngineGUIFrame;

	struct EngineGUI
	{
	private:
		friend struct Core;
		std::vector<std::shared_ptr<EngineGUIElement>> m_elements;
		std::weak_ptr<Core> m_core;
		std::weak_ptr<EngineGUI> m_self;
		std::shared_ptr<EngineGUIFrame> m_frame;

	public:
		void addFrame();
		void setFrameColour(int _r, int _g, int _b, int _a);
		void update();
		std::shared_ptr<EngineGUIElement> addElement();
		std::vector<std::shared_ptr<EngineGUIElement>> getElements();
		std::shared_ptr<Core> getCore();
		std::shared_ptr<EngineGUIFrame> getFrame();
	};
}