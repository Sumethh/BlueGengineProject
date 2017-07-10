#pragma once
#include "BlueCore/Core/Game.h"
#include "BlueCore/Core/World.h"
#include "BlueCore/Input/Input.h"

#include "BlueCore/Serialization/ArchiveObject.h"
namespace Blue
{
	Game::Game() :
		mWorld(nullptr)
	{

	}

	Game::~Game()
	{
		if (mWorld)
		{
			delete mWorld;
		}
	}
	void Game::BeginPlay()
	{
		//TODO load a game config
		mWorld = new World();
		mWorld->BeginPlay();
	}

	void Game::Update(float aDt)
	{
		mWorld->Update(aDt);

		if (Input::GetKeyDown(Input::Key::Y))
		{
			ArchiveObject savingWorld("SavingWorld");
			mWorld->Save(savingWorld);
			savingWorld.WriteToFile("Assets/Saves/", "World.save");
		}

	}

	void Game::LateUpdate(float aDt)
	{
		mWorld->LateUpdate(aDt);
	}

	void Game::GizmoDraw(GizmoRenderer* aRenderer)
	{
		mWorld->GizmoDraw(aRenderer);
	}
}