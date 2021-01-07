
#include "../../SmartPtr/ScopedPtr.hpp"
#include "../Tools.hpp"
#include <type_traits>

namespace Test
{

	namespace SmartPtr
	{

		void TestScopedPtr() noexcept
		{
			using Test::Tools::TestProject;
			using Test::Tools::Test;
			using Test::Tools::PassTest;
			using Test::Tools::PassTestProject;
			using _Class = Test::Tools::Class;
			using _Method = Test::Tools::Method;
			using _Type = Test::Tools::Type;

			TestProject<_Class>("Lynx::SmartPtr::ScopedPtr<T>");

			using Lynx::SmartPtr::ScopedPtr;

			//# 测试 ScopedPtr<T>::ScopedPtr(T* ptr = nullptr)。
			Test<_Method>({ "ScopedPtr<T>::ScopedPtr(T* ptr = nullptr)" });
			{
				ScopedPtr<int> sp1;
				PassOrFail(sp1.Get() == nullptr);

				ScopedPtr<int> sp2(new int(1));
				PassOrFail(sp2.Get() != nullptr);
			}
			PassTest();

			//# 测试 ScopedPtr<T>::ScopedPtr(T* ptr = nullptr)。
			//# 测试 ScopedPtr<T>::~ScopedPtr()。
			Test<_Method, _Method>
			({
				"ScopedPtr<T>::ScopedPtr(T* ptr = nullptr)",
				"ScopedPtr<T>::~ScopedPtr()"
			});
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
					PassOrFail(value == -1);

					ScopedPtr<Foo> sp(new Foo(&value));
					PassOrFail(static_cast<bool>(sp));
					PassOrFail(value == 1);
				}

				PassOrFail(value == 0);
			}
			PassTest();

			//# 测试 ScopedPtr<T>::ScopedPtr(ScopedPtr<T>&)。
			//# 测试 ScopedPtr<T>::ScopedPtr(ScopedPtr<T>&&)。
			//# 测试 ScopedPtr<T>::ScopedPtr(const ScopedPtr<T>&)。
			//# 测试 ScopedPtr<T>::ScopedPtr(const ScopedPtr<T>&&)。
			//# 测试 ScopedPtr<T>::ScopedPtr<T>& ScopedPtr<T>::operator=(ScopedPtr<T>&)。
			//# 测试 ScopedPtr<T>::ScopedPtr<T>& ScopedPtr<T>::operator=(ScopedPtr<T>&&)。
			//# 测试 ScopedPtr<T>::ScopedPtr<T>& ScopedPtr<T>::operator=(const ScopedPtr<T>&)。
			//# 测试 ScopedPtr<T>::ScopedPtr<T>& ScopedPtr<T>::operator=(const ScopedPtr<T>&&)。
			Test<_Method, _Method, _Method, _Method, _Method, _Method, _Method, _Method>
			({
				"ScopedPtr<T>::ScopedPtr(ScopedPtr<T>&)",
				"ScopedPtr<T>::ScopedPtr(ScopedPtr<T>&&)",
				"ScopedPtr<T>::ScopedPtr(const ScopedPtr<T>&)",
				"ScopedPtr<T>::ScopedPtr(const ScopedPtr<T>&&)",
				"ScopedPtr<T>::ScopedPtr<T>& ScopedPtr<T>::operator=(ScopedPtr<T>&)",
				"ScopedPtr<T>::ScopedPtr<T>& ScopedPtr<T>::operator=(ScopedPtr<T>&&)",
				"ScopedPtr<T>::ScopedPtr<T>& ScopedPtr<T>::operator=(const ScopedPtr<T>&)",
				"ScopedPtr<T>::ScopedPtr<T>& ScopedPtr<T>::operator=(const ScopedPtr<T>&&)"
			});
			{
				// ScopedPtr<int> sp(new int(1));
				// ScopedPtr<int> sp1 = sp;
				// sp1 = sp;
				// ScopedPtr<int> sp2 = std::move(sp);
				// sp2 = std::move(sp);
			}
			PassTest();

			//# 测试 bool ScopedPtr<T>::operator==(const ScopedPtr<T>&)。
			//# 测试 bool ScopedPtr<T>::operator!=(const ScopedPtr<T>&)。
			Test<_Method, _Method>
			({
				"bool ScopedPtr<T>::operator==(const ScopedPtr<T>&)",
				"bool ScopedPtr<T>::operator!=(const ScopedPtr<T>&)"
			});
			{
				// ScopedPtr<int> sp1(new int(1));
				// ScopedPtr<int> sp2(new int(1));
				// sp1 == sp2;
				// sp2 == sp1;
				// sp1 != sp2;
				// sp2 != sp1;
			}
			PassTest();

			//# 测试 void ScopedPtr<T>::Reset(T* ptr = nullptr)。
			Test<_Method>({ "void ScopedPtr<T>::Reset(T* ptr = nullptr)" });
			{
				ScopedPtr<int> sp(new int);
				PassOrFail(sp.Get() != nullptr);

				sp.Reset();
				PassOrFail(sp.Get() == nullptr);

				int* ptr = new int;
				sp.Reset(ptr);
				PassOrFail(ptr != nullptr);
				PassOrFail(sp.Get() != nullptr);
				PassOrFail(sp.Get() == ptr);
			}
			PassTest();

