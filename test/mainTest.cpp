#include "../source/Loader.hpp"
#include <iostream>
int main(){
    Loader ld;
    Assembly as;
    as.AssemblyLocation = "test.dll";
    ld.Resolve(&as);
    return 0;
}

