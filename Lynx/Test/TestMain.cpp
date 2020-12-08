
#include "./SmartPtr/TestScopedPtr.hpp"
#include "./SmartPtr/TestScopedArr.hpp"
#include "./CircularQueue_ThreadSafety_V1/TestCircularQueueV1.hpp"
#include "./CircularQueue_ThreadSafety_V2/TestCircularQueueV2.hpp"
#include "./Note/TestNote.hpp"

namespace Test
{

	int Main() noexcept
	{
		SmartPtr::TestScopedPtr();
		SmartPtr::TestScopedArr();
		CircularQueue_ThreadSafety_V1::TestCircularQueue();
		CircularQueue_ThreadSafety_V2::TestCircularQueue();
		Note::TestNote();
		return 0;
	}

} //# namespace Test
