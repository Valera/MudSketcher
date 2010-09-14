#include "reader.h"

#include <QString>
#include <QFile>
#include <QtGui>
#include <QtDebug>

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
    STATE_SYMBOL
};

void error(QString message)
{
    QMessageBox::warning(NULL,QString("Internal error"), message);
}

SExpr *getf(SExpr *list, const char *keyword)
{
    Q_ASSERT(list->type == LIST);
    for(int i = 0; i < list->list.length(); i+=2){
        Q_ASSERT(list->list[i]->type == SYMBOL);
        if (list->list[i]->string.compare(keyword, Qt::CaseInsensitive) == 0){
            return list->list[i+1];
        }
    }
    return 0;
}

SExpr *getfOfType(SExpr *list, const char *keyword, SExprType type)
{
    SExpr *result = getf(list, keyword);
    Q_ASSERT(result->type == type);
    return result;
}

SExpr *readSExpr(const QString &fileName)
{
    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)){ // Standard Qt way to open files.
        QMessageBox::warning(NULL,QString("S-Expression reader error"),
                             QString("Can't open file\"%1\".\nPlease try read it again").arg(fileName));
        return 0;
    }
    char c;
    ReaderState state = STATE_INITIAL;
    SExpr *result = new SExpr(LIST);
    SExpr *current = 0;
    QList <SExpr *> stack;
    SExpr *parent = result;
    QString intBuf;
    QString symBuf;
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
                current = new SExpr(STRING);
                parent->list.append(current);
                state = STATE_STRING;
                break;
            default:
                current = new SExpr(SYMBOL);
                parent->list.append(current);
                state = STATE_SYMBOL;
                current->string.append(c);;
                break;
            }
            break;
        case STATE_SYMBOL:
            switch(c){
                case ')':
                    current->string = current->string.toUpper();
                    state = STATE_INITIAL;
                    qDebug() << 'symb ' << current->string;
                    parent = stack.takeLast();
                    current = 0;
                    break;
                case ' ': case '\t': case '\n':
                    current->string = current->string.toUpper();
                    state = STATE_INITIAL;
                    qDebug() << 'symb ' << current->string;
                    break;
                default:
                    current->string.append(c);
                    break;
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
                qDebug() << 'str  ' << current->string;
                state = STATE_INITIAL;
                break;
            case ' ': case '\t': case '\n':
                current->integer = intBuf.toInt();
                current->type = INTEGER;
                qDebug() << 'int  ' << current->integer;
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
                qDebug() << 'str  ' << current->string;
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

    return result;
}
