
#pragma once

#include <cstddef>

namespace Lynx
{

	namespace Note
	{

#ifndef NoteLengthLimit
#define NoteLengthLimit 50
#endif

		template<std::size_t N>
		constexpr void CheckNoteLength(const wchar_t(&StringLiteral)[N]) noexcept
		{
			static_assert(N > NoteLengthLimit, "Code notes are too short.");
		}

#define ScopedNote(StringLiteral)	\
    ::Lynx::Note::CheckNoteLength(L##StringLiteral);

#define Note(StringLiteral)													\
    static_assert															\
	(																		\
        ((sizeof(L##StringLiteral) / sizeof(wchar_t)) > NoteLengthLimit),	\
        "Code notes are too short."											\
	);

	} //# namespace Note

} //# namespace Lynx
