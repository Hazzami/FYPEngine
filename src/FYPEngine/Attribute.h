#pragma once
#include <memory>

namespace FYPEngine
{
	struct EngineGUIObject;
	struct EngineGUIAttrib;
	struct EngineGUIContent;

	struct Attribute
	{
	private:
		friend struct EngineGUIObject;
		friend struct EngineGUIAttrib;
		friend struct EngineGUIContent;
		std::weak_ptr<EngineGUIObject> m_object;
	public:
		virtual void affect() {}
		std::shared_ptr< EngineGUIObject> getObject() { return m_object.lock(); }
	};
}