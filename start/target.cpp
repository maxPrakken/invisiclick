#include "Target.h"

Target::Target() : EntityMain()
{
	this->addSprite("assets/slimshady.tga");
}


Target::~Target()
{
}
void Target::update(float deltaTime)
{

}

bool Target::isCollidingWith(Entity* other) {
	float dx = this->position.x - other->position.x;
	float dy = this->position.y - other->position.y;

	if ((abs(dx) * 2.0f < (sprite()->size.x * xy + other->sprite()->size.x)) &&
		(abs(dy) * 2.0f < (sprite()->size.y * xy + other->sprite()->size.y)))
	{
		std::cout << other->worldscale().x << std::endl;
		return true;
	}
	return false;
}