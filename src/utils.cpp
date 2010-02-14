/*
    MudSketcher, program for building LispMud zones.
    Copyright (C) 2009  Valeriy Fedotov

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

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

QColor qColorFromHex(const char *hexString)
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

QString toLispString(QString original)
{
    if(original.isEmpty())
        return QString("nil");
    else
        return QString("\"%1\"").arg(original);
}
