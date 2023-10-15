#pragma once
#include <cstdint>
#include <fstream>
#include <string>
#include <vector>
#include <iostream>
#define IMAGE_ENTRIES 16
#define IMAGE_NAME 8

// M$ STYLE
using WORD = uint16_t;
using DWORD = uint32_t;
using BYTE = uint8_t;
using QWORD = uint64_t;
using CHAR = char;
using STRING = std::string;

template <class T> class ILoadInteraction {
  virtual void Interact(T *Object) = 0;
};

template <class T, class J> class ILoadConflict {
  virtual T Resolve(J Object) = 0;
};
