//
// Created by cakilgan on 7/10/26.
//

#ifndef OMNIX_PLATFORM_ALLOCATOR_H
#define OMNIX_PLATFORM_ALLOCATOR_H
#include <utility>

#include "omnix/platform/result.h"
#include "memory.h"

namespace ox {
    struct allocator {
        virtual ~allocator() = default;
        virtual result<vptr> allocate(bytes size,bytes alignment) = 0;
        virtual result_t deallocate(vptr ptr) = 0;
        virtual result<vptr> reallocate(vptr ptr,bytes new_size) {
            return results::err::unsupported;
        }
        virtual result<memory> allocate_as_memory(bytes size,bytes alignment) = 0;
        virtual result_t deallocate(memory mem) = 0;
        virtual result<memory> reallocate_as_memory(memory mem,bytes new_size) {
            return results::err::unsupported;
        }
    };

    struct default_allocator {
        static result<vptr> allocate(bytes size,bytes alignment) {
            return alloc(size,alignment);
        }
        static result_t deallocate(vptr ptr) {
            return free(ptr);
        }
        static result<vptr> reallocate(vptr ptr,bytes new_size) {
            return realloc(ptr,new_size);
        }
        static result<memory> allocate_as_memory(bytes size,bytes alignment) {
            return alloc_as_memory(size,alignment);
        }
        static result_t deallocate(memory mem) {
            return free(mem);
        }
        static result<memory> reallocate_as_memory(memory mem,bytes new_size) {
            return realloc_as_memory(mem,new_size);
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
