#pragma once
#include "entitymain.h"

/// @brief background class in background implementation.
#pragma once
#include "entitymain.h"

/// @brief background class in background implementation.
class Ping :
	public EntityMain
{
public:
	/// @brief background constructor.
	Ping();

	RGBAColor pingColor;

	float alpha;

	/// @brief virtual backround deconstructor.
	virtual ~Ping();

	/// @brief update is automatically called every frame
	/// @param deltatime, the time elapsed in seconds.
	/// @return void
	virtual void update(float deltaTime);
}; 