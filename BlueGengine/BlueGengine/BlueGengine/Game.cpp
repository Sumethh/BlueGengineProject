#pragma once
#include "Game.h"
#include "World.h"
namespace BlueGengine
{

	Game::Game() :
	m_world(nullptr)
	{

	}

	Game::~Game()
	{
		if (m_world)
		{
			delete m_world;
		}
	}

	void Game::BeginPlay()
	{
		//TODO load a game config
		m_world = new World();
		m_world->BeginPlay();
	}

	void Game::Update(float a_dt)
	{
		m_world->Update(a_dt);
	}

	void Game::LateUpdate(float a_dt)
	{
		m_world->LateUpdate(a_dt);
	}

	void Game::PreRender()
	{
		m_world->PreRender();
	}

	void Game::Render(IRenderer* a_renderer)
	{
		m_world->Render(a_renderer);
	}

	void Game::PostRender()
	{
		m_world->PostRender();
	}

}
