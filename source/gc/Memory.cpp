#include "Memory.hpp"

Reference::Reference(struct Pointer *Pointer) {
    this->Pointer = Pointer;
}

Reference::~Reference() {
    this->Pointer->LinkCounter--;
}
