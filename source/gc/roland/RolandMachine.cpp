/*
 *
 *  * PROJECT:     Roland OODB
 *  * LICENSE:     GPL - See COPYING in the top level directory
 *  * PROGRAMMER:  Maltsev Daniil <brickexberiment@lenta.ru>
 *
 */
#include "RolandMachine.hpp"
#include <cstdlib>

MemoryChunk::MemoryChunk()
{
    this->data = (Object*)malloc(16000);
}
MemoryChunk::~MemoryChunk()
{
    delete this->data;
}
