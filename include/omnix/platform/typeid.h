//
// Created by cakilgan on 7/22/26.
//

#ifndef OMNIX_PLATFORM_TYPEID_H
#define OMNIX_PLATFORM_TYPEID_H

#include "types.h"
#include <string_view>

namespace ox {
    using typeid_t = u64;

    struct type_identifier {
        typeid_t id;

        constexpr bool operator==(const type_identifier& other) const noexcept { return id == other.id; }
        constexpr bool operator!=(const type_identifier& other) const noexcept { return id != other.id; }
        constexpr bool operator<(const type_identifier& other) const noexcept { return id < other.id; }
    };

    inline constexpr type_identifier type_id_empty{0};

    namespace internal {
        constexpr typeid_t fnv1a_64(std::string_view str) noexcept {
            typeid_t hash = 14695981039346656037ULL;
            for (char c : str) {
                hash ^= static_cast<typeid_t>(c);
                hash *= 1099511628211ULL;
            }
            return hash;
        }

        template <typename T>
        constexpr std::string_view raw_type_name() noexcept {
#if defined(__clang__) || defined(__GNUC__)
            std::string_view name = __PRETTY_FUNCTION__;
            size_t start = name.find("T = ") + 4;
            size_t end = name.find_last_of("]");
            return name.substr(start, end - start);
#elif defined(_MSC_VER)
            std::string_view name = __FUNCSIG__;
            size_t start = name.find("raw_type_name<") + 14;
            size_t end = name.find_last_of(">");
            return name.substr(start, end - start);
#endif
        }

        template <typename T>
        constexpr typeid_t type_of() noexcept {
            return fnv1a_64(raw_type_name<T>());
        }
    }

    template <typename T>
    constexpr type_identifier type_of() noexcept {
        return {internal::type_of<T>()};
    }

    template <typename T>
    constexpr type_identifier type_of(const T& /*ignore*/) noexcept {
        return {internal::type_of<T>()};
    }
}

#endif //OMNIX_PLATFORM_TYPEID_H