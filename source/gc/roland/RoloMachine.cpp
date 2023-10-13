/*
 *
 *  * PROJECT:     Rolo OODB
 *  * LICENSE:     GPL - See COPYING in the top level directory
 *  * PROGRAMMER:  Maltsev Daniil <brickexberiment@lenta.ru>
 *
 */
#include "RoloMachine.hpp"
#include <cstdlib>

MemoryChunk::MemoryChunk() {
  this->data = malloc(16000);
  this->AllocatedSize = 0;
}
MemoryChunk::~MemoryChunk() { free(data); }

Pointer::Pointer() { this->ReferencesCount = 1; }

Pointer::~Pointer() { delete this->Value; }

TypeSystemController *TypeSystemController::Resolve(TypeDefinition *Object) {
  this->Definitions.push_back(*Object);
  return nullptr;
}

HeapController::HeapController() { this->chunks.push_back(MemoryChunk()); }

HeapController *HeapController::Resolve(TypeDefinition *Object) {
  struct Object value{};
  value.type = Object;
  value.value = (char*)&chunks.back().data + chunks.back().AllocatedSize;
  chunks.back().AllocatedSize+=(Object->mainData.size);
  return nullptr;
}

HeapController *HeapController::Resolve(Object *Object) {
  return nullptr; // дописать
}

void Object::Interact(HeapController *Object) {
  Object->Resolve(this);
}
