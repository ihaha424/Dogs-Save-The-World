#include "Resource.h"

namespace game
{
	Resource::Resource() {}

	Resource::~Resource() {}

	void Resource::SetKey(const char* _resKey)
	{
		resKey = _resKey;
	}

	void Resource::SetPath(const char* _resPath)
	{
		resPath = _resPath;
	}

	const char* Resource::GetKey()
	{
		return resKey;
	}

	const char* Resource::GetPath()
	{
		return resPath;
	}
}
