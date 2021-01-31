
#pragma once

#include <vector>
#include <mutex>

namespace Lynx
{

	namespace CircularQueue_ThreadSafety_V1
	{

		/*
		 *  线程安全的循环队列：
		 *      1. 向循环队列尾部覆盖写入最新数据。
		 *      2. 一次性从循环队列头部读取数据直到循环队列尾部结束。
		 */
		template<typename T>
		class CircularQueue
		{
		public:
			explicit CircularQueue() noexcept;
			explicit CircularQueue(const std::size_t& len);
			virtual ~CircularQueue() noexcept;

		public:
			CircularQueue(CircularQueue<T>&) noexcept = delete;
			CircularQueue(CircularQueue<T>&&) noexcept = delete;
			CircularQueue(const CircularQueue<T>&) noexcept = delete;
			CircularQueue(const CircularQueue<T>&&) noexcept = delete;
			CircularQueue<T>& operator=(CircularQueue<T>&) noexcept = delete;
			CircularQueue<T>& operator=(CircularQueue<T>&&) noexcept = delete;
			CircularQueue<T>& operator=(const CircularQueue<T>&) noexcept = delete;
			CircularQueue<T>& operator=(const CircularQueue<T>&&) noexcept = delete;

		public:
			void SetCircularQueueSize(const std::size_t& len);
			void ResizeCircularQueueSize(const std::size_t& len);
			std::size_t GetCircularQueueSize() noexcept;

		public:
			bool AddData(const T& data) noexcept;
			std::vector<T> GetData() noexcept;

		private:
			T* mArr;
			std::size_t mLen;

		private:
			std::size_t mFrontPointer;
			std::size_t mBackPointer;
			std::size_t mCount;

		private:
			std::mutex mMutex;
		};

		template<typename T>
		CircularQueue<T>::CircularQueue() noexcept
			: mArr(nullptr), mLen(0), mFrontPointer(0), mBackPointer(0), mCount(0), mMutex()
		{
		}

		template<typename T>
		CircularQueue<T>::CircularQueue(const std::size_t& len)
			: mArr(nullptr), mLen(0), mFrontPointer(0), mBackPointer(0), mCount(0), mMutex()
		{
			std::lock_guard<std::mutex> _(mMutex);

			mLen = len;

			if (mLen != 0)
			{
				mArr = new T[mLen];
			}
		}

		template<typename T>
		CircularQueue<T>::~CircularQueue() noexcept
		{
			std::lock_guard<std::mutex> _(mMutex);

			if (mArr != nullptr)
			{
				delete[] mArr;
				mArr = nullptr;
			}
		}

		template<typename T>
		void CircularQueue<T>::SetCircularQueueSize(const std::size_t& len)
		{
			std::lock_guard<std::mutex> _(mMutex);

			if (mArr == nullptr && len != 0)
			{
				mLen = len;
				mArr = new T[mLen];
			}
		}

		template<typename T>
		void CircularQueue<T>::ResizeCircularQueueSize(const std::size_t& len)
		{
			std::lock_guard<std::mutex> _(mMutex);

			// TODO
		}

		template<typename T>
		std::size_t CircularQueue<T>::GetCircularQueueSize() noexcept
		{
			std::lock_guard<std::mutex> _(mMutex);

			return mLen;
		}

		template<typename T>
		bool CircularQueue<T>::AddData(const T& data) noexcept
		{
			std::lock_guard<std::mutex> _(mMutex);

			if (mLen == 0)
			{
				return false;
			}

			if (mLen == mCount)
			{
				mArr[mFrontPointer] = data;
				mFrontPointer = (mFrontPointer + 1) % mLen;
				mBackPointer = mFrontPointer;
			}
			else
			{
				++mCount;
				mArr[mFrontPointer] = data;
				mFrontPointer = (mFrontPointer + 1) % mLen;
			}

			return true;
		}

		template<typename T>
		std::vector<T> CircularQueue<T>::GetData() noexcept
		{
			std::lock_guard<std::mutex> _(mMutex);

			std::vector<T> vec;

			if (mLen == 0 || mCount == 0)
			{
				return vec;
			}

			std::size_t index = mBackPointer;

			do
			{
				vec.push_back(mArr[index]);
				index = (index + 1) % mLen;
			}
			while (index != mFrontPointer);

			return vec;
		}

	} //# namespace CircularQueue_ThreadSafety_V1

} //# namespace Lynx
