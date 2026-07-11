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

        result<memory> malloc(bytes size,bytes alignment = default_alignment);
        result_t free(memory& mem,bytes alignment = no_alignment);

        result<memory> vmalloc(bytes size);
        result_t vfree(memory& mem);

        template<typename T>
        result<pointer<T>> single_malloc() {
            auto mem = malloc(size_of<T>(),align_of<T>());
            if (!mem) return {mem.err()};
            return {static_cast<T*>(mem.value().pointer.get())};
        }
    }

    using mem::malloc;
    using mem::free;

    using mem::vmalloc;
    using mem::vfree;

    using mem::single_malloc;
}
#endif //OMNIX_PLATFORM_ALLOC_H
