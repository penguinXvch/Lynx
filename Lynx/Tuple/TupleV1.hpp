
#pragma once

#include <utility>


namespace Lynx::Tuple_V1
{

    namespace
    {
        template <std::size_t N, typename T>
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

            template <std::size_t I, typename U>
            constexpr explicit TupleCell(const TupleCell<I, U>& tc) noexcept
                : value(tc.value)
            {
            }

            template <std::size_t I, typename U>
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

            template <std::size_t I, typename U>
            constexpr TupleCell& operator=(const TupleCell<I, U>& tc) noexcept
            {
                value = tc.value;
                return *this;
            }

            template <std::size_t I, typename U>
            constexpr TupleCell& operator=(TupleCell<I, U>&& tc) noexcept
            {
                value = tc.value;
                tc.value = U();
                return *this;
            }

            constexpr void Swap(TupleCell& tc) noexcept
            {
                T tmp = value;
                value = tc.value;
                tc.value = tmp;
            }

            T value;
        };
    }

    namespace
    {
        template <typename...>
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

        template <std::size_t... Ns, typename... Ts>
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

            template <std::size_t... Is, typename... Args>
            constexpr explicit TupleImpl(const TupleImpl<std::index_sequence<Is...>, Args...>& ti) noexcept
                : TupleCell<Ns, Ts>(static_cast<const TupleCell<Is, Args>&>(ti))...
            {
            }

            template <std::size_t... Is, typename... Args>
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

            template <std::size_t... Is, typename... Args>
            constexpr TupleImpl& operator=(const TupleImpl<std::index_sequence<Is...>, Args...>& ti) noexcept
            {
                std::initializer_list<int>
                {
                    (TupleCell<Ns, Ts>::template operator=<Is, Args>(static_cast<const TupleCell<Is, Args>&>(ti)), 0)...
                };
                return *this;
            }

            template <std::size_t... Is, typename... Args>
            constexpr TupleImpl& operator=(TupleImpl<std::index_sequence<Is...>, Args...>&& ti) noexcept
            {
                std::initializer_list<int>
                {
                    (TupleCell<Ns, Ts>::template operator=<Is, Args>(static_cast<TupleCell<Is, Args>&&>(ti)), 0)...
                };
                return *this;
            }

            constexpr void Swap(TupleImpl& ti) noexcept
            {
                std::initializer_list<int>
                {
                    (TupleCell<Ns, Ts>::Swap(static_cast<TupleCell<Ns, Ts>&>(ti)), 0)...
                };
            }
        };
    }

    /*
     * Tuple 实现方式：非递归式多继承。
     */
    template <typename... Ts>
    struct Tuple
        : public TupleImpl<std::make_index_sequence<sizeof...(Ts)>, Ts...>
    {
        static constexpr std::size_t TupleSize = sizeof...(Ts);

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

        constexpr void Swap(Tuple& tuple) noexcept
        {
            TupleImpl<std::make_index_sequence<sizeof...(Ts)>, Ts...>::Swap
            (
                static_cast<TupleImpl<std::make_index_sequence<sizeof...(Ts)>, Ts...>&>(tuple)
            );
        }
    };

    template <>
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

} // namespace Lynx::Tuple_V1


namespace Lynx::Tuple_V1
{

    namespace
    {
        template <std::size_t N, typename T, typename... Ts>
        struct TupleElementTypeImpl
        {
            using Type = typename TupleElementTypeImpl<N - 1, Ts...>::Type;
        };

        template <typename T, typename... Ts>
        struct TupleElementTypeImpl<0, T, Ts...>
        {
            using Type = T;
        };
    }

    template <std::size_t, typename>
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

    template <std::size_t N, typename... Ts>
    struct TupleElementType<N, Lynx::Tuple_V1::Tuple<Ts...>>
    {
        using Type = std::enable_if_t
        <
            (N >= 0) && (N < sizeof...(Ts)),
            typename TupleElementTypeImpl<N, Ts...>::Type
        >;
    };

    template <std::size_t N, typename... Ts>
    struct TupleElementType<N, const Lynx::Tuple_V1::Tuple<Ts...>> : public TupleElementType<N, Lynx::Tuple_V1::Tuple<Ts...>>
    {
    };
    template <std::size_t N, typename... Ts>
    struct TupleElementType<N, Lynx::Tuple_V1::Tuple<Ts...>&> : public TupleElementType<N, Lynx::Tuple_V1::Tuple<Ts...>>
    {
    };
    template <std::size_t N, typename... Ts>
    struct TupleElementType<N, const Lynx::Tuple_V1::Tuple<Ts...>&> : public TupleElementType<N, Lynx::Tuple_V1::Tuple<Ts...>>
    {
    };
    template <std::size_t N, typename... Ts>
    struct TupleElementType<N, Lynx::Tuple_V1::Tuple<Ts...>&&> : public TupleElementType<N, Lynx::Tuple_V1::Tuple<Ts...>>
    {
    };
    template <std::size_t N, typename... Ts>
    struct TupleElementType<N, const Lynx::Tuple_V1::Tuple<Ts...>&&> : public TupleElementType<N, Lynx::Tuple_V1::Tuple<Ts...>>
    {
    };

