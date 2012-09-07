#include <QDebug>
#include "databaseconnection.h"

namespace note { namespace model {

DatabaseConnection::DatabaseConnection()
    : sqlite_(std::unique_ptr<Sqlite>(new Sqlite())),
      kDatabaseFileName_("notes.db") {
}

bool DatabaseConnection::openExisting() {
    return sqlite_->openExisting(kDatabaseFileName_);
}

void DatabaseConnection::createDatabaseAndOpen() {
    sqlite_->openOrCreate(kDatabaseFileName_);
}

int DatabaseConnection::execDML(const std::string &sql) {
    return sqlite_->execDML(sql);
}

std::unique_ptr<SqliteQuery> DatabaseConnection::execQuery(const std::string &sql) {
    return sqlite_->execQuery(sql);
}

std::unique_ptr<SqliteTable> DatabaseConnection::getTable(const std::string &sql) {
    return sqlite_->getTable(sql);
}

long long int DatabaseConnection::getLastInsertId() {
    return sqlite_->getLastInsertId();
}

} }
