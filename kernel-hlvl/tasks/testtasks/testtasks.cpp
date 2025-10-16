#include <tasks/testtasks/testtasks.hpp>

int main_prog1() {
	while (true) {
		asm volatile("hlt");
	}
}

int main_prog2() {
	while (true) {
		asm volatile("hlt");
	}
}
