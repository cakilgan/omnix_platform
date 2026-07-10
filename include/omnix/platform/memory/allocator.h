//
// Created by cakilgan on 7/10/26.
//

#ifndef OMNIX_PLATFORM_ALLOCATOR_H
#define OMNIX_PLATFORM_ALLOCATOR_H
#include <utility>

#include "omnix/platform/result.h"

namespace ox {
    struct allocator {
        virtual ~allocator() = default;
        virtual result<memory> allocate(bytes size,bytes alignment) = 0;
        virtual result_t deallocate(memory ptr) = 0;
        virtual result<memory> reallocate(memory ptr,bytes new_size,bytes alignment) {
            return results::err::unsupported;
        }
    };
    struct region_allocator : allocator {
    protected:
        memory region;

    public:
        explicit region_allocator(memory region)
            : region(std::move(region)) {}
    };
}
#endif //OMNIX_PLATFORM_ALLOCATOR_H
