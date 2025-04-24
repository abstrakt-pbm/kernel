#include "pcie.hpp"

void PCI::init() {
    this->base_segment = nullptr;
}


void PCI::append_pci_domain( PCIDomain* new_domain ) {
    if ( new_domain == nullptr ) {
        return;
    } 

    if (base_segment == nullptr) {
        base_segment = new_domain;
        base_segment->scan();
        return;
    }
    
    PCIDomain* current_domain;
    while ( current_domain->next != nullptr && current_domain->next->domain_id < new_domain->domain_id) {
        current_domain = current_domain->next;
    }

    if ( current_domain->next == nullptr) {
        current_domain->next = new_domain;
    } else {
        new_domain->next = current_domain->next;
        current_domain->next = new_domain;
    }

    current_domain->scan();
    return;

}

//PCI_DOMAIN////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

PCIDomain::PCIDomain( uint64_t domain_id, void* ecam_start, uint16_t start_bus_number, uint16_t end_bus_number) : domain_id(domain_id), ecam_start(ecam_start), start_bus_number(start_bus_number), end_bus_number(end_bus_number) {
    this->next = nullptr;
    //this->root_complexes = nullptr;
    this->host_bridges_list_head = nullptr;
    this->buses_list_head = nullptr;
}

void PCIDomain::scan() {
    for ( uint64_t i = start_bus_number ; i < end_bus_number ; i++ ) {
        Address bus_address = reinterpret_cast<Address>(ecam_start) + (i << 20);
        volatile uint32_t* bus_ptr = reinterpret_cast<volatile uint32_t*>(bus_address);
        if ( *bus_ptr != 0xFFFFFFFF ) {
            PCIBus* bus = new PCIBus(
                i,
                reinterpret_cast<void*>(bus_address)
            );

            if (bus == nullptr) {
                return;
            }

            append_bus_in_list( bus );
            
        }
    }
}

void PCIDomain::append_bus_in_list( PCIBus* bus_to_insert ) {
    if ( bus_to_insert == nullptr ) {
        return;
    }

    if ( buses_list_head == nullptr ) {
        buses_list_head = bus_to_insert;
        return;
    }

    PCIBus* current_bus = buses_list_head;
    while ( current_bus->next != nullptr & current_bus->next->bus_id < bus_to_insert->bus_id ) {
        current_bus = current_bus->next;
    }

    if ( current_bus->next == nullptr ) {
        current_bus->next = bus_to_insert;
    } else {
        bus_to_insert->next - current_bus->next;
        current_bus->next = bus_to_insert;
    }
    return;

}

//PCI_BUS////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
PCIBus::PCIBus( uint16_t bus_id, void* ecam_base ) : bus_id(bus_id), ecam_base(ecam_base) {

}