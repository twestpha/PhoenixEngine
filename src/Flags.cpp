#include <stdio.h>

#include "Flags.hpp"

Flags::Flags(){
    data = 0;
}

void Flags::SetIndex(int index, bool value){
    if(value){
        data = data | (1 << index);
    } else {
        data = data & !(1 << index);
    }
}

bool Flags::GetIndex(int index){
    return (data >> index) & 1;
}

bool Flags::HasError(){
    return data != 0;
}
