#include <koa/allocatable.hpp>
#include <koa/koa.hpp>
namespace KOA {

void* Allocatable::operator new( size_t size ) {
    return koa.allocate(size);
}

void Allocatable::operator delete(void* ptr, size_t size ) noexcept {
	koa.free(ptr, size);
}

} // KOA namespace
