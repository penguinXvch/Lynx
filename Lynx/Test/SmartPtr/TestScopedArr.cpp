
#include "../../SmartPtr/ScopedArr.hpp"
#include "../Tools.hpp"
#include <type_traits>

namespace Test
{

	namespace SmartPtr
	{

		void TestScopedArr() noexcept
		{
			using Test::Tools::TestProject;
			using Test::Tools::Test;
			using Test::Tools::PassTest;
			using Test::Tools::PassTestProject;
			using _Class = Test::Tools::Class;
			using _Method = Test::Tools::Method;
			using _Type = Test::Tools::Type;

			TestProject<_Class>("Lynx::SmartPtr::ScopedArr<T>");

			using Lynx::SmartPtr::ScopedArr;

			//# 测试 ScopedArr<T>::ScopedArr(T* ptr = nullptr)。
			Test<_Method>({ "ScopedArr<T>::ScopedArr(T* ptr = nullptr)" });
			{
				ScopedArr<int> sa1;
				PassOrFail(sa1.Get() == nullptr);

				ScopedArr<int> sa2(new int[2]{ 1, 2 });
				PassOrFail(sa2.Get() != nullptr);
			}
			PassTest();

			//# 测试 ScopedArr<T>::~ScopedArr()。
			Test<_Method>({ "ScopedArr<T>::~ScopedArr()" });
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
				PassOrFail(count == 0);

				{
					ScopedArr<Foo> sa(new Foo[2]{ Foo(&count), Foo(&count) });
					PassOrFail(count == 2);
				}

				PassOrFail(count == 0);
			}
			PassTest();

			//# 测试 ScopedArr<T>::ScopedArr(ScopedArr<T>&)。
			//# 测试 ScopedArr<T>::ScopedArr(ScopedArr<T>&&)。
			//# 测试 ScopedArr<T>::ScopedArr(const ScopedArr<T>&)。
			//# 测试 ScopedArr<T>::ScopedArr(const ScopedArr<T>&&)。
			//# 测试 ScopedArr<T>::ScopedArr<T>& ScopedArr<T>::operator=(ScopedArr<T>&)。
			//# 测试 ScopedArr<T>::ScopedArr<T>& ScopedArr<T>::operator=(ScopedArr<T>&&)。
			//# 测试 ScopedArr<T>::ScopedArr<T>& ScopedArr<T>::operator=(const ScopedArr<T>&)。
			//# 测试 ScopedArr<T>::ScopedArr<T>& ScopedArr<T>::operator=(const ScopedArr<T>&&)。
			Test<_Method, _Method, _Method, _Method, _Method, _Method, _Method, _Method>
			({
				"ScopedArr<T>::ScopedArr(ScopedArr<T>&)",
				"ScopedArr<T>::ScopedArr(ScopedArr<T>&&)",
				"ScopedArr<T>::ScopedArr(const ScopedArr<T>&)",
				"ScopedArr<T>::ScopedArr(const ScopedArr<T>&&)",
				"ScopedArr<T>::ScopedArr<T>& ScopedArr<T>::operator=(ScopedArr<T>&)",
				"ScopedArr<T>::ScopedArr<T>& ScopedArr<T>::operator=(ScopedArr<T>&&)",
				"ScopedArr<T>::ScopedArr<T>& ScopedArr<T>::operator=(const ScopedArr<T>&)",
				"ScopedArr<T>::ScopedArr<T>& ScopedArr<T>::operator=(const ScopedArr<T>&&)"
			});
			{
				// ScopedArr<int> sa(new int[1]);
				// ScopedArr<int> sa1 = sa;
				// sa1 = sa;
				// ScopedArr<int> sa2 = std::move(sa);
				// sa2 = std::move(sa);
			}
			PassTest();

			//# 测试 bool ScopedArr<T>::operator==(const ScopedArr<T>&)。
			//# 测试 bool ScopedArr<T>::operator!=(const ScopedArr<T>&)。
			Test<_Method, _Method>
			({
				"bool ScopedArr<T>::operator==(const ScopedArr<T>&)",
				"bool ScopedArr<T>::operator!=(const ScopedArr<T>&)"
			});
			{
				// ScopedArr<int> sa1(new int[1]);
				// ScopedArr<int> sa2(new int[1]);
				// sa1 == sa2;
				// sa2 == sa1;
				// sa1 != sa2;
				// sa2 != sa1;
			}
			PassTest();

