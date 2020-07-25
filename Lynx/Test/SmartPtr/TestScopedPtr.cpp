
#include "../../SmartPtr/ScopedPtr.hpp"
#include <cassert>
#include <type_traits>

namespace Test
{

	namespace SmartPtr
	{

		void TestScopedPtr() noexcept
		{
			using Lynx::SmartPtr::ScopedPtr;

			//# 测试 ScopedPtr::ScopedPtr(T* ptr = nullptr)。
			{
				ScopedPtr<int> sp1;
				assert(sp1.Get() == nullptr);

				ScopedPtr<int> sp2(new int(1));
				assert(sp2.Get() != nullptr);
			}

			//# 测试 ScopedPtr::ScopedPtr(T* ptr = nullptr)。
			//# 测试 ScopedPtr::~ScopedPtr。
			{
				class Foo
				{
				public:
					explicit Foo(int* flag) noexcept
						: _flag(flag)
					{
						*_flag = 1;
					}

					virtual ~Foo() noexcept
					{
						*_flag = 0;
					}

				private:
					int* _flag = nullptr;
				};

				int value = -1;

				{
					assert(value == -1);

					ScopedPtr<Foo> sp(new Foo(&value));
					assert(sp);
					assert(value == 1);
				}

				assert(value == 0);
			}

			//# 测试 ScopedPtr::ScopedPtr(ScopedPtr&)。
			//# 测试 ScopedPtr::ScopedPtr(ScopedPtr&&)。
			//# 测试 ScopedPtr::ScopedPtr(const ScopedPtr&)。
			//# 测试 ScopedPtr::ScopedPtr(const ScopedPtr&&)。
			//# 测试 ScopedPtr::operator=(ScopedPtr&)。
			//# 测试 ScopedPtr::operator=(ScopedPtr&&)。
			//# 测试 ScopedPtr::operator=(const ScopedPtr&)。
			//# 测试 ScopedPtr::operator=(const ScopedPtr&&)。
			{
				// ScopedPtr<int> sp(new int(1));
				// ScopedPtr<int> sp1 = sp;
				// sp1 = sp;
				// ScopedPtr<int> sp2 = std::move(sp);
				// sp2 = std::move(sp);
			}

			//# 测试 ScopedPtr::operator==(const ScopedPtr&)。
			//# 测试 ScopedPtr::operator!=(const ScopedPtr&)。
			{
				// ScopedPtr<int> sp1(new int(1));
				// ScopedPtr<int> sp2(new int(1));
				// sp1 == sp2;
				// sp2 == sp1;
				// sp1 != sp2;
				// sp2 != sp1;
			}

			//# 测试 ScopedPtr::Get。
			//# 测试 ScopedPtr::operator*。
			{
				int* ptr = new int(1);
				assert(ptr);

				ScopedPtr<int> sp(ptr);
				assert(sp && sp.Get());

				assert(sp.Get() == ptr);
				assert(*sp == 1 && *ptr == 1);

				*sp = 2;
				assert(*sp == 2 && *ptr == 2);

				*(sp.Get()) = 3;
				assert(*(sp.Get()) == 3 && *ptr == 3);
			}
		}

	} //# namespace SmartPtr

} //# namespace Test
