#include "Attribute.h"
#include <vector>
#include <memory>

namespace FYPEngine
{
	struct CollisionBox : Attribute
	{
	private:
		std::vector<std::shared_ptr<CollisionBox>> m_boxes;
	public:
		void affect();
		bool colliding(CollisionBox& _other);
	};
}