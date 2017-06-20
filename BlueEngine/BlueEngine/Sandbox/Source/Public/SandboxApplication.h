#pragma once
#include "Core/Application.h"

class SandboxApplication : public Blue::Application
{
public:

	SandboxApplication();
	~SandboxApplication();

	bool Run() override;
	void Update() override;
	void EndUpdate() override;
	void ShutDown() override;

private:

};