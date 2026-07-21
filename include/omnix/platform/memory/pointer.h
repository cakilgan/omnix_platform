//
// Created by cakilgan on 7/10/26.
//

#ifndef OMNIX_PLATFORM_POINTER_H
#define OMNIX_PLATFORM_POINTER_H
#include "../types.h"
#include <cstddef>
namespace ox {
    namespace mem {
        template<typename T>
        struct pointer {
            constexpr pointer(T* from = nullptr):raw(from){}
            pointer(const pointer& copy) = default;
            pointer& operator=(const pointer& copy) = default;

            pointer(pointer&&) noexcept = default;
            pointer& operator=(pointer&&) noexcept = default;

            constexpr T& operator*() const noexcept{
                return *raw;
            }
            constexpr T* operator->() const noexcept{
                return raw;
            }
            constexpr T* get() const noexcept{
                return raw;
            }
            constexpr T* release() noexcept {
                T* tmp = raw;
                raw = nullptr;
                return tmp;
            }

            pointer operator+(usize count) const noexcept{
                return {this->get() + count};
            }
            friend constexpr pointer operator+(usize n, pointer p) noexcept{
                return p + n;
            }
            pointer& operator+=(usize count) noexcept{
                raw = this->get() + count;
                return *this;
            }
            pointer operator-(usize count) const noexcept{
                return {this->get() - count};
            }
            pointer& operator-=(usize count) noexcept{
                raw = this->get() - count;
                return *this;
            }

            constexpr pointer& operator++() noexcept {
                ++raw;
                return *this;
            }
            constexpr pointer operator++(int) noexcept {
                pointer tmp(*this);
                ++(*this);
                return tmp;
            }
            constexpr pointer& operator--() noexcept {
                --raw;
                return *this;
            }
            constexpr pointer operator--(int) noexcept {
                pointer tmp(*this);
                --(*this);
                return tmp;
            }

            constexpr T& operator[](usize index) noexcept{
                return raw[index];
            }
            constexpr const T& operator[](usize index) const noexcept{
                return raw[index];
            }

            constexpr explicit operator bool() const { return raw != nullptr; }

            constexpr isize operator-(pointer other) const noexcept{
                return raw - other.raw;
            }


            friend constexpr bool operator<(pointer lhs, pointer rhs) noexcept{
                return lhs.raw < rhs.raw;
            }
            friend constexpr bool operator<=(pointer lhs, pointer rhs) noexcept{
                return lhs.raw <= rhs.raw;
            }
            friend constexpr bool operator>(pointer lhs, pointer rhs) noexcept{
                return lhs.raw > rhs.raw;
            }
            friend constexpr bool operator>=(pointer lhs, pointer rhs) noexcept{
                return lhs.raw >= rhs.raw;
            }

            friend constexpr bool operator==(pointer lhs, pointer rhs) noexcept{
                return lhs.raw == rhs.raw;
            }
            friend constexpr bool operator!=(pointer lhs, pointer rhs) noexcept{
                return lhs.raw != rhs.raw;
            }

            friend constexpr bool operator==(pointer a, std::nullptr_t) noexcept{
                return a.raw == nullptr;
            }
            friend constexpr bool operator!=(pointer a, std::nullptr_t) noexcept{
                return a.raw != nullptr;
            }
            friend constexpr bool operator==(std::nullptr_t, pointer p) noexcept {
                return p.raw == nullptr;
            }
            friend constexpr bool operator!=(std::nullptr_t, pointer p) noexcept {
                return p.raw != nullptr;
            }

            friend constexpr void swap(pointer& a, pointer& b) noexcept {
                if (a.raw == b.raw) return;
                const auto tmp = a.raw;
                a.raw = b.raw;
                b.raw = tmp;
            }
        protected:
            T *raw;
        };

        template<>
        struct pointer<void> {
            constexpr pointer(void* from = nullptr):raw(from){}
            pointer(const pointer& copy) = default;
            pointer& operator=(const pointer& copy) = default;
            pointer(pointer&& o) noexcept = default;
            pointer& operator=(pointer&& o)  noexcept = default;

            constexpr void* get() const {
                return raw;
            }

            constexpr explicit operator bool() const { return raw != nullptr; }

            friend constexpr bool operator<(pointer lhs, pointer rhs) noexcept{
                return lhs.raw < rhs.raw;
            }
            friend constexpr bool operator<=(pointer lhs, pointer rhs) noexcept{
                return lhs.raw <= rhs.raw;
            }
            friend constexpr bool operator>(pointer lhs, pointer rhs) noexcept{
                return lhs.raw > rhs.raw;
            }
            friend constexpr bool operator>=(pointer lhs, pointer rhs) noexcept{
                return lhs.raw >= rhs.raw;
            }

            friend constexpr bool operator==(pointer lhs, pointer rhs) noexcept{
                return lhs.raw == rhs.raw;
            }
            friend constexpr bool operator!=(pointer lhs, pointer rhs) noexcept{
                return lhs.raw != rhs.raw;
            }

            friend constexpr bool operator==(pointer a, std::nullptr_t) noexcept{
                return a.raw == nullptr;
            }
            friend constexpr bool operator!=(pointer a, std::nullptr_t) noexcept{
                return a.raw != nullptr;
            }
            friend constexpr bool operator==(std::nullptr_t, pointer p) noexcept {
                return p.raw == nullptr;
            }
            friend constexpr bool operator!=(std::nullptr_t, pointer p) noexcept {
                return p.raw != nullptr;
            }

            friend constexpr void swap(pointer& a, pointer& b) noexcept {
                const auto tmp = a.raw;
                a.raw = b.raw;
                b.raw = tmp;
            }
        private:
            void* raw;
        };

        template<typename T = void>
        using ptr = pointer<T>;
        using vptr =  ptr<void>;
        using cvptr = const vptr;
        using vptrc = vptr const;

        template <typename T = void> constexpr pointer<T> null = nullptr;

        template<typename T, typename U>
        constexpr pointer<T> cast(pointer<U> other) noexcept {
            return {reinterpret_cast<T*>(other.get())};
        }
        template<typename T, typename U>
        constexpr pointer<T> cast_s(pointer<U> other) noexcept {
            return {static_cast<T*>(other.get())};
        }
        template<typename T>
        constexpr pointer<void> vcast(pointer<T> other) noexcept {
            return cast_s<void>(other);
        }

        template <typename T> pointer<T> safe(pointer<T> check) {
            OX_CHECK(check != nullptr);
            return check;
        }


    }

    using mem::pointer;
    using mem::ptr;
    using mem::vptr;
    using mem::cvptr;
    using mem::vptrc;
    using mem::null;
    using mem::cast;
    using mem::cast_s;
    using mem::vcast;
    using mem::safe;
}

#endif //OMNIX_PLATFORM_POINTER_H
