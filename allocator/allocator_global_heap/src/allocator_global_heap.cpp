#include <not_implemented.h>
#include "../include/allocator_global_heap.h"

allocator_global_heap::allocator_global_heap() = default;

[[nodiscard]] void *allocator_global_heap::do_allocate_sm(
    size_t size)
{
    std::lock_guard <std::mutex> lock(this->mutex_);
    if (size == 0) return nullptr;
    void* ptr = ::operator new(size); // возврашает void* указатель на блок память ращмером size
    return ptr;
}

void allocator_global_heap::do_deallocate_sm(
    void *at)
{
    if (at == nullptr) return;
    std::lock_guard <std::mutex> lock(this->mutex_);
    ::operator delete(at);
}

allocator_global_heap::~allocator_global_heap() = default;

allocator_global_heap::allocator_global_heap(const allocator_global_heap &other) :
    allocator_dbg_helper(other),
    smart_mem_resource(other)
{
}

allocator_global_heap &allocator_global_heap::operator=(const allocator_global_heap &other)
{
    if (&other != this) {
        allocator_dbg_helper::operator=(other);
        smart_mem_resource::operator=(other);
    }
    return *this;
}

bool allocator_global_heap::do_is_equal(const std::pmr::memory_resource &other) const noexcept
{
    auto p = dynamic_cast<const allocator_global_heap*>(&other); // пытается привести к этому типу
    return p != nullptr;
}

allocator_global_heap::allocator_global_heap(allocator_global_heap &&other) noexcept :
    allocator_dbg_helper(std::move(other)),
    smart_mem_resource(std::move(other))
{
}

allocator_global_heap &allocator_global_heap::operator=(allocator_global_heap &&other) noexcept
{
    if (&other != this) {
        allocator_dbg_helper::operator=(std::move(other));
        smart_mem_resource::operator=(std::move(other));
    }
    return *this;
}
