/*
 *
 *  * PROJECT:     Roland OODB
 *  * LICENSE:     GPL - See COPYING in the top level directory
 *  * PROGRAMMER:  Maltsev Daniil <brickexberiment@lenta.ru>
 * 
 */

#pragma once
#include <cstdint>
#include <fstream>
#include <string>
#include <vector>

using u2 = uint16_t;
using u4 = uint32_t;
using u1 = uint8_t;
using u8 = uint64_t;
using s1 = char;
using string = std::string;

template <class T> class ILoadInteraction {
  virtual void Interact(T *Object) = 0;
};

template <class T, class J> class ILoadConflict {
  virtual T Resolve(J Object) = 0;
};
