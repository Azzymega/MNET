#pragma once
#include "Defines.hpp"
#include <bitset>
#include <functional>
#include <vector>

enum TableTypes {
  TModule = 0x00,
  TTypeReference = 0x01,
  TTypeDef = 0x02,
  TField = 0x04,
  TMethodDef = 0x06,
  TParameter = 0x08,
  TInterfaceImplementation = 0x09,
  TMemberReference = 0x0A,
  TConstant = 0x0B,
  TCustomAttribute = 0x0C,
  TFieldMarshal = 0x0D,
  TDeclarativeSecurity = 0x0E,
  TClassLayout = 0x0F,
  TFieldLayout = 0x10,
  TStandAloneSignature = 0x11,
  TEventMap = 0x12,
  TEvent = 0x14,
  TPropertyMap = 0x15,
  TProperty = 0x17,
  TMethodSemantics = 0x18,
  TMethodImplementation = 0x19,
  TModuleReference = 0x1A,
  TTypeSpecification = 0x1B,
  TImplementationMap = 0x1C,
  TFieldRVA = 0x1D,
  TAssembly = 0x20,
  TAssemblyProcessor = 0x21,
  TAssemblyOS = 0x22,
  TAssemblyReference = 0x23,
  TAssemblyReferenceProcessor = 0x24,
  TAssemblyReferenceOS = 0x25,
  TFile = 0x26,
  TExportedType = 0x27,
  TManifestResource = 0x28,
  TNestedClass = 0x29,
  TGenericParameter = 0x2A,
  TMethodSpecification = 0x2B,
  TGenericParameterConstraint = 0x2C
};

enum MethodSemanticsAttribute : WORD {
  msSetter = 0x0001,
  msGetter = 0x0002,
  msOther = 0x0004,
  msAddOn = 0x0008,
  msRemoveOn = 0x0010,
  msFire = 0x0020
};

enum PropertyAttribute : WORD {
  prSpecialName = 0x0200,
  prReservedMask = 0xf400,
  prRTSpecialName = 0x0400,
  prHasDefault = 0x1000,
  prUnused = 0xe9ff
};

enum EventAttribute : WORD {
  evSpecialName = 0x0200,
  evReservedMask = 0x0400,
  evRTSpecialName = 0x0400
};

enum ParamterAttribute : WORD {
  pdIn = 0x0001,
  pdOut = 0x0002,
  pdOptional = 0x0010,
  pdReservedMask = 0xf000,
  pdHasDefault = 0x1000,
  pdHasFieldMarshal = 0x2000,
  pdUnused = 0xcfe0
};

enum ImplementationFlags : WORD {
  miCodeTypeMask = 0x0003,
  miIL = 0x0000,
  miNative = 0x0001,
  miOPTIL = 0x0002,
  miRuntime = 0x0003,
  miManagedMask = 0x0004,
  miUnmanaged = 0x0004,
  miManaged = 0x0000,
  miForwardRef = 0x0010,
  miPreserveSig = 0x0080,
  miInternalCall = 0x1000,
  miSynchronized = 0x0020,
  miNoInlining = 0x0008,
  miMaxMethodImplVal = 0xffff
};

enum MethodAttributes : WORD {
  mdMemberAccessMask = 0x0007,
  mdPrivateScope = 0x0000,
  mdPrivate = 0x0001,
  mdFamANDAssem = 0x0002,
  mdAssem = 0x0003,
  mdFamily = 0x0004,
  mdFamORAssem = 0x0005,
  mdPublic = 0x0006,
  mdStatic = 0x0010,
  mdFinal = 0x0020,
  mdVirtual = 0x0040,
  mdHideBySig = 0x0080,
  mdVtableLayoutMask = 0x0100,
  mdReuseSlot = 0x0000,
  mdNewSlot = 0x0100,
  mdCheckAccessOnOverride = 0x0200,
  mdAbstract = 0x0400,
  mdSpecialName = 0x0800,
  mdPinvokeImpl = 0x2000,
  mdUnmanagedExport = 0x0008,
  mdReservedMask = 0xd000,
  mdRTSpecialName = 0x1000,
  mdHasSecurity = 0x4000,
  mdRequireSecObject = 0x8000
};

