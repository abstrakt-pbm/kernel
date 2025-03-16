#include "acpi.hpp"

ACPI::ACPI( Address rsdp_address ) {
    this->rsdp = reinterpret_cast<RootSystemDescriptionPointer*>( rsdp_address );
     
}