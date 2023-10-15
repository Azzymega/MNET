#include "Loader.hpp"
#include <bitset>
#include <corecrt.h>
#include <cwchar>
#include <vector>

Loader *Loader::Resolve(Assembly *Object) {
  this->ABuffer.Assembly = Object;
  Interact(&this->Stream);
  Interact(&this->Buffer);
  Resolve(&Object->Header);
  Resolve(&Object->Base);
  this->Buffer.BufferCounter += 16; // WTF, зачем там эти 16 байт?
  Resolve(&Object->ManagedMetadata);
  Resolve(&Object->MetadataEntryPoint);
  Resolve(&Object->MainStream);
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
  Resolve(&Object->SectionsHeaders);
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

Loader *Loader::Resolve(PEOptionalHeader *Object) {
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

Loader *Loader::Resolve(PESectionsHeaders *Object) {
  Object->SectionsHeaders = std::vector<ImageSectionHeader>(
      this->ABuffer.Assembly->Base.FileHeader.NumberOfSections);
  for (auto &&Section : Object->SectionsHeaders) {
    Resolve(&Section);
  }
  return nullptr;
}

Loader *Loader::Resolve(ImageSectionHeader *Object) {
  for (auto &&Letter : Object->Name) {
    Letter = this->Buffer.Resolve(BYTE());
  }
  Object->VirtualSize = this->Buffer.Resolve(DWORD());
  Object->VirtualAddress = this->Buffer.Resolve(DWORD());
  Object->SizeOfRawData = this->Buffer.Resolve(DWORD());
  Object->PointerToRawData = this->Buffer.Resolve(DWORD());
  Object->PointerToRelocations = this->Buffer.Resolve(DWORD());
  Object->PointerToLinenumbers = this->Buffer.Resolve(DWORD());
  Object->NumberOfRelocations = this->Buffer.Resolve(WORD());
  Object->NumberOfLinenumbers = this->Buffer.Resolve(WORD());
  Object->SectionCharacteristics =
      (Characteristics)this->Buffer.Resolve(DWORD());
  return nullptr;
}

Loader *Loader::Resolve(CLIHeader *Object) {
  Object->HeaderSize = this->Buffer.Resolve(DWORD());
  Object->MajorRuntimeVersion = this->Buffer.Resolve(WORD());
  Object->MinorRuntimeVersion = this->Buffer.Resolve(WORD());
  Resolve(&Object->MetaData);
  Object->Flags = this->Buffer.Resolve(DWORD());
  Object->EntryPointToken = this->Buffer.Resolve(DWORD());
  Resolve(&Object->Resources);
  Resolve(&Object->StrongNameSignature);
  Resolve(&Object->CodeManagerTable);
  Object->VTableFixups.VirtualAddress = this->Buffer.Resolve(DWORD());
  Object->VTableFixups.Size = this->Buffer.Resolve(WORD());
  Object->VTableFixups.Type = this->Buffer.Resolve(WORD());
  Resolve(&Object->ExportAddressTableJumps);
  Resolve(&Object->MangedNativeHeader);
  return nullptr;
}

Loader *Loader::Resolve(CLIMetadata *Object) {
  Resolve(&Object->ITAAble);
  Resolve(&Object->Header);
  return nullptr;
};

Loader *Loader::Resolve(ImportAddressTable *Object) {
  Object->RVA = this->Buffer.Resolve(DWORD());
  Object->ImportEnd = this->Buffer.Resolve(DWORD());
  return nullptr;
}

Loader *Loader::Resolve(MetadataRoot *Object) {
  this->Buffer.BufferCounter -= sizeof(CLIHeader) + sizeof(RVA);
  this->Buffer.BufferCounter +=
      this->ABuffer.Assembly->ManagedMetadata.Header.MetaData.VirtualAddress -=
      this->ABuffer.Assembly->Base.SectionsHeaders.SectionsHeaders[0]
          .VirtualAddress;
  Object->Offset = this->Buffer.BufferCounter;
  Object->Signature = this->Buffer.Resolve(DWORD());
  Object->MajorVersion = this->Buffer.Resolve(WORD());
  Object->MinorVersion = this->Buffer.Resolve(WORD());
  Object->Reserved = this->Buffer.Resolve(DWORD());
  Object->VersionLength = this->Buffer.Resolve(DWORD());
  for (size_t stringLength = 0; stringLength < Object->VersionLength;
       stringLength++) {
    Object->VERSION.push_back(this->Buffer.Resolve(BYTE()));
  }
  Object->Flags = this->Buffer.Resolve(WORD());
  Object->Streams = this->Buffer.Resolve(WORD());
  Object->StreamHeaders = std::vector<StreamHeader>(Object->Streams);
  for (auto &&stream : Object->StreamHeaders) {
    Resolve(&stream);
  }
  return nullptr;
}

Loader *Loader::Resolve(StreamHeader *Object) {
  Object->Offset = this->Buffer.Resolve(DWORD());
  Object->Size = this->Buffer.Resolve(DWORD());
  while (true) {
    char c;
    c = this->Buffer.Resolve(BYTE());
    Object->Name.push_back(c);
    if (c == 0) {
      while (Object->Name.length() % 4 != 0) {
        Object->Name.push_back(this->Buffer.Resolve(BYTE()));
      }
      break;
    }
  }
  return nullptr;
}

Loader *Loader::Resolve(TildaStream *Object) {
  Object->Reserved = this->Buffer.Resolve(DWORD());
  Object->MajorVersion = this->Buffer.Resolve(BYTE());
  Object->MinorVersion = this->Buffer.Resolve(BYTE());
  Object->HeapSizes = this->Buffer.Resolve(BYTE());
  Object->ReservedB = this->Buffer.Resolve(BYTE());
  Resolve(&Object->ValidTables);
  Object->Rows = std::vector<DWORD>(Object->ValidTables.ValidCount);
  for (auto &&row : Object->Rows) {
    row = this->Buffer.Resolve(DWORD());
  }
  Object->MetadataTables.Tables =
      std::vector<MetadataTable *>(Object->ValidTables.ValidCount);
  for (size_t i = 0; i < Object->MetadataTables.Tables.size(); i++) {
    Object->MetadataTables.Tables[i] = new MetadataTable();
    Object->MetadataTables.Buffer = Object->ValidTables.Types.at(i);
    Object->MetadataTables.RowBuffer = Object->Rows.at(i);
    Resolve(Object->MetadataTables.Tables.at(i));
  }
  return nullptr;
}

Loader *Loader::Resolve(ValidTables *Object) {
  Object->Valid = this->Buffer.Resolve(QWORD());
  Object->Sorted = this->Buffer.Resolve(QWORD());
  Object->ValidCount = Object->Valid.count();
  for (size_t x = 0; x < Object->Valid.size(); x++) {
    if (Object->Valid[x]) {
      switch (x) {

      case TModule: {
        Object->Types.push_back(TModule);
        break;
      }
      case TTypeReference: {
        Object->Types.push_back(TTypeReference);
        break;
      }
      case TTypeDef: {
        Object->Types.push_back(TTypeDef);
        break;
      }
      case TField: {
        Object->Types.push_back(TField);
        break;
      }
      case TMethodDef: {
        Object->Types.push_back(TMethodDef);
        break;
      }
      case TParameter: {
        Object->Types.push_back(TParameter);
        break;
      }
      case TInterfaceImplementation: {
        Object->Types.push_back(TInterfaceImplementation);
        break;
      }
      case TMemberReference: {
        Object->Types.push_back(TMemberReference);
        break;
      }
      case TConstant: {
        Object->Types.push_back(TConstant);
        break;
      }
      case TCustomAttribute: {
        Object->Types.push_back(TCustomAttribute);
        break;
      }
      case TFieldMarshal: {
        Object->Types.push_back(TFieldMarshal);
        break;
      }
      case TDeclarativeSecurity: {
        Object->Types.push_back(TDeclarativeSecurity);
        break;
      }
      case TClassLayout: {
        Object->Types.push_back(TClassLayout);
        break;
      }
      case TFieldLayout: {
        Object->Types.push_back(TFieldLayout);
        break;
      }
      case TStandAloneSignature: {
        Object->Types.push_back(TStandAloneSignature);
        break;
      }
      case TEventMap: {
        Object->Types.push_back(TEventMap);
        break;
      }
      case TEvent: {
        Object->Types.push_back(TEvent);
        break;
      }
      case TPropertyMap: {
        Object->Types.push_back(TPropertyMap);
        break;
      }
      case TProperty: {
        Object->Types.push_back(TProperty);
        break;
      }
      case TMethodSemantics: {
        Object->Types.push_back(TMethodSemantics);
        break;
      }
      case TMethodImplementation: {
        Object->Types.push_back(TMethodImplementation);
        break;
      }
      case TModuleReference: {
        Object->Types.push_back(TModuleReference);
        break;
      }
      case TTypeSpecification: {
        Object->Types.push_back(TTypeSpecification);
        break;
      }
      case TImplementationMap: {
        Object->Types.push_back(TImplementationMap);
        break;
      }
      case TFieldRVA: {
        Object->Types.push_back(TFieldRVA);
        break;
      }
      case TAssembly: {
        Object->Types.push_back(TAssembly);
        break;
      }
      case TAssemblyProcessor: {
        Object->Types.push_back(TAssemblyProcessor);
        break;
      }
      case TAssemblyOS: {
        Object->Types.push_back(TAssemblyOS);
        break;
      }
      case TAssemblyReference: {
        Object->Types.push_back(TAssemblyReference);
        break;
      }
      case TAssemblyReferenceProcessor: {
        Object->Types.push_back(TAssemblyReferenceProcessor);
        break;
      }
      case TAssemblyReferenceOS: {
        Object->Types.push_back(TAssemblyReferenceOS);
        break;
      }
      case TFile: {
        Object->Types.push_back(TFile);
        break;
      }
      case TExportedType: {
        Object->Types.push_back(TExportedType);
        break;
      }
      case TManifestResource: {
        Object->Types.push_back(TManifestResource);
        break;
      }
      case TNestedClass: {
        Object->Types.push_back(TNestedClass);
        break;
      }
      case TGenericParameter: {
        Object->Types.push_back(TGenericParameter);
        break;
      }
      case TMethodSpecification: {
        Object->Types.push_back(TMethodSpecification);
        break;
      }
      case TGenericParameterConstraint: {
        Object->Types.push_back(TGenericParameterConstraint);
        break;
      }
      default: {
        Object->ValidCount--;
        break;
      }
      }
    }
  }
  return nullptr;
}

Loader *Loader::Resolve(MetadataTable *Object) {
  switch (this->ABuffer.Assembly->MainStream.MetadataTables.Buffer) {
  case TModule: {
    Object->Type = TModule;
    Object->ModuleTable = std::vector<ModuleTable>(
        this->ABuffer.Assembly->MainStream.MetadataTables.RowBuffer);
    for (auto &&row : Object->ModuleTable) {
      row.Generation = this->Buffer.Resolve(WORD());
      row.Name = this->Buffer.Resolve(WORD());
      row.MvID = this->Buffer.Resolve(WORD());
      row.EncID = this->Buffer.Resolve(WORD());
      row.EncBaseID = this->Buffer.Resolve(WORD());
    }
    break;
  };
  case TTypeReference: {
    Object->Type = TTypeReference;
    Object->TypeReferenceTable = std::vector<TypeReferenceTable>(
        this->ABuffer.Assembly->MainStream.MetadataTables.RowBuffer);
    for (auto &&row : Object->TypeReferenceTable) {
      row.ResolutionScope = this->Buffer.Resolve(WORD());
      row.TypeName = this->Buffer.Resolve(WORD());
      row.TypeNamespace = this->Buffer.Resolve(WORD());
    }
    break;
  };
  case TTypeDef: {
    Object->Type = TTypeDef;
    Object->TypeDefinitionTable = std::vector<TypeDefinitionTable>(
        this->ABuffer.Assembly->MainStream.MetadataTables.RowBuffer);
    for (auto &&row : Object->TypeDefinitionTable) {
      row.Flags = (TypeAttributes)this->Buffer.Resolve(DWORD());
      row.Name = this->Buffer.Resolve(WORD());
      row.Namespace = this->Buffer.Resolve(WORD());
      row.Extends = this->Buffer.Resolve(WORD());
      row.FieldList = this->Buffer.Resolve(WORD());
      row.MethodList = this->Buffer.Resolve(WORD());
    }
    break;
  };
  case TField: {
    Object->Type = TField;
    Object->FieldTable = std::vector<FieldTable>(
        this->ABuffer.Assembly->MainStream.MetadataTables.RowBuffer);
    for (auto &&row : Object->FieldTable) {
      row.Flags = (FieldAttributes)this->Buffer.Resolve(WORD());
      row.Name = this->Buffer.Resolve(WORD());
      row.Signature = this->Buffer.Resolve(WORD());
    }
    break;
  };
  case TMethodDef: {
    Object->Type = TMethodDef;
    Object->MethodDefinitionTable = std::vector<MethodDefinitionTable>(
        this->ABuffer.Assembly->MainStream.MetadataTables.RowBuffer);
    for (auto &&row : Object->MethodDefinitionTable) {
      row.RVA = this->Buffer.Resolve(DWORD());
      row.ImpelementationFlags =
          (ImplementationFlags)this->Buffer.Resolve(WORD());
      row.Flags = (MethodAttributes)this->Buffer.Resolve(WORD());
      row.Name = this->Buffer.Resolve(WORD());
      row.Signature = this->Buffer.Resolve(WORD());
      row.ParameterList = this->Buffer.Resolve(WORD());
    }
    break;
  };
  case TParameter: {
    Object->Type = TParameter;
    break;
  };
  case TInterfaceImplementation: {
    Object->Type = TInterfaceImplementation;
    break;
  };
  case TMemberReference: {
    Object->Type = TMemberReference;
    Object->MemberReferenceTable = std::vector<MemberReferenceTable>(
        this->ABuffer.Assembly->MainStream.MetadataTables.RowBuffer);
    for (auto &&row : Object->MemberReferenceTable) {
      row.Class = this->Buffer.Resolve(WORD());
      row.Name = this->Buffer.Resolve(WORD());
      row.Signature = this->Buffer.Resolve(WORD());
    }
    break;
  };
  case TConstant: {
    Object->Type = TConstant;
    break;
  };
  case TCustomAttribute: {
    Object->Type = TCustomAttribute;
    Object->CustomAttributeTable = std::vector<CustomAttributeTable>(
        this->ABuffer.Assembly->MainStream.MetadataTables.RowBuffer);
    for (auto &&row : Object->CustomAttributeTable) {
      row.Parent = this->Buffer.Resolve(WORD());
      row.Type = this->Buffer.Resolve(WORD());
      row.Value = this->Buffer.Resolve(WORD());
    }
    break;
  };
  case TFieldMarshal: {
    Object->Type = TFieldMarshal;
    break;
  };
  case TDeclarativeSecurity: {
    Object->Type = TDeclarativeSecurity;
    break;
  };
  case TClassLayout: {
    Object->Type = TClassLayout;
    break;
  };
  case TFieldLayout: {
    Object->Type = TFieldLayout;
    break;
  };
  case TStandAloneSignature: {
    Object->Type = TStandAloneSignature;
    Object->StandAloneSignatureTable = std::vector<StandAloneSignatureTable>(
        this->ABuffer.Assembly->MainStream.MetadataTables.RowBuffer);
    for (auto &&row : Object->StandAloneSignatureTable) {
      row.Signature = this->Buffer.Resolve(WORD());
    }
    break;
  };
  case TEventMap: {
    Object->Type = TEventMap;
    break;
  };
  case TEvent: {
    Object->Type = TEvent;
    break;
  };
  case TPropertyMap: {
    Object->Type = TPropertyMap;
    break;
  };
  case TProperty: {
    Object->Type = TProperty;
    break;
  };
  case TMethodSemantics: {
    Object->Type = TMethodSemantics;
    break;
  };
  case TMethodImplementation: {
    Object->Type = TMethodImplementation;
    break;
  };
  case TModuleReference: {
    Object->Type = TModuleReference;
    break;
  };
  case TTypeSpecification: {
    Object->Type = TTypeSpecification;
    break;
  };
  case TImplementationMap: {
    Object->Type = TImplementationMap;
    break;
  };
  case TFieldRVA: {
    Object->Type = TFieldRVA;
    break;
  };
  case TAssembly: {
    Object->Type = TAssembly;
    Object->AssemblyTable = std::vector<AssemblyTable>(
        this->ABuffer.Assembly->MainStream.MetadataTables.RowBuffer);
    for (auto &&row : Object->AssemblyTable) {
      row.HashAlgorithmId = this->Buffer.Resolve(DWORD());
      row.MajorVersion = this->Buffer.Resolve(WORD());
      row.MinorVersion = this->Buffer.Resolve(WORD());
      row.BuildNumber = this->Buffer.Resolve(WORD());
      row.RevisionNumber = this->Buffer.Resolve(WORD());
      row.Flags = (AssemblyFlags)this->Buffer.Resolve(DWORD());
      row.PublicKey = this->Buffer.Resolve(WORD());
      row.Name = this->Buffer.Resolve(WORD());
      row.Culture = this->Buffer.Resolve(WORD());
    }
    break;
  };
  case TAssemblyProcessor: {
    Object->Type = TAssemblyProcessor;
    break;
  };
  case TAssemblyOS: {
    Object->Type = TAssemblyOS;
    break;
  };
  case TAssemblyReference: {
    Object->Type = TAssemblyReference;
    Object->AssemblyRefTable = std::vector<AssemblyRefTable>(
        this->ABuffer.Assembly->MainStream.MetadataTables.RowBuffer);
    for (auto &&row : Object->AssemblyRefTable) {
      row.MajorVersion = this->Buffer.Resolve(WORD());
      row.MinorVersion = this->Buffer.Resolve(WORD());
      row.BuildNumber = this->Buffer.Resolve(WORD());
      row.RevisionNumber = this->Buffer.Resolve(WORD());
      row.Flags = (AssemblyFlags)this->Buffer.Resolve(DWORD());
      row.PublicKeyOrToken = this->Buffer.Resolve(WORD());
      row.Name = this->Buffer.Resolve(WORD());
      row.Culture = this->Buffer.Resolve(WORD());
      row.HashValue = this->Buffer.Resolve(WORD());
    }
    break;
  };
  case TAssemblyReferenceProcessor: {
    Object->Type = TAssemblyReferenceProcessor;
    break;
  };
  case TAssemblyReferenceOS: {
    Object->Type = TAssemblyReferenceOS;
    break;
  };
  case TFile: {
    Object->Type = TFile;
    break;
  };
  case TExportedType: {
    Object->Type = TExportedType;
    break;
  };
  case TManifestResource: {
    Object->Type = TManifestResource;
    break;
  };
  case TNestedClass: {
    Object->Type = TNestedClass;
    break;
  };
  case TGenericParameter: {
    Object->Type = TGenericParameter;
    break;
  };
  case TMethodSpecification: {
    Object->Type = TMethodSpecification;
    break;
  };
  case TGenericParameterConstraint:
    Object->Type = TGenericParameterConstraint;
    break;
  }
  return nullptr;
}

AssemblyStream *AssemblyStream::Resolve(Assembly *Object) {
  this->LoaderStream.open(Object->AssemblyLocation, std::ios::binary);
  if (!LoaderStream.is_open()) {
    std::cout << "Fail";
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
  DWORD Value = 0;
  memcpy(&Value, &temp, 4);
  BufferCounter += sizeof(DWORD);
  return Value;
}

unsigned short BytecodeBuffer::Resolve(unsigned short Object) {
  BYTE temp[2];
  temp[0] = Buffer[BufferCounter];
  temp[1] = Buffer[BufferCounter + 1];
  WORD Value = 0;
  memcpy(&Value, &temp, 2);
  BufferCounter += sizeof(WORD);
  return Value;
}

unsigned long long BytecodeBuffer::Resolve(unsigned long long Object) {
  BYTE temp[8];
  temp[0] = Buffer[BufferCounter];
  temp[1] = Buffer[BufferCounter + 1];
  temp[2] = Buffer[BufferCounter + 2];
  temp[3] = Buffer[BufferCounter + 3];
  temp[4] = Buffer[BufferCounter + 4];
  temp[5] = Buffer[BufferCounter + 5];
  temp[6] = Buffer[BufferCounter + 6];
  temp[7] = Buffer[BufferCounter + 7];
  QWORD Value = 0;
  memcpy(&Value, &temp, 8); // Hackfix!!!
  BufferCounter += sizeof(QWORD);
  return Value;
}
