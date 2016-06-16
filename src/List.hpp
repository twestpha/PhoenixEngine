#include <stdio.h>
#pragma once

template <class T>
class List {
public:
    List<T>(){
        memory = new T*[1];
        max = 1;
        used = 0;
    }

    ~List<T>(){
        for(int i; i < max; i++){
            delete memory[i];
            memory[i] = NULL;
        }

        memory = NULL;
    }

    int Used(){
        return used;
    }

    void Add(T element){
        if(used + 1 > max){
            max *= 2;
            T** newMemory = new T*[max];

            for(int i; i < used; i++){
                newMemory[i] = memory[i];
            }

            memory = newMemory;
        }

        memory[used] = new T(element);

        used++;
    }

    void Remove(int index){
        T* endElement = memory[used];
        memory[index] = endElement;
        memory[used] = NULL;

        used--;
    }

    T* At(int index){
        return memory[index];
    }

    T* operator[](int index){
        return memory[index];
    }

private:
    T **memory;
    unsigned max, used;
};
