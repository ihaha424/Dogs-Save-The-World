#include "PathManager.h"
#include <Windows.h>

namespace game
{
	PathManager* PathManager::instance = nullptr;

	PathManager::PathManager() : resourcePath{} {}
	PathManager::~PathManager() {}

	PathManager* PathManager::GetInstance()
	{
		if (instance == nullptr)
		{
			instance = new PathManager();
		}
		return instance;
	}

	void PathManager::DestoryPathManager()
	{
		if (instance != nullptr)
		{
			delete instance;
			instance = nullptr;
		}
	}

	void PathManager::InitPathManager()
	{
		GetCurrentDirectoryA(255, resourcePath);
		// ..\Release\Resource
	
		int len = Strlen(resourcePath);
		//for (int i = len - 1; i >= 0; i--)
		//{
		//	if (resourcePath[i] == '\\')
		//	{
		//		len = i;
		//		break;
		//	}
		//}
		const char* Path = "\\Resource";
		for (int i = 0; Path[i] != '\0'; i++)
		{
			resourcePath[len++] = Path[i];
		}
		resourcePath[len] = '\0';
		//len이 255를 넘으면 터짐
	}

	const char* PathManager::GetResourcePath()
	{
		return resourcePath;
	}

	char* PathManager::Strjoin(char const* s1, char const* s2)
	{
		char* str;
		size_t		len1;
		size_t		len2;

		if (!s1 || !s2)
			return (NULL);
		len1 = Strlen(s1);
		len2 = Strlen(s2);
		str = (char*)malloc(sizeof(char) * (len1 + len2 + 1));
		if (!str)
			return (NULL);
		Memcpy(str, (char*)s1, len1);
		Memcpy(str + len1, (char*)s2, len2);
		str[len1 + len2] = '\0';
		return (str);
	}

	void PathManager::Memcpy(void* dst, const void* src, size_t n)
	{
		size_t			i;
		unsigned char* ndst;
		unsigned char* nsrc;

		ndst = (unsigned char*)dst;
		nsrc = (unsigned char*)src;
		if (ndst == NULL && src == NULL)
			return (void)(NULL);
		i = 0;
		while (i < n)
		{
			ndst[i] = nsrc[i];
			i++;
		}
		return (void)(ndst);
	}

	size_t PathManager::Strlen(const char* str)
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

}