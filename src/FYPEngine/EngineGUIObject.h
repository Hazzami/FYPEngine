#include "EngineGUIContent.h"
#include <SDL2/SDL.h>
#include "EngineGUITexture.h"
#include <memory>
#include <vector>

namespace FYPEngine
{
	struct EngineGUIElement;
	struct Attribute;

	struct EngineGUIObject : EngineGUIContent
	{
	private:
		friend struct EngineGUIElement;
		int m_initX;
		int m_initY;
		int m_initW;
		int m_initH;
		std::shared_ptr<EngineGUITexture> m_texture;
		std::weak_ptr<EngineGUIObject> m_self;
		bool m_released;
		int m_spawn = 0;
		std::vector<std::shared_ptr<Attribute>> m_attributes;
		bool m_rigid = false;

	public:
		void onInitialize(int _x, int _y, int _w, int _h, const char* _path, int _type);
		void render();
		void update();
		std::shared_ptr<EngineGUIObject> getObject();
		std::shared_ptr<EngineGUITexture> getTexture();
		int getFloor();
		std::vector<std::shared_ptr<Attribute>> getAttributes();
		bool getRigid();
		void setRigid(bool _r);

		template <typename T>
		std::shared_ptr<T> addAttribute();

	};

	template <typename T>
	std::shared_ptr<T> EngineGUIObject::addAttribute()
	{
		std::shared_ptr<T> rtn = std::make_shared<T>();
		rtn->m_object = m_self;
		m_attributes.push_back(rtn);
		return rtn;
	}
}
