#include "SandboxApplication.h"
#include "BlueCore/Core/Log.h"
SandboxApplication::SandboxApplication()
{

}

SandboxApplication::~SandboxApplication()
{

}

bool SandboxApplication::Run()
{
	Blue::Log::Info("Sandbox Application starting up");
	return true;
}

void SandboxApplication::Update()
{

}

void SandboxApplication::EndUpdate()
{

}

void SandboxApplication::ShutDown()
{
	Blue::Log::Info("Sandbox Application shutting down");
}

