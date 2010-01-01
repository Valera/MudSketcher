#include "utils.h"

#include <QColor>

int charToHex(char c)
{
    Q_ASSERT(isxdigit(c));
    if(c <= '9'){
        return c - '0';
    }else{
        return 10 + toupper(c) - 'A';
    }
}


// Return QColor from string of form "#RRGGBB"
QColor qColorFromHex(char *hexString)
{
    Q_ASSERT(hexString);
    Q_ASSERT(strlen(hexString) == 7);
    Q_ASSERT(hexString[0]=='#');
    int r, g, b;
    r = charToHex(hexString[1]) * 16 + charToHex(hexString[2]);
    g = charToHex(hexString[3]) * 16 + charToHex(hexString[4]);
    b = charToHex(hexString[5]) * 16 + charToHex(hexString[6]);
    return QColor(r, g, b);
}
