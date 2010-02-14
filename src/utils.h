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

#ifndef UTILS_H
#define UTILS_H

inline int roundBy(double value, int roundStep)
// returns nearest integer to value integer number, divided by roundStep.
{
    int sgn = (value > 0 ? 1 : -1); // For correct rounding of negative values.
    return roundStep * (int(value + sgn * roundStep / 2.0) / roundStep);
}

class QColor;
// Return QColor from string of form "#RRGGBB"
QColor qColorFromHex(const char *hexString);

class QString;
// if original string is empty, return nil for reading as Common Lisp NIL object.
// if not empty, add \" to begin and end, escapes some symblols.
QString toLispString(QString original);

#endif // UTILS_H
