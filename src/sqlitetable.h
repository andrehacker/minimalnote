#ifndef SQLITETABLE_H
#define SQLITETABLE_H

namespace sqliteWrapper {

class SqliteTable
{
public:
    SqliteTable(char **result, int numberRows, int numberCols);
    ~SqliteTable();

    const char* getField(int row, int column);
    const char* getColumnName(int column);
    const int numberRows();
    const int numberCols();

private:
    SqliteTable& operator=(const SqliteTable&);    // disallow copy
    SqliteTable(const SqliteTable&);    // disallow copy

    char **result_;
    int numberRows_;
    int numberCols_;
    int currentRow_;
};

}

#endif // SQLITETABLE_H
