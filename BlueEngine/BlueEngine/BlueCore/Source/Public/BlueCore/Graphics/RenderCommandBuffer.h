#pragma once
#include "BlueCore/Core/Defines.h"
#include "BlueCore/Core/Types.h"
#include "BlueCore/Managers/MemoryManager.h"

#include <vector>
#include <mutex>
#include <new>
namespace Blue
{

	template <typename T>
	class RenderCommandBuffer
	{
		using Key = T;		

		struct SubmittedCommand
		{
			void* dispatchFunction;
			void* nextCommand;			
		};

		template<typename U>
		struct KeyCommandPair
		{
			U key;
			SubmittedCommand* command;
		};

	public:
		RenderCommandBuffer();
		~RenderCommandBuffer();

		template<typename U>
		U* CreateCommand(Key aKey);
		
		template<typename U>
		U* CreateChildCommand(void* aParentCommand);

		
	private:
		template<typename U>
		byte* AllocateCommand();

		std::vector<KeyCommandPair<Key>> mCommands;
		std::mutex mCommandMutex;
	};

	template <typename T>
	Blue::RenderCommandBuffer<T>::~RenderCommandBuffer(){}

	template <typename T>
	Blue::RenderCommandBuffer<T>::RenderCommandBuffer()
	{

	}

	template<typename T>
	template<typename U>
	U* RenderCommandBuffer<T>::CreateCommand(Key aKey)
	{
		byte* memory = AllocateCommand<U>();

		KeyCommandPair<Key> pair = { aKey, reinterpret_cast<SubmittedCommand*>(memory)};

		std::lock_guard<std::mutex> lock(mCommandMutex);
		mCommands.push_back(std::move(pair));

		return reinterpret_cast<U*>(memory + sizeof(SubmittedCommand));
	}

	template<typename T>
	template<typename U>
	U* Blue::RenderCommandBuffer<T>::CreateChildCommand(void* aParentCommand)
	{
		BlueAssert(aParentCommand);
		byte* memory = AllocateCommand<U>();

		SubmittedCommand* childCommand = reinterpret_cast<SubmittedCommand*>(memory);
		SubmittedCommand* parentCommand = reinterpret_cast<SubmittedCommand*>(aParentCommand);
		parentCommand->nextCommand = childCommand;

		return reinterpret_cast<U*>(memory + sizeof(SubmittedCommand));
	}

	template<typename T>
	template<typename U>
	byte* RenderCommandBuffer<T>::AllocateCommand()
	{
		TaggedBlockAllocator* renderingAllocator = MemoryManager::GI()->GetRenderingAllocator();
		void* memory = renderingAllocator->Allocate(sizeof(SubmittedCommand) + sizeof(U));

		SubmittedCommand* command = reinterpret_cast<SubmittedCommand*>(memory);
		command->dispatchFunction = reinterpret_cast<void*>(&U::dispatchFunction);
		command->nextCommand = nullptr;

		return static_cast<byte*>(memory);
	}
}

