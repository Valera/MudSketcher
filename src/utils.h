#ifndef UTILS_H
#define UTILS_H

inline int roundBy(double value, int roundStep)
{
    return roundStep * (int(value + roundStep / 2.0) / roundStep);
}

class QColor;
QColor qColorFromHex(const char *hexString);

#endif // UTILS_H
