#ifndef SYMBOL_H
#define SYMBOL_H

// Basic type so it's lowercase
class symbol {
public:
    symbol();
    symbol(const char* string);
    static int char_to_symbol_table[];
    static char symbol_to_char_table[];
    bool Valid();
    

    bool operator==(const symbol& other);
private:
    unsigned long data;
};

#endif // SYMBOL_H
