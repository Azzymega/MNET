/*
 *
 *  * PROJECT:     Rolo OODB
 *  * LICENSE:     GPL - See COPYING in the top level directory
 *  * PROGRAMMER:  Maltsev Daniil <brickexberiment@lenta.ru>
 *
 */

#pragma once
#include "RoloBase.hpp"
#include <vector>

enum Types {
  tbyte,
  tint,
  tshort,
  tlong,
  tdouble,
  tfloat,
  tbool,
  tchar,
  twchar,
  tobject,
};

struct Metadata {
  Types type;
  string name;
  u4 size;
  u4 annotationsCount;
  string *annotations;
};

struct MetadataDefinition {
  u4 metadataCount;
  Metadata *typeMetadata;
};

using MethodsDefinition = MetadataDefinition;

struct TypeDefinition {
  Metadata mainData;
  MetadataDefinition otherMetadata;
  MethodsDefinition methods;
  // TypeDefinition *superClass;
};

struct HeapController;

struct Object : ILoadInteraction<HeapController> {
  u8 id;
  TypeDefinition *type;
  void *value;
  void Interact(HeapController *Object) override;
};

struct MemoryChunk {
  u4 AllocatedSize;
  void *data; // 16 kb
  MemoryChunk();
  ~MemoryChunk();
};

struct Pointer {
  Object *Value;
  u4 ReferencesCount;
  Pointer(Object* Value);
  ~Pointer();
};

struct Reference {
  Pointer *Value;
};

struct HeapController : ILoadConflict<HeapController *, TypeDefinition *>,
                        ILoadConflict<HeapController *, Object *> {
  HeapController();
  std::vector<MemoryChunk> chunks;
  std::vector<Pointer> Pointers;
  HeapController *Resolve(TypeDefinition *Object) override;
  HeapController *Resolve(Object *Object) override;
};

struct TypeSystemController
    : ILoadConflict<TypeSystemController *, TypeDefinition *> {
  std::vector<TypeDefinition> Definitions;
  TypeSystemController *Resolve(TypeDefinition *Object) override;
};

struct Memory {
  TypeSystemController typesController;
  HeapController controller;
};

struct Allocator {
  Memory memory;
};

struct Roland {};