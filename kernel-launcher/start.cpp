#include "start.hpp"

#include <initstage/start_initstage.hpp>
#include <kernel-hlvl/start_kernel.hpp>
#include <kl-launch/ctxswitch.hpp>

void start() {
	start_initstage();
	switcher->makeCTXSwitching(start_kernel);
}
