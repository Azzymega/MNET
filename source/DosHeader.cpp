#include "DosHeader.hpp"
#include "Loader.hpp"

void Assembly::Interact(Loader *Object) {
  Object->Resolve(this);
}
