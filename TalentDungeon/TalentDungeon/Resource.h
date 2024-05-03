#pragma once

namespace game
{
	class Resource
	{
	private:
		const char* resKey;
		const char* resPath;

	public:
		Resource();
		~Resource();

		void SetKey(const char* _resKey);
		void SetPath(const char* _resPath);

		const char* GetKey();
		const char* GetPath();
	};
}