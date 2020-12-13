
#pragma once

#include <utility>

namespace Lynx
{

	namespace Tuple_V1
	{

		namespace
		{
			template<std::size_t N, typename T>
			struct TupleCell
			{
				constexpr explicit TupleCell() noexcept
					: value()
				{
				}

				~TupleCell() noexcept = default;

				template<typename Arg>
				constexpr explicit TupleCell(Arg&& arg) noexcept
					: value(std::forward<Arg>(arg))
				{
				}

				T value;
			};
		}

		namespace
		{
			template<typename...>
			struct TupleImpl
			{
				constexpr explicit TupleImpl() noexcept = delete;
				~TupleImpl() noexcept = delete;
				constexpr explicit TupleImpl(TupleImpl&) noexcept = delete;
				constexpr explicit TupleImpl(TupleImpl&&) noexcept = delete;
				constexpr explicit TupleImpl(const TupleImpl&) noexcept = delete;
				constexpr explicit TupleImpl(const TupleImpl&&) noexcept = delete;
				constexpr TupleImpl& operator=(TupleImpl&) noexcept = delete;
				constexpr TupleImpl& operator=(TupleImpl&&) noexcept = delete;
				constexpr TupleImpl& operator=(const TupleImpl&) noexcept = delete;
				constexpr TupleImpl& operator=(const TupleImpl&&) noexcept = delete;
			};

			/*
			 * 特化 TupleImpl。
			 */
			template<std::size_t... Ns, typename... Ts>
			struct TupleImpl<std::index_sequence<Ns...>, Ts...>
				: public TupleCell<Ns, Ts>...
			{
				constexpr explicit TupleImpl() noexcept
					: TupleCell<Ns, Ts>()...
				{
				}

				~TupleImpl() noexcept = default;

				template<typename... Args>
				constexpr explicit TupleImpl(Args&&... args) noexcept
					: TupleCell<Ns, Ts>(std::forward<Args>(args))...
				{
				}
			};
		}

		/*
		 * Tuple 实现方式：非递归式多继承。
		 */
		template<typename... Ts>
		struct Tuple
			: public TupleImpl<std::make_index_sequence<sizeof...(Ts)>, Ts...>
		{
			constexpr explicit Tuple() noexcept
				: TupleImpl<std::make_index_sequence<sizeof...(Ts)>, Ts...>()
			{
			}

			~Tuple() noexcept = default;

			template<typename... Args>
			constexpr explicit Tuple(Args&&... args) noexcept
				: TupleImpl<std::make_index_sequence<sizeof...(Ts)>, Ts...>(std::forward<Args>(args)...)
			{
			}
		};

	} //# namespace Tuple_V1

} //# namespace Lynx