enum FieldAttributes : WORD {
  fdFieldAccessMask = 0x0007,
  fdPrivateScope = 0x0000,
  fdPrivate = 0x0001,
  fdFamANDAssem = 0x0002,
  fdAssembly = 0x0003,
  fdFamily = 0x0004,
  fdFamORAssem = 0x0005,
  fdPublic = 0x0006,
  fdStatic = 0x0010,
  fdInitOnly = 0x0020,
  fdLiteral = 0x0040,
  fdNotSerialized = 0x0080,
  fdSpecialName = 0x0200,
  fdPinvokeImpl = 0x2000,
  fdReservedMask = 0x9500,
  fdRTSpecialName = 0x0400,
  fdHasFieldMarshal = 0x1000,
  fdHasDefault = 0x8000,
  fdHasFieldRVA = 0x0100
};

enum TypeAttributes : DWORD {
  tdVisibilityMask = 0x00000007,
  tdNotPublic = 0x00000000,
  tdPublic = 0x00000001,
  tdNestedPublic = 0x00000002,
  tdNestedPrivate = 0x00000003,
  tdNestedFamily = 0x00000004,
  tdNestedAssembly = 0x00000005,
  tdNestedFamANDAssem = 0x00000006,
  tdNestedFamORAssem = 0x00000007,
  tdLayoutMask = 0x00000018,
  tdAutoLayout = 0x00000000,
  tdSequentialLayout = 0x00000008,
  tdExplicitLayout = 0x00000010,
  tdClassSemanticsMask = 0x00000060,
  tdClass = 0x00000000,
  tdInterface = 0x00000020,
  tdAbstract = 0x00000080,
  tdSealed = 0x00000100,
  tdSpecialName = 0x00000400,
  tdImport = 0x00001000,
  tdSerializable = 0x00002000,
  tdStringFormatMask = 0x00030000,
  tdAnsiClass = 0x00000000,
  tdUnicodeClass = 0x00010000,
  tdAutoClass = 0x00020000,
  tdCustomFormatClass = 0x00030000,
  tdCustomFormatMask = 0x00C00000,
  tdBeforeFieldInit = 0x00100000,
  tdForwarder = 0x00200000,
  tdReservedMask = 0x00040800,
  tdRTSpecialName = 0x00000800,
  tdHasSecurity = 0x00040000
};

enum AssemblyFlags : DWORD {
  afPublicKey = 0x0001,
  afPA_None = 0x0000,
  afPA_MSIL = 0x0010,
  afPA_x86 = 0x0020,
  afPA_IA64 = 0x0030,
  afPA_AMD64 = 0x0040,
  afPA_Specified = 0x0080,
  afPA_Mask = 0x0070,
  afPA_FullMask = 0x00F0,
  afPA_Shift = 0x0004,
  afEnableJITcompileTracking = 0x8000,
  afDisableJITcompileOptimizer = 0x4000,
  afRetargetable = 0x0100
};

enum FileTableAttribute : DWORD {
  ffContainsMetaData = 0x0000,
  ffContainsNoMetaData = 0x0001
};

enum GenericParemeterAttribute : WORD {
  gpVarianceMask = 0x0003,
  gpNonVariant = 0x0000,
  gpCovariant = 0x0001,
  gpContravariant = 0x0002,
  gpSpecialConstraintMask = 0x001C,
  gpNoSpecialConstraint = 0x0000,
  gpReferenceTypeConstraint = 0x0004,
  gpNotNullableValueTypeConstraint = 0x0008
};

