#include <stdlib.h>

#include "Assert.hpp"

#ifndef ALLOCATOR_H
#define ALLOCATOR_H

class Allocator {
public:
    static void* Allocate(unsigned int sizeInBytes){
        return (void*) malloc(sizeInBytes);
    }

    static void Deallocate(void* memory){
        Assert_(memory, "Deallocating null memory.");
        free(memory);
    }
};

#endif
