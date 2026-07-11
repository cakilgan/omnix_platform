//
// Created by cakilgan on 7/10/26.
//

#ifndef OMNIX_PLATFORM_POINTER_H
#define OMNIX_PLATFORM_POINTER_H
#include "omnix/platform/types.h"
namespace ox {
    namespace mem {
        template<typename T>
        struct pointer {
            constexpr pointer(T* from = nullptr):raw(from){}
            pointer(const pointer& copy) = default;
            pointer& operator=(const pointer& copy) = default;

            pointer(pointer&& o) noexcept :raw(o.raw){o.raw = nullptr;}
            pointer& operator=(pointer&& o)  noexcept {
                raw = o.raw;
                o.raw = nullptr;
                return *this;
            }

            T& operator*() const {
                return *raw;
            }
            T* operator->() const {
                return raw;
            }

            constexpr T* get() const {
                return raw;
            }
            constexpr operator void*() const {
                return get();
            }

            pointer operator+(usize count) {
                return {this->get() + count};
            }
            pointer& operator+=(usize count) {
                raw = this->get() + count;
                return *this;
            }
            pointer operator-(usize count) {
                return {this->get() - count};
            }
            pointer& operator-=(usize count) {
                raw = this->get() - count;
                return *this;
            }

            T& operator[](usize index) {
                return raw[index];
            }
        private:
            T *raw;
        };

        template<>
        struct pointer<void> {
            constexpr pointer(void* from = nullptr):raw(from){}
            pointer(const pointer& copy) = default;
            pointer& operator=(const pointer& copy) = default;
            pointer(pointer&& o) noexcept :raw(o.raw){o.raw = nullptr;}
            pointer& operator=(pointer&& o)  noexcept {
                raw = o.raw;
                o.raw = nullptr;
                return *this;
            }

            constexpr void* get() const {
                return raw;
            }
            constexpr operator void*() const {
                return get();
            }
        private:
            void* raw;
        };

        template<typename T = void>
        using ptr = pointer<T>;
        using vptr =  ptr<void>;
        using cvptr = const vptr;
        using vptrc = vptr const;

        template <typename T = void> constexpr ptr<T> null = nullptr;

        template<typename T,typename U>
        pointer<T> cast(const pointer<U>& other) {
            return {static_cast<T*>(other.get())};
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
    using mem::safe;


}
#endif //OMNIX_PLATFORM_POINTER_H
