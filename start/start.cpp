#include <start/start.hpp>

#include <initstage/start_initstage.hpp>
#include <kernel-hlvl/start_kernel.hpp>
#include <ctxswitch/ctxswitch.hpp>
void start() {
	start_initstage();
	switcher->makeCTXSwitching(&start_kernel);
}
