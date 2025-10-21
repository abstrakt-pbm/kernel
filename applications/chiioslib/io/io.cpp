#include <io/io.hpp>
#include <cstding.hpp>
using namespace CHIIOS;

int putchar(int c) {
	char ch = (char)c;
    long ret;
    asm volatile (
        "syscall"
        : "=a" (ret)                     // возвращаемое значение в rax
        : "a"(1),                         // номер системного вызова: SYS_write
          "D"(1),                         // fd = 1 (stdout)
          "S"(&ch),                       // указатель на символ
          "d"(1)                          // длина = 1
        : "rcx", "r11", "memory"
    );
    return (ret < 0) ? -1 : c;
}

int puts(const char *s) {

}
