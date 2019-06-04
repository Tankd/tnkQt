#ifndef CSVPARSER_H
#define CSVPARSER_H

#include "baseparser.h"

class QFile;
class QTextCodec;

namespace tnk {
namespace parser {


class  CsvParser : public BaseParser
{
public:
    CsvParser();

    // baseParser interface
public:
    void open(const QString &path);
    void close();
    RowData nextRow();



private:
      QFile *m_inFile = nullptr;
      QTextCodec *m_codec = nullptr;

      // BaseParser interface
public:
      void selectTable(const QString& tableName = QString(), int headerLine = 0);
};

}}
#endif // CSVPARSER_H
