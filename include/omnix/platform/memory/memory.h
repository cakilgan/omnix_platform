//
// Created by cakilgan on 7/10/26.
//

#ifndef OMNIX_PLATFORM_MEMORY_H
#define OMNIX_PLATFORM_MEMORY_H
#include "../byte.h"
#include "pointer.h"
namespace ox {
    namespace mem {
        struct memory {
            vptr pointer;
            bytes size;
        };

        template<typename T>
        pointer<T> as(memory& mem) {
            return static_cast<T*>(mem.pointer.get());
        }

        constexpr memory slice(const memory& mem,const bytes offset, bytes length){
            if (offset > mem.size)
                return {};

            if (offset + length > mem.size)
                length = mem.size - offset;

            return {
                static_cast<byte*>(mem.pointer.get()) + offset,
                length
            };
        }
        constexpr memory slice(const memory& mem, const bytes offset){
            return slice(mem,offset, mem.size - offset);
        }
    }

    using mem::memory;
    using mem::as;
    using mem::slice;
}
#include "alloc.h"
#include "allocator.h"
#endif //OMNIX_PLATFORM_MEMORY_H
