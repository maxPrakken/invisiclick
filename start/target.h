#pragma once
#include "entitymain.h"

/// @brief background class in background implementation.
class Target :
	public EntityMain
{
public:
	/// @brief background constructor.
	Target();

	/// @brief virtual backround deconstructor.
	virtual ~Target();

	/// @brief update is automatically called every frame
	/// @param deltatime, the time elapsed in seconds.
	/// @return void
	virtual void update(float deltaTime);

};