
#include "../../CircularQueue_ThreadSafety_V1/CircularQueueV1.hpp"
#include "../Tools.hpp"
#include <vector>
#include <string>

namespace Test
{

	namespace CircularQueue_ThreadSafety_V1
	{

		void TestCircularQueue() noexcept
		{
			using Test::Tools::TestProject;
			using Test::Tools::Test;
			using Test::Tools::PassTest;
			using Test::Tools::PassTestProject;
			using _Class = Test::Tools::Class;
			using _Method = Test::Tools::Method;

			TestProject<_Class>("Lynx::CircularQueue_ThreadSafety_V1::CircularQueue<T>");

			using Lynx::CircularQueue_ThreadSafety_V1::CircularQueue;

			//# 测试 CircularQueue<T>::CircularQueue()。
			Test<_Method>({ "CircularQueue<T>::CircularQueue()" });
			{
				CircularQueue<int> cq;
				
				PassOrFail(cq.GetCircularQueueSize() == 0);
				PassOrFail(cq.AddData(0) == false);

				std::vector<int> vec = cq.GetData();
				PassOrFail(vec.size() == 0);
			}
			PassTest();

			//# 测试 CircularQueue<T>::CircularQueue(const std::size_t&)。
			Test<_Method>({ "CircularQueue<T>::CircularQueue(const std::size_t&)" });
			{
				CircularQueue<int> cq(1);

				PassOrFail(cq.GetCircularQueueSize() == 1);
				PassOrFail(cq.AddData(0) == true);

				std::vector<int> vec = cq.GetData();
				PassOrFail(vec.size() == 1);
				PassOrFail(vec.front() == 0);

				CircularQueue<int> cq2(0);

				PassOrFail(cq2.GetCircularQueueSize() == 0);
				PassOrFail(cq2.AddData(0) == false);

				std::vector<int> vec2 = cq2.GetData();
				PassOrFail(vec2.size() == 0);
			}
			PassTest();

			//# 测试 void CircularQueue<T>::SetCircularQueueSize(const std::size_t&)。
			Test<_Method>({ "void CircularQueue<T>::SetCircularQueueSize(const std::size_t&)" });
			{
				CircularQueue<int> cq;
				cq.SetCircularQueueSize(0);

				PassOrFail(cq.GetCircularQueueSize() == 0);
				PassOrFail(cq.AddData(0) == false);

				std::vector<int> vec = cq.GetData();
				PassOrFail(vec.size() == 0);

				cq.SetCircularQueueSize(1);

				PassOrFail(cq.GetCircularQueueSize() == 1);
				PassOrFail(cq.AddData(0) == true);

				std::vector<int> vec2 = cq.GetData();
				PassOrFail(vec2.size() == 1);
				PassOrFail(vec2.front() == 0);

				cq.SetCircularQueueSize(0);

				PassOrFail(cq.GetCircularQueueSize() == 1);
				PassOrFail(cq.AddData(1) == true);

				std::vector<int> vec3 = cq.GetData();
				PassOrFail(vec3.size() == 1);
				PassOrFail(vec3.front() == 1);
			}

			//# 测试 void CircularQueue<T>::SetCircularQueueSize(const std::size_t&)。
			{
				CircularQueue<int> cq;
				cq.SetCircularQueueSize(2);

				PassOrFail(cq.GetCircularQueueSize() == 2);
				PassOrFail(cq.AddData(0) == true);

				std::vector<int> vec = cq.GetData();
				PassOrFail(vec.size() == 1);
				PassOrFail(vec.front() == 0);

				cq.SetCircularQueueSize(0);

				PassOrFail(cq.GetCircularQueueSize() == 2);
				PassOrFail(cq.AddData(1) == true);

				std::vector<int> vec2 = cq.GetData();
				PassOrFail(vec2.size() == 2);
				PassOrFail(vec2.front() == 0 && vec2.back() == 1);
			}
			PassTest();

			//# 测试 std::size_t CircularQueue<T>::GetCircularQueueSize()。
			Test<_Method>({ "std::size_t CircularQueue<T>::GetCircularQueueSize()" });
			{
				CircularQueue<std::vector<int>> cq1(10);
				PassOrFail(cq1.GetCircularQueueSize() == 10);

				CircularQueue<const char*> cq2(5);
				PassOrFail(cq2.GetCircularQueueSize() == 5);

				CircularQueue<bool> cq3;
				PassOrFail(cq3.GetCircularQueueSize() == 0);
				cq3.SetCircularQueueSize(3);
				PassOrFail(cq3.GetCircularQueueSize() == 3);
				cq3.SetCircularQueueSize(0);
				PassOrFail(cq3.GetCircularQueueSize() == 3);
			}
			PassTest();

			//# 测试 bool CircularQueue<T>::AddData(const T&)。
			//# 测试 std::vector<T> CircularQueue<T>::GetData()。
			Test<_Method, _Method>
			({
				"bool CircularQueue<T>::AddData(const T&)",
				"std::vector<T> CircularQueue<T>::GetData()"
			});
			{
				CircularQueue<std::string> cq1(3);
				
				PassOrFail(cq1.AddData("1str") == true);
				PassOrFail(cq1.AddData("2str") == true);
				PassOrFail(cq1.AddData("3str") == true);
				std::string str4 = "str4", str5 = "str5";
				PassOrFail(cq1.AddData(str4) == true);
				PassOrFail(cq1.AddData(str5) == true);

				std::vector<std::string> vec1 = cq1.GetData();
				PassOrFail(vec1.size() == 3);
				PassOrFail(vec1[0] == "3str" && vec1[1] == "str4" && vec1[2] == "str5");

				CircularQueue<std::string> cq2(1);

				PassOrFail(cq2.AddData(str4) == true);
				PassOrFail(cq2.AddData(str5) == true);

				std::vector<std::string> vec2 = cq2.GetData();
				PassOrFail(vec2.size() == 1);
				PassOrFail(vec2[0] == "str5");
			}
			PassTest();

			//# 测试 CircularQueue<T>::CircularQueue(CircularQueue<T>&)。
			//# 测试 CircularQueue<T>::CircularQueue(CircularQueue<T>&&)。
			//# 测试 CircularQueue<T>::CircularQueue(const CircularQueue<T>&)。
			//# 测试 CircularQueue<T>::CircularQueue(const CircularQueue<T>&&)。
			//# 测试 CircularQueue<T>::CircularQueue<T>& CircularQueue<T>::operator=(CircularQueue<T>&)。
			//# 测试 CircularQueue<T>::CircularQueue<T>& CircularQueue<T>::operator=(CircularQueue<T>&&)。
			//# 测试 CircularQueue<T>::CircularQueue<T>& CircularQueue<T>::operator=(const CircularQueue<T>&)。
			//# 测试 CircularQueue<T>::CircularQueue<T>& CircularQueue<T>::operator=(const CircularQueue<T>&&)。
			Test<_Method, _Method, _Method, _Method, _Method, _Method, _Method, _Method>
			({
				"CircularQueue<T>::CircularQueue(CircularQueue<T>&)",
				"CircularQueue<T>::CircularQueue(CircularQueue<T>&&)",
				"CircularQueue<T>::CircularQueue(const CircularQueue<T>&)",
				"CircularQueue<T>::CircularQueue(const CircularQueue<T>&&)",
				"CircularQueue<T>::CircularQueue<T>& CircularQueue<T>::operator=(CircularQueue<T>&)",
				"CircularQueue<T>::CircularQueue<T>& CircularQueue<T>::operator=(CircularQueue<T>&&)",
				"CircularQueue<T>::CircularQueue<T>& CircularQueue<T>::operator=(const CircularQueue<T>&)",
				"CircularQueue<T>::CircularQueue<T>& CircularQueue<T>::operator=(const CircularQueue<T>&&)"
			});
			{
				// CircularQueue<std::string> cq1;
				// CircularQueue<std::string> cq2(3);

				// cq1 = cq2;
				// cq1 = std::move(cq2);

				// CircularQueue<std::string> cq3 = cq1;
				// CircularQueue<std::string> cq4 = std::move(cq2);
			}
			PassTest();

			PassTestProject();
		}

	} //# namespace CircularQueue_ThreadSafety_V1

} //# namespace Test
