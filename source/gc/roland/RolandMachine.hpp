/*
 *
 *  * PROJECT:     Roland OODB
 *  * LICENSE:     GPL - See COPYING in the top level directory
 *  * PROGRAMMER:  Maltsev Daniil <brickexberiment@lenta.ru>
 *
 */

#pragma once
#include "RolandBase.hpp"
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
  ttype
};

struct Metadata {
  u8 id;
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
  MetadataDefinition metadata;
  MethodsDefinition methods;
  // TypeDefinition *superClass;
};

struct Object {
  TypeDefinition type;
  void *value;
};

struct MemoryChunk {
  Object *data; // 16 kb
  MemoryChunk();
  ~MemoryChunk();
};

struct HeapController {
  std::vector<MemoryChunk> chunks;
};

struct Memory {
  HeapController controller;
};

struct Allocator {
  Memory memory;
};

struct Roland {};