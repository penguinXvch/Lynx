
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

			//# 测试 ScopedPtr::Reset。
			{
				ScopedPtr<int> sp(new int);
				assert(sp.Get() != nullptr);

				sp.Reset();
				assert(sp.Get() == nullptr);

				int* ptr = new int;
				sp.Reset(ptr);
				assert(ptr != nullptr);
				assert(sp.Get() != nullptr);
				assert(sp.Get() == ptr);
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

			//# 测试 ScopedPtr::operator->。
			{
				struct Foo
				{
					int value = 1;
				};

				ScopedPtr<Foo> sp(new Foo);
				assert(sp->value == 1);

				sp->value = 10;
				assert(sp->value != 1 && sp->value == 10);
			}

			//# 测试 ScopedPtr::Release。
			{
				int* ptr = new int;

				ScopedPtr<int> sp(ptr);
				assert(sp.Get() != nullptr);
				assert(sp.Release() == ptr);
				assert(sp.Get() == nullptr);

				ScopedPtr<int> sp1(ptr);
				assert(sp1.Get() != nullptr);

				ScopedPtr<int> sp2(sp1.Release());
				assert(sp1.Get() == nullptr);
				assert(sp2.Get() == ptr);
			}

			//# 测试 ScopedPtr::operator bool。
			{
				ScopedPtr<int> sp(new int);
				assert(bool(sp) == true);
				sp.Reset();
				assert(bool(sp) == false);
			}

			//# 测试 ScopedPtr::Swap。
			{
				int* ptr1 = new int(1);
				int* ptr2 = new int(2);

				ScopedPtr<int> sp1(ptr1);
				ScopedPtr<int> sp2(ptr2);
				assert(*sp1 == 1);
				assert(*sp2 == 2);
				assert(sp1.Get() == ptr1);
				assert(sp2.Get() == ptr2);
				
				sp1.Swap(sp2);
				assert(*sp1 == 2);
				assert(*sp2 == 1);
				assert(sp1.Get() == ptr2);
				assert(sp2.Get() == ptr1);
			}

			//# 测试 ScopedPtr::ElementType。
			{
				ScopedPtr<int> sp(new int);
				assert((std::is_same_v<ScopedPtr<int>::ElementType, int> == 1));
			}

			//# 禁止使用 ScopedPtr 针对 T[] 的特化。
			{
				// ScopedPtr<int[]> sp1;
				// ScopedPtr<int[]> sp2(new int[10]);
			}

			//# 测试 Lynx::Swap。
			{
				int* ptr1 = new int(1);
				int* ptr2 = new int(2);

				ScopedPtr<int> sp1(ptr1);
				ScopedPtr<int> sp2(ptr2);
				assert(*sp1 == 1);
				assert(*sp2 == 2);
				assert(sp1.Get() == ptr1);
				assert(sp2.Get() == ptr2);

				Lynx::Swap(sp1, sp2);
				assert(*sp1 == 2);
				assert(*sp2 == 1);
				assert(sp1.Get() == ptr2);
				assert(sp2.Get() == ptr1);
			}

			//# 测试 Lynx::operator== 和 Lynx::operator!=。
			{
				using Lynx::operator==;
				using Lynx::operator!=;

				ScopedPtr<int> sp;
				sp == nullptr;
				nullptr == sp;

				sp.Reset(new int);
				sp != nullptr;
				nullptr != sp;
			}
		}

	} //# namespace SmartPtr

} //# namespace Test
