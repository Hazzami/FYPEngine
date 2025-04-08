#include <vector>
#include <memory>

namespace FYPEngine
{
	struct Core;

	struct Keyboard
	{
	private:
		friend struct FYPEngine::Core;
		std::vector<int>keys;
		std::vector<int>pressedKeys;
		std::vector<int>releasedKeys;
		std::weak_ptr<Core> m_core;

	public:
		bool isKey(int key);
		bool isKeyPressed(int key);
		bool isKeyReleased(int key);
		std::shared_ptr<Core> getCore();
	};
}