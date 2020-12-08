
#include "../../SmartPtr/ScopedArr.hpp"
#include <cassert>
#include <type_traits>

namespace Test
{

	namespace SmartPtr
	{

		void TestScopedArr() noexcept
		{
			using Lynx::SmartPtr::ScopedArr;

			//# 测试 ScopedArr::ScopedArr(T* ptr = nullptr)。
			{
				ScopedArr<int> sa1;
				assert(sa1.Get() == nullptr);

				ScopedArr<int> sa2(new int[2]{ 1, 2 });
				assert(sa2.Get() != nullptr);
			}

			//# 测试 ScopedArr::~ScopedArr。
			{
				class Foo
				{
				public:
					Foo(int* count) : _count(count)
					{
						++(*_count);
					}
					~Foo()
					{
						--(*_count);
					}

				public:
					int* _count = nullptr;
				};

				int count = 0;
				
				{
					ScopedArr<Foo> sa3(new Foo[2]{ Foo(&count), Foo(&count) });
					assert(count == 2);
				}

				assert(count == 0);
			}

			//# 测试 ScopedArr::ScopedArr(ScopedArr&)。
			//# 测试 ScopedArr::ScopedArr(ScopedArr&&)。
			//# 测试 ScopedArr::ScopedArr(const ScopedArr&)。
			//# 测试 ScopedArr::ScopedArr(const ScopedArr&&)。
			//# 测试 ScopedArr::operator=(ScopedArr&)。
			//# 测试 ScopedArr::operator=(ScopedArr&&)。
			//# 测试 ScopedArr::operator=(const ScopedArr&)。
			//# 测试 ScopedArr::operator=(const ScopedArr&&)。
			{
				// ScopedArr<int> sa(new int[1]);
				// ScopedArr<int> sa1 = sa;
				// sa1 = sa;
				// ScopedArr<int> sa2 = std::move(sa);
				// sa2 = std::move(sa);
			}

			//# 测试 ScopedArr::operator==(const ScopedArr&)。
			//# 测试 ScopedArr::operator!=(const ScopedArr&)。
			{
				// ScopedArr<int> sa1(new int[1]);
				// ScopedArr<int> sa2(new int[1]);
				// sa1 == sa2;
				// sa2 == sa1;
				// sa1 != sa2;
				// sa2 != sa1;
			}

			//# 测试 ScopedArr::Reset。
			//# 测试 ScopedArr::operator[](const std::size_t&)。
			{
				int* src = new int[3]{ 1, 2, 3 };

				ScopedArr<int> sa(new int[2]{ 10, 20 });
				assert(sa[0] == 10);
				assert(sa[1] == 20);

				sa[0] = 100;
				sa[1] = 200;
				assert(sa[0] == 100);
				assert(sa[1] == 200);

				sa.Reset(src);
				assert(sa[0] == 1);
				assert(sa[1] == 2);
				assert(sa[2] == 3);

				sa.Reset();
				assert(sa.Get() == nullptr);
			}

			//# 测试 ScopedArr::Get。
			{
				ScopedArr<int> sa1;
				assert(sa1.Get() == nullptr);

				ScopedArr<int> sa2(new int[2]{ 1, 2 });
				assert(sa2.Get() != nullptr);
				
				int* src = sa2.Get();
				assert(src[0] == 1);
				assert(src[1] == 2);

				src[0] = 10;
				src[1] = 20;
				assert(src[0] == 10);
				assert(src[1] == 20);
			}

			//# 测试 ScopedArr::Release。
			{
				ScopedArr<int> sa(new int[2]{ 1, 2 });
				int* src = sa.Release();
				
				assert(sa.Get() == nullptr);
				assert(src != nullptr);

				assert(src[0] == 1);
				assert(src[1] == 2);

				delete[] src;
				src = nullptr;

				int* src2 = sa.Release();
				assert(src2 == nullptr);
			}

			//# 测试 ScopedArr::operator bool
			{
				ScopedArr<int> sa1;
				assert(bool(sa1) == false);

				ScopedArr<int> sa2(new int[2]{ 1, 2 });
				assert(bool(sa2) == true);
			}

			//# 测试 ScopedArr::Swap(ScopedArr&)
			{
				ScopedArr<int> sa1;
				assert(bool(sa1) == false);

				ScopedArr<int> sa2(new int[2]{ 1, 2 });
				assert(bool(sa2) == true);

				sa1.Swap(sa2);

				assert(bool(sa1) == true);
				assert(bool(sa2) == false);

				assert(sa1[0] == 1);
				assert(sa1[1] == 2);
			}

			//# 测试 ScopedArr::ElementType
			{
				assert
				(
					(std::is_same_v<ScopedArr<int>::ElementType, int> == 1)
				);
			}

			//# 测试 Lynx::Swap。
			{
				ScopedArr<int> sa1;
				assert(bool(sa1) == false);

				ScopedArr<int> sa2(new int[2]{ 1, 2 });
				assert(bool(sa2) == true);

				// std::swap(sa1, sa2);
				Lynx::Swap(sa1, sa2);

				assert(bool(sa1) == true);
				assert(bool(sa2) == false);

				assert(sa1[0] == 1);
				assert(sa1[1] == 2);
			}

			//# 测试 Lynx::operator== 和 Lynx::operator!=。
			{
				using Lynx::operator==;
				using Lynx::operator!=;

				ScopedArr<int> sa;
				sa == nullptr;
				nullptr == sa;

				sa.Reset(new int[1]);
				sa != nullptr;
				nullptr != sa;
			}
		}

	} //# namespace SmartPtr

} //# namespace Test
