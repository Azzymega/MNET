#include "Loader.hpp"

Loader *Loader::Resolve(Assembly *Object) {
  this->ABuffer.Assembly = Object;
  Interact(&this->Stream);
  Interact(&this->Buffer);
  Resolve(&Object->Header);
  Resolve(&Object->Base);
  return nullptr;
}

void Loader::Interact(BytecodeBuffer *Object) {
  Object->Resolve(&this->Stream);
}

void Loader::Interact(AssemblyStream *Object) {
  Object->Resolve(this->ABuffer.Assembly);
}

Loader *Loader::Resolve(DOSHeader *Object) {
  Object->magic = this->Buffer.Resolve(WORD());
  for (auto &&value : Object->garbage) {
    value = this->Buffer.Resolve(WORD());
  }
  Object->peStart = this->Buffer.Resolve(WORD());
  this->Buffer.BufferCounter = Object->peStart;
  return nullptr;
}

Loader *Loader::Resolve(PEBase *Object) {
  Object->Signature = this->Buffer.Resolve(DWORD());
  Resolve(&Object->FileHeader);
  Resolve(&Object->OptionalHeader);
  return nullptr;
}

Loader *Loader::Resolve(PEHeader *Object) {
  Object->Architecture = this->Buffer.Resolve(WORD());
  Object->NumberOfSections = this->Buffer.Resolve(WORD());
  Object->TimeDateStamp = this->Buffer.Resolve(DWORD());
  Object->PointerToSymbolTable = this->Buffer.Resolve(DWORD());
  Object->NumberOfSymbols = this->Buffer.Resolve(DWORD());
  Object->SizeOfOptionalHeader = this->Buffer.Resolve(WORD());
  Object->Characteristics = (FileHeaders)this->Buffer.Resolve(WORD());
  return nullptr;
}

Loader *Loader::Resolve(PEOptionalHeader *Object) { // пофиксить баг
  Object->Magic = this->Buffer.Resolve(WORD());
  Object->MajorLinkerVersion = this->Buffer.Resolve(BYTE());
  Object->MinorLinkerVersion = this->Buffer.Resolve(BYTE());
  Object->SizeOfCode = this->Buffer.Resolve(DWORD());
  Object->SizeOfInitializedData = this->Buffer.Resolve(DWORD());
  Object->SizeOfUninitializedData = this->Buffer.Resolve(DWORD());
  Object->AddressOfEntryPoint = this->Buffer.Resolve(DWORD());
  Object->BaseOfCode = this->Buffer.Resolve(DWORD());
  Object->BaseOfData = this->Buffer.Resolve(DWORD());
  Object->ImageBase = this->Buffer.Resolve(DWORD());
  Object->SectionAlignment = this->Buffer.Resolve(DWORD());
  Object->FileAlignment = this->Buffer.Resolve(DWORD());
  Object->MajorOperatingSystemVersion = this->Buffer.Resolve(WORD());
  Object->MinorOperatingSystemVersion = this->Buffer.Resolve(WORD());
  Object->MajorImageVersion = this->Buffer.Resolve(WORD());
  Object->MinorImageVersion = this->Buffer.Resolve(WORD());
  Object->MajorSubsystemVersion = this->Buffer.Resolve(WORD());
  Object->MinorSubsystemVersion = this->Buffer.Resolve(WORD());
  Object->Win32VersionValue = this->Buffer.Resolve(DWORD());
  Object->SizeOfImage = this->Buffer.Resolve(DWORD());
  Object->SizeOfHeaders = this->Buffer.Resolve(DWORD());
  Object->CheckSum = this->Buffer.Resolve(DWORD());
  Object->Subsystem = this->Buffer.Resolve(WORD());
  Object->DllCharacteristics = this->Buffer.Resolve(WORD());
  Object->SizeOfStackReserve = this->Buffer.Resolve(DWORD());
  Object->SizeOfStackCommit = this->Buffer.Resolve(DWORD());
  Object->SizeOfHeapReserve = this->Buffer.Resolve(DWORD());
  Object->SizeOfHeapCommit = this->Buffer.Resolve(DWORD());
  Object->LoaderFlags = this->Buffer.Resolve(DWORD());
  Object->NumberOfRvaAndSizes = this->Buffer.Resolve(DWORD());
  Resolve(&Object->ExportTable);
  Resolve(&Object->ImportTable);
  Resolve(&Object->ResourceTable);
  Resolve(&Object->ExceptionTable);
  Resolve(&Object->CertificateTable);
  Resolve(&Object->BaseRelocationTable);
  Resolve(&Object->Debug);
  Resolve(&Object->Copyright);
  Resolve(&Object->GlobalPtr);
  Resolve(&Object->TlsTable);
  Resolve(&Object->LoadConfigTable);
  Resolve(&Object->BoundImport);
  Resolve(&Object->ImportAddressTable);
  Resolve(&Object->DelayImportDescriptor);
  Resolve(&Object->CLIHeader);
  Resolve(&Object->Reserver);
  return nullptr;
}

Loader *Loader::Resolve(ImageDataDirectory *Object) {
  Object->VirtualAddress = this->Buffer.Resolve(DWORD());
  Object->Size = this->Buffer.Resolve(DWORD());
  return nullptr;
}

AssemblyStream *AssemblyStream::Resolve(Assembly *Object) {
  this->LoaderStream.open(Object->AssemblyLocation, std::ios::binary);
  if (!LoaderStream.is_open()) {
    throw "FAIL";
  }
  return nullptr;
}

BytecodeBuffer *BytecodeBuffer::Resolve(AssemblyStream *Object) {
  this->BufferCounter = 0;
  while (!Object->LoaderStream.eof()) {
    uint8_t data;
    Object->LoaderStream >> data >> std::noskipws;
    this->Buffer.push_back(data);
  }
  return nullptr;
}

unsigned char BytecodeBuffer::Resolve(unsigned char Object) {
  BYTE temp[1];
  temp[0] = Buffer[BufferCounter];
  BufferCounter += sizeof(BYTE);
  return temp[0];
}

unsigned int BytecodeBuffer::Resolve(unsigned int Object) {
  BYTE temp[4];
  temp[0] = Buffer[BufferCounter];
  temp[1] = Buffer[BufferCounter + 1];
  temp[2] = Buffer[BufferCounter + 2];
  temp[3] = Buffer[BufferCounter + 3];
  BufferCounter += sizeof(DWORD);
  return temp[0] + temp[1] + temp[2] + temp[3];
}

unsigned short BytecodeBuffer::Resolve(unsigned short Object) {
  BYTE temp[2];
  temp[0] = Buffer[BufferCounter];
  temp[1] = Buffer[BufferCounter + 1];
  BufferCounter += sizeof(WORD);
  return temp[0] + temp[1];
}
