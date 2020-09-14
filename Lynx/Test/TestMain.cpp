
#include "./SmartPtr/TestScopedPtr.hpp"
#include "./CircularQueue_V1/TestCircularQueue.hpp"

namespace Test
{

	int Main() noexcept
	{
		SmartPtr::TestScopedPtr();
		CircularQueue_V1::TestCircularQueue();
		return 0;
	}

} //# namespace Test
