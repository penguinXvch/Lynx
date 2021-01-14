
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
				constexpr explicit TupleCell() noexcept : value() {}

				constexpr explicit TupleCell(T&) noexcept = delete;
				constexpr explicit TupleCell(const T&&) noexcept = delete;

				constexpr explicit TupleCell(const T& arg) noexcept : value(arg) {}
				constexpr explicit TupleCell(T&& arg) noexcept : value(std::move(arg)) {}

				~TupleCell() noexcept = default;

				constexpr explicit TupleCell(TupleCell&) noexcept = delete;
				constexpr explicit TupleCell(const TupleCell&&) noexcept = delete;

				constexpr explicit TupleCell(const TupleCell& tc) noexcept : value(tc.value) {}
				constexpr explicit TupleCell(TupleCell&& tc) noexcept : value(std::move(tc.value)) {}

				constexpr TupleCell& operator=(TupleCell&) noexcept = delete;
				constexpr TupleCell& operator=(const TupleCell&&) noexcept = delete;

				constexpr TupleCell& operator=(const TupleCell& tc) noexcept
				{
					value = tc.value;
					return *this;
				}

				constexpr TupleCell& operator=(TupleCell&& tc) noexcept
				{
					value = std::move(tc.value);
					return *this;
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

				constexpr explicit TupleImpl(Ts&...) noexcept = delete;
				constexpr explicit TupleImpl(const Ts&&...) noexcept = delete;

				constexpr explicit TupleImpl(const Ts&... args) noexcept
					: TupleCell<Ns, Ts>(static_cast<const Ts&>(args))...
				{
				}

				constexpr explicit TupleImpl(Ts&&... args) noexcept
					: TupleCell<Ns, Ts>(static_cast<Ts&&>(args))...
				{
				}

				~TupleImpl() noexcept = default;

				constexpr explicit TupleImpl(TupleImpl&) noexcept = delete;
				constexpr explicit TupleImpl(const TupleImpl&&) noexcept = delete;

				constexpr explicit TupleImpl(const TupleImpl& ti) noexcept
					: TupleCell<Ns, Ts>(static_cast<const TupleCell<Ns, Ts>&>(ti))...
				{
				}

				constexpr explicit TupleImpl(TupleImpl&& ti) noexcept
					: TupleCell<Ns, Ts>(static_cast<TupleCell<Ns, Ts>&&>(ti))...
				{
				}

				constexpr TupleImpl& operator=(TupleImpl&) noexcept = delete;
				constexpr TupleImpl& operator=(const TupleImpl&&) noexcept = delete;

				constexpr TupleImpl& operator=(const TupleImpl& ti) noexcept
				{
					std::initializer_list<int>
					{
						(TupleCell<Ns, Ts>::operator=(static_cast<const TupleCell<Ns, Ts>&>(ti)), 0)...
					};
					return *this;
				}

				constexpr TupleImpl& operator=(TupleImpl&& ti) noexcept
				{
					std::initializer_list<int>
					{
						(TupleCell<Ns, Ts>::operator=(static_cast<TupleCell<Ns, Ts>&&>(ti)), 0)...
					};
					return *this;
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
			constexpr Tuple() noexcept
				: TupleImpl<std::make_index_sequence<sizeof...(Ts)>, Ts...>()
			{
			}

			constexpr Tuple(Ts&...) noexcept = delete;
			constexpr Tuple(const Ts&&...) noexcept = delete;

			constexpr Tuple(const Ts&... args) noexcept
				: TupleImpl<std::make_index_sequence<sizeof...(Ts)>, Ts...>(static_cast<const Ts&>(args)...)
			{
			}

			constexpr Tuple(Ts&&... args) noexcept
				: TupleImpl<std::make_index_sequence<sizeof...(Ts)>, Ts...>(static_cast<Ts&&>(args)...)
			{
			}

			~Tuple() noexcept = default;

			constexpr Tuple(Tuple&) noexcept = delete;
			constexpr Tuple(const Tuple&&) noexcept = delete;

			constexpr Tuple(const Tuple& tuple) noexcept
				: TupleImpl<std::make_index_sequence<sizeof...(Ts)>, Ts...>
				  (
					  static_cast<const TupleImpl<std::make_index_sequence<sizeof...(Ts)>, Ts...>&>(tuple)
				  )
			{
			}

			constexpr Tuple(Tuple&& tuple) noexcept
				: TupleImpl<std::make_index_sequence<sizeof...(Ts)>, Ts...>
				  (
					  static_cast<TupleImpl<std::make_index_sequence<sizeof...(Ts)>, Ts...>&&>(tuple)
				  )
			{
			}

			constexpr Tuple& operator=(Tuple&) noexcept = delete;
			constexpr Tuple& operator=(const Tuple&&) noexcept = delete;

			constexpr Tuple& operator=(const Tuple& tuple) noexcept
			{
				TupleImpl<std::make_index_sequence<sizeof...(Ts)>, Ts...>::operator=
				(
					static_cast<const TupleImpl<std::make_index_sequence<sizeof...(Ts)>, Ts...>&>(tuple)
				);
				return *this;
			}

			constexpr Tuple& operator=(Tuple&& tuple) noexcept
			{
				TupleImpl<std::make_index_sequence<sizeof...(Ts)>, Ts...>::operator=
				(
					static_cast<TupleImpl<std::make_index_sequence<sizeof...(Ts)>, Ts...>&&>(tuple)
				);
				return *this;
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
			(tuple.Tuple_V1::template TupleCell<N, typename TupleElementType<N, Tuple_V1::Tuple<Ts...>>::Type>::value);
	}

	template<std::size_t N, typename... Ts>
	inline constexpr auto Get(Tuple_V1::Tuple<Ts...>&& tuple) noexcept
		-> typename TupleElementType<N, Tuple_V1::Tuple<Ts...>>::Type&&
	{
		return static_cast<typename TupleElementType<N, Tuple_V1::Tuple<Ts...>>::Type&&>
			(tuple.Tuple_V1::template TupleCell<N, typename TupleElementType<N, Tuple_V1::Tuple<Ts...>>::Type>::value);
	}

	template<std::size_t N, typename... Ts>
	inline constexpr auto Get(const Tuple_V1::Tuple<Ts...>& tuple) noexcept
		-> const typename TupleElementType<N, Tuple_V1::Tuple<Ts...>>::Type&
	{
		return static_cast<const typename TupleElementType<N, Tuple_V1::Tuple<Ts...>>::Type&>
			(tuple.Tuple_V1::template TupleCell<N, typename TupleElementType<N, Tuple_V1::Tuple<Ts...>>::Type>::value);
	}

	template<std::size_t N, typename... Ts>
	inline constexpr auto Get(const Tuple_V1::Tuple<Ts...>&& tuple) noexcept
		-> const typename TupleElementType<N, Tuple_V1::Tuple<Ts...>>::Type&&
	{
		return static_cast<const typename TupleElementType<N, Tuple_V1::Tuple<Ts...>>::Type&&>
			(tuple.Tuple_V1::template TupleCell<N, typename TupleElementType<N, Tuple_V1::Tuple<Ts...>>::Type>::value);
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
			(tuple.Tuple_V1::template TupleCell<N, typename TupleElementType<N, Tuple_V1::Tuple<Ts...>>::Type>::value);
	}

	template<typename T, typename... Ts>
	inline constexpr T&& Get(Tuple_V1::Tuple<Ts...>&& tuple) noexcept
	{
		constexpr std::size_t N = GetImpl<sizeof...(Ts), T, 0, Ts...>::value;
		return static_cast<T&&>
			(tuple.Tuple_V1::template TupleCell<N, typename TupleElementType<N, Tuple_V1::Tuple<Ts...>>::Type>::value);
	}

	template<typename T, typename... Ts>
	inline constexpr const T& Get(const Tuple_V1::Tuple<Ts...>& tuple) noexcept
	{
		constexpr std::size_t N = GetImpl<sizeof...(Ts), T, 0, Ts...>::value;
		return static_cast<const T&>
			(tuple.Tuple_V1::template TupleCell<N, typename TupleElementType<N, Tuple_V1::Tuple<Ts...>>::Type>::value);
	}

	template<typename T, typename... Ts>
	inline constexpr const T&& Get(const Tuple_V1::Tuple<Ts...>&& tuple) noexcept
	{
		constexpr std::size_t N = GetImpl<sizeof...(Ts), T, 0, Ts...>::value;
		return static_cast<const T&&>
			(tuple.Tuple_V1::template TupleCell<N, typename TupleElementType<N, Tuple_V1::Tuple<Ts...>>::Type>::value);
	}

} //# namespace Lynx


namespace Lynx
{

	template<typename... Ts>
	inline constexpr auto MakeTuple(Ts&&... args) noexcept -> Tuple_V1::Tuple<std::remove_reference_t<Ts>...>
	{
		return Tuple_V1::Tuple<std::remove_reference_t<Ts>...>{ std::forward<Ts>(args)... };
	}

	struct IgnoreType
	{
		template<typename T>
		const IgnoreType& operator=(const T&) const noexcept
		{
			return *this;
		}
	};

	static const IgnoreType Ignore;

	template<typename... Ts>
	inline constexpr auto Tie(Ts&... args) noexcept -> Tuple_V1::Tuple<Ts&...>
	{
		return Tuple_V1::Tuple<Ts&...>{ args... };
	}

} //# namespace Lynx
