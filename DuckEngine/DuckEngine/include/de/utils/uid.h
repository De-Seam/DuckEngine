#pragma once
#include "variables.h"

#ifdef DUCK_EXPORTS
#define DUCK_API __declspec(dllexport)
#else
#define DUCK_API __declspec(dllimport)
#endif

namespace de
{
	class DUCK_API UID
	{
	public:
		UID();
		UID(const UID& other) = default;

		operator u64() const { return m_uid; }
	private:
		u64 m_uid;
	};
}

#include <vcruntime.h>

namespace std 
{
	template <typename T> struct hash;

	template<>
	struct hash<de::UID>
	{
		size_t operator()(const de::UID& uid) const
		{
			return uid;
		}
	};

}