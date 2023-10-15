#include "../source/Loader.hpp"
#include <iostream>

int main() {
  Loader ld;
  Assembly as;
  as.AssemblyLocation = "jsl.dll";
  ld.Resolve(&as); 
  return 0;
}
