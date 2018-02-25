#pragma once
#include "BlueCore/Core/Application.h"

class SandboxApplication : public Blue::Application
{
public:

	SandboxApplication();
	~SandboxApplication();

	bool Run() override;
	void Update(float aDt) override;
	void EndUpdate() override;
	void ShutDown() override;

private:

};