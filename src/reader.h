#ifndef READER_H
#define READER_H

#include <QString>
#include <QList>

enum SExprType
{
    LIST,
    INTEGER,
    STRING,
    FLOAT
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

void readSExpr(const QString &fileName);

class Reader
{
public:
    Reader();
};

#endif // READER_H
