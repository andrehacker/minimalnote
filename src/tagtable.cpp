#include "tagtable.h"
#include <sstream>
#include "databaseconnection.h"

namespace note { namespace model {

TagTable::TagTable(DatabaseConnection &db)
    : db_(db)
{

}

bool TagTable::createTable()
{
    // Column id will be an alias for sqlites internal rowid.
    // See http://www.sqlite.org/lang_createtable.html#rowid
    db_.execDML("CREATE TABLE tags (id INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL, name TEXT NOT NULL, notecount INTEGER DEFAULT 0 NOT NULL)");
    db_.execDML("INSERT INTO tags (name) values ('Personal');");
    db_.execDML("INSERT INTO tags (name) values ('DEV');");
    db_.execDML("INSERT INTO tags (name) values ('Learn');");
    return true;    //TODO: separate method execDDL needed
}

std::vector<TagDto> TagTable::getAll()
{
    std::vector<TagDto> tags;
    std::unique_ptr<SqliteQuery> query = db_.execQuery("SELECT id, name, notecount FROM tags");
    if (query) {
        while (!query->eof()) {
            tags.push_back(TagDto(
                                query->getIntField("id"),
                                query->getStringField("name"),
                                query->getIntField("notecount")
                                ));
            query->nextRow();
        }
    }
    return tags;
}

bool TagTable::add(TagDto &newTag) {
    std::string sql = "INSERT INTO tags (name) VALUES ('" + newTag.getName() + "');";

    if (db_.execDML(sql) > 0) {
        // Update tag id!
        newTag.setId(db_.getLastInsertId());

        return true;
    }
    return false;
}

bool TagTable::update(const TagDto &changedTag) {
    // TODO: Replace with std::to_string(changedNote.getId());
    std::ostringstream id;
    id << changedTag.getId();
    std::ostringstream noteCount;
    noteCount << changedTag.getNoteCount();
    std::string sql = "UPDATE tag SET name='" + changedTag.getName()
            + "', notecount=" + noteCount.str() + " WHERE ID = " + id.str() + ";";
    return (db_.execDML(sql) == 1);
}


bool TagTable::remove(const TagDto &tag) {
    // The caller should call NoteTable::removeTagFromNotes(...) after calling this method
    // TODO: Replace with std::to_string(tag.getId());
    std::ostringstream id;
    id << tag.getId();
    std::string sql = "DELETE FROM tags WHERE ID = " + id.str() + ";";
    return (db_.execDML(sql) == 1);
}

}}