    template <typename>
    struct TupleSize
    {
        constexpr explicit TupleSize() noexcept = delete;
        ~TupleSize() noexcept = delete;
        constexpr explicit TupleSize(TupleSize&) noexcept = delete;
        constexpr explicit TupleSize(TupleSize&&) noexcept = delete;
        constexpr explicit TupleSize(const TupleSize&) noexcept = delete;
        constexpr explicit TupleSize(const TupleSize&&) noexcept = delete;
        constexpr TupleSize& operator=(TupleSize&) noexcept = delete;
        constexpr TupleSize& operator=(TupleSize&&) noexcept = delete;
        constexpr TupleSize& operator=(const TupleSize&) noexcept = delete;
        constexpr TupleSize& operator=(const TupleSize&&) noexcept = delete;
    };

    template <typename... Ts>
    struct TupleSize<Lynx::Tuple_V1::Tuple<Ts...>>
    {
        static constexpr std::enable_if_t<(sizeof...(Ts) > 0), std::size_t> value = sizeof...(Ts);
    };

    template <typename... Ts>
    struct TupleSize<const Lynx::Tuple_V1::Tuple<Ts...>> : public TupleSize<Lynx::Tuple_V1::Tuple<Ts...>>
    {
    };
    template <typename... Ts>
    struct TupleSize<Lynx::Tuple_V1::Tuple<Ts...>&> : public TupleSize<Lynx::Tuple_V1::Tuple<Ts...>>
    {
    };
    template <typename... Ts>
    struct TupleSize<const Lynx::Tuple_V1::Tuple<Ts...>&> : public TupleSize<Lynx::Tuple_V1::Tuple<Ts...>>
    {
    };
    template <typename... Ts>
    struct TupleSize<Lynx::Tuple_V1::Tuple<Ts...>&&> : public TupleSize<Lynx::Tuple_V1::Tuple<Ts...>>
    {
    };
    template <typename... Ts>
    struct TupleSize<const Lynx::Tuple_V1::Tuple<Ts...>&&> : public TupleSize<Lynx::Tuple_V1::Tuple<Ts...>>
    {
    };

} // namespace Lynx::Tuple_V1


namespace Lynx::Tuple_V1
{

    template <std::size_t N, typename... Ts>
    inline constexpr auto Get(Lynx::Tuple_V1::Tuple<Ts...>& tuple) noexcept
        -> typename TupleElementType<N, Lynx::Tuple_V1::Tuple<Ts...>>::Type&
    {
        return static_cast<typename TupleElementType<N, Lynx::Tuple_V1::Tuple<Ts...>>::Type&>
        (
            tuple.Lynx::Tuple_V1::template TupleCell<N, typename TupleElementType<N, Lynx::Tuple_V1::Tuple<Ts...>>::Type>::value
        );
    }

    template <std::size_t N, typename... Ts>
    inline constexpr auto Get(Lynx::Tuple_V1::Tuple<Ts...>&& tuple) noexcept
        -> typename TupleElementType<N, Lynx::Tuple_V1::Tuple<Ts...>>::Type&&
    {
        return static_cast<typename TupleElementType<N, Lynx::Tuple_V1::Tuple<Ts...>>::Type&&>
        (
            tuple.Lynx::Tuple_V1::template TupleCell<N, typename TupleElementType<N, Lynx::Tuple_V1::Tuple<Ts...>>::Type>::value
        );
    }

    template <std::size_t N, typename... Ts>
    inline constexpr auto Get(const Lynx::Tuple_V1::Tuple<Ts...>& tuple) noexcept
        -> const typename TupleElementType<N, Lynx::Tuple_V1::Tuple<Ts...>>::Type&
    {
        return static_cast<const typename TupleElementType<N, Lynx::Tuple_V1::Tuple<Ts...>>::Type&>
        (
            tuple.Lynx::Tuple_V1::template TupleCell<N, typename TupleElementType<N, Lynx::Tuple_V1::Tuple<Ts...>>::Type>::value
        );
    }

