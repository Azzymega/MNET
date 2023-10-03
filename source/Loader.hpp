#pragma once
#include "Defines.hpp"
#include "DosHeader.hpp"

struct AssemblyStream;

struct BytecodeBuffer : ILoadConflict<BytecodeBuffer *, AssemblyStream *>,
                        ILoadConflict<BYTE, BYTE>,
                        ILoadConflict<WORD, WORD>,
                        ILoadConflict<DWORD, DWORD> {
  std::vector<BYTE> Buffer;
  DWORD BufferCounter;
  BytecodeBuffer *Resolve(AssemblyStream *Object) override;
  unsigned char Resolve(unsigned char Object) override;
  unsigned int Resolve(unsigned int Object) override;
  unsigned short Resolve(unsigned short Object) override;
};

struct AssemblyBuffer {
  Assembly *Assembly;
};

struct AssemblyStream : public ILoadConflict<AssemblyStream *, Assembly *> {
  std::ifstream LoaderStream;
  AssemblyStream *Resolve(Assembly *Object) override;
};

struct Loader : public ILoadConflict<Loader *, Assembly *>,
                ILoadInteraction<BytecodeBuffer>,
                ILoadInteraction<AssemblyStream>,
                ILoadConflict<Loader *, DOSHeader *>,
                ILoadConflict<Loader *, PEBase *>,
                ILoadConflict<Loader *, PEHeader *>,
                ILoadConflict<Loader *, PEOptionalHeader *>,
                ILoadConflict<Loader *, ImageDataDirectory *> {
  BytecodeBuffer Buffer;
  AssemblyBuffer ABuffer;
  AssemblyStream Stream;

public:
  Loader *Resolve(Assembly *Object) override;

private:
  void Interact(BytecodeBuffer *Object) override;
  void Interact(AssemblyStream *Object) override;
  Loader *Resolve(DOSHeader *Object) override;
  Loader *Resolve(PEBase *Object) override;
  Loader *Resolve(PEHeader *Object) override;
  Loader *Resolve(PEOptionalHeader *Object) override;
  Loader *Resolve(ImageDataDirectory *Object) override;
};