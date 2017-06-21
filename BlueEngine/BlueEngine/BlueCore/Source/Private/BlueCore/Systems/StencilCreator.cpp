#include "BlueCore/Systems/StencilCreator.h"

#include "BlueCore/Input/input.h"
#include "BlueCore/Serialization/ArchiveObject.h"

namespace Blue
{
	StencilCreator* StencilCreator::mInstance;
	char stencilName[128] = {};
	void StencilCreator::Update()
	{

		if (Input::GetKeyPressed(Input::Key::P) && !Input::IsKeyboardCaptured())
		{
			mOpened = !mOpened;
		}

		if (mOpened)
		{
			//ImGui::SetNextWindowSize(ImVec2(350, 600));
			//ImGui::Begin("Stencil Creator");

			//if (//ImGui::InputText("Stencil Name", stencilName, sizeof(stencilName)))
			{
				mCurrentStencil.SetName(stencilName);
			}

			//ImGui::BeginChild("CompList", ImVec2(//ImGui::GetWindowContentRegionWidth(), 100));
			//ImGui::ListBox("##Components", &mCurrentSelectedComponent, EComponentTypeStrings, (int)EComponentType::ECount);
			//ImGui::SameLine();

			//if (//ImGui::Button("Add Component"))
			{
				mCurrentAddedComponents.emplace_back(EComponentTypeStrings[mCurrentSelectedComponent]);
				mCurrentStencil.AddComponent((EComponentType)mCurrentSelectedComponent);
			}

			//ImGui::EndChild();
			//ImGui::Text("Added Components");
			//ImGui::BeginChild("AddedComponents", ImVec2(0, 200), true);
			int count = 0;

			for (auto i = mCurrentAddedComponents.begin(); i != mCurrentAddedComponents.end();)
			{
				//ImGui::Text(*i);
				//ImGui::SameLine();
				//ImGui::PushID(count);

				//if (//ImGui::Button("Remove"))
				{
					i = mCurrentAddedComponents.erase(i);
					mCurrentStencil.RemoveComponent(count);
				}
				//				else
				{
					++i;
				}

				count++;
				//ImGui::PopID();
			}

			//ImGui::EndChild();

			//ImGui::BeginChild("Stencil Controls");

			//if (//ImGui::Button("Save"))
			{
				ArchiveObject archive("");

				if (mCurrentStencil.Name().size() != 0)
				{
					mCurrentStencil.OnSerialize(&archive);
					archive.WriteToFile("Assets/Stencils/", mCurrentStencil.Name().append(".stencil").c_str());
				}
			}

			//ImGui::EndChild();

			//ImGui::End();
		}

	}

	StencilCreator::StencilCreator() : mOpened(false), mCurrentSelectedComponent(0), mCurrentStencil("Stencil")
	{

	}

	StencilCreator::~StencilCreator()
	{

	}
}
