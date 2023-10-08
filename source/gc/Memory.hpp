#pragma once
#include "../Defines.hpp"

struct Pointer {
  DWORD LinkCounter;
  void *Information;
};

struct Reference {
public:
  Pointer *Pointer;
  Reference(struct Pointer *Pointer);
  ~Reference();
};

struct Heap {
  std::vector<Pointer> Pointers;
};

struct Memory {};