
#pragma once

#include <cstddef>

namespace Lynx
{

	namespace SmartPtr
	{

		template<typename T>
		class ScopedArr
		{
		public:
			ScopedArr(ScopedArr&) noexcept = delete;
			ScopedArr(ScopedArr&&) noexcept = delete;
			ScopedArr(const ScopedArr&) noexcept = delete;
			ScopedArr(const ScopedArr&&) noexcept = delete;
			ScopedArr& operator=(ScopedArr&) noexcept = delete;
			ScopedArr& operator=(ScopedArr&&) noexcept = delete;
			ScopedArr& operator=(const ScopedArr&) noexcept = delete;
			ScopedArr& operator=(const ScopedArr&&) noexcept = delete;
			bool operator==(const ScopedArr&) const noexcept = delete;
			bool operator!=(const ScopedArr&) const noexcept = delete;

		public:
			explicit ScopedArr(T* ptr = nullptr) noexcept : _ptr(ptr)
			{
			}

			virtual ~ScopedArr() noexcept
			{
				delete[] _ptr;
				_ptr = nullptr;
			}

		public:
			void Reset(T* ptr = nullptr) noexcept
			{
				delete[] _ptr;
				_ptr = ptr;
			}

			T& operator[](const std::size_t& index) const noexcept
			{
				return _ptr[index];
			}

			T* Get() const noexcept
			{
				return _ptr;
			}

			T* Release() noexcept
			{
				T* ptr = _ptr;
				_ptr = nullptr;
				return ptr;
			}

			explicit operator bool() const noexcept
			{
				return static_cast<bool>(_ptr);
			}

			void Swap(ScopedArr& sa) noexcept
			{
				T* tmp = sa.Release();
				sa.Reset(_ptr);
				_ptr = tmp;
			}

		public:
			using ElementType = T;

		private:
			T* _ptr;
		};

	} //# namespace SmartPtr

} //# namespace Lynx


namespace Lynx
{

	template<typename T>
	void Swap(SmartPtr::ScopedArr<T>& a, SmartPtr::ScopedArr<T>& b) noexcept
	{
		a.Swap(b);
	}

	template<typename T>
	bool operator==(const SmartPtr::ScopedArr<T>& sp, std::nullptr_t) noexcept
	{
		return sp.Get() == nullptr;
	}

	template<typename T>
	bool operator==(std::nullptr_t, const SmartPtr::ScopedArr<T>& sp) noexcept
	{
		return sp.Get() == nullptr;
	}

	template<typename T>
	bool operator!=(const SmartPtr::ScopedArr<T>& sp, std::nullptr_t) noexcept
	{
		return sp.Get() != nullptr;
	}

	template<typename T>
	bool operator!=(std::nullptr_t, const SmartPtr::ScopedArr<T>& sp) noexcept
	{
		return sp.Get() != nullptr;
	}

} //# namespace Lynx
