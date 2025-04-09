#include "CollisionBox.h"
#include "EngineGUIObject.h"
#include "EngineGUIElement.h"
#include "EngineGUI.h"
#include "Core.h"

namespace FYPEngine
{
	void CollisionBox::affect()
	{
		std::vector<std::shared_ptr<CollisionBox>> allBoxes;
		getObject()->getElement()->getGUI()->getCore()->find<CollisionBox>(allBoxes);
		m_boxes = allBoxes;

		if (getObject()->getRigid() == false)
		{
			for (int i = 0; i < allBoxes.size(); i++)
			{
				if (!(allBoxes.at(i)->getObject()->getX() == getObject()->getX() && allBoxes.at(i)->getObject()->getY() == getObject()->getY()
					&& allBoxes.at(i)->getObject()->getWidth() == getObject()->getWidth() && allBoxes.at(i)->getObject()->getHeight() == getObject()->getHeight()))
				{
					if (colliding(*allBoxes.at(i)))
					{
						int amount = 1;
						while (true)
						{
							if (!colliding(*allBoxes.at(i))) break;
							getObject()->setX(getObject()->getX() + amount);
							if (!colliding(*allBoxes.at(i))) break;
							getObject()->setX(getObject()->getX() - (amount*2));
							if (!colliding(*allBoxes.at(i))) break;
							getObject()->setX(getObject()->getX() + (amount));
							getObject()->setY(getObject()->getY() + (amount));
							if (!colliding(*allBoxes.at(i))) break;
							getObject()->setY(getObject()->getY() - (amount*2));
							if (!colliding(*allBoxes.at(i))) break;
							getObject()->setY(getObject()->getY() + (amount));
							amount++;
						}
					}
				}
			}
		}
	}

	bool CollisionBox::colliding(CollisionBox& _other)
	{
		int x = getObject()->getX();
		int y = getObject()->getY();
		int w = getObject()->getWidth();
		int h = getObject()->getHeight();
		
		int ox = _other.getObject()->getX();
		int oy = _other.getObject()->getY();
		int ow = _other.getObject()->getWidth();
		int oh = _other.getObject()->getHeight();

		if (x + w > ox)
		{
			if (x > ox + ow)
			{
				return false;
			}
		}
		else
		{
			return false;
		}
		
		if (y + h > oy)
		{
			if (y > oy + oh)
			{
				return false;
			}
		}
		else
		{
			return false;
		}

		return true;
	}

}