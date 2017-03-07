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
#include "ping.h"

MyScene::MyScene() : Scene()
{
	startgame();
}


MyScene::~MyScene()
{
	cleanse();
}

void MyScene::update(float deltaTime)
{

	//slim shady simulator(uncomment to unlock)
	//disclamer!
	//uncommenting this for loop will kill your fps, no matter the system

	/*for (int i = 0; i < 20; i++) {
		targetSpawn();
		std::cout << "im spawning" << std::endl;
	}*/

	//############################################
	//############################################

	//deals with restart of the game
	if (lives <= 0) {
		lives = 0;
		std::stringstream ls;
		ls << lives;
		livestext->message(ls.str());

		this->addChild(restarttext);

		if (input()->getKeyDown(GLFW_KEY_R)) {
			cleanse();
			startgame();
		}
	}
	else {

		//score 
		std::stringstream ts;
		ts << score;
		scoretext->message(ts.str());

		if (startTimer.seconds() >= 1 && countdowntime >= 0) {
			countdowntime--;
			startTimer.start();
		}
		else if (countdowntime <= 0) {
			this->removeChild(starttext);
			rendermouse = false;
		}

		std::cout << rendermouse << std::endl;

		//before score count
		std::stringstream rs;
		beforescoretext->message("score:");

		//lives 
		std::stringstream ls;
		ls << lives;
		livestext->message(ls.str());

		//text before lives
		std::stringstream bs;
		beforelivestext->message("lives:");

		//start countdown
		std::stringstream st;
		st << countdowntime;
		starttext->message(st.str());

		//keeps mouse collisiton member on mouse position
		mouseCol->position = Point2(input()->getMouseX(), input()->getMouseY());

		// ###############################################################
		// Escape key stops the Scene
		// ###############################################################
		if (input()->getKeyUp(GLFW_KEY_ESCAPE)) {
			this->stop();
		}

		// ###############################################################
		// Spacebar scales myentity
		// ###############################################################
		if (input()->getKeyDown(GLFW_KEY_SPACE)) {
			myentity->scale = Point(0.5f, 0.5f);
		}
		if (input()->getKeyUp(GLFW_KEY_SPACE)) {
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
		targetSpawnController();
	}

	pingDespawn();
	std::cout << rendermouse << std::endl;
}

void MyScene::cleanse() {
	// deconstruct and delete the Tree
	this->removeChild(myentity);
	this->removeChild(mouseCol);
	this->removeChild(scoretext);
	this->removeChild(beforescoretext);
	this->removeChild(starttext);
	this->removeChild(livestext);
	this->removeChild(beforelivestext);
	this->removeChild(restarttext);

	// delete myentity from the heap (there was a 'new' in the constructor)
	delete myentity;
	delete mouseCol;
	delete scoretext;
	delete beforescoretext;
	delete starttext;
	delete livestext;
	delete beforelivestext;
	delete restarttext;

	//cleanup vectors
	for (unsigned int i = 0; i < targetVector.size(); i++) {
		this->removeChild(targetVector[i]);
		delete targetVector[i];
	}
	targetVector.clear();

	for (unsigned int i = 0; i < pingVector.size(); i++) {
		this->removeChild(pingVector[i]);
		delete pingVector[i];
	}
	pingVector.clear();
}

void MyScene::startgame() {
	lives = 3;

	//renders the mouse
	rendermouse = true;

	score = 0;

	targetTimer.start();

	countdowntime = 3;

	srand(time(NULL));

	// start the timer.
	t.start();

	//start countdown timer
	startTimer.start();

	//mouse collision checker
	//colColor makes collision checker invisible
	mouseCol = new Target();
	mouseCol->scale = Point2(1, 1);
	this->addChild(mouseCol);
	RGBAColor colColor(255, 255, 255, 0);
	mouseCol->sprite()->color = colColor;

	//score counter
	scoretext = new Text();
	this->addChild(scoretext);
	scoretext->position = Point2(320, 100);

	//before score counter
	beforescoretext = new Text();
	this->addChild(beforescoretext);
	beforescoretext->position = Point2(100, 100);

	//start counter
	starttext = new Text();
	this->addChild(starttext);
	starttext->position = Point2(SWIDTH / 2, SHEIGHT / 2);

	//lives text
	livestext = new Text();
	this->addChild(livestext);
	livestext->position = Point2(1820, 100);

	//text before the lives counter
	beforelivestext = new Text();
	this->addChild(beforelivestext);
	beforelivestext->position = Point2(1600, 100);

	//restarttext
	restarttext = new Text();
	restarttext->position = Point2(600, SHEIGHT / 2 + 100);
	std::stringstream rs;
	restarttext->message("press R to restart the game", RED);

	// create a single instance of MyEntity in the middle of the screen.
	// the Sprite is added in Constructor of MyEntity.
	myentity = new MyEntity();
	myentity->position = Point2(SWIDTH / 2, SHEIGHT / 2);

	// create the scene 'tree'
	// add myentity to this Scene as a child.
	this->addChild(myentity);
}

void MyScene::pingSpawn() {
	Ping* ping = new Ping();
	ping->position = Point2(input()->getMouseX(), input()->getMouseY());
	this->addChild(ping);
	pingVector.push_back(ping);
}

void MyScene::pingDespawn() {
	std::vector<Ping*>::iterator it = pingVector.begin();
	while (it != pingVector.end()) {
		if ((*it)->alpha < 0) {
			Ping* p = (*it);
			this->removeChild(p);
			it = pingVector.erase(it);
			delete p;
			//std::cout << "im despawning" << std::endl;
		}
		else {
			it++;
		}
	}
}

void MyScene::mouseClickOnTarget() {
	if (input()->getMouseDown(GLFW_MOUSE_BUTTON_1)) {
		pingSpawn();
		int count = 0;
		std::vector<Target*>::iterator it = targetVector.begin();
		while (it != targetVector.end()) {
			if (mouseCol->isCollidingWith((*it))) {
				Target* b = (*it);
				this->removeChild(b);
				it = targetVector.erase(it);
				delete b;
				score += 1;
				count++;
				return;
			}
			else
			{
				it++;
			}
		}
		if (count == 0) {
			lives -= 1;
			std::cout << "i have " << lives << " lives left" << std::endl;
		}
	}
}

void MyScene::targetSpawnController() {
	if (targetTimer.seconds() > 1.0f) {
		targetSpawn();
		targetTimer.start();
	}
}

void MyScene::targetSpawn() {

	int targetX = rand() % 1500;
	int targetY = rand() % 800 + 50;

	Target* target1 = new Target();
	target1->position = Point2(targetX, targetY);
	targetVector.push_back(target1);
	addChild(target1);
	//std::cout << "my X position is " << targetX << std::endl;
}

