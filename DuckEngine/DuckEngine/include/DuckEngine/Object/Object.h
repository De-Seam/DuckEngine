#pragma once
#include "CoreLight.h"
#include "Utils/UID.h"

#define OBJECT Object(typeid(*this).name())

namespace DE
{
	class DUCK_API Object
	{
	public:
		Object(const char* className);
		~Object();

		const UID& GetUID() const { return m_uid; }
		const char* GetClassName() const { return className; }

	private:
		UID m_uid;
		const char* className;
	};
}