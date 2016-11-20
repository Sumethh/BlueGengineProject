#pragma once
#include "Game.h"
#include "World.h"
namespace BlueGengine
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
