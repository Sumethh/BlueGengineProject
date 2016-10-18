#include "World.h."
#include "Log.h"
namespace BlueGengine
{

	World::World()
	{
		LOGI("World Constructed");
	}

	World::~World()
	{
		LOGI("World Destructed");
	}

	void World::BeginPlay()
	{
		LOGI("World BeginPlay");
	}

	void World::Update(float a_dt)
	{

	}

	void World::LateUpdate(float a_dt)
	{

	}

	void World::PreRender()
	{

	}

	void World::Render()
	{

	}

	void World::PostRender()
	{

	}

}