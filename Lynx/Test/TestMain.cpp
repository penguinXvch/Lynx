
#include "./SmartPtr/TestScopedPtr.hpp"
#include "./CircularQueue_ThreadSafety_V1/TestCircularQueue.hpp"

namespace Test
{

	int Main() noexcept
	{
		SmartPtr::TestScopedPtr();
		CircularQueue_ThreadSafety_V1::TestCircularQueue();
		return 0;
	}

} //# namespace Test
