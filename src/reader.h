#ifndef READER_H
#define READER_H

#include <QString>
#include <QList>

enum SExprType
{
    LIST,
    INTEGER,
    STRING,
    FLOAT,
    SYMBOL
};

class SExpr
{
public:
    SExprType type;
    int integer;
    double floatpoint;
    QString string;
    QList <SExpr *> list;

    SExpr(SExprType t);
    ~SExpr();
};

SExpr *getf(SExpr *list, const char *keyword);
SExpr *getfOfType(SExpr *list, const char *keyword, SExprType type);
SExpr *readSExpr(const QString &fileName);

#endif // READER_H
