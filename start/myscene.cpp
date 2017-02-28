/**
 * This class describes MyScene behavior.
 *
 * Copyright 2015 Your Name <you@yourhost.com>
 */

#include <fstream>
#include <sstream>

#include "myscene.h"
#include "target.h"
#include "entitymain.h"
#include "input.h"

MyScene::MyScene() : Scene()
{
	//checks if mousebutton 1 is pressed
	mousepress = false;

	//renders the mouse
	rendermouse = false;

	// start the timer.
	t.start();

	//mouse collision checker
	mouseCol = new Target();
	mouseCol->scale = Point2(1, 1);
	this->addChild(mouseCol);

	// create a single instance of MyEntity in the middle of the screen.
	// the Sprite is added in Constructor of MyEntity.
	myentity = new MyEntity();
	myentity->position = Point2(SWIDTH/2, SHEIGHT/2);

	targetSpawn(SWIDTH / 2, SHEIGHT / 2);

	// create the scene 'tree'
	// add myentity to this Scene as a child.
	this->addChild(myentity);
}


MyScene::~MyScene()
{
	// deconstruct and delete the Tree
	this->removeChild(myentity);

	// delete myentity from the heap (there was a 'new' in the constructor)
	delete myentity;
}

void MyScene::update(float deltaTime)
{
	//keeps mouse collisiton member on mouse position
	mouseCol->position = Point2(input()->getMouseX(), input()->getMouseY());

	// ###############################################################
	// Escape key stops the Scene
	// ###############################################################
	if (input()->getKeyUp( GLFW_KEY_ESCAPE )) {
		this->stop();
	}

	// ###############################################################
	// Spacebar scales myentity
	// ###############################################################
	if (input()->getKeyDown( GLFW_KEY_SPACE )) {
		myentity->scale = Point(0.5f, 0.5f);
	}
	if (input()->getKeyUp( GLFW_KEY_SPACE )) {
		myentity->scale = Point(1.0f, 1.0f);
	}

	// ###############################################################
	// Rotate color
	// ###############################################################
	if (t.seconds() > 0.0333f) {
		RGBAColor color = myentity->sprite()->color;
		myentity->sprite()->color = Color::rotate(color, 0.01f);
		t.start();
	}

	mouseClickOnTarget();
}

void MyScene::mouseClickOnTarget() {
	if (input()->getMouseDown(GLFW_MOUSE_BUTTON_1)) {
	std::vector<Target*>::iterator it = targetVector.begin();
	while (it != targetVector.end())
	{
		
			if (mouseCol->isCollidingWith((*it))) {
				Target* b = (*it);
				this->removeChild(b);
				it = targetVector.erase(it);
				delete b;
			}
			else
			{
				it++;
			}
		}
	}
}

void MyScene::targetSpawn(int x, int y) {
	srand(time(0));
	Target* target1 = new Target();
	target1->position = Point2(x, y);
	//targetSizeXY();
	xy = rand() % 10;
	std::cout << "the random number is: " << xy << std::endl;
	target1->scale = Point2(xy, xy);
	addChild(target1);
	targetVector.push_back(target1);
}

/*int MyScene::targetSizeXY() {
	xy = rand() % 10;
	return xy;
}*/

