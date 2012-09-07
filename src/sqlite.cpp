#include <memory>
#include <QDebug>
#include "sqlite.h"
#include "sqlite3.h"
#include "sqlitetable.h"

namespace sqliteWrapper {

Sqlite::Sqlite()
{
    open_ = false;
    db_ = 0;
}

Sqlite::~Sqlite() {
    qDebug() << "Sqlite Destructor";
    if (isOpen()) {
        close();
    }
}

const bool Sqlite::openExisting(const std::string &fileName) {
    qDebug() << "Sqlite::openExisting";
    if (open_) {
        // don't allow to reopen implicitly
        return false;
    }

    if (!sqlite3_open_v2(fileName.c_str(), &db_, SQLITE_OPEN_READWRITE, 0) == SQLITE_OK) {
        open_ = false;
        return false;
    }
    open_ = true;
    return true;
}

const bool Sqlite::openOrCreate(const std::string &fileName) {
    qDebug() << "Sqlite::openOrCreate";
    if (open_) {
        // don't allow to reopen implicitly
        return false;
    }

    if (!sqlite3_open_v2(fileName.c_str(), &db_, SQLITE_OPEN_READWRITE | SQLITE_OPEN_CREATE, 0) == SQLITE_OK) {
        open_ = false;
        return false;
    }
    open_ = true;
    return true;
}

const bool Sqlite::close() {
    if (open_) {
        return (sqlite3_close(db_) == SQLITE_OK);
    }
    return false;
}

const bool Sqlite::isOpen() {
    return open_;
}

const int Sqlite::execDML(const std::string &sql) {

    qDebug() << "Sqlite::execDML: " << sql.c_str();

    char* szError=0;

    if (sqlite3_exec(db_, sql.c_str(), 0, 0, &szError) != SQLITE_OK) {
        return 0;
    }
    return sqlite3_changes(db_);
}

std::unique_ptr<SqliteQuery> Sqlite::execQuery(const std::string &sql) {
    qDebug() << "Sqlite::execQuery: " << sql.c_str();

    // Compile statement
    sqlite3_stmt *preparedStatement;
    const char *unusedTailIgnore=0;
    if (sqlite3_prepare_v2(db_, sql.c_str(), -1, &preparedStatement, &unusedTailIgnore) != SQLITE_OK) {
        const char *error= sqlite3_errmsg(db_);
        qDebug() << "Error executing sql: " << error;
        return std::unique_ptr<SqliteQuery>(); // TODO: Replace 0 with nullptr when available
    }

    // 2) Execute first step
    int ret = sqlite3_step(preparedStatement);
    if (ret == SQLITE_DONE) {
        qDebug() << "Sqlite::execQuery: Query returned no rows";
        // query returned no rows, don't call step again => has Next
        return std::unique_ptr<SqliteQuery>(new SqliteQuery(preparedStatement, false, db_));
    } else if (ret == SQLITE_ROW) {
        qDebug() << "Sqlite::execQuery: Query returned >=1 rows";
        // >=1 row
        return std::unique_ptr<SqliteQuery>(new SqliteQuery(preparedStatement, true, db_));
    } else {
        // any error
        sqlite3_finalize(preparedStatement);
        const char *error= sqlite3_errmsg(db_);
        qDebug() << "Error executing sql: " << error;
        return std::unique_ptr<SqliteQuery>(); // TODO: Replace 0 with nullptr
    }
}

std::unique_ptr<SqliteTable> Sqlite::getTable(const std::string &sql) {
    qDebug() << "Sqlite::getTable: " << sql.c_str();

    char **result;
    int resultRows;
    int resultCols;
    int ret = sqlite3_get_table(db_, sql.c_str(), &result, &resultRows, &resultCols, 0);

    if (ret != SQLITE_OK) {
        return std::unique_ptr<SqliteTable>(); //replace 0 with nullptr when available
    }

    std::unique_ptr<SqliteTable> resultTable(new SqliteTable(result, resultRows, resultCols));
    return resultTable;
}

long long int Sqlite::getLastInsertId() {
    return sqlite3_last_insert_rowid(db_);
}

}
