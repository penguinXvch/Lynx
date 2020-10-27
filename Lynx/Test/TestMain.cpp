
#include "./SmartPtr/TestScopedPtr.hpp"
#include "./CircularQueue_ThreadSafety_V1/TestCircularQueueV1.hpp"
#include "./CircularQueue_ThreadSafety_V2/TestCircularQueueV2.hpp"

namespace Test
{

	int Main() noexcept
	{
		SmartPtr::TestScopedPtr();
		CircularQueue_ThreadSafety_V1::TestCircularQueue();
		CircularQueue_ThreadSafety_V2::TestCircularQueue();
		return 0;
	}

} //# namespace Test
