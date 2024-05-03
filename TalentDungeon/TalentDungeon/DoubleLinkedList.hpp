#pragma once

namespace CTN
{


	template <typename T>
	class DoubleLinkedList
	{

	private:
		struct Node
		{
			T		data;
			Node* prev;
			Node* next;
		};

		Node* Head = nullptr;
		Node* Tail = nullptr;

	public:
		class Iterator
		{
		public:
			Node* pCurr = nullptr;
			Iterator(Node* p = nullptr)
			{
				pCurr = p;
			}

			//전위
			Iterator& operator++()
			{
				pCurr = pCurr->next;
				return *this;
			}

			Iterator& operator--()
			{
				pCurr = pCurr->prev;
				return *this;
			}

			Iterator operator+(const int rhs) const
			{
				int num = 0;
				Node* tempCur = pCurr;
				while (num++ < rhs)
				{
					tempCur = tempCur->next;
				}
				return Iterator(tempCur);
			}

			Iterator operator-(const int rhs) const
			{
				int num = 0;
				Node* tempCur = pCurr;
				while (num++ < rhs)
				{
					tempCur = tempCur->prev;
				}
				return Iterator(tempCur);
			}

			T& operator*()
			{
				return pCurr->data;
			}

			bool operator==(const Iterator& ref)
			{
				return  pCurr == ref.pCurr;
			}

			bool operator!=(const Iterator& ref)
			{
				return  pCurr != ref.pCurr;
			}
		};
	private:

	public:

		DoubleLinkedList()
		{
			Head = new Node;
			Tail = new Node;

			Head->prev = nullptr;
			Head->next = Tail;
			Tail->prev = Head;
			Tail->next = nullptr;
		}
		~DoubleLinkedList()
		{
			Clear();
			delete Head;
			delete Tail;
		}

		Node* Insert(Node* pPos, T _data)
		{
			Node* insert = Head;
			Node* newNode = new Node;

			newNode->data = _data;
			while (!(pPos == insert || Tail == insert->next))
			{
				insert = insert->next;
			}

			newNode->next = insert->next;
			newNode->prev = insert;
			insert->next->prev = newNode;
			insert->next = newNode;

			return newNode;
		}

		Node* PushBack(T _data)
		{
			Node* insert = Head;
			Node* newNode = new Node;

			newNode->data = _data;
			while (Tail != insert->next)
			{
				insert = insert->next;
			}

			insert->next = newNode;
			Tail->prev = newNode;
			newNode->next = Tail;
			newNode->prev = insert;

			return newNode;
		}

		Node* Erase(Node* pPos, void (*del)(T) = nullptr)
		{
			Node* erase = Head->next;
			Node* returnValue;

			while (!(pPos == erase || Tail == erase))
			{
				erase = erase->next;
			}
			if (Tail == erase)
				return nullptr;
			erase->prev->next = erase->next;
			erase->next->prev = erase->prev;
			returnValue = erase->next;

			if (del != nullptr)
				del(erase->data);
			delete erase;
			return returnValue;
		}

		void	Clear(void (*del)(T) = nullptr)
		{
			Node* erase = Head->next;
			Node* indexNode = erase;

			while (Tail != indexNode)
			{
				erase = indexNode;
				indexNode = erase->next;
				if (del != nullptr)
					del(erase->data);
				delete erase;
			}
		}

		Iterator Begin()
		{
			return Iterator(Head->next);
		}

		Iterator End()
		{
			return Iterator(Tail);
		}

		T& operator[](const int _index)
		{
			Iterator index = Begin();
			int tmp = 0;

			//인덱스 값이 넘어가면 그냥 아웃오브바운드뜨게 해야함
			while (tmp < _index)
			{
				++index;
				tmp++;
			}
			return *index;
		}

	};
}
