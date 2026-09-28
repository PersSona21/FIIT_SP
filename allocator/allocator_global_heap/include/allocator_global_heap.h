#ifndef MATH_PRACTICE_AND_OPERATING_SYSTEMS_ALLOCATOR_ALLOCATOR_GLOBAL_HEAP_H
#define MATH_PRACTICE_AND_OPERATING_SYSTEMS_ALLOCATOR_ALLOCATOR_GLOBAL_HEAP_H

#include <allocator_dbg_helper.h>
#include <pp_allocator.h>
#include <mutex>

class allocator_global_heap final:
    private allocator_dbg_helper,
    public smart_mem_resource
{

private:

    static constexpr const size_t size_t_size = sizeof(size_t);

public:
    
    explicit allocator_global_heap(); // конструктор
    
    ~allocator_global_heap() override; // деструктор
    
    allocator_global_heap(
        allocator_global_heap const &other); // конструктор копированием
    
    allocator_global_heap &operator=(
        allocator_global_heap const &other); // оператор присваивания копированием b = a
    
    allocator_global_heap(
        allocator_global_heap &&other) noexcept; // конструктор move (забираем ресурсы)
    
    allocator_global_heap &operator=(
        allocator_global_heap &&other) noexcept; // оператор присваивания перемещением a = std::move(b);

private:
    
    [[nodiscard]] void *do_allocate_sm( // предупреждение если игнорировать возвращённое
        size_t size) override; // аллокатор памяти
    
    void do_deallocate_sm(
        void *at) override; // освобождение памяти после аллокации (по адресу)

    // const - не изменяем обьект, говорит одинаковы ли ресурсы памяти
    bool do_is_equal(const std::pmr::memory_resource& other) const noexcept override;

    std::mutex mutex_;
};

#endif //MATH_PRACTICE_AND_OPERATING_SYSTEMS_ALLOCATOR_ALLOCATOR_GLOBAL_HEAP_H