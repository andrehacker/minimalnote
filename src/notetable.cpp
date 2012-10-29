#include <QDebug>
#include <sstream>
#include <boost/algorithm/string.hpp>
#include <algorithm>
#include "notetable.h"
#include "helper.h"
#include "databaseconnection.h"

namespace note { namespace model {

NoteTable::NoteTable(DatabaseConnection &db)
    : db_(db)
{

}

bool NoteTable::createTable()
{
    // Column id will be an alias for sqlites internal rowid.
    // See http://www.sqlite.org/lang_createtable.html#rowid
    const std::string firstNoteText = "'Delete this note and create your own!\n" \
        "============== \n\n" \
        "How to use \n" \
        "============== \n" \
        "There are 3 areas in this app \n" \
        "* On the left, you can filter by one or more Tags \n" \
        "* In the middle, you can search for a note (fulltext in title and text) \n" \
        "* On the right side, you can edit the selected note.'";

    db_.execDML("CREATE TABLE notes (id INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL, title TEXT NOT NULL, content TEXT NOT NULL, deleted INTEGER DEFAULT 0 NOT NULL, tags TEXT NOT NULL)");
    db_.execDML("INSERT INTO notes (title, content, tags) values ('Welcome to MinimalNote', " + firstNoteText + ", ',DEV,');");
    db_.execDML("INSERT INTO notes (title, content, tags) values ('This is a second note', 'Please delete me by pressing the DEL key', ',Personal,');");
    return true;    //TODO: separate method execDDL needed
}

std::vector<NoteDto> NoteTable::getNotes() {
    return getNotes("", std::vector<TagDto>());
}

std::vector<NoteDto> NoteTable::getNotes(const std::string &searchText) {
    return getNotes(searchText, std::vector<TagDto>());
}

std::vector<NoteDto> NoteTable::getNotes(const std::string &searchText, const std::vector<TagDto> &tagFilter) {

    std::string sql = "SELECT id, title, content, tags FROM notes where deleted=0";

    for (auto it = tagFilter.begin(); it != tagFilter.end(); ++it) {
        sql += " AND tags like '%," + it->getName() + ",%'";
    }
    if (searchText != "") {
        sql += " AND (title like '%" + searchText
            + "%' OR content like '%" + searchText + "%')";
    }

    std::vector<NoteDto> notes;
    std::unique_ptr<SqliteQuery> query = db_.execQuery(sql);
    if (query) {
        while (query->hasNext()) {
            notes.push_back(NoteDto(
                                query->getIntField("id"),
                                query->getStringField("title"),
                                query->getStringField("content"),
                                normalizeTagsForUi(query->getStringField("tags"))
                                ));
            query->nextRow();
        }
    }
    return notes;
}

bool NoteTable::add(NoteDto &newNote) {
    std::string sql = "INSERT INTO notes (title, content, tags) VALUES ('"
            + newNote.getTitle() + "', '"
            + newNote.getContent() + "', '"
			+ normalizeTagsForDB(newNote.getTags()) + "');";

    if (db_.execDML(sql) > 0) {
        // Update note id!
        // notes.id is an alias for sqlites rowid, so no problem to use the returned rowid as id
        newNote.setId(db_.getLastInsertId());

		// Normalize tags for ui
		newNote.setTags(normalizeTagsForUi(newNote.getTags()));

        return true;
    }
    return false;
}

bool NoteTable::update(NoteDto &changedNote) {
    // TODO: Replace with std::to_string(changedNote.getId());
    std::ostringstream id;
    id << changedNote.getId();
    std::string sql = "UPDATE notes SET title='" + changedNote.getTitle()
            + "', content='" + changedNote.getContent()
            + "', tags='" + normalizeTagsForDB(changedNote.getTags())
			+ "' WHERE ID = " + id.str() + ";";

	// Normalize tags for ui
	changedNote.setTags(normalizeTagsForUi(changedNote.getTags()));

    return (db_.execDML(sql) == 1);
}


bool NoteTable::remove(const NoteDto &note) {
    // TODO: Replace with std::to_string(changedNote.getId());
    std::ostringstream id;
    id << note.getId();
    std::string sql = "UPDATE notes SET deleted=1 WHERE ID = " + id.str() + ";";
    return (db_.execDML(sql) == 1);
}

bool NoteTable::removeTagFromNotes(const std::string &tagName) {
    // TODO: This function must be called whenever a tag (with notes assigned) is deleted
    return false;
}

// Tags are stored with "," as prefix and suffix, to be able to easily search for ... like '%,TAG,%'
// However the model and UI should not be bothered by this so we convert it always
// TODO: One day the way to store tags should be changed to be less complex!
// Example: "DEV, Personal" => ",DEV,Personal,"
// For string algos see http://www.boost.org/doc/libs/1_36_0/doc/html/string_algo/usage.html
std::string NoteTable::normalizeTagsForDB(std::string tags) {
	//qDebug() << "normalizeTagsForDB before: " << tags.c_str();
	// get list of tags
	std::vector<std::string> taglist;
	boost::split(taglist, tags, boost::is_any_of(","));

	// trim each tag and output to normalized string (if tag not empty)
	std::string normalized = ",";
	std::for_each(taglist.begin(), taglist.end(), [&normalized](std::string &curTag) {
		// TODO: replace with boost::trim(curTag); Currently causes VC compiler to crash;-(
		note::common::Helper::trimString(curTag);
		if (curTag != "") {
			normalized.append(curTag);
			normalized.append(",");
		}
	});
	
	return normalized;
}

std::string NoteTable::normalizeTagsForUi(std::string tags) {
	//qDebug() << "normalizeTagsForUi before: " << tags.c_str();
	// get list of tags
	std::vector<std::string> taglist;
	boost::split(taglist, tags, boost::is_any_of(","));

	// trim each tag and output to normalized string (if tag not empty)
	std::string normalized = "";
	std::for_each(taglist.begin(), taglist.end(), [&normalized](std::string &curTag) {
		// TODO: replace with boost::trim(curTag); Currently causes VC compiler to crash;-(
		note::common::Helper::trimString(curTag);
		if (curTag != "") {
			normalized.append(curTag);
			normalized.append(", ");
		}
	});

	return normalized;
}

}}
