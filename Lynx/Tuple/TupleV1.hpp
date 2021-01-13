
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


namespace Lynx
{

	namespace
	{
		template<std::size_t N, typename T, typename... Ts>
		struct TupleElementTypeImpl
		{
			using Type = typename TupleElementTypeImpl<N - 1, Ts...>::Type;
		};

		template<typename T, typename... Ts>
		struct TupleElementTypeImpl<0, T, Ts...>
		{
			using Type = T;
		};
	}

	template<std::size_t, typename>
	struct TupleElementType
	{
		constexpr explicit TupleElementType() noexcept = delete;
		~TupleElementType() noexcept = delete;
		constexpr explicit TupleElementType(TupleElementType&) noexcept = delete;
		constexpr explicit TupleElementType(TupleElementType&&) noexcept = delete;
		constexpr explicit TupleElementType(const TupleElementType&) noexcept = delete;
		constexpr explicit TupleElementType(const TupleElementType&&) noexcept = delete;
		constexpr TupleElementType& operator=(TupleElementType&) noexcept = delete;
		constexpr TupleElementType& operator=(TupleElementType&&) noexcept = delete;
		constexpr TupleElementType& operator=(const TupleElementType&) noexcept = delete;
		constexpr TupleElementType& operator=(const TupleElementType&&) noexcept = delete;
	};

	template<std::size_t N, typename... Ts>
	struct TupleElementType<N, Tuple_V1::Tuple<Ts...>>
	{
		using Type = std::enable_if_t
		<
			(N >= 0) && (N < sizeof...(Ts)),
			typename TupleElementTypeImpl<N, Ts...>::Type
		>;
	};

} //# namespace Lynx


namespace Lynx
{

	template<std::size_t N, typename... Ts>
	inline constexpr auto Get(Tuple_V1::Tuple<Ts...>& tuple) noexcept
		-> typename TupleElementType<N, Tuple_V1::Tuple<Ts...>>::Type&
	{
		return static_cast<typename TupleElementType<N, Tuple_V1::Tuple<Ts...>>::Type&>
			(tuple.Tuple_V1::TupleCell<N, typename TupleElementType<N, Tuple_V1::Tuple<Ts...>>::Type>::value);
	}

	template<std::size_t N, typename... Ts>
	inline constexpr auto Get(Tuple_V1::Tuple<Ts...>&& tuple) noexcept
		-> typename TupleElementType<N, Tuple_V1::Tuple<Ts...>>::Type&&
	{
		return static_cast<typename TupleElementType<N, Tuple_V1::Tuple<Ts...>>::Type&&>
			(tuple.Tuple_V1::TupleCell<N, typename TupleElementType<N, Tuple_V1::Tuple<Ts...>>::Type>::value);
	}

	template<std::size_t N, typename... Ts>
	inline constexpr auto Get(const Tuple_V1::Tuple<Ts...>& tuple) noexcept
		-> const typename TupleElementType<N, Tuple_V1::Tuple<Ts...>>::Type&
	{
		return static_cast<const typename TupleElementType<N, Tuple_V1::Tuple<Ts...>>::Type&>
			(tuple.Tuple_V1::TupleCell<N, typename TupleElementType<N, Tuple_V1::Tuple<Ts...>>::Type>::value);
	}

	template<std::size_t N, typename... Ts>
	inline constexpr auto Get(const Tuple_V1::Tuple<Ts...>&& tuple) noexcept
		-> const typename TupleElementType<N, Tuple_V1::Tuple<Ts...>>::Type&&
	{
		return static_cast<const typename TupleElementType<N, Tuple_V1::Tuple<Ts...>>::Type&&>
			(tuple.Tuple_V1::TupleCell<N, typename TupleElementType<N, Tuple_V1::Tuple<Ts...>>::Type>::value);
	}

	namespace
	{
		template<std::size_t N, typename T, std::size_t I, typename U, typename... Us>
		struct GetImpl
		{
			static_assert(I < N, "Index out of range.");
			static constexpr std::size_t value = GetImpl<N, T, I + 1, Us...>::value;
		};

		template<std::size_t N, typename T, std::size_t I, typename... Us>
		struct GetImpl<N, T, I, T, Us...>
		{
			static_assert(I < N, "Index out of range.");
			static constexpr std::size_t value = I;
		};
	}

	template<typename T, typename... Ts>
	inline constexpr T& Get(Tuple_V1::Tuple<Ts...>& tuple) noexcept
	{
		constexpr std::size_t N = GetImpl<sizeof...(Ts), T, 0, Ts...>::value;
		return static_cast<T&>
			(tuple.Tuple_V1::TupleCell<N, typename TupleElementType<N, Tuple_V1::Tuple<Ts...>>::Type>::value);
	}

	template<typename T, typename... Ts>
	inline constexpr T&& Get(Tuple_V1::Tuple<Ts...>&& tuple) noexcept
	{
		constexpr std::size_t N = GetImpl<sizeof...(Ts), T, 0, Ts...>::value;
		return static_cast<T&&>
			(tuple.Tuple_V1::TupleCell<N, typename TupleElementType<N, Tuple_V1::Tuple<Ts...>>::Type>::value);
	}

	template<typename T, typename... Ts>
	inline constexpr const T& Get(const Tuple_V1::Tuple<Ts...>& tuple) noexcept
	{
		constexpr std::size_t N = GetImpl<sizeof...(Ts), T, 0, Ts...>::value;
		return static_cast<const T&>
			(tuple.Tuple_V1::TupleCell<N, typename TupleElementType<N, Tuple_V1::Tuple<Ts...>>::Type>::value);
	}

	template<typename T, typename... Ts>
	inline constexpr const T&& Get(const Tuple_V1::Tuple<Ts...>&& tuple) noexcept
	{
		constexpr std::size_t N = GetImpl<sizeof...(Ts), T, 0, Ts...>::value;
		return static_cast<const T&&>
			(tuple.Tuple_V1::TupleCell<N, typename TupleElementType<N, Tuple_V1::Tuple<Ts...>>::Type>::value);
	}

} //# namespace Lynx


namespace Lynx
{

	template<typename... Ts>
	inline constexpr auto MakeTuple(Ts&&... args) noexcept -> Tuple_V1::Tuple<std::remove_reference_t<Ts>...>
	{
		return Tuple_V1::Tuple<std::remove_reference_t<Ts>...>{ std::forward<Ts>(args)... };
	}

} //# namespace Lynx
