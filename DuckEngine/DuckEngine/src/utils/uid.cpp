#include "de/utils/uid.h"
#include <mutex>

namespace de
{
	u64 g_last_uid = 0;
	std::mutex g_mutex = {};

	UID::UID()
	{
		g_mutex.lock();
		g_last_uid++;
		m_uid = g_last_uid;
		g_mutex.unlock();
	}
}