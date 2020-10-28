
#include "../../CircularQueue_ThreadSafety_V2/CircularQueue.hpp"
#include <cassert>
#include <vector>

namespace Test
{

	namespace CircularQueue_ThreadSafety_V2
	{

		void TestCircularQueue() noexcept
		{
			using Lynx::CircularQueue_ThreadSafety_V2::CircularQueue;

			//# 测试 CircularQueue::CircularQueue()。
			{
				CircularQueue<int, 1> cq1;
				// CircularQueue<int, 0> cq2;

				CircularQueue<std::vector<int>, 1> cq3;
				// CircularQueue<std::vector<int>, 0> cq4;
			}

			//# 测试 CircularQueue::CircularQueue(CircularQueue<T, N>&)。
			//# 测试 CircularQueue::CircularQueue(CircularQueue<T, N>&&)。
			//# 测试 CircularQueue::CircularQueue(const CircularQueue<T, N>&)。
			//# 测试 CircularQueue::CircularQueue(const CircularQueue<T, N>&&)。
			//# 测试 CircularQueue::CircularQueue<T, N>& operator=(CircularQueue<T, N>&)。
			//# 测试 CircularQueue::CircularQueue<T, N>& operator=(CircularQueue<T, N>&&)。
			//# 测试 CircularQueue::CircularQueue<T, N>& operator=(const CircularQueue<T, N>&)。
			//# 测试 CircularQueue::CircularQueue<T, N>& operator=(const CircularQueue<T, N>&&)。
			{
				// CircularQueue<int, 1> cq;

				// CircularQueue<int, 1> cq1 = cq;
				// CircularQueue<int, 1> cq2 = std::move(cq);

				// cq1 = cq;
				// cq2 = std::move(cq);
			}

			//# 测试 CircularQueue::Push(const T& value)。
			//# 测试 CircularQueue::Pop(T& value)。
			{
				CircularQueue<int, 2> cq;
				
				assert(cq.Push(1) == true);
				assert(cq.Push(2) == true);
				assert(cq.Push(3) == false);

				int value = -1;
				assert(cq.Pop(value) == true && value == 1);
				assert(cq.Pop(value) == true && value == 2);
				assert(cq.Pop(value) == false && value == 2);
			}
		}

	} //# namespace CircularQueue_ThreadSafety_V2

} //# namespace Test
