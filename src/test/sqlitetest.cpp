#define BOOST_TEST_MODULE sqlitetest
#include <boost/test/included/unit_test.hpp>
#include "../sqlite.h"
#include "../sqlitequery.h"
#include <memory>

//
// QTDIR variable is only working with addin. Otherwise I have to add it to the system environment variables...
// https://bugreports.qt-project.org/browse/QTVSADDINBUG-82
//
//
//

BOOST_AUTO_TEST_SUITE (sqlitetest) // name of the test suite

BOOST_AUTO_TEST_CASE (newdbtest)
{
    const std::string insertSQL = "CREATE TABLE test (id INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL, text TEXT NOT NULL, deleted INTEGER DEFAULT 0 NOT NULL)";

    // TODO: Delete db-file
    sqliteWrapper::Sqlite sqlite;
    BOOST_CHECK( sqlite.openOrCreate("test.db") );
    BOOST_CHECK( sqlite.isOpen() );
    sqlite.execDML("DROP TABLE test");
    BOOST_CHECK_EQUAL(1, sqlite.execDML(insertSQL));
    BOOST_CHECK_EQUAL(1, sqlite.execDML("INSERT INTO test VALUES ('foo')"));
    std::unique_ptr<sqliteWrapper::SqliteQuery> query = sqlite.execQuery("SELECT * FROM test");
    // Iterate over query
    BOOST_CHECK_EQUAL(false, query->hasNext());
    //BOOST_CHECK_EQUAL("foo", query->getStringField().c_str());
    std::cin.ignore();
}

BOOST_AUTO_TEST_CASE (existingdbtest)
{
  //mystring s;
  //s.setbuffer("hello world");
  //BOOST_REQUIRE_EQUAL ('h', s[0]); // basic test
}

BOOST_AUTO_TEST_SUITE_END( )