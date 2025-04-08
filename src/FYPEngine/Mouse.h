#include <vector>
#include <memory>
#include <SDL2/SDL.h>

namespace FYPEngine
{
	struct Core;

	struct Mouse
	{
	private:
		friend struct FYPEngine::Core;
		std::vector<int>keys;
		std::vector<int>pressedKeys;
		std::vector<int>releasedKeys;
		int m_x, m_y;
		std::weak_ptr<Core> m_core;

	public:
		bool isKey(int key);
		bool isKeyPressed(int key);
		bool isKeyReleased(int key);
		void update();
		int getMouseX();
		int getMouseY();
		void setMouse(int _x, int _y);
		std::shared_ptr<Core> getCore();
	};
}