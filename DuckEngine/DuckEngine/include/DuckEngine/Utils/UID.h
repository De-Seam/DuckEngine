#pragma once
#include "Variables.h"

namespace DE
{
	class UID
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
	struct hash<DE::UID>
	{
		size_t operator()(const DE::UID& uid) const
		{
			return uid;
		}
	};

}