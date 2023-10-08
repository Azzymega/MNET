#include "../source/Loader.hpp"
#include <iostream>

int main() {
  Loader ld;
  Assembly as;
  as.AssemblyLocation = "test.dll";
  ld.Resolve(&as);

// доделать. сдвиг на metadataroot = 206
  
  return 0;
}
