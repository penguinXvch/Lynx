
#include "../../../CircularQueue/CircularQueue_ThreadSafety_V2/CircularQueueV2.hpp"
#include "../../Tools.hpp"
#include <vector>

namespace Test
{

	namespace CircularQueue_ThreadSafety_V2
	{

		void TestCircularQueue() noexcept
		{
			using Test::Tools::TestProject;
			using Test::Tools::Test;
			using Test::Tools::PassTest;
			using Test::Tools::PassTestProject;
			using _Class = Test::Tools::Class;
			using _Method = Test::Tools::Method;

			TestProject<_Class>("Lynx::CircularQueue_ThreadSafety_V2::CircularQueue<T, N>");

			using Lynx::CircularQueue_ThreadSafety_V2::CircularQueue;

			//# 测试 CircularQueue<T, N>::CircularQueue()。
			Test<_Method>({ "CircularQueue<T, N>::CircularQueue()" });
			{
				CircularQueue<int, 1> cq1;
				// CircularQueue<int, 0> cq2;

				CircularQueue<std::vector<int>, 1> cq3;
				// CircularQueue<std::vector<int>, 0> cq4;
			}
			PassTest();

			//# 测试 CircularQueue<T, N>::CircularQueue(CircularQueue<T, N>&)。
			//# 测试 CircularQueue<T, N>::CircularQueue(CircularQueue<T, N>&&)。
			//# 测试 CircularQueue<T, N>::CircularQueue(const CircularQueue<T, N>&)。
			//# 测试 CircularQueue<T, N>::CircularQueue(const CircularQueue<T, N>&&)。
			//# 测试 CircularQueue<T, N>::CircularQueue<T, N>& CircularQueue<T, N>::operator=(CircularQueue<T, N>&)。
			//# 测试 CircularQueue<T, N>::CircularQueue<T, N>& CircularQueue<T, N>::operator=(CircularQueue<T, N>&&)。
			//# 测试 CircularQueue<T, N>::CircularQueue<T, N>& CircularQueue<T, N>::operator=(const CircularQueue<T, N>&)。
			//# 测试 CircularQueue<T, N>::CircularQueue<T, N>& CircularQueue<T, N>::operator=(const CircularQueue<T, N>&&)。
			Test<_Method, _Method, _Method, _Method, _Method, _Method, _Method, _Method>
			({
				"CircularQueue<T, N>::CircularQueue(CircularQueue<T, N>&)",
				"CircularQueue<T, N>::CircularQueue(CircularQueue<T, N>&&)",
				"CircularQueue<T, N>::CircularQueue(const CircularQueue<T, N>&)",
				"CircularQueue<T, N>::CircularQueue(const CircularQueue<T, N>&&)",
				"CircularQueue<T, N>::CircularQueue<T, N>& CircularQueue<T, N>::operator=(CircularQueue<T, N>&)",
				"CircularQueue<T, N>::CircularQueue<T, N>& CircularQueue<T, N>::operator=(CircularQueue<T, N>&&)",
				"CircularQueue<T, N>::CircularQueue<T, N>& CircularQueue<T, N>::operator=(const CircularQueue<T, N>&)",
				"CircularQueue<T, N>::CircularQueue<T, N>& CircularQueue<T, N>::operator=(const CircularQueue<T, N>&&)"
			});
			{
				// CircularQueue<int, 1> cq;

				// CircularQueue<int, 1> cq1 = cq;
				// CircularQueue<int, 1> cq2 = std::move(cq);

				// cq1 = cq;
				// cq2 = std::move(cq);
			}
			PassTest();

			//# 测试 bool CircularQueue<T, N>::Push(const T&)。
			//# 测试 bool CircularQueue<T, N>::Pop(T&)。
			Test<_Method, _Method>
			({
				"bool CircularQueue<T, N>::Push(const T&)",
				"bool CircularQueue<T, N>::Pop(T&)"
			});
			{
				CircularQueue<int, 2> cq;
				
				PassOrFail(cq.Push(1) == true);
				PassOrFail(cq.Push(2) == true);
				PassOrFail(cq.Push(3) == false);

				int value = -1;
				PassOrFail(cq.Pop(value) == true && value == 1);
				PassOrFail(cq.Pop(value) == true && value == 2);
				PassOrFail(cq.Pop(value) == false && value == 2);
			}
			PassTest();

			PassTestProject();
		}

	} //# namespace CircularQueue_ThreadSafety_V2

} //# namespace Test