enum PInvokeMapAttribute : WORD {
  pmNoMangle = 0x0001,
  pmCharSetMask = 0x0006,
  pmCharSetNotSpec = 0x0000,
  pmCharSetAnsi = 0x0002,
  pmCharSetUnicode = 0x0004,
  pmCharSetAuto = 0x0006,
  pmBestFitUseAssem = 0x0000,
  pmBestFitEnabled = 0x0010,
  pmBestFitDisabled = 0x0020,
  pmBestFitMask = 0x0030,
  pmThrowOnUnmappableCharUseAssem = 0x0000,
  pmThrowOnUnmappableCharEnabled = 0x1000,
  pmThrowOnUnmappableCharDisabled = 0x2000,
  pmThrowOnUnmappableCharMask = 0x3000,
  pmSupportsLastError = 0x0040,
  pmCallConvMask = 0x0700,
  pmCallConvWinapi = 0x0100,
  pmCallConvCdecl = 0x0200,
  pmCallConvStdcall = 0x0300,
  pmCallConvThiscall = 0x0400,
  pmCallConvFastcall = 0x0500,
  pmMaxValue = 0xFFFF
};

struct TypeSpecificationTable {
  DWORD Signature;
};

struct TypeReferenceTable {
  DWORD ResolutionScope;
  DWORD TypeName;
  DWORD TypeNamespace;
};

struct TypeDefinitionTable {
  TypeAttributes Flags;
  DWORD Name;
  DWORD Namespace;
  DWORD Extends;
  DWORD FieldList;
  DWORD MethodList;
};

struct StandAloneSignatureTable {
  DWORD Signature;
};

struct PropertyMapTable {
  DWORD Parent;
  DWORD PropertyList;
};

struct PropertyTable {
  PropertyAttribute Flags;
  DWORD Name;
  DWORD Type;
};

struct ParameterTable {
  ParamterAttribute Flags;
  WORD Sequence;
  DWORD Name;
};

struct NestedClassTable {
  DWORD NestedClassType;
  DWORD EnclosingClassType;
};

struct ModuleReferenceTable {
  DWORD Name;
};

struct ModuleTable {
  WORD Generation;
  DWORD Name;
  DWORD MvID;
  DWORD EncID;
  DWORD EncBaseID;
};

struct MemberReferenceTable {
  DWORD Class;
  DWORD Name;
  DWORD Signature;
};

struct MethodSemanticsTable {
  MethodSemanticsAttribute Semantics;
  DWORD Method;
  DWORD Association;
};

struct MethodImplementationTable {
  DWORD Class;
  DWORD MethodBody;
  DWORD MethodDeclaration;
};

struct MethodDefinitionTable {
  DWORD RVA;
  ImplementationFlags ImpelementationFlags;
  MethodAttributes Flags;
  DWORD Name;
  DWORD Signature;
  DWORD ParameterList;
};  

struct MethodReferenceTable {
  DWORD Class;
  DWORD Name;
  DWORD Signature;
};

struct ManifestResourceTable {
  DWORD Offset;
  DWORD Flags;
  DWORD Name;
  DWORD Implementation;
};

struct InterfaceImplementationTable {
  DWORD Class;
  DWORD Interface;
};

struct ImplementationMapTable {
  PInvokeMapAttribute MappingFlags;
  DWORD MemberForwarded;
  DWORD ImportName;
  DWORD ImportScope;
};

struct GenericParameterConstraintTable {
  DWORD Owner;
  DWORD Constraint;
};

struct GenericParameterTable {
  WORD Number;
  GenericParemeterAttribute Flags;
  DWORD Owner;
  DWORD Name;
};

struct FileTable {
  FileTableAttribute Flags;
  DWORD Name;
  DWORD HashValue;
};

struct FieldRVATabel {
  DWORD RVA;
  DWORD Field;
};

struct FieldMarshalTable {
  DWORD Parent;
  DWORD NativeType;
};

struct FieldLayoutTable {
  DWORD Offset;
  DWORD Field;
};

