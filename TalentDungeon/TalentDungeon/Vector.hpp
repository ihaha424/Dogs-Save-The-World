#pragma once
#include <cassert>
namespace CTN
{
	template <typename T>
	class Vector
	{
	private:
		int	capacity = 1;
		int size = 0;
		T* arr;

	private:

	public:
		Vector()
		{
			arr = new T[capacity];
		}

		Vector(int n)
		{
			capacity = n;
			arr = new T[capacity];
			size = n;
		}

		~Vector()
		{
			delete[] arr;
		}

		void ReSize()
		{
			T* tmp = new T[capacity * 2];
			for (int i = 0; i < capacity; i++)
			{
				tmp[i] = arr[i];
			}
			capacity *= 2;
			delete[] arr;
			arr = tmp;
		}

		int Size()
		{
			return size;
		}

		int Size() const
		{
			return size;
		}

		void PushBack(T data)
		{
			if (size == capacity)
				ReSize();
			arr[size++] = data;
		}

		//이터레이팅X 인덱스의 번호로 접근
		void Erase(const int start, const int end = -1)
		{
			int Start = start;
			int End = end;
			if (end == -1)
				End = start + 1;
			assert(!(Start < 0 || End > size || Start > End));
			for (int i = 0; End < size; i++)
			{
				arr[Start++] = arr[End++];
			}
			size -= (End - Start);
		}

		T operator[](int index) const {
			assert(!(index >= size || index < 0));
			return arr[index];
		}

		T& operator[](const int index)
		{
			assert(!(index >= size || index < 0));
			return arr[index];
		}
	};
}