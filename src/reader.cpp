#include "reader.h"

#include <QString>
#include <QFile>
#include <QtGui>

SExpr::SExpr(SExprType t)
{
    type = t;
    integer = 0;
    floatpoint = 0;
    string = "";
}

enum ReaderState
{
    STATE_INITIAL,
    STATE_INTEGER,
    STATE_STRING,
    STATE_STRING_ESCAPED,
    STATE_FLOAT,
};

void error(QString message)
{
    QMessageBox::warning(NULL,QString("Internal error"), message);
}

void readSExpr(const QString &fileName)
{
    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)){ // Standard Qt way to open files.
        QMessageBox::warning(NULL,QString("S-Expression reader error"),
                             QString("Can't open file\"%1\".\nPlease try read it again").arg(fileName));
        return;
    }
    char c;
    ReaderState state = STATE_INITIAL;
    SExpr *result = new SExpr(LIST);
    SExpr *current = 0;
    QList <SExpr *> stack;
    SExpr *parent = result;
    QString intBuf;
    while(file.getChar(&c)){
        switch(state){
        case STATE_INITIAL:
            switch(c){
            case ' ': case '\t': case '\n':
                break;
            case '(':
            {
                stack.append(parent);
                SExpr *newParent = new SExpr(LIST);
                parent->list.append(newParent);
                parent = newParent;
                current = 0;
                break;
            }
            case ')':
                parent = stack.takeLast();
                current = 0;
                break;
            case '0': case '1': case '2': case '3': case '4':
            case '5': case '6': case '7': case '8': case '9':
                current = new SExpr(INTEGER);
                parent->list.append(current);
                state = STATE_INTEGER;
                intBuf = "";
                intBuf.append(c);
                break;
            case '"':
                current = new SExpr(INTEGER);
                parent->list.append(current);
                state = STATE_STRING;
                current->string = "";
                break;
            default:
                error(QString("STATE_INITIAL, unexpected char %1").arg(c));
            }
            break;
        case STATE_INTEGER:
            switch(c){
            case '0': case '1': case '2': case '3': case '4':
            case '5': case '6': case '7': case '8': case '9':
                intBuf.append(c);
                break;
            case ')':
                file.ungetChar(c);
                current->integer = intBuf.toInt();
                current->type = INTEGER;
                state = STATE_INITIAL;
                break;
            case ' ': case '\t': case '\n':
                current->integer = intBuf.toInt();
                current->type = INTEGER;
                state = STATE_INITIAL;
                break;
            default:
                error(QString("STATE_INTEGER, unexpected char %1").arg(c));
            }
            break;
        case STATE_STRING:
            switch(c){
            case '\'':
                state = STATE_STRING_ESCAPED;
                break;
            case '"':
                state = STATE_INITIAL;
                break;
            default:
                current->string.append(c);
                break;
            }
            break;
        case STATE_STRING_ESCAPED:
            current->string.append(c);
            break;
        default:
            error("Shouldn't get here");

        }
    }
    file.close();
}

Reader::Reader()
{
}
