
#include "../../Note/Note.hpp"
#include "../Tools.hpp"

namespace Test
{

	namespace Note
	{

		void TestNote() noexcept
		{
			using Test::Tools::TestProject;
			using Test::Tools::Test;
			using Test::Tools::PassTest;
			using Test::Tools::PassTestProject;
			using _Macro = Test::Tools::Macro;

			TestProject<_Macro>("ScopedNote + Note");

			//# 测试 ScopedNote 与 Note。
			Test<_Macro, _Macro>({ "ScopedNote", "Note" });
			{
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

				ScopedNote
				(
					"这是测试用例，此用例注释字符数大于限定值。"
					"这是测试用例，此用例注释字符数大于限定值。"
					"这是测试用例，此用例注释字符数大于限定值。"
					"这是测试用例，此用例注释字符数大于限定值。"
					"这是测试用例，此用例注释字符数大于限定值。"
				);

				// ScopedNote
				// (
				//	 "这是测试用例，此用例注释字符数小于限定值。"
				// );
			}
			PassTest();

			PassTestProject();
		}

	} //# namespace Note

} //# namespace Test
