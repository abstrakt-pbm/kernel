#include "start.hpp"

#include <initstage/start_initstage.hpp>
#include <kl-transformation/start_transformation.hpp>
#include <kernel-hlvl/start_kernel.hpp>

#include <kl-launch/ctxswitch.hpp>

void start() {
	start_initstage();
	start_transformation();
	switcher->makeCTXSwitching(start_kernel);
}
