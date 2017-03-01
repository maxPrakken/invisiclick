#include "ping.h"

Ping::Ping() : EntityMain()
{
	alpha = 255;
	RGBAColor pingColor(0, 0, 255, alpha);
	this->addSprite("assets/ping.tga");
}


Ping::~Ping()
{
}
void Ping::update(float deltaTime)
{
	if (alpha > 0) {
		alpha -= 200 * deltaTime;
		RGBAColor pingColor(0, 0, 255, (int)alpha);
		this->sprite()->color = pingColor;
		std::cout << alpha << std::endl;
	}
	else if (alpha <= 0) {
		RGBAColor pingColor(0, 0, 0, 0);
		this->sprite()->color = pingColor;
	}
}

