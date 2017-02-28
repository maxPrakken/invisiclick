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
	alpha -= 20;
	this->sprite()->color = pingColor;
	RGBAColor pingColor(0, 0, 255, alpha);
}

