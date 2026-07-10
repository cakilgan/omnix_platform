//
// Created by cakilgan on 3/8/26.
//

#ifndef OMNIX_UTIL_H
#define OMNIX_UTIL_H
#include "../platform/assert.h"
#include "byte.h"
#include "crash.h"
#include "omnix/platform/defines.h"
#include "result.h"

namespace ox {
// NOTE: exact copy of std:: type trait , utils.
template <typename _Tp> struct remove_reference {
    using type = _Tp;
};
template <typename _Tp> struct remove_reference<_Tp &> {
    using type = _Tp;
};
template <typename _Tp> struct remove_reference<_Tp &&> {
    using type = _Tp;
};

template <typename _Tp, _Tp __v> struct integral_constant {
    static constexpr _Tp value = __v;
    using value_type = _Tp;
    using type = integral_constant<_Tp, __v>;
    constexpr operator value_type() const noexcept { return value; }
    constexpr value_type operator()() const noexcept { return value; }
};

template <bool __v> using __bool_constant = integral_constant<bool, __v>;
using true_type = __bool_constant<true>;
using false_type = __bool_constant<false>;
template <typename...> using void_t = void;

template <typename> struct is_lvalue_reference : public false_type {};
template <typename _Tp> struct is_lvalue_reference<_Tp &> : public true_type {};

template <typename _Tp>
[[__nodiscard__, __gnu__::__always_inline__]]
constexpr typename remove_reference<_Tp>::type &&move(_Tp &&__t) noexcept {
    return static_cast<typename remove_reference<_Tp>::type &&>(__t);
}

template <typename _Tp>
[[__nodiscard__, __gnu__::__always_inline__]]
constexpr _Tp &&forward(typename remove_reference<_Tp>::type &__t) noexcept {
    return static_cast<_Tp &&>(__t);
}

template <typename _Tp>
[[__nodiscard__, __gnu__::__always_inline__]]
constexpr _Tp &&forward(typename remove_reference<_Tp>::type &&__t) noexcept {
    static_assert(
        !is_lvalue_reference<_Tp>::value,
        "ox::forward must not be used to convert an rvalue to an lvalue");
    return static_cast<_Tp &&>(__t);
}

template <typename T> T *safe(T *check) {
    OX_CHECK(check != nullptr);
    return check;
}

template <typename T> T unchecked(result<T> _result) {
    OX_ASSERT(_result);
    return ox::move(_result.value());
}
OX_INLINE void unchecked(const result_t _result) { OX_ASSERT(_result == ok); }

template <typename T> OX_FORCE_CONSTEXPR bytes size_of(const T &obj) {
    return bytes(sizeof(T));
}
template <typename T> OX_FORCE_CONSTEXPR bytes size_of() {
    return bytes{sizeof(T)};
}
template <typename T> OX_FORCE_CONSTEXPR bytes align_of(const T &obj) {
    return bytes(alignof(T));
}
template <typename T> OX_FORCE_CONSTEXPR bytes align_of() {
    return bytes{alignof(T)};
}


} // namespace ox
#endif // OMNIX_UTIL_H