struct FieldTable {
  FieldAttributes Flags;
  DWORD Name;
  DWORD Signature;
};

struct ExportedTypeTable {
  DWORD Flags;
  DWORD TypeDefId;
  DWORD TypeName;
  DWORD TypeNamespace;
};

struct EventMapTable {
  DWORD Parent;
  DWORD EventList;
};

struct EventTable {
  EventAttribute EventFlag;
  DWORD Name;
  DWORD EventType;
};

struct DeclSecurityTable {
  WORD Action;
  DWORD Parent;
  DWORD PermissionSet;
};

struct CustomAttributeTable {
  DWORD Parent;
  DWORD Type;
  DWORD Value;
};

struct ConstantTable {
  BYTE Type;
  DWORD Parent;
  DWORD Value;
};

struct ClassLayoutTable {
  WORD PackingSize;
  DWORD ClassSize;
  DWORD Parent;
};

struct AsemblyRefProcessorTable {
  DWORD Processor;
  DWORD AssemblyRef;
};

struct AssemblyRefOsTable {
  DWORD OSPlatformID;
  DWORD OSMajorVersion;
  DWORD OSMinorVersion;
  DWORD AssemblyRef;
};

struct AssemblyRefTable {
  WORD MajorVersion;
  WORD MinorVersion;
  WORD BuildNumber;
  WORD RevisionNumber;
  DWORD Flags;
  DWORD PublicKeyOrToken;
  DWORD Name;
  DWORD Culture;
  DWORD HashValue;
};

struct AssemblyProcessorTable {
  DWORD Processor;
};

struct AssemblyOSTable {
  DWORD OSPlatformID;
  DWORD OSMajorVersion;
  DWORD OSMinorVersion;
};

struct AssemblyTable {
  DWORD HashAlgorithmId;
  WORD MajorVersion;
  WORD MinorVersion;
  WORD BuildNumber;
  WORD RevisionNumber;
  AssemblyFlags Flags;
  DWORD PublicKey;
  DWORD Name;
  DWORD Culture;
};

struct ValidTables {
  std::bitset<64> Valid;
  std::bitset<64> Sorted;
  std::vector<TableTypes> Types;
  WORD ValidCount;
};

struct MetadataTable {
  TableTypes Type;
  std::vector<TypeDefinitionTable> TypeDefinitionTable;
  std::vector<FieldTable> FieldTable;
  std::vector<MethodDefinitionTable> MethodDefinitionTable;
  std::vector<TypeReferenceTable> TypeReferenceTable;
  std::vector<ModuleTable> ModuleTable;
  std::vector<AssemblyTable> AssemblyTable;
  std::vector<AssemblyOSTable> AssemblyOSTable;
  std::vector<AssemblyProcessorTable> AssemblyProcessorTable;
  std::vector<AssemblyRefTable> AssemblyRefTable;
  std::vector<AssemblyRefOsTable> AssemblyRefOsTable;
  std::vector<AsemblyRefProcessorTable> AsemblyRefProcessorTable;
  std::vector<ClassLayoutTable> ClassLayoutTable;
  std::vector<ConstantTable> ConstantTable;
  std::vector<CustomAttributeTable> CustomAttributeTable;
  std::vector<DeclSecurityTable> DeclSecurityTable;
  std::vector<EventTable> EventTable;
  std::vector<MemberReferenceTable> MemberReferenceTable;
  std::vector<StandAloneSignatureTable> StandAloneSignatureTable;
};

struct MetadataTables {
  TableTypes Buffer;
  WORD RowBuffer;
  std::vector<MetadataTable *> Tables;
};

struct TildaStream {
  DWORD Reserved;
  BYTE MajorVersion;
  BYTE MinorVersion;
  std::bitset<8> HeapSizes;
  BYTE ReservedB;
  ValidTables ValidTables;
  std::vector<DWORD> Rows;
  MetadataTables MetadataTables;
};