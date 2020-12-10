
#pragma once

#include <iostream>
#include <array>
#include <windows.h>

namespace Test
{

	namespace Tools
	{

		struct Class {};
		struct Type {};
		struct Method {};
		struct Function {};



		template<typename T>
		void TestProject(const char* Str) noexcept
		{
			std::cout << std::endl;

			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
				FOREGROUND_RED | FOREGROUND_GREEN);
			std::cout << TestProject_Info << Blank;

			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
				FOREGROUND_RED | FOREGROUND_BLUE);
			std::cout << TestProjectCategory<T>::Category << Blank;

			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
				FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
			std::cout << Str << std::endl;
		}

		template<typename... Ts>
		void Test(const std::array<const char*, sizeof...(Ts)>& Strings) noexcept
		{
			std::array<const char*, sizeof...(Ts)> arr{ TestProjectCategory<Ts>::Category... };

			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
				FOREGROUND_RED | FOREGROUND_GREEN);
			std::cout << Test_Info << Blank;

			for (std::size_t i = 0; i < Strings.size(); ++i)
			{
				if (i == 0)
				{
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
						FOREGROUND_RED | FOREGROUND_BLUE);
					std::cout << arr[i] << Blank;
				}
				else
				{
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
						FOREGROUND_RED | FOREGROUND_GREEN);
					std::cout << Blank << Blank << Blank << Blank << Blank;
					std::cout << RightBracket << Blank;

					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
						FOREGROUND_RED | FOREGROUND_BLUE);
					std::cout << arr[i] << Blank;
				}

				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
					FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
				std::cout << Strings[i] << std::endl;
			}
		}

		void PassTest() noexcept;

		void _PassOrFail(const bool& Cond, const char* Str,
			const char* const File, const char* const Func, const std::size_t& Line) noexcept;

#define PassOrFail(Cond) \
	::Test::Tools::_PassOrFail(Cond, #Cond, __FILE__, __FUNCTION__, __LINE__)

	} //# namespace Tools

} //# namespace Test
