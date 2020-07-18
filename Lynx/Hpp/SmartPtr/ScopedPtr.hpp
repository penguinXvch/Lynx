
#pragma once

#include <cstddef>

namespace Lynx
{

	namespace SmartPtr
	{

		template<typename T>
		class ScopedPtr
		{
		public:
			ScopedPtr(ScopedPtr&) noexcept = delete;
			ScopedPtr(ScopedPtr&&) noexcept = delete;
			ScopedPtr(const ScopedPtr&) noexcept = delete;
			ScopedPtr(const ScopedPtr&&) noexcept = delete;
			ScopedPtr& operator=(ScopedPtr&) noexcept = delete;
			ScopedPtr& operator=(ScopedPtr&&) noexcept = delete;
			ScopedPtr& operator=(const ScopedPtr&) noexcept = delete;
			ScopedPtr& operator=(const ScopedPtr&&) noexcept = delete;
			bool operator==(const ScopedPtr&) const noexcept = delete;
			bool operator!=(const ScopedPtr&) const noexcept = delete;

		public:
			explicit ScopedPtr(T* ptr = nullptr) noexcept : _ptr(ptr)
			{
			}

			virtual ~ScopedPtr() noexcept
			{
				delete _ptr;
				_ptr = nullptr;
			}

			void Reset(T* ptr = nullptr) noexcept
			{
				delete _ptr;
				_ptr = ptr;
			}

			T& operator*() const noexcept
			{
				return *_ptr;
			}

			T* operator->() const noexcept
			{
				return _ptr;
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

			void Swap(ScopedPtr& sp) noexcept
			{
				T* tmp = *sp;
				*sp = _ptr;
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
	void Swap(SmartPtr::ScopedPtr<T>& a, SmartPtr::ScopedPtr<T>& b) noexcept
	{
		a.Swap(b);
	}

	template<typename T>
	bool operator==(const SmartPtr::ScopedPtr<T>& sp, std::nullptr_t) noexcept
	{
		return *sp == nullptr;
	}

	template<typename T>
	bool operator==(std::nullptr_t, const SmartPtr::ScopedPtr<T>& sp) noexcept
	{
		return *sp == nullptr;
	}

	template<typename T>
	bool operator!=(const SmartPtr::ScopedPtr<T>& sp, std::nullptr_t) noexcept
	{
		return *sp != nullptr;
	}

	template<typename T>
	bool operator!=(std::nullptr_t, const SmartPtr::ScopedPtr<T>& sp) noexcept
	{
		return *sp != nullptr;
	}

} //# namespace Lynx
