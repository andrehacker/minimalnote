#include <QDebug>
#include "sqlitequery.h"

namespace sqliteWrapper {

SqliteQuery::SqliteQuery(sqlite3_stmt *preparedStatement, bool eof, sqlite3 *db)
    : preparedStatement_(preparedStatement),
      db_ (db),
      eof_(eof) {
    cols_ = sqlite3_column_count(preparedStatement_);
}


SqliteQuery::~SqliteQuery() {
    sqlite3_finalize(preparedStatement_);
}

const std::string SqliteQuery::getStringField(int fieldIndex, const std::string &nullValue) {
    if (fieldIndex < 0) {
        return nullValue;
    }
    if (getFieldDataType(fieldIndex) == SQLITE_NULL) {
        return nullValue;
    } else {
        return std::string( reinterpret_cast<const char*>(
                    sqlite3_column_text(preparedStatement_, fieldIndex)
                    ));
    }
}

const std::string SqliteQuery::getStringField(const std::string &fieldName, const std::string &nullValue)
{
    int fieldIndex = getFieldIndexByName(fieldName);
    return getStringField(fieldIndex, nullValue);
}

int SqliteQuery::getIntField(int fieldIndex, const int nullValue) {
    if (fieldIndex < 0) {
        return nullValue;
    }
    if (getFieldDataType(fieldIndex) == SQLITE_NULL) {
        return nullValue;
    } else {
        return sqlite3_column_int(preparedStatement_, fieldIndex);
    }
}

int SqliteQuery::getIntField(const std::string &fieldName, const int nullValue)
{
    int fieldIndex = getFieldIndexByName(fieldName);
    return getIntField(fieldIndex, nullValue);
}

bool SqliteQuery::eof() {
    return eof_;
}

void SqliteQuery::nextRow() {

    int ret = sqlite3_step(preparedStatement_);

    if (ret == SQLITE_DONE) {
        eof_ = true;
    } else if (ret == SQLITE_ROW) {
        // more rows, nothing to do
    } else {
        // Unknown error occured!
        sqlite3_finalize(preparedStatement_);
        preparedStatement_ = 0;
        const char* temp = sqlite3_errmsg(db_);
        qDebug() << "ERROR SqliteQuery::nextRow: " << temp;
    }
}

int SqliteQuery::getFieldIndexByName(const std::string &name)
{
    for (int index = 0; index < cols_; index++) {
        const char* temp = sqlite3_column_name(preparedStatement_, index);
        if (name.compare(temp) == 0) {
            return index;
        }
    }
    qDebug() << "ERROR SqliteQuery: Field " << name.c_str() << " not found";
    return -1;
}

int SqliteQuery::getFieldDataType(int col) {
    if (col < 0 || col > cols_ -1) {
       return -1;
    }

    return sqlite3_column_type(preparedStatement_, col);
}

}
