#include "myhighlight.h"

using namespace std;

MyHighlighter::MyHighlighter(QTextDocument *parent)
    : QSyntaxHighlighter (parent)
{
    // initial highlight rule 
    rule = new QRegularExpression("(\\b)(\\w+)(\\b)");

    // initial highlight format
    myClassFormat.setFontWeight(QFont::Bold);
    myClassFormat.setForeground(Qt::blue);

    BF = new BloomFilter();
}

MyHighlighter::~MyHighlighter()
{
    
}

bool MyHighlighter::isKeyExisted(QString key)
{
    return BF->KeyExistInBitFilter((key.toStdString()));
}

void MyHighlighter::highlightBlock(const QString &text)
{
    auto i = rule->globalMatch(text);
    while (i.hasNext())
    {
        auto match = i.next();
        auto begin = match.capturedStart();
        auto end = match.capturedLength();
        if (isKeyExisted(text.mid(begin, end)))
        {
            setFormat(begin, end, myClassFormat);
        }
    }

    setCommentLine(text);
}

void MyHighlighter::setCommentLine(const QString &text)
{
    QTextCharFormat multiLineCommentFormat;
    multiLineCommentFormat.setForeground(Qt::red);

    QRegularExpression startExpression("/\\*");
    QRegularExpression endExpression("\\*/");

    setCurrentBlockState(0);

    int startIndex = 0;
    if (previousBlockState() != 1)
        startIndex = text.indexOf(startExpression);

    while (startIndex >= 0) {
    QRegularExpressionMatch endMatch;
    int endIndex = text.indexOf(endExpression, startIndex, &endMatch);
    int commentLength;
    if (endIndex == -1) {
        setCurrentBlockState(1);
        commentLength = text.length() - startIndex;
    } else {
        commentLength = endIndex - startIndex
                        + endMatch.capturedLength();
    }
    setFormat(startIndex, commentLength, multiLineCommentFormat);
    startIndex = text.indexOf(startExpression,
                                startIndex + commentLength);
    }
}

void MyHighlighter::switchCpp()
{
    BF->import_CPP_KeyWords();
}

void MyHighlighter::switchJava()
{
    BF->import_Java_keyWords();
}

void MyHighlighter::switchPython()
{
    BF->import_Python_keyWords();
}