#include "de/utils/uid.h"
#include <mutex>

namespace de
{
	u64 g_last_uid = 0;
	std::mutex* g_mutex = nullptr;

	UID::UID()
	{
		if(!g_mutex)
			g_mutex = new std::mutex;

		g_mutex->lock();
		g_last_uid++;
		m_uid = g_last_uid;
		g_mutex->unlock();
	}
}