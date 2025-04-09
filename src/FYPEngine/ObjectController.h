#include "Attribute.h"

namespace FYPEngine
{
	struct ObjectController : Attribute
	{
	private:
		int m_jumpCoolDown = 5;
		bool m_jumping = false;
		int m_frameCount = 0;
	public:
		void affect();
	};
}