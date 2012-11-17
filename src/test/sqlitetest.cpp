#define BOOST_TEST_MODULE sqlitetest

#include <boost/test/included/unit_test.hpp>
#include "../sqlite.h"
#include "../sqlitequery.h"
#include "../textfilelogger.h"
#include <memory>
#include <fstream>

//
// QTDIR variable is only working with addin. So you have to add it to your system environment variables!
// https://bugreports.qt-project.org/browse/QTVSADDINBUG-82
//

struct GlobalConfig {
    GlobalConfig() : test_log( "log-test.txt" ), logger("log-program.txt") {
        boost::unit_test::unit_test_log.set_stream( test_log );

        // Docu says: Avoid, because overrides runtime parameters. Prefer to use runtime parameters for log level selection.
        // Equivalent commandline argument: --log_level=all
        // http://www.boost.org/doc/libs/1_43_0/libs/test/doc/html/utf/user-guide/test-output/log-ct-config.html
        // http://www.boost.org/doc/libs/1_43_0/libs/test/doc/html/utf/user-guide/runtime-config/reference.html
        // boost::unit_test::unit_test_log.set_threshold_level( boost::unit_test::log_successful_tests );

        // Docu says: Avoid this, prefer runtime parameters
        // boost::unit_test::unit_test_log.set_format( boost::unit_test::XML );
        
        // Init Qt Logger
        qInstallMsgHandler(note::model::TextFileLogger::fileMessageHandler);
    }
    ~GlobalConfig() {
        boost::unit_test::unit_test_log.set_stream( std::cout );
    }

    note::model::TextFileLogger logger;
    std::ofstream test_log;
};

struct Fix {
    Fix() { BOOST_TEST_MESSAGE( "setup fixture" ); }
    ~Fix()         { BOOST_TEST_MESSAGE( "teardown fixture" ); }
    
    sqliteWrapper::Sqlite sqlite;
};

BOOST_AUTO_TEST_SUITE (sqlitetest) // name of the test suite

BOOST_GLOBAL_FIXTURE( GlobalConfig );

//BOOST_AUTO_TEST_CASE (newdbtest)
BOOST_FIXTURE_TEST_CASE (newdbtest, Fix)    // also automatically, but with fixture. Members can be accessed!
{
    const std::string createSQL = "CREATE TABLE test (id INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL, text TEXT NOT NULL, deleted INTEGER DEFAULT 0 NOT NULL)";

    // TODO: Delete db-file
    BOOST_CHECK( sqlite.openOrCreate("test.db") );
    BOOST_CHECK( sqlite.isOpen() );
    sqlite.execDML("DROP TABLE test");
    sqlite.execDML(createSQL);
    BOOST_CHECK_EQUAL(1, sqlite.execDML("INSERT INTO test (text) VALUES ('foo')"));
    BOOST_CHECK_EQUAL(1, sqlite.execDML("INSERT INTO test (text) VALUES ('bar')"));
    std::unique_ptr<sqliteWrapper::SqliteQuery> query = sqlite.execQuery("SELECT * FROM test");
    BOOST_CHECK_EQUAL(false, query->eof());
    // Iterate over query
    BOOST_CHECK_EQUAL("foo", query->getStringField("text").c_str());
    query->nextRow();
    BOOST_CHECK_EQUAL("bar", query->getStringField("text").c_str());
    query->nextRow();
    BOOST_CHECK_EQUAL(true, query->eof());
    std::cin.ignore();
}

BOOST_FIXTURE_TEST_CASE (existingdbtest, Fix)
{
    BOOST_CHECK( sqlite.openExisting("test.db") );
    BOOST_CHECK( sqlite.isOpen() );
}

BOOST_AUTO_TEST_SUITE_END( )