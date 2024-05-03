#pragma once

namespace game
{
	class PathManager
	{
	private:
		static PathManager* instance;
		//���� �����쿡�� �ּ� ���� �ִ�ġ 255
		char resourcePath[255];

	private:
		PathManager();
		~PathManager();

		void Memcpy(void* dst, const void* src, size_t n);
		size_t	Strlen(const char* str);
	
	public:
		static PathManager* GetInstance();
		static void DestoryPathManager();

		void InitPathManager();
		const char* GetResourcePath();
		char* Strjoin(char const* s1, char const* s2);
	};
}
