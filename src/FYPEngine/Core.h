#include "memory"
#include <vector>
#include <SDL2/SDL.h>
#include <SDL_ttf/SDL_ttf.h>


namespace FYPEngine
{
	struct Entity;
	struct Window;
	struct EngineGUI;
	struct Keyboard;
	struct Mouse;

	struct Core
	{
	private:
		std::vector<std::shared_ptr<Entity>> m_entities;
		bool m_running;
		std::weak_ptr<Core> m_self;
		std::shared_ptr<Window> m_window;
		std::shared_ptr<EngineGUI> m_engineGUI;
		std::shared_ptr<Keyboard> m_keyboard;
		std::shared_ptr<Mouse> m_mouse;
		int m_state = 0;

	public:
		static std::shared_ptr<Core> initialize();
		std::shared_ptr<Entity> addEntity();
		std::shared_ptr<Window> getWindow();
		void start();
		std::shared_ptr<Keyboard> getKeyboard();
		std::shared_ptr<Mouse> getMouse();
		std::shared_ptr<EngineGUI> getEngineGUI();
		
		template <typename T>
		void find(std::vector<std::shared_ptr<T> >& _out);
	};
	
	template <typename T>
	void Core::find(std::vector<std::shared_ptr<T> >& _out)
	{
		for (size_t ei = 0; ei < m_engineGUI->getElements().size(); ++ei)
		{
			std::shared_ptr<EngineGUIElement> e = m_engineGUI->getElements().at(ei);

			for (size_t ci = 0; ci < e->getContent().size(); ++ci)
			{
				std::shared_ptr<EngineGUIContent> c = e->getContent().at(ci);
				std::shared_ptr<EngineGUIObject> t = std::dynamic_pointer_cast<EngineGUIObject>(c);
				if (t)
				{
					for (size_t ai = 0; ai < t->getAttributes().size(); ++ai)
					{
						std::shared_ptr<Attribute> a = t->getAttributes().at(ai);

						std::shared_ptr<T> n = std::dynamic_pointer_cast<T>(a);

						if (n)
						{
							_out.push_back(n);
						}
					}
				}
			}
		}
	}
}