#ifndef SYMBOL_H
#define SYMBOL_H

#include <stdint.h>

typedef uint64_t long64;

// Basic type so it's lowercase
class symbol {
public:
    symbol();
    symbol(const char* string);
    static int char_to_symbol_table[];
    static char symbol_to_char_table[];
    bool Valid();
    void Print();

    bool operator=(const symbol& other);
    bool operator==(const symbol& other);
private:
    long64 data;
};

#endif // SYMBOL_H
