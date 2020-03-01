#ifndef MYHIGHLIGHTER_H
#define MYHIGHLIGHTER_H

#include <QSyntaxHighlighter>
#include <QTextCharFormat>
#include <QRegularExpression>
#include <memory>

#include "bloomfilter.h"

class MyHighlighter : public QSyntaxHighlighter
{
public:
    MyHighlighter(QTextDocument *parent = nullptr);
    ~MyHighlighter();

    // judge key whether exists in bloom filter or not.
    bool isKeyExisted(QString key);

    void switchCpp();
    void switchJava();
    void switchPython();

protected:
    // highlight the word on TextEditor.
    void highlightBlock(const QString &text) override;
    // highliogh comment
    void setCommentLine(const QString &text);

private:
    QTextCharFormat myClassFormat;
    QRegularExpression *rule;
    
    // my Bloom Filter member
    BloomFilter *BF;
};

#endif // MYHIGHLIGHTER_H
