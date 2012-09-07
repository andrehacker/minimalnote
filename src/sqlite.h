#ifndef SQLITE_H
#define SQLITE_H

#include <string>
#include <memory>
#include "sqlite3.h"
#include "sqlitetable.h"
#include "sqlitequery.h"

namespace sqliteWrapper {

class Sqlite
{
public:
    Sqlite();
    ~Sqlite();
    const bool openExisting(const std::string &fileName);
    const bool openOrCreate(const std::string &fileName);
    const bool close();
    const bool isOpen();
    const int execDML(const std::string &sql);
    std::unique_ptr<SqliteQuery> execQuery(const std::string &sql);
    std::unique_ptr<SqliteTable> getTable(const std::string &sql);
    long long int getLastInsertId();

private:
    Sqlite& operator=(const Sqlite&);    // disallow copy
    Sqlite(const Sqlite&);    // disallow copy

    sqlite3 *db_;
    bool open_;
};

}

#endif // SQLITE_H
