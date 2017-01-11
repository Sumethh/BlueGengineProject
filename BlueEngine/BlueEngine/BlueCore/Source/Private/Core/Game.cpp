#pragma once
#include "Core/Game.h"
#include "Core/World.h"
#include "Input/Input.h"

#include "Serialization/ArchiveObject.h"
namespace BlueCore
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

	void Game::PreRender()
	{
		mWorld->PreRender();
	}

	void Game::Render(IRenderer* aRenderer)
	{
		mWorld->Render(aRenderer);
	}

	void Game::GizmoDraw(GizmoRenderer* aRenderer)
	{
		mWorld->GizmoDraw(aRenderer);
	}

	void Game::PostRender()
	{
		mWorld->PostRender();
	}

}
