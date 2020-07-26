
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

		public:
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
				T* tmp = sp.Release();
				sp.Reset(_ptr);
				_ptr = tmp;
			}

		public:
			using ElementType = T;

		private:
			T* _ptr;
		};


		//# 禁止使用 ScopedPtr 针对 T[] 的特化。
		template<typename T>
		class ScopedPtr<T[]>
		{
		public:
			ScopedPtr(T* ptr = nullptr) noexcept = delete;
			virtual ~ScopedPtr() noexcept = delete;
			ScopedPtr(ScopedPtr&) noexcept = delete;
			ScopedPtr(ScopedPtr&&) noexcept = delete;
			ScopedPtr(const ScopedPtr&) noexcept = delete;
			ScopedPtr(const ScopedPtr&&) noexcept = delete;
			ScopedPtr& operator=(ScopedPtr&) noexcept = delete;
			ScopedPtr& operator=(ScopedPtr&&) noexcept = delete;
			ScopedPtr& operator=(const ScopedPtr&) noexcept = delete;
			ScopedPtr& operator=(const ScopedPtr&&) noexcept = delete;
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
		return sp.Get() == nullptr;
	}

	template<typename T>
	bool operator==(std::nullptr_t, const SmartPtr::ScopedPtr<T>& sp) noexcept
	{
		return sp.Get() == nullptr;
	}

	template<typename T>
	bool operator!=(const SmartPtr::ScopedPtr<T>& sp, std::nullptr_t) noexcept
	{
		return sp.Get() != nullptr;
	}

	template<typename T>
	bool operator!=(std::nullptr_t, const SmartPtr::ScopedPtr<T>& sp) noexcept
	{
		return sp.Get() != nullptr;
	}

} //# namespace Lynx
