#include "SandboxApplication.h"
#include "Core/Log.h"
SandboxApplication::SandboxApplication()
{

}

SandboxApplication::~SandboxApplication()
{

}

bool SandboxApplication::Run()
{
	Log::Info("Sandbox Application starting up");
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
	Log::Info("Sandbox Application shutting down");
}

