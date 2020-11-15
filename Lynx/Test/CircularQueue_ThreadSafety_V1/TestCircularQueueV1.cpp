
#include "../../CircularQueue_ThreadSafety_V1/CircularQueueV1.hpp"
#include <cassert>
#include <vector>
#include <string>

namespace Test
{

	namespace CircularQueue_ThreadSafety_V1
	{

		void TestCircularQueue() noexcept
		{
			using Lynx::CircularQueue_ThreadSafety_V1::CircularQueue;

			//# 测试 CircularQueue::CircularQueue()。
			{
				CircularQueue<int> cq;
				
				assert(cq.GetCircularQueueSize() == 0);
				assert(cq.AddData(0) == false);

				std::vector<int> vec = cq.GetData();
				assert(vec.size() == 0);
			}

			//# 测试 CircularQueue::CircularQueue(const std::size_t& len)。
			{
				CircularQueue<int> cq(1);

				assert(cq.GetCircularQueueSize() == 1);
				assert(cq.AddData(0) == true);

				std::vector<int> vec = cq.GetData();
				assert(vec.size() == 1);
				assert(vec.front() == 0);

				CircularQueue<int> cq2(0);

				assert(cq2.GetCircularQueueSize() == 0);
				assert(cq2.AddData(0) == false);

				std::vector<int> vec2 = cq2.GetData();
				assert(vec2.size() == 0);
			}

			//# 测试 CircularQueue::SetCircularQueueSize(const std::size_t& len)。
			{
				CircularQueue<int> cq;
				cq.SetCircularQueueSize(0);

				assert(cq.GetCircularQueueSize() == 0);
				assert(cq.AddData(0) == false);

				std::vector<int> vec = cq.GetData();
				assert(vec.size() == 0);

				cq.SetCircularQueueSize(1);

				assert(cq.GetCircularQueueSize() == 1);
				assert(cq.AddData(0) == true);

				std::vector<int> vec2 = cq.GetData();
				assert(vec2.size() == 1);
				assert(vec2.front() == 0);

				cq.SetCircularQueueSize(0);

				assert(cq.GetCircularQueueSize() == 1);
				assert(cq.AddData(1) == true);

				std::vector<int> vec3 = cq.GetData();
				assert(vec3.size() == 1);
				assert(vec3.front() == 1);
			}

			//# 测试 CircularQueue::SetCircularQueueSize(const std::size_t& len)。
			{
				CircularQueue<int> cq;
				cq.SetCircularQueueSize(2);

				assert(cq.GetCircularQueueSize() == 2);
				assert(cq.AddData(0) == true);

				std::vector<int> vec = cq.GetData();
				assert(vec.size() == 1);
				assert(vec.front() == 0);

				cq.SetCircularQueueSize(0);

				assert(cq.GetCircularQueueSize() == 2);
				assert(cq.AddData(1) == true);

				std::vector<int> vec2 = cq.GetData();
				assert(vec2.size() == 2);
				assert(vec2.front() == 0 && vec2.back() == 1);
			}

			//# 测试 CircularQueue::GetCircularQueueSize()。
			{
				CircularQueue<std::vector<int>> cq1(10);
				assert(cq1.GetCircularQueueSize() == 10);

				CircularQueue<const char*> cq2(5);
				assert(cq2.GetCircularQueueSize() == 5);

				CircularQueue<bool> cq3;
				assert(cq3.GetCircularQueueSize() == 0);
				cq3.SetCircularQueueSize(3);
				assert(cq3.GetCircularQueueSize() == 3);
				cq3.SetCircularQueueSize(0);
				assert(cq3.GetCircularQueueSize() == 3);
			}

			//# 测试 CircularQueue::AddData(const T& data)。
			//# 测试 CircularQueue::GetData()。
			{
				CircularQueue<std::string> cq1(3);
				
				assert(cq1.AddData("1str") == true);
				assert(cq1.AddData("2str") == true);
				assert(cq1.AddData("3str") == true);
				std::string str4 = "str4", str5 = "str5";
				assert(cq1.AddData(str4) == true);
				assert(cq1.AddData(str5) == true);

				std::vector<std::string> vec1 = cq1.GetData();
				assert(vec1.size() == 3);
				assert(vec1[0] == "3str" && vec1[1] == "str4" && vec1[2] == "str5");

				CircularQueue<std::string> cq2(1);

				assert(cq2.AddData(str4) == true);
				assert(cq2.AddData(str5) == true);

				std::vector<std::string> vec2 = cq2.GetData();
				assert(vec2.size() == 1);
				assert(vec2[0] == "str5");
			}

			//# 测试 CircularQueue::CircularQueue(CircularQueue<T>&)。
			//# 测试 CircularQueue::CircularQueue(CircularQueue<T>&&)。
			//# 测试 CircularQueue::CircularQueue(const CircularQueue<T>&)。
			//# 测试 CircularQueue::CircularQueue(const CircularQueue<T>&&)。
			//# 测试 CircularQueue::CircularQueue<T>& operator=(CircularQueue<T>&)。
			//# 测试 CircularQueue::CircularQueue<T>& operator=(CircularQueue<T>&&)。
			//# 测试 CircularQueue::CircularQueue<T>& operator=(const CircularQueue<T>&)。
			//# 测试 CircularQueue::CircularQueue<T>& operator=(const CircularQueue<T>&&)。
			{
				// CircularQueue<std::string> cq1;
				// CircularQueue<std::string> cq2(3);

				// cq1 = cq2;
				// cq1 = std::move(cq2);

				// CircularQueue<std::string> cq3 = cq1;
				// CircularQueue<std::string> cq4 = std::move(cq2);
			}
		}

	} //# namespace CircularQueue_ThreadSafety_V1

} //# namespace Test
