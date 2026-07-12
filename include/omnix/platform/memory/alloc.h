//
// Created by cakilgan on 7/10/26.
//

#ifndef OMNIX_PLATFORM_ALLOC_H
#define OMNIX_PLATFORM_ALLOC_H


#include "../util.h"
#include "../result.h"
#include "../byte.h"
#include "memory.h"
#include <cstddef>

namespace ox {
    OX_RESULT_CATEGORY(memory,51000);
    namespace mem {
        struct err {
            OX_RESULT(memory,not_enough_memory);
            OX_RESULT(memory,already_freed);
            OX_RESULT(memory,memory_size_is_zero);
        };
        constexpr auto default_alignment = bytes(alignof(std::max_align_t));
        constexpr auto no_alignment = bytes(u64_max);

        result<memory> alloc_as_memory(bytes size,bytes alignment = default_alignment);
        result_t free(memory& mem,bytes alignment = no_alignment);
        result<vptr> alloc(bytes size,bytes alignment = default_alignment);
        result_t free(vptr& ptr);

        result<memory> valloc_as_memory(bytes size);
        result_t vfree(memory& mem);
        result<vptr> valloc(bytes size);
        result_t vfree(vptr& ptr,bytes size);

        result<memory> realloc_as_memory(memory& mem,bytes new_size) {
            return results::err::unsupported;
        }
        result<vptr> realloc(vptr& ptr,bytes new_size) {
            return results::err::unsupported;
        }

        template<typename T>
        result<pointer<T>> single_alloc() {
            auto mem = alloc_as_memory(size_of<T>(),align_of<T>());
            if (!mem) return {mem.err()};
            return {static_cast<T*>(mem.value().pointer.get())};
        }
    }

    using mem::alloc;
    using mem::alloc_as_memory;
    using mem::free;

    using mem::valloc;
    using mem::valloc_as_memory;
    using mem::vfree;

    using mem::realloc;
    using mem::realloc_as_memory;

    using mem::single_alloc;
}
#endif //OMNIX_PLATFORM_ALLOC_H