    template <std::size_t N, typename... Ts>
    inline constexpr auto Get(const Lynx::Tuple_V1::Tuple<Ts...>&& tuple) noexcept
        -> const typename TupleElementType<N, Lynx::Tuple_V1::Tuple<Ts...>>::Type&&
    {
        return static_cast<const typename TupleElementType<N, Lynx::Tuple_V1::Tuple<Ts...>>::Type&&>
        (
            tuple.Lynx::Tuple_V1::template TupleCell<N, typename TupleElementType<N, Lynx::Tuple_V1::Tuple<Ts...>>::Type>::value
        );
    }

    namespace
    {
        template <std::size_t N, typename T, std::size_t I, typename U, typename... Us>
        struct GetImpl
        {
            static constexpr std::enable_if_t<(I < N), std::size_t> value = GetImpl<N, T, I + 1, Us...>::value;
        };

        template <std::size_t N, typename T, std::size_t I, typename... Us>
        struct GetImpl<N, T, I, T, Us...>
        {
            static constexpr std::enable_if_t<(I < N), std::size_t> value = I;
        };
    }

    template <typename T, typename... Ts>
    inline constexpr T& Get(Lynx::Tuple_V1::Tuple<Ts...>& tuple) noexcept
    {
        constexpr std::size_t N = GetImpl<sizeof...(Ts), T, 0, Ts...>::value;
        return static_cast<T&>(tuple.Lynx::Tuple_V1::template TupleCell<N, typename TupleElementType<N, Lynx::Tuple_V1::Tuple<Ts...>>::Type>::value);
    }

    template <typename T, typename... Ts>
    inline constexpr T&& Get(Lynx::Tuple_V1::Tuple<Ts...>&& tuple) noexcept
    {
        constexpr std::size_t N = GetImpl<sizeof...(Ts), T, 0, Ts...>::value;
        return static_cast<T&&>(tuple.Lynx::Tuple_V1::template TupleCell<N, typename TupleElementType<N, Lynx::Tuple_V1::Tuple<Ts...>>::Type>::value);
    }

    template <typename T, typename... Ts>
    inline constexpr const T& Get(const Lynx::Tuple_V1::Tuple<Ts...>& tuple) noexcept
    {
        constexpr std::size_t N = GetImpl<sizeof...(Ts), T, 0, Ts...>::value;
        return static_cast<const T&>(tuple.Lynx::Tuple_V1::template TupleCell<N, typename TupleElementType<N, Lynx::Tuple_V1::Tuple<Ts...>>::Type>::value);
    }

    template <typename T, typename... Ts>
    inline constexpr const T&& Get(const Lynx::Tuple_V1::Tuple<Ts...>&& tuple) noexcept
    {
        constexpr std::size_t N = GetImpl<sizeof...(Ts), T, 0, Ts...>::value;
        return static_cast<const T&&>(tuple.Lynx::Tuple_V1::template TupleCell<N, typename TupleElementType<N, Lynx::Tuple_V1::Tuple<Ts...>>::Type>::value);
    }

} // namespace Lynx::Tuple_V1


namespace Lynx::Tuple_V1
{

    template <typename... Ts>
    inline constexpr auto MakeTuple(Ts&&... args) noexcept -> Lynx::Tuple_V1::Tuple<std::remove_reference_t<Ts>...>
    {
        return Lynx::Tuple_V1::Tuple<std::remove_reference_t<Ts>...>{ std::forward<Ts>(args)... };
    }

    namespace
    {
        struct IgnoreType
        {
            template <typename T>
            const IgnoreType& operator=(const T&) const
            {
                return *this;
            }
        };

        inline constexpr IgnoreType _;
    }

    template <typename... Ts>
    inline constexpr auto Tie(Ts&... args) noexcept -> Lynx::Tuple_V1::Tuple<Ts&...>
    {
        return Lynx::Tuple_V1::Tuple<Ts&...>{ args... };
    }

    template <typename... Ts>
    inline constexpr void Swap(Lynx::Tuple_V1::Tuple<Ts...>& a, Lynx::Tuple_V1::Tuple<Ts...>& b) noexcept
    {
        a.Swap(b);
    }

    namespace
    {
        template <std::size_t... Ns, typename... Ts>
        inline constexpr bool OperatorEqual
        (
            std::index_sequence<Ns...>,
            const Lynx::Tuple_V1::Tuple<Ts...>& a,
            const Lynx::Tuple_V1::Tuple<Ts...>& b
        ) noexcept
        {
            return (... && (Get<Ns>(a) == Get<Ns>(b)));
        }
    }

    template <typename... Ts>
    inline constexpr bool operator==(const Lynx::Tuple_V1::Tuple<Ts...>& a, const Lynx::Tuple_V1::Tuple<Ts...>& b) noexcept
    {
        return OperatorEqual(std::make_index_sequence<sizeof...(Ts)>{}, a, b);
    }

    template <typename... Ts>
    inline constexpr bool operator!=(const Lynx::Tuple_V1::Tuple<Ts...>& a, const Lynx::Tuple_V1::Tuple<Ts...>& b) noexcept
    {
        return !OperatorEqual(std::make_index_sequence<sizeof...(Ts)>{}, a, b);
    }

} // namespace Lynx::Tuple_V1


namespace Lynx::Tuple_V1
{

    namespace
    {
        template <template <typename...> typename>
        struct IsLynxTupleV1Tuple
        {
            static constexpr bool value = false;
        };

        template <>
        struct IsLynxTupleV1Tuple<Lynx::Tuple_V1::Tuple>
        {
            static constexpr bool value = true;
        };
    }

    namespace
    {
        template <typename...>
        struct OutputType;

        template
        <
            template <typename...> typename LynxTupleV1Tuple,
            typename... Ts
        >
        struct OutputType<LynxTupleV1Tuple<Ts...>>
        {
            using type = std::enable_if_t
            <
                (IsLynxTupleV1Tuple<LynxTupleV1Tuple>::value && (sizeof...(Ts) > 0)),
                Lynx::Tuple_V1::Tuple<std::remove_reference_t<Ts>...>
            >;
        };

        template
        <
            template <typename...> typename LynxTupleV1Tuple,
            typename... Ts1,
            typename... Ts2
        >
        struct OutputType<LynxTupleV1Tuple<Ts1...>, LynxTupleV1Tuple<Ts2...>>
        {
            using type = std::enable_if_t
            <
                (IsLynxTupleV1Tuple<LynxTupleV1Tuple>::value && (sizeof...(Ts1) > 0) && (sizeof...(Ts2) > 0)),
                Lynx::Tuple_V1::Tuple<std::remove_reference_t<Ts1>..., std::remove_reference_t<Ts2>...>
            >;
        };

        template
        <
            template <typename...> typename LynxTupleV1Tuple,
            typename... Ts1,
            typename... Ts2,
            typename... Us
        >
        struct OutputType<LynxTupleV1Tuple<Ts1...>, LynxTupleV1Tuple<Ts2...>, Us...>
        {
            using type = std::enable_if_t
            <
                (IsLynxTupleV1Tuple<LynxTupleV1Tuple>::value && (sizeof...(Ts1) > 0) && (sizeof...(Ts2) > 0)),
                typename OutputType<Lynx::Tuple_V1::Tuple<std::remove_reference_t<Ts1>..., std::remove_reference_t<Ts2>...>, Us...>::type
            >;
        };
    }

    namespace
    {
        template <typename T, std::size_t... Ns>
        inline constexpr auto TupleCatImpl(T&& arg, std::index_sequence<Ns...>) noexcept
            -> typename OutputType<std::remove_cv_t<std::remove_reference_t<T>>>::type
        {
            return { Get<Ns>(std::forward<T>(arg))... };
        }

        template <typename T, std::size_t... Ns, typename U, std::size_t... Is>
        inline constexpr auto TupleCatImpl(T&& arg1, std::index_sequence<Ns...>, U&& arg2, std::index_sequence<Is...>) noexcept
            -> typename OutputType<std::remove_cv_t<std::remove_reference_t<T>>, std::remove_cv_t<std::remove_reference_t<U>>>::type
        {
            return { Get<Ns>(std::forward<T>(arg1))..., Get<Is>(std::forward<U>(arg2))... };
        }
    }

    template <typename T>
    inline constexpr auto TupleCat(T&& arg) noexcept
        -> typename OutputType<std::remove_cv_t<std::remove_reference_t<T>>>::type
    {
        return TupleCatImpl(std::forward<T>(arg), std::make_index_sequence<TupleSize<T>::value>{});
    }

    template <typename T, typename U>
    inline constexpr auto TupleCat(T&& arg1, U&& arg2) noexcept
        -> typename OutputType<std::remove_cv_t<std::remove_reference_t<T>>, std::remove_cv_t<std::remove_reference_t<U>>>::type
    {
        return TupleCatImpl
        (
            std::forward<T>(arg1), std::make_index_sequence<TupleSize<T>::value>{},
            std::forward<U>(arg2), std::make_index_sequence<TupleSize<U>::value>{}
        );
    }

    template <typename T, typename U, typename... Vs>
    inline constexpr auto TupleCat(T&& arg1, U&& arg2, Vs&&... args) noexcept
        -> typename OutputType
        <
            std::remove_cv_t<std::remove_reference_t<T>>,
            std::remove_cv_t<std::remove_reference_t<U>>,
            std::remove_cv_t<std::remove_reference_t<Vs>>...
        >::type
    {
        return TupleCat
        (
            TupleCat(std::forward<T>(arg1), std::forward<U>(arg2)),
            TupleCat(std::forward<Vs>(args)...)
        );
    }

} // namespace Lynx::Tuple_V1
