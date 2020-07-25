
#include "../../SmartPtr/ScopedPtr.hpp"
#include <cassert>

namespace Test
{

	namespace SmartPtr
	{

		void TestScopedPtr() noexcept
		{
			//# 测试 ScopedPtr::ScopedPtr。
			{
				int* ptr = new int(1);
				Lynx::SmartPtr::ScopedPtr<int> sp(ptr);
				assert(sp);
				assert(sp.Get() == ptr);
				assert(*sp == 1 && *ptr == 1);
			}
		}

	} //# namespace SmartPtr

} //# namespace Test
