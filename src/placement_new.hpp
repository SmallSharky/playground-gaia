
#include <new>

inline void* operator new(std::size_t, void* ptr) noexcept { return ptr; }