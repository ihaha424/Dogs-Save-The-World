#pragma once

namespace CTN
{
	template <typename T>
	class Queue
	{
	private:
		int _size = 0;
		int _front = -1;
		int _back = -1;
		int _capacity = 10;
		T* _queue;

	private:
		void ReSize()
		{
			T* tmp = new T[_capacity * 2];
			for (int i = 0; i < _size; i++)
			{
				tmp[i] = _queue[++_front];
				if (_front == _capacity)
					_front = 0;
			}
			delete[] _queue;
			_queue = tmp;
			_front = -1;
			_back = _size - 1;
			_capacity *= 2;
		}

	public:
		Queue()
		{
			_queue = new T[_capacity];
		}


		Queue(int N)
		{
			if (N > 0)
				_capacity = N;
			_queue = new T[_capacity];
		}

		~Queue()
		{
			delete[] _queue;
		}

		void	EnQueue(T data)
		{
			if (IsFull())
				ReSize();
			_size++;
			_back++;
			if (_back == _capacity)
				_back = 0;
			_queue[_back] = data;
		}

		void	DeQueue()
		{
			if (IsEmpty())
				return;
			_front++;
			_size--;
			if (_front == _capacity)
				_front == 0;
		}

		T	Front()
		{
			if (IsEmpty())
				return NULL;
			return _queue[_front + 1];
		}

		int		Size()
		{
			return _size;
		}

		bool	IsEmpty()
		{
			return (_size == 0);
		}

		bool	IsFull()
		{
			return (_size == _capacity);
		}

	};
}
