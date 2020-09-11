
#pragma once

#include<array>
#include<mutex>

namespace Lynx
{

    namespace CircularQueue_V2
    {

        /*
         *  线程安全的循环队列：
         *      1. 向循环队列尾部写入数据直到循环队列装满。
         *      2. 从循环队列头部弹出数据直到循环队列为空。
         */
        template<typename T, std::size_t N>
        class CircularQueue
        {
        public:
			explicit CircularQueue() noexcept;
			virtual ~CircularQueue() noexcept = default;

		public:
			CircularQueue(CircularQueue<T, N>&) noexcept = delete;
			CircularQueue(CircularQueue<T, N>&&) noexcept = delete;
			CircularQueue(const CircularQueue<T, N>&) noexcept = delete;
			CircularQueue(const CircularQueue<T, N>&&) noexcept = delete;
			CircularQueue<T, N>& operator=(CircularQueue<T, N>&) noexcept = delete;
			CircularQueue<T, N>& operator=(CircularQueue<T, N>&&) noexcept = delete;
			CircularQueue<T, N>& operator=(const CircularQueue<T, N>&) noexcept = delete;
			CircularQueue<T, N>& operator=(const CircularQueue<T, N>&&) noexcept = delete;

        public:
            bool Push(const T& value) noexcept;
            bool Pop(T& value) noexcept;

        private:
            std::array<T, N> mArr;
            
        private:
            std::size_t mFrontPointer;
            std::size_t mBackPointer;
            std::size_t mCount;
            
        private:
            std::mutex mMutex;
        };

        template<typename T, std::size_t N>
        CircularQueue<T, N>::CircularQueue() noexcept
            : mArr(), mFrontPointer(0), mBackPointer(0), mCount(0), mMutex() 
        {
        }

        template<typename T, std::size_t N>
        bool CircularQueue<T, N>::Push(const T& value) noexcept
        {
            std::lock_guard<std::mutex> _(mMutex);

            if (mCount == N)
            { 
                return false; 
            }
            else 
            {
                ++mCount;
                mArr[mFrontPointer] = value;
                mFrontPointer = (mFrontPointer + 1) % N;
                return true;
            }
        }

        template<typename T, std::size_t N>
        bool CircularQueue<T, N>::Pop(T& value) noexcept
        {
            std::lock_guard<std::mutex> _(mMutex);

            if (mCount == 0) 
            { 
                return false; 
            }
            else 
            {
                --mCount;
                value = mArr[mBackPointer];
                mBackPointer = (mBackPointer + 1) % N;
                return true;
            }
        }

    } //# namespace CircularQueue_V2

} //# namespace Lynx
