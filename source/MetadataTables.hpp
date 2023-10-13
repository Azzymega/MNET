#pragma once
#include "Defines.hpp"
#include <bitset>
#include <functional>

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

struct TypeSpecificationTable {
  DWORD Signature;
};

struct TypeReferenceTable {
  DWORD ResolutionScope;
  DWORD TypeName;
  DWORD TypeNamespace;
};

struct TypeDefinitionTable {
  DWORD Flags;
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
  WORD Flags;
  DWORD Name;
  DWORD Type;
};

struct ParameterTable {
  WORD Flags;
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

struct Module {
  WORD Generation;
  DWORD Name;
  DWORD MvID;
  DWORD EncID;
  DWORD EncBaseID;
};

struct MethodSemanticsTable {
  WORD Semantics;
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
  WORD ImpelementationFlags;
  WORD Flags;
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
  WORD MappingFlags;
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
  WORD Flags;
  DWORD Owner;
  DWORD Name;
};

struct FileTable {
  DWORD Flags;
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
  WORD Flags;
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
  WORD EventFlag;
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
  DWORD Flags;
  DWORD PublicKey;
  DWORD Name;
  DWORD Culture;
};

struct TildaStream {
  DWORD Reserved;
  BYTE MajorVersion;
  BYTE MinorVersion;
  std::bitset<8> HeapSizes;
  BYTE ReservedB;
  std::bitset<64> Valid;
  std::bitset<64> Sorted;
  std::vector<DWORD> Rows;
};