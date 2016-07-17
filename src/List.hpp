#include "Assert.hpp"

#pragma once

template <class T>
class List {
public:
    List<T>(){
        memory = new T*[1]; // TODO Use allocator
        max = 1;
        used = 0;
    }

    ~List<T>(){
        for(int i; i < max; i++){
            free(memory[i]); // use allocator deallocate
            memory[i] = NULL;
        }

        delete [] memory;
        memory = NULL;
    }

    int Used(){
        return used;
    }

    void Add(T element){
        if(used + 1 > max){
            max *= 2;
            T** newMemory = new T*[max]; // TODO use allocator

            for(int i = 0; i < used; i++){
                newMemory[i] = memory[i];
            }

            memory = newMemory;
        }

        memory[used++] = new T(element);

    }

    void Remove(int index){
        T* endElement = memory[used - 1];
        memory[index] = endElement;
        memory[used--] = NULL;
    }

    T At(int index){
        _Assert(index >= 0 && index < used, "Index is out of range");
        return *memory[index];
    }

    void At(T element, int index){
        _Assert(index >= 0 && index < used, "Index is out of range");
        memory[index] = (T*) &element;
    }

    T operator[](int index){
        _Assert(index >= 0 && index < used, "Index is out of range");
        return *memory[index];
    }

private:
    T **memory;
    unsigned max, used;
};