			//# 测试 T* ScopedPtr<T>::Get()。
			//# 测试 T& ScopedPtr<T>::operator*()。
			Test<_Method, _Method>
			({
				"T* ScopedPtr<T>::Get()",
				"T& ScopedPtr<T>::operator*()"
			});
			{
				int* ptr = new int(1);
				PassOrFail(ptr);

				ScopedPtr<int> sp(ptr);
				PassOrFail(sp && sp.Get());

				PassOrFail(sp.Get() == ptr);
				PassOrFail(*sp == 1 && *ptr == 1);

				*sp = 2;
				PassOrFail(*sp == 2 && *ptr == 2);

				*(sp.Get()) = 3;
				PassOrFail(*(sp.Get()) == 3 && *ptr == 3);
			}
			PassTest();

			//# 测试 T* ScopedPtr<T>::operator->()。
			Test<_Method>({ "T* ScopedPtr<T>::operator->()" });
			{
				struct Foo
				{
					int value = 1;
				};

				ScopedPtr<Foo> sp(new Foo);
				PassOrFail(sp->value == 1);

				sp->value = 10;
				PassOrFail(sp->value != 1 && sp->value == 10);
			}
			PassTest();

			//# 测试 T* ScopedPtr<T>::Release()。
			Test<_Method>({ "T* ScopedPtr<T>::Release()" });
			{
				int* ptr = new int;

				ScopedPtr<int> sp(ptr);
				PassOrFail(sp.Get() != nullptr);
				PassOrFail(sp.Release() == ptr);
				PassOrFail(sp.Get() == nullptr);

				ScopedPtr<int> sp1(ptr);
				PassOrFail(sp1.Get() != nullptr);

				ScopedPtr<int> sp2(sp1.Release());
				PassOrFail(sp1.Get() == nullptr);
				PassOrFail(sp2.Get() == ptr);
			}
			PassTest();

			//# 测试 ScopedPtr<T>::operator bool()。
			Test<_Method>({ "ScopedPtr<T>::operator bool()" });
			{
				ScopedPtr<int> sp(new int);
				PassOrFail(bool(sp) == true);
				sp.Reset();
				PassOrFail(bool(sp) == false);
			}
			PassTest();

			//# 测试 void ScopedPtr<T>::Swap(ScopedPtr<T>&)。
			Test<_Method>({ "void ScopedPtr<T>::Swap(ScopedPtr<T>&)" });
			{
				int* ptr1 = new int(1);
				int* ptr2 = new int(2);

				ScopedPtr<int> sp1(ptr1);
				ScopedPtr<int> sp2(ptr2);
				PassOrFail(*sp1 == 1);
				PassOrFail(*sp2 == 2);
				PassOrFail(sp1.Get() == ptr1);
				PassOrFail(sp2.Get() == ptr2);
				
				sp1.Swap(sp2);
				PassOrFail(*sp1 == 2);
				PassOrFail(*sp2 == 1);
				PassOrFail(sp1.Get() == ptr2);
				PassOrFail(sp2.Get() == ptr1);
			}
			PassTest();

			//# 测试 ScopedPtr<T>::ElementType。
			Test<_Type>({ "ScopedPtr<T>::ElementType" });
			{
				ScopedPtr<int> sp(new int);
				PassOrFail((std::is_same_v<ScopedPtr<int>::ElementType, int> == 1));
			}
			PassTest();

			//# 禁止使用 ScopedPtr<T[]> 的特化。
			Test<_Class>({ "ban : ScopedPtr<T[]>" });
			{
				// ScopedPtr<int[]> sp1;
				// ScopedPtr<int[]> sp2(new int[10]);
			}
			PassTest();

			//# 测试 void Lynx::Swap(ScopedPtr<T>&, ScopedPtr<T>&)。
			Test<_Method>({ "void Lynx::Swap(ScopedPtr<T>&, ScopedPtr<T>&)" });
			{
				int* ptr1 = new int(1);
				int* ptr2 = new int(2);

				ScopedPtr<int> sp1(ptr1);
				ScopedPtr<int> sp2(ptr2);
				PassOrFail(*sp1 == 1);
				PassOrFail(*sp2 == 2);
				PassOrFail(sp1.Get() == ptr1);
				PassOrFail(sp2.Get() == ptr2);

				Lynx::Swap(sp1, sp2);
				PassOrFail(*sp1 == 2);
				PassOrFail(*sp2 == 1);
				PassOrFail(sp1.Get() == ptr2);
				PassOrFail(sp2.Get() == ptr1);
			}
			PassTest();

			//# 测试 bool Lynx::operator==(const ScopedPtr<T>&, std::nullptr_t)。
			//# 测试 bool Lynx::operator==(std::nullptr_t, const ScopedPtr<T>&)。
			//# 测试 bool Lynx::operator!=(const ScopedPtr<T>&, std::nullptr_t)。
			//# 测试 bool Lynx::operator!=(std::nullptr_t, const ScopedPtr<T>&)。
			Test<_Method, _Method, _Method, _Method>
			({
				"bool Lynx::operator==(const ScopedPtr<T>&, std::nullptr_t)",
				"bool Lynx::operator==(std::nullptr_t, const ScopedPtr<T>&)",
				"bool Lynx::operator!=(const ScopedPtr<T>&, std::nullptr_t)",
				"bool Lynx::operator!=(std::nullptr_t, const ScopedPtr<T>&)"
			});
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
			PassTest();

			PassTestProject();
		}

	} //# namespace SmartPtr

} //# namespace Test
