#include "Utils/UID.h"
#include <mutex>

namespace DE
{
	u64 g_lastUID = 0;
	std::mutex* g_mutex = nullptr;

	UID::UID()
	{
		if (!g_mutex)
			g_mutex = new std::mutex;

		g_mutex->lock();
		g_lastUID++;
		m_uid = g_lastUID;
		g_mutex->unlock();
	}
}