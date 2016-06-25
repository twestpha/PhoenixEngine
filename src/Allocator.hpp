#include <stdlib.h>

#include "Assert.hpp"

#pragma once

class Allocator {
public:
    static void* Allocate(unsigned int sizeInBytes){
        return (void*) malloc(sizeInBytes);
    }

    static void Deallocate(void* memory){
        _Assert(memory, "Deallocating null memory.");
        free(memory);
    }
};
