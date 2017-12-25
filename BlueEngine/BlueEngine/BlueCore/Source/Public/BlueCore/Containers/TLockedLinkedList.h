#pragma once
#include "BlueCore/BlueCore.h"
#include <mutex>
#if 0
	#include <atomic>
#endif

namespace Blue
{
	template<typename T>
	class TLockedLinkedList
	{
	private:
		template<typename U>
		struct Node
		{

			U item;
			Node* next = nullptr;
		};

	public:
		TLockedLinkedList();
		~TLockedLinkedList();

		void Add(T aItem);
		T PopFront();
		void Clear();

		inline uint32 Size() const
		{
			return mListSize.load();
		}

		inline bool IsEmpty() const
		{
			return mListSize.load() == 0
		};

	private:

		Node<T>* AllocateNode();
		void DeleteNode(Node<T>* aNode);

		std::atomic<uint32> mListSize = 0;
		Node<T>* mHead = nullptr;
		Node<T>* mTail = nullptr;

		TLockedLinkedList(const TLockedLinkedList&) = delete;
		TLockedLinkedList(TLockedLinkedList&&) = delete;
	};


	template<typename T>
	Blue::TLockedLinkedList<T>::TLockedLinkedList()
	{

	}

	template<typename T>
	Blue::TLockedLinkedList<T>::~TLockedLinkedList()
	{

	}

	template<typename T>
	void Blue::TLockedLinkedList<T>::Add(T aItem)
	{
		Node<T>* newNode = AllocateNode();
		BlueEnsure(newNode);


	}

	template<typename T>
	T Blue::TLockedLinkedList<T>::PopFront()
	{

	}

	template<typename T>
	void Blue::TLockedLinkedList<T>::Clear()
	{

	}

	template<typename T>
	Node<T>* Blue::TLockedLinkedList<T>::AllocateNode()
	{
#if 0
		IMemoryAllocator* allocator = MemoryManager::GI()->GetSmallBlockAllocator();
		BlueAssert(allocator);
		Node<T>* returningNode = new (allocator->Allocate(sizeof(Node<T>), 0)) Node<T>;
		BlueAssert(returningNode);
		return returningNode;
#endif
		return new Node<T>();
	}

	template<typename T>
	void Blue::TLockedLinkedList<T>::DeleteNode(Node<T>* aNode)
	{
#if 0
		IMemoryAllocator* allocator = MemoryManager::GI()->GetSmallBlockAllocator();
		BlueAssert(aNode && allocator);
		allocator->Deallocate(reinterpret_cast<void*>(aNode), sizeof(Node<T>));
#endif
		delete aNode;
	}
}