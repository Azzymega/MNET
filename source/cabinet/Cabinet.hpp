#pragma once
#include "../Defines.hpp"
#include <vector>

enum CabinetFlags : WORD {
    NotFirstCabinet  = 0x0001,
    NotLastCabinet = 0x0002,
    HasReservedFields = 0x0004
};

enum CabinetFileAttributes : WORD {
    ReadOnly = 0x01,
    Hidden = 0x02,
    System = 0x03,
    Modified = 0x20,
    ExecuteAfterExtraction = 0x40,
    NameIsUTF = 0x80
};

struct CabinetFileHeader {
    BYTE Signature[4]; // MSCF signature
    DWORD Reserved1;
    DWORD CabinetSize;
    DWORD Reserverd2;
    DWORD CabinetFileEntryOffset;
    DWORD Reserved3;
    BYTE MinorVersion;
    BYTE MajorVersion;
    WORD FoldersNumber;
    WORD FilesNumber;
    CabinetFlags Flags;
    WORD SetID;
    WORD CabinetID;
};

struct CabinetFolder {
    DWORD CabinetDataOffset;
    WORD CabinetDataBlocksCount;
    WORD CompressionType;
};

struct CabinetFile {
    DWORD CabinetFileSize;
    DWORD CabinetFolderOffset;
    WORD IndexInCabinetFolder;
    WORD Date;
    WORD Time;
    CabinetFileAttributes Attributes;
    STRING Name;
};

struct CabinetFileData {
    DWORD Checksum;
    WORD CompressedSize;
    WORD UncompressedSize;
    std::vector<BYTE> Data;
};