#include <ctxswitch/ctxswitch.hpp>
#include <thinlibcxx/hwtypes.hpp>
using namespace thinlibcxx;

class CTXSingleSwitcherAmd64 : public CTXSingleSwitcher {
public:
	void makeCTXSwitching(void (*func)(void)) override;

	Address ctx_pml4;
	Address stack_addr;
};
