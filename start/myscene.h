/**
 * Copyright 2015 Your Name <you@yourhost.com>
 *
 * @file myscene.h
 *
 * @brief description of MyScene behavior.
 */

#ifndef MYSCENE_H
#define MYSCENE_H

#include <rt2d/scene.h>
#include <start\target.h>
#include <rt2d/text.h>

#include "myentity.h"
#include "ping.h"

/// @brief The MyScene class is the Scene implementation.
class MyScene : public Scene
{
public:
	/// @brief Constructor
	MyScene();
	/// @brief Destructor
	virtual ~MyScene();

	int xy;

	int countdowntime;

	int score;

	int lives;

	int targetX;
	int targetY;

	/// @brief update is automatically called every frame
	/// @param deltaTime the elapsed time in seconds
	/// @return void
	virtual void update(float deltaTime);

	void MyScene::pingDespawn();

	void MyScene::targetSpawn();

	void MyScene::mouseClickOnTarget();

	void MyScene::targetSpawnController();

	void MyScene::pingSpawn();

	void MyScene::startgame();

	void MyScene::cleanse();

	Target* mouseCol;

private:
	std::vector<Target*>targetVector;

	std::vector<Ping*>pingVector;

	/// @brief the rotating square in the middle of the screen
	MyEntity* myentity;

	/// @brief a Timer to rotate the color every n seconds
	Timer t;

	Timer targetTimer;

	Timer startTimer;

	Text* scoretext;
	Text* beforescoretext;
	Text* starttext;
	Text* livestext;
	Text* beforelivestext;
	Text* restarttext;
};

#endif /* SCENE00_H */
