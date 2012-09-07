#include "sqlite.h"
#include "sqlitetable.h"

namespace sqliteWrapper {

/*
This implementation uses the convenience function sqlite_get_table.
It stores the whole result in a table of strings on the heap (fast).
*/
/*SqliteTable::SqliteTable()
{
    result_ = 0;
    numberRows_ = 0;
    numberCols_ = 0;
    currentRow_ = 0;
}*/

SqliteTable::SqliteTable(char **result, int numberRows, int numberCols)
{
    result_ = result;
    numberRows_ = numberRows;
    numberCols_ = numberCols;
    currentRow_ = 0;
}

SqliteTable::~SqliteTable()
{
    // We always have to free up the table (on heap)
    sqlite3_free_table(result_);
}

const char* SqliteTable::getField(int row, int column)
{
    return result_[((row+1)*numberCols_)+column];
}

const char* SqliteTable::getColumnName(int column)
{
    return result_[column];
}

const int SqliteTable::numberRows() {
    return numberRows_;
}

const int SqliteTable::numberCols() {
    return numberCols_;
}

}
