#pragma once

#define NULL 0

namespace CTN
{
	//Key가 스트링전용 해쉬맵
	template <typename T1, typename T2>
	class LinkedHashMap
	{
#define HashRound 31
#define HashModule 1234567891
	public:
		struct Data
		{
			T1  key;
			T2	value;
			Data* next;
		};
		int size = 0;
		int capacity = 100;
		Data* list;

	private:
		size_t	Strlen(const char* str)
		{
			int	temp;

			temp = 0;
			if (str == NULL)
				return (temp);
			while (str[temp])
			{
				temp++;
			}
			return (temp);
		}

		size_t	Strlcpy(char* dest, const char* src, size_t dest_size)
		{
			size_t	count;

			count = 0;
			if (dest_size != 0 && dest != NULL)
			{
				while (count < dest_size - 1 && src[count])
				{
					dest[count] = src[count];
					count++;
				}
				dest[count] = '\0';
				count++;
			}
			count = 0;
			while (src[count])
			{
				count++;
			}
			return (count);
		}


		int	Strncmp(const char* s1, const char* s2, size_t n)
		{
			unsigned int	count;

			count = 0;
			if (n == 0)
				return (0);
			while (s1[count] && s2[count] && s1[count] == s2[count] && count < n)
				count++;
			if (count == n)
				return ((unsigned char)s1[count - 1] - (unsigned char)s2[count - 1]);
			return ((unsigned char)s1[count] - (unsigned char)s2[count]);
		}

		void SetKey(Data* data, const char* key)
		{
			data->key = new char[Strlen(key) + 1];
			Strlcpy((char* )data->key, key, Strlen(key) + 1);
		}

		void SetKey(Data*  data, long long key)
		{
			data->key = key;
		}

		bool MyCompare(const char* a, const char* b)
		{
			return (Strncmp(a, b, Strlen(a)) == 0);
		}

		bool MyCompare(long long a, long long b)
		{
			return (a == b);
		}


		unsigned int Hashing(const char* str)
		{
			long long tmp = 1;
			long long hashingValue = 0;
			unsigned int value;
			int i = -1;
			while (str[++i] != '\0')
			{
				hashingValue = ((hashingValue + ((long long)(str[i] - 'a' + 1) * tmp)) % HashModule) % HashModule;
				tmp = tmp * HashRound;
				tmp = tmp % HashModule;
			}
			value = (unsigned int)hashingValue % capacity;
			return (value);
		}

		unsigned int Hashing(long long str)
		{
			long long tmp = 1;
			long long hashingValue = 0;
			unsigned int value;
			int i = -1;
			tmp = tmp * HashRound;
			tmp = tmp % HashModule;
			value = (unsigned int)hashingValue % capacity;
			return (value);
		}
	public:
		LinkedHashMap()
		{
			list = new Data[capacity];
			for (int i = 0; i < capacity; i++)
			{
				list[i].key = NULL;
				list[i].value = NULL;
				list[i].next = nullptr;
			}
		}
		~LinkedHashMap()
		{
			Clear();
			delete[] list;
		}

		void Put(T1 key, T2 value) {
			unsigned int index = Hashing(key);
			Data* tmp = list[index].next;
			if (tmp == nullptr)
			{
				size++;
				Data* curIndex = new Data();
				SetKey(curIndex, key);
				curIndex->value = value;
				curIndex->next = nullptr;

				list[index].next = curIndex;
				return;
			}
			while (tmp->next != nullptr)
			{
				if (MyCompare(tmp->key, key))
				{
					tmp->value = value;
					return;
				}
				tmp = tmp->next;
			}
			size++;
			Data* curIndex = new Data();
			SetKey(curIndex, key);
			curIndex->value = value;
			curIndex->next = nullptr;

			tmp->next = curIndex;
		}
		void Remove(T1 key)
		{
			unsigned int index = Hashing(key);
			Data* curIndex = list[index].next;
			if (curIndex == nullptr)
				return;
			else
			{
				if (Strncmp(curIndex->key, key, Strlen(curIndex->key)) == 0)
				{
					list[index].next = nullptr;
					delete curIndex;
					size--;
					return;
				}
			}
			while (curIndex->next != nullptr)
			{
				if (Strncmp(curIndex->next->key, key, Strlen(curIndex->key)) == 0)
				{
					Data* tmp = curIndex->next;

					curIndex->next = tmp->next;
					delete tmp;
					size--;
					return;
				}
				curIndex = curIndex->next;
			}
		}
		void Clear()
		{
			for (int i = 0; i < capacity; i++)
			{
				if (list[i].next == nullptr)
					continue;
				Data* tmp = list[i].next;
				while (tmp != nullptr)
				{
					list[i].next = tmp->next;
					delete tmp;
					tmp = list[i].next;
				}
				list[i].next = nullptr;
			}
		}
		T2 Get(T1 key)
		{
			unsigned int index = Hashing(key);
			Data* tmp = list[index].next;
			while (tmp != nullptr)
			{
				if (MyCompare(tmp->key, key))
				{
					return tmp->value;
				}
				tmp = tmp->next;
			}
			return (T2)nullptr;
		}

		bool Find(T1 key)
		{
			unsigned int index = Hashing(key);
			Data* tmp = list[index].next;
			while (tmp != nullptr)
			{
				if (MyCompare(tmp->key, key))
				{
					return true;
				}
				tmp = tmp->next;
			}
			return false;
		}

		int Size()
		{
			return size;
		}

		T2& operator[](T1 key)
		{
			unsigned int index = Hashing(key);
			Data* tmp = list[index].next;
			while (tmp != nullptr)
			{
				if (MyCompare(tmp->key, key))
				{
					return tmp->value;
				}
				tmp = tmp->next;
			}
			Put(key, NULL);
			tmp = list[index].next;
			while (tmp != nullptr)
			{
				if (MyCompare(tmp->key, key))
				{
					return tmp->value;
				}
				tmp = tmp->next;
			}
		}

		//Iterator
		class Iterator
		{
		private:
			Data* current; // 현재 노드를 가리키는 포인터
			Data** table;  // LinkedHashMap의 데이터 테이블을 가리키는 포인터
			int capacity;  // 테이블의 크기
			int index;     // 현재 인덱스를 가리키는 변수

		public:
			Iterator(Data** table, int capacity) : table(table), capacity(capacity), index(0)
			{
				for (index = 0; index < capacity; ++index)
				{
					if ((*table)[index].next != nullptr)
					{
						current = (*table)[index].next;
						break;
					}
				}
			}

			void Next()
			{
				if (current != nullptr)
					current = current->next;

				// 다음 노드가 nullptr이면 다음 유효한 인덱스로 이동
				while (current == nullptr && index < capacity)
				{
					++index;
					if (index < capacity && (*table)[index].next != nullptr)
						current = (*table)[index].next;
				}
			}

			Data* GetCurrent() const
			{
				return current;
			}

			bool IsEnd() const
			{
				return index >= capacity;
			}

			/*  Iteraor 사용법
				CTN::LinkedHashMap<Texture*>::Iterator iter(&(mapTexture.list), mapTexture.capacity);

				while (!iter.IsEnd())
				{
					CTN::LinkedHashMap<Texture*>::Data* data = iter.GetCurrent();
					if (data != nullptr)
						delete data;
					iter.Next();
				}
			*/
		};
	};
}
