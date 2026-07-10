#include <omnix/platform/memory/memory.h>
#include <omnix/platform/memory/alloc.h>
#include <sys/mman.h>
//
// Created by cakilgan on 7/10/26.
//

ox::result<ox::memory> ox::mem::malloc(bytes size, bytes alignment) {
    OX_ASSERT(size != bytes(0));
    OX_ASSERT(alignment != bytes(0));
    if (size == bytes(0) || alignment == bytes(0)) return err::memory_size_is_zero;

    if (alignment == no_alignment) {
        if (const auto pointer = ::malloc(size.ct))
            return memory{pointer,size};
        return err::not_enough_memory;
    }

    if (const auto pointer = ::aligned_alloc(alignment.ct,size.ct))
        return memory{pointer,size};
    return err::not_enough_memory;
}

ox::result_t ox::mem::free(memory &mem, bytes alignment){
    OX_ASSERT(mem.pointer != nullptr);
    if (!mem.pointer) return err::already_freed;
    if (mem.size == bytes(0)) return err::memory_size_is_zero;
    if (alignment != no_alignment) {
        free_aligned_sized(mem.pointer,alignment.ct,mem.size.ct);
    }else {
        free_sized(mem.pointer,mem.size.ct);
    }
    mem.pointer = nullptr;
    mem.size = bytes(0);
    return ok;
}


ox::result<ox::memory> ox::mem::vmalloc(bytes size) {
    OX_ASSERT(size != bytes(0));
    if (size == bytes(0)) return err::memory_size_is_zero;

    void* ptr = ::mmap(nullptr, size.ct,
           PROT_READ | PROT_WRITE,
           MAP_PRIVATE | MAP_ANONYMOUS | MAP_NORESERVE,
           -1, 0);
    if (ptr == MAP_FAILED) {
        return err::not_enough_memory;
    }
    return memory{ptr,size};
}

ox::result_t       ox::mem::vfree(memory& o) {
    OX_ASSERT(o.pointer != nullptr);
    if (!o.pointer) return err::already_freed;
    if (o.size == bytes(0)) return err::memory_size_is_zero;

    ::munmap(o.pointer,o.size.ct);
    o.pointer = nullptr;
    o.size = bytes(0);
    return ok;
}
