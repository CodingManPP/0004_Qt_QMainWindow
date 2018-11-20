#include "mysyntaxhighlighter.h"

MySyntaxHighlighter::MySyntaxHighlighter(QTextDocument *parent):
    QSyntaxHighlighter(parent)
{
}
//必须重新实现该函数
void MySyntaxHighlighter::highlightBlock(const QString &text)
{
   QTextCharFormat myFormat;                            //字符格式
   myFormat.setFontWeight(QFont::Bold);
   myFormat.setForeground(Qt::green);
   QString pattern = "\\bchar\\b";                      //要匹配的字符是“char”单词
   QRegExp expression(pattern);                         //创建正则表达式
   int index = text.indexOf(expression);
   while(index >= 0){
       int length = expression.matchedLength();
       setFormat(index,length,myFormat);                //如果匹配成功则设置格式
       index = text.indexOf(expression,index+length);   //继续匹配
   }
}
