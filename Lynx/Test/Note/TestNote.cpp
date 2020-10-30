﻿
#include "../../Note/Note.hpp"

namespace Test
{

	namespace Note
	{

		void TestNote() noexcept
		{
			//# 测试 Note 与 Global_Note。
			{
				Global_Note
				(
					"这是测试用例，此用例注释字符数大于限定值。"
					"这是测试用例，此用例注释字符数大于限定值。"
					"这是测试用例，此用例注释字符数大于限定值。"
					"这是测试用例，此用例注释字符数大于限定值。"
					"这是测试用例，此用例注释字符数大于限定值。"
				);

				// Global_Note
				// (
				//	 "这是测试用例，此用例注释字符数小于限定值。"
				// );

				Note
				(
					"这是测试用例，此用例注释字符数大于限定值。"
					"这是测试用例，此用例注释字符数大于限定值。"
					"这是测试用例，此用例注释字符数大于限定值。"
					"这是测试用例，此用例注释字符数大于限定值。"
					"这是测试用例，此用例注释字符数大于限定值。"
				);

				// Note
				// (
				//	 "这是测试用例，此用例注释字符数小于限定值。"
				// );
			}
		}

	} //# namespace Note

} //# namespace Test
