
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

				constexpr explicit TupleCell(const T& arg) noexcept
					: value(arg)
				{
				}

				template<std::size_t I, typename U>
				constexpr explicit TupleCell(const TupleCell<I, U>& tc) noexcept
					: value(tc.value)
				{
				}

				template<std::size_t I, typename U>
				constexpr explicit TupleCell(TupleCell<I, U>&& tc) noexcept
					: value(tc.value)
				{
					tc.value = U();
				}

				~TupleCell() noexcept = default;

				constexpr explicit TupleCell(const TupleCell& tc) noexcept
					: value(tc.value)
				{
				}

				constexpr explicit TupleCell(TupleCell&& tc) noexcept
					: value(tc.value)
				{
					tc.value = T();
				}

				constexpr TupleCell& operator=(const TupleCell& tc) noexcept
				{
					if (this != &tc)
					{
						value = tc.value;
					}
					return *this;
				}

				constexpr TupleCell& operator=(TupleCell&& tc) noexcept
				{
					if (this != &tc)
					{
						value = tc.value;
						tc.value = T();
					}
					return *this;
				}

				template<std::size_t I, typename U>
				constexpr TupleCell& operator=(const TupleCell<I, U>& tc) noexcept
				{
					value = tc.value;
					return *this;
				}

				template<std::size_t I, typename U>
				constexpr TupleCell& operator=(TupleCell<I, U>&& tc) noexcept
				{
					value = tc.value;
					tc.value = U();
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

				constexpr explicit TupleImpl(const Ts&... args) noexcept
					: TupleCell<Ns, Ts>(static_cast<const Ts&>(args))...
				{
				}

				template<std::size_t... Is, typename... Args>
				constexpr explicit TupleImpl(const TupleImpl<std::index_sequence<Is...>, Args...>& ti) noexcept
					: TupleCell<Ns, Ts>(static_cast<const TupleCell<Is, Args>&>(ti))...
				{
				}

				template<std::size_t... Is, typename... Args>
				constexpr explicit TupleImpl(TupleImpl<std::index_sequence<Is...>, Args...>&& ti) noexcept
					: TupleCell<Ns, Ts>(static_cast<TupleCell<Is, Args>&&>(ti))...
				{
				}

				~TupleImpl() noexcept = default;

				constexpr explicit TupleImpl(const TupleImpl& ti) noexcept
					: TupleCell<Ns, Ts>(static_cast<const TupleCell<Ns, Ts>&>(ti))...
				{
				}

				constexpr explicit TupleImpl(TupleImpl&& ti) noexcept
					: TupleCell<Ns, Ts>(static_cast<TupleCell<Ns, Ts>&&>(ti))...
				{
				}

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

				template<std::size_t... Is, typename... Args>
				constexpr TupleImpl& operator=(const TupleImpl<std::index_sequence<Is...>, Args...>& ti) noexcept
				{
					std::initializer_list<int>
					{
						(TupleCell<Ns, Ts>::template operator=<Is, Args>(static_cast<const TupleCell<Is, Args>&>(ti)), 0)...
					};
					return *this;
				}

				template<std::size_t... Is, typename... Args>
				constexpr TupleImpl& operator=(TupleImpl<std::index_sequence<Is...>, Args...>&& ti) noexcept
				{
					std::initializer_list<int>
					{
						(TupleCell<Ns, Ts>::template operator=<Is, Args>(static_cast<TupleCell<Is, Args>&&>(ti)), 0)...
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

			constexpr Tuple(const Ts&... args) noexcept
				: TupleImpl<std::make_index_sequence<sizeof...(Ts)>, Ts...>(static_cast<const Ts&>(args)...)
			{
			}

			template
			<
				typename... Args,
				typename = std::enable_if_t
				<
					sizeof...(Ts) == sizeof...(Args) &&
					(... && std::is_constructible_v<Ts, const Args&>)
				>
			>
			constexpr Tuple(const Tuple<Args...>& tuple) noexcept
				: TupleImpl<std::make_index_sequence<sizeof...(Ts)>, Ts...>
				  (
					  static_cast<const TupleImpl<std::make_index_sequence<sizeof...(Args)>, Args...>&>(tuple)
				  )
			{
			}

			template
			<
				typename... Args,
				typename = std::enable_if_t
				<
					sizeof...(Ts) == sizeof...(Args) &&
					(... && std::is_constructible_v<Ts, Args&&>)
				>
			>
			constexpr Tuple(Tuple<Args...>&& tuple) noexcept
				: TupleImpl<std::make_index_sequence<sizeof...(Ts)>, Ts...>
				  (
					  static_cast<TupleImpl<std::make_index_sequence<sizeof...(Args)>, Args...>&&>(tuple)
				  )
			{
			}

			~Tuple() noexcept = default;

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

			template
			<
				typename... Args,
				typename = std::enable_if_t
				<
					sizeof...(Ts) == sizeof...(Args) &&
					(... && std::is_assignable_v<Ts&, const Args&>)
				>
			>
			constexpr Tuple& operator=(const Tuple<Args...>& tuple) noexcept
			{
				TupleImpl<std::make_index_sequence<sizeof...(Ts)>, Ts...>::template operator=
				(
					static_cast<const TupleImpl<std::make_index_sequence<sizeof...(Args)>, Args...>&>(tuple)
				);
				return *this;
			}

			template
			<
				typename... Args,
				typename = std::enable_if_t
				<
					sizeof...(Ts) == sizeof...(Args) &&
					(... && std::is_assignable_v<Ts&, Args>)
				>
			>
			constexpr Tuple& operator=(Tuple<Args...>&& tuple) noexcept
			{
				TupleImpl<std::make_index_sequence<sizeof...(Ts)>, Ts...>::template operator=
				(
					static_cast<TupleImpl<std::make_index_sequence<sizeof...(Args)>, Args...>&&>(tuple)
				);
				return *this;
			}
		};

		template<>
		struct Tuple<>
		{
			constexpr Tuple() noexcept = delete;
			~Tuple() noexcept = delete;
			constexpr Tuple(Tuple&) noexcept = delete;
			constexpr Tuple(Tuple&&) noexcept = delete;
			constexpr Tuple(const Tuple&) noexcept = delete;
			constexpr Tuple(const Tuple&&) noexcept = delete;
			constexpr Tuple& operator=(Tuple&) noexcept = delete;
			constexpr Tuple& operator=(Tuple&&) noexcept = delete;
			constexpr Tuple& operator=(const Tuple&) noexcept = delete;
			constexpr Tuple& operator=(const Tuple&&) noexcept = delete;
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

	namespace
	{
		struct IgnoreType
		{
			template<typename T>
			const IgnoreType& operator=(const T&) const
			{
				return *this;
			}
		};

		inline constexpr IgnoreType _;
	}

	template<typename... Ts>
	inline constexpr auto Tie(Ts&... args) noexcept -> Tuple_V1::Tuple<Ts&...>
	{
		return Tuple_V1::Tuple<Ts&...>{ args... };
	}

} //# namespace Lynx