			//# 测试 void ScopedArr<T>::Reset(T* ptr = nullptr)。
			//# 测试 T& ScopedArr<T>::operator[](const std::size_t&)。
			Test<_Method, _Method>
			({
				"void ScopedArr<T>::Reset(T* ptr = nullptr)",
				"T& ScopedArr<T>::operator[](const std::size_t&)"
			});
			{
				int* src = new int[3]{ 1, 2, 3 };

				ScopedArr<int> sa(new int[2]{ 10, 20 });
				PassOrFail(sa[0] == 10);
				PassOrFail(sa[1] == 20);

				sa[0] = 100;
				sa[1] = 200;
				PassOrFail(sa[0] == 100);
				PassOrFail(sa[1] == 200);

				sa.Reset(src);
				PassOrFail(sa[0] == 1);
				PassOrFail(sa[1] == 2);
				PassOrFail(sa[2] == 3);

				sa.Reset();
				PassOrFail(sa.Get() == nullptr);
			}
			PassTest();

			//# 测试 T* ScopedArr<T>::Get()。
			Test<_Method>({ "T* ScopedArr<T>::Get()" });
			{
				ScopedArr<int> sa1;
				PassOrFail(sa1.Get() == nullptr);

				ScopedArr<int> sa2(new int[2]{ 1, 2 });
				PassOrFail(sa2.Get() != nullptr);
				
				int* src = sa2.Get();
				PassOrFail(src[0] == 1);
				PassOrFail(src[1] == 2);

				src[0] = 10;
				src[1] = 20;
				PassOrFail(src[0] == 10);
				PassOrFail(src[1] == 20);
			}
			PassTest();

			//# 测试 T* ScopedArr<T>::Release()。
			Test<_Method>({ "T* ScopedArr<T>::Release()" });
			{
				ScopedArr<int> sa(new int[2]{ 1, 2 });
				int* src = sa.Release();
				
				PassOrFail(sa.Get() == nullptr);
				PassOrFail(src != nullptr);

				PassOrFail(src[0] == 1);
				PassOrFail(src[1] == 2);

				delete[] src;
				src = nullptr;

				int* src2 = sa.Release();
				PassOrFail(src2 == nullptr);
			}
			PassTest();

			//# 测试 ScopedArr<T>::operator bool()。
			Test<_Method>({ "ScopedArr<T>::operator bool()" });
			{
				ScopedArr<int> sa1;
				PassOrFail(bool(sa1) == false);

				ScopedArr<int> sa2(new int[2]{ 1, 2 });
				PassOrFail(bool(sa2) == true);
			}
			PassTest();

			//# 测试 void ScopedArr<T>::Swap(ScopedArr<T>&)。
			Test<_Method>({ "void ScopedArr<T>::Swap(ScopedArr<T>&)" });
			{
				ScopedArr<int> sa1;
				PassOrFail(bool(sa1) == false);

				ScopedArr<int> sa2(new int[2]{ 1, 2 });
				PassOrFail(bool(sa2) == true);

				sa1.Swap(sa2);

				PassOrFail(bool(sa1) == true);
				PassOrFail(bool(sa2) == false);

				PassOrFail(sa1[0] == 1);
				PassOrFail(sa1[1] == 2);
			}
			PassTest();

			//# 测试 ScopedArr<T>::ElementType。
			Test<_Type>({ "ScopedArr<T>::ElementType" });
			{
				PassOrFail
				(
					(std::is_same_v<ScopedArr<int>::ElementType, int> == 1)
				);
			}
			PassTest();

			//# 测试 void Lynx::Swap(ScopedArr<T>&, ScopedArr<T>&)。
			Test<_Method>({ "void Lynx::Swap(ScopedArr<T>&, ScopedArr<T>&)" });
			{
				ScopedArr<int> sa1;
				PassOrFail(bool(sa1) == false);

				ScopedArr<int> sa2(new int[2]{ 1, 2 });
				PassOrFail(bool(sa2) == true);

				// std::swap(sa1, sa2);
				Lynx::Swap(sa1, sa2);

				PassOrFail(bool(sa1) == true);
				PassOrFail(bool(sa2) == false);

				PassOrFail(sa1[0] == 1);
				PassOrFail(sa1[1] == 2);
			}
			PassTest();

			//# 测试 bool Lynx::operator==(const ScopedArr<T>&, std::nullptr_t)。
			//# 测试 bool Lynx::operator==(std::nullptr_t, const ScopedArr<T>&)。
			//# 测试 bool Lynx::operator!=(const ScopedArr<T>&, std::nullptr_t)。
			//# 测试 bool Lynx::operator!=(std::nullptr_t, const ScopedArr<T>&)。
			Test<_Method, _Method, _Method, _Method>
			({
				"bool Lynx::operator==(const ScopedArr<T>&, std::nullptr_t)",
				"bool Lynx::operator==(std::nullptr_t, const ScopedArr<T>&)",
				"bool Lynx::operator!=(const ScopedArr<T>&, std::nullptr_t)",
				"bool Lynx::operator!=(std::nullptr_t, const ScopedArr<T>&)"
			});
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
			PassTest();

			PassTestProject();
		}

	} //# namespace SmartPtr

} //# namespace Test
