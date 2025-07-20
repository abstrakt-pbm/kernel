#include "virtsystems_init.hpp"
#include <initstage/utility/memory_morph.hpp>
#include <HWRC/virtualsystems/virtualsystems.hpp>
#include <HWRC/arch/amd64/vmemsubsystem/vmemsubsystem.hpp>

void initialize_virtsystems() {
    VirtualSubsystemsControl *vsc = reinterpret_cast<VirtualSubsystemsControl*>( kernel_vaddr_to_paddr_initstage( reinterpret_cast<Address>( &virtual_subsystems_control )) );
    vsc->vmemcontrol = &amd64_vmem_subsystem;
}