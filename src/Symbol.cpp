#include "Symbol.hpp"
#include "Assert.hpp"
#include <stdio.h>

#define MAX_SYMBOL_LENGTH 10
#define BITS_PER_CHARACTER 6
#define INVALID_CHARACTER -1
#define INVALID_SYMBOL unsigned(-1)

int symbol::char_to_symbol_table[] = {
    // 0
    INVALID_CHARACTER, // NUL
    INVALID_CHARACTER, // SOH
    INVALID_CHARACTER, // STX
    INVALID_CHARACTER, // ETX
    INVALID_CHARACTER, // EOT
    INVALID_CHARACTER, // ENQ
    INVALID_CHARACTER, // ACK
    INVALID_CHARACTER, // BEL
    INVALID_CHARACTER, // BS
    INVALID_CHARACTER, // TAB
    INVALID_CHARACTER, // LF
    INVALID_CHARACTER, // VT
    INVALID_CHARACTER, // FF
    INVALID_CHARACTER, // CR
    INVALID_CHARACTER, // SO
    INVALID_CHARACTER, // SI
    // 16
    INVALID_CHARACTER,
    INVALID_CHARACTER,
    INVALID_CHARACTER,
    INVALID_CHARACTER,
    INVALID_CHARACTER,
    INVALID_CHARACTER,
    INVALID_CHARACTER,
    INVALID_CHARACTER,
    INVALID_CHARACTER,
    INVALID_CHARACTER,
    INVALID_CHARACTER,
    INVALID_CHARACTER,
    INVALID_CHARACTER,
    INVALID_CHARACTER,
    INVALID_CHARACTER,
    INVALID_CHARACTER,
    // 32
    INVALID_CHARACTER,
    INVALID_CHARACTER,
    INVALID_CHARACTER,
    INVALID_CHARACTER,
    INVALID_CHARACTER,
    INVALID_CHARACTER,
    INVALID_CHARACTER,
    INVALID_CHARACTER,
    INVALID_CHARACTER,
    INVALID_CHARACTER,
    INVALID_CHARACTER,
    INVALID_CHARACTER,
    INVALID_CHARACTER,
    INVALID_CHARACTER,
    INVALID_CHARACTER,
    INVALID_CHARACTER,
    // 48
    0, // '0'
    1, // '1'
    2, // '2'
    3, // '3'
    4, // '4'
    5, // '5'
    6, // '6'
    7, // '7'
    8, // '8'
    9, // '9'
    INVALID_CHARACTER, // :
    INVALID_CHARACTER, // ;
    INVALID_CHARACTER, // <
    INVALID_CHARACTER, // =
    INVALID_CHARACTER, // >
    INVALID_CHARACTER, // ?
    // 64
    INVALID_CHARACTER, // @
    10, // 'A'
    11, // 'B'
    12, // 'C'
    13, // 'D'
    14, // 'E'
    15, // 'F'
    16, // 'G'
    17, // 'H'
    18, // 'I'
    19, // 'J'
    20, // 'K'
    21, // 'L'
    22, // 'M'
    23, // 'N'
    24, // 'O'
    // 80
    25, // 'P'
    26, // 'Q'
    27, // 'R'
    28, // 'S'
    29, // 'T'
    30, // 'U'
    31, // 'V'
    32, // 'W'
    33, // 'X'
    34, // 'Y'
    35, // 'Z'
    INVALID_CHARACTER, // [
    INVALID_CHARACTER, // Backslash
    INVALID_CHARACTER, // ]
    INVALID_CHARACTER, // ^
    36, // _
    // 96
    INVALID_CHARACTER, // `
    10, // 'A'
    11, // 'B'
    12, // 'C'
    13, // 'D'
    14, // 'E'
    15, // 'F'
    16, // 'G'
    17, // 'H'
    18, // 'I'
    19, // 'J'
    20, // 'K'
    21, // 'L'
    22, // 'M'
    23, // 'N'
    24, // 'O'
    // 112
    25, // 'P'
    26, // 'Q'
    27, // 'R'
    28, // 'S'
    29, // 'T'
    30, // 'U'
    31, // 'V'
    32, // 'W'
    33, // 'X'
    34, // 'Y'
    35, // 'Z'
    INVALID_CHARACTER, // {
    INVALID_CHARACTER, // |
    INVALID_CHARACTER, // }
    INVALID_CHARACTER, // ~
    INVALID_CHARACTER // None
};

char symbol::symbol_to_char_table[] = {
    '0',
    '1',
    '2',
    '3',
    '4',
    '5',
    '6',
    '7',
    '8',
    '9',
    'A',
    'B',
    'C',
    'D',
    'E',
    'F',
    'G',
    'H',
    'I',
    'J',
    'K',
    'L',
    'M',
    'N',
    'O',
    'P',
    'Q',
    'R',
    'S',
    'T',
    'U',
    'V',
    'W',
    'X',
    'Y',
    'Z',
    '_'
};

symbol::symbol(){
    data = INVALID_SYMBOL;
}

symbol::symbol(const char* string){
    data = INVALID_SYMBOL;
    // 37 is the special ENDMSG character, unless the string is ten chars long already
    for(int i(0); string[i] != NULL && i < MAX_SYMBOL_LENGTH; ++i){
        int symbolCharacter = char_to_symbol_table[string[i]];

        if(symbolCharacter == INVALID_CHARACTER){
            Assert_(false, "Invalid character in symbol constructor.");
            data = INVALID_SYMBOL;
            return;
        }

        data = data & (symbolCharacter << (i * BITS_PER_CHARACTER));

        // printf("Character %c -> %d -> %c\n", string[i], symbolCharacter, symbol_to_char_table[symbolCharacter]);
    }
}

bool symbol::Valid(){
    return data != INVALID_SYMBOL;
}

bool symbol::operator==(const symbol& other){
    return data == other.data;
}
