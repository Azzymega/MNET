#pragma once
#include "Defines.hpp"
#include <vector>

struct DOSHeader {
  WORD magic; // 0x4D5A
  WORD garbage[29];
  WORD peStart;
};

struct ImageDataDirectory {
  DWORD VirtualAddress;
  DWORD Size;
};

struct PEOptionalHeader {
  WORD Magic;              // FIXED 0x10B
  BYTE MajorLinkerVersion; // FIXED 6
  BYTE MinorLinkerVersion; // FIXED 0
  DWORD SizeOfCode;
  DWORD SizeOfInitializedData;
  DWORD SizeOfUninitializedData;
  DWORD AddressOfEntryPoint;
  DWORD BaseOfCode; // FIXED 0x0040 FOR EXE AND 0x20 FOR DLL
  DWORD BaseOfData;
  DWORD ImageBase;                  // FIXED 0x40
  DWORD SectionAlignment;           // FIXED 0x20
  DWORD FileAlignment;              // FIXED 0x2 or 0x1
  WORD MajorOperatingSystemVersion; // FIXED 4
  WORD MinorOperatingSystemVersion; // FIXED 0
  WORD MajorImageVersion;           // FIXED 0
  WORD MinorImageVersion;           // FIXED 0
  WORD MajorSubsystemVersion;       // FIXED 4
  WORD MinorSubsystemVersion;       // FIXED 0
  DWORD Win32VersionValue;          // FIXED 0
  DWORD SizeOfImage;
  DWORD SizeOfHeaders;
  DWORD CheckSum;                 // FIXED 0
  WORD Subsystem;                 // FIXED 0x3 OR 0x2
  WORD DllCharacteristics;        // FIXED 0
  DWORD SizeOfStackReserve;       // FIXED 0x10
  DWORD SizeOfStackCommit;        // FIXED 0x10
  DWORD SizeOfHeapReserve;        // FIXED 0x10
  DWORD SizeOfHeapCommit;         // FIXED 0x10
  DWORD LoaderFlags;              // FIXED 0
  DWORD NumberOfRvaAndSizes;      // FIXED 0x10
  ImageDataDirectory ExportTable; // FIXED 0 // ТУТ ВОЗМОЖНО БАГ!!!
  ImageDataDirectory ImportTable;
  ImageDataDirectory ResourceTable;       // FIXED 0
  ImageDataDirectory ExceptionTable;      // FIXED 0
  ImageDataDirectory CertificateTable;    // FIXED 0
  ImageDataDirectory BaseRelocationTable; // MAYBE UNUSED
  ImageDataDirectory Debug;               // FIXED 0
  ImageDataDirectory Copyright;           // FIXED 0
  ImageDataDirectory GlobalPtr;           // FIXED 0
  ImageDataDirectory TlsTable;            // FIXED 0
  ImageDataDirectory LoadConfigTable;     // FIXED 0
  ImageDataDirectory BoundImport;         // FIXED 0
  ImageDataDirectory ImportAddressTable;
  ImageDataDirectory DelayImportDescriptor; // FIXED 0
  ImageDataDirectory CLIHeader;
  ImageDataDirectory Reserver; // FIXED 0
};

enum FileHeaders : WORD { IsDLL = 0x2000, IsCILEXE = 0 };

enum Characteristics : DWORD {
  Executable = 0x00000020,
  InitializedData = 0x00000040,
  UninitializedData = 0x00000080,
  ExecutableCode = 0x20000000,
  Readable = 0x40000000,
  Writeable = 0x80000000,
};

struct StreamHeader {
  DWORD Offset;
  DWORD Size;
  STRING Name;
};

struct MetadataRoot {
  DWORD Signature;
  WORD MajorVersion;
  WORD MinorVersion;
  DWORD Reserved;
  DWORD VersionLength;
  STRING VERSION; // VersionLength
  WORD Flags;
  WORD Streams;
  std::vector<StreamHeader> StreamHeaders;
};

struct ImageSectionHeader {
  BYTE Name[IMAGE_NAME];
  union {
    DWORD PhysicalAddress;
    DWORD VirtualSize;
  };
  DWORD VirtualAddress;
  DWORD SizeOfRawData;
  DWORD PointerToRawData;
  DWORD PointerToRelocations;
  DWORD PointerToLinenumbers; // FIXED 0
  WORD NumberOfRelocations;
  WORD NumberOfLinenumbers; // FIXED 0
  Characteristics SectionCharacteristics;
};

struct VTable {
  DWORD VirtualAddress;
  WORD Size;
  WORD Type;
};

struct CLIHeader {
  DWORD HeaderSize;
  WORD MajorRuntimeVersion;
  WORD MinorRuntimeVersion;
  DWORDLONG MetaData;
  DWORD Flags;
  DWORDLONG Resources;
  DWORDLONG StrongNameSignature;
  DWORDLONG CodeManagerTable; // FIXED 0
  VTable VTableFixups;
  DWORDLONG ExportAddressTableJumps; // FIXED 0
  DWORDLONG MangedNativeHeader;      // FIXED 0
};

struct ImportAddressTable {
  DWORD ImportLookupTable;
  DWORD DateTimeStamp;  // FIXED 0
  DWORD ForwarderChain; // FIXED 0
  DWORD Name;
  DWORD ImportAddressTable;
  BYTE ZEROS[20];
};

struct PEHeader {
  WORD Architecture; // FIXED 0x14C
  WORD NumberOfSections;
  DWORD TimeDateStamp;
  DWORD PointerToSymbolTable; // FIXED 0
  DWORD NumberOfSymbols;      // FIXED 0
  WORD SizeOfOptionalHeader;
  FileHeaders Characteristics; // DLL FLAG 0x2000 OR EXE FLAG 0
};

struct PEBase {
  DWORD Signature; // 0x5045
  PEHeader FileHeader;
  PEOptionalHeader OptionalHeader;
};

struct Loader;

struct Assembly : public ILoadInteraction<Loader> {
  std::string AssemblyLocation;
  DOSHeader Header;
  PEBase Base;
  void Interact(Loader *Object) override;
};