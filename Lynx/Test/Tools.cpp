
#include "Tools.hpp"

namespace Test
{

	namespace Tools
	{

		namespace
		{
			const char* const Blank = " ";
			const char* const RightBracket = ">";

			const char* const TestProject_Info = "[Test Project]";
			const char* const Test_Info = "[Test]";
			const char* const Pass_Info = "[Pass]";
			const char* const PassTest_Info = "[Pass Test]";
			const char* const Fail_Info = "[Fail]";
		}

		namespace
		{
			template<typename>
			struct TestProjectCategory
			{
			};

			template<>
			struct TestProjectCategory<Class>
			{
				static const char* const Category;
			};
			const char* const TestProjectCategory<Class>::Category = "(Class)";

			template<>
			struct TestProjectCategory<Type>
			{
				static const char* const Category;
			};
			const char* const TestProjectCategory<Type>::Category = "(Type)";

			template<>
			struct TestProjectCategory<Method>
			{
				static const char* const Category;
			};
			const char* const TestProjectCategory<Method>::Category = "(Method)";

			template<>
			struct TestProjectCategory<Function>
			{
				static const char* const Category;
			};
			const char* const TestProjectCategory<Function>::Category = "(Function)";
		}

		void PassTest() noexcept
		{
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
				FOREGROUND_GREEN);
			std::cout << PassTest_Info << Blank;

			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
				FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
			std::cout << std::endl;
		}

	} //# namespace Tools

} //# namespace Test
