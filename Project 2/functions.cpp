#include "Book_info.h"

//
Book::Book() {
	title = "";
	authors_name = "";
	isbn = "";
	publication_year = 0;
	availability = "";
}

//
void Book::read_details(sqlite3* db) {
	string available[2] = { "Available","Not Available" };
	int option;
	cout << "Please,Enter book details:\n";
	cout << "Title: ";
	getline(cin, title);
	cout << "Author(s): ";
	getline(cin, authors_name);
	cout << "ISBN: ";
	getline(cin,isbn);
	//
	while (is_in_database(db,isbn) > 0) {
		cout << "ISBN already in database.\n";
		cout << "ISBN: ";
		getline(cin,isbn);
	}
	//
	cout << "Publicatioon Year: ";
	cin >> publication_year;
	cin.ignore();
	cout << "Is the book avilable for borrow:\n";
	cout << "1. Yes\n";
	cout << "2. No\n";
	cin >> option;
	availability = available[option-1];
}

//
void Book::save_details(sqlite3* db) {
	char* error_message;
	int rc;
	char* sql;
	sql = sqlite3_mprintf("INSERT INTO BOOKS(title,author,publication,availability,isbn) VALUES ('%q','%q', %d, '%q','%q')", title.c_str(), authors_name.c_str(), publication_year, availability.c_str(), isbn.c_str());
	cout << sql << endl;
	rc = sqlite3_exec(db, sql, callback, 0, &error_message);
	if (rc != SQLITE_OK) {
		cout << rc << endl;
		fprintf(stderr, "SQL error: %s\n", error_message);
		sqlite3_free(error_message);
		//sqlite3_close(db);
	}
	else {
		printf("Records created successfully\n");
	}
	sqlite3_free(sql);
}
//
int callback(void* data, int argc, char** argv, char** colName) {
	int* count = (int*)data;
	(*count)++;
	return 0;
}

//
int print_callback(void* data, int argc, char** argv, char** colName) {
	for (int i = 0; i < argc; i++) {
		cout << colName[i] << " = " << argv[i] << endl;
	}
	cout << "--------------------------------\n";

	return 0;
}

//
int is_in_database(sqlite3* db, string isbn) {
	char sql[100];
	snprintf(sql, 100, "SELECT * FROM BOOKS WHERE isbn='%s'", isbn.c_str());
	int count = 0;
	int rc = sqlite3_exec(db, sql, callback, &count, NULL);
	if (rc != SQLITE_OK) {
		fprintf(stderr, "Error: %s\n", sqlite3_errmsg(db));
		return -1;
	}
	return count > 0;
}

//
string change_title(sqlite3* db, string isbn) {
	string new_title;
	cout << "Enter New Title: ";
	getline(cin, new_title);

	char* error_message = 0;
	int rc;
	char* sql = sqlite3_mprintf("UPDATE BOOKS SET title='%q' WHERE isbn='%q';", new_title.c_str(), isbn.c_str());
	rc = sqlite3_exec(db, sql, callback, 0, &error_message);
	if (rc != SQLITE_OK) {
		fprintf(stderr, "SQL error: %s\n", error_message);
		sqlite3_free(error_message);
		//sqlite3_close(db);
	}
	else {
		cout << "Title changed Successfully.\n";
	}
	sqlite3_free(sql);
	return new_title;
}

//
string change_authors_name(sqlite3* db, string isbn) {
	string new_authors;
	cout << "Enter the new authors name: ";
	getline(cin, new_authors);
	char* error_message = 0;
	int rc;
	char* sql = sqlite3_mprintf("UPDATE BOOKS SET author='%q' WHERE isbn ='%q';", new_authors.c_str(), isbn.c_str());
	rc = sqlite3_exec(db, sql, callback, 0, &error_message);
	if (rc != SQLITE_OK) {
		fprintf(stderr, "SQL error: %s\n", error_message);
		sqlite3_free(error_message);
		//
	}
	else {
		cout << "Author changed successfully\n";
	}
	return new_authors;
}

//
int change_publication_year(sqlite3* db, string isbn) {
	int new_publication_year;
	cout << "Enter new Publication year: ";
	cin >> new_publication_year;
	cin.ignore();
	char* error_message = 0;
	int rc;
	char* sql = sqlite3_mprintf("UPDATE BOOKS SET publication = %d WHERE isbn = '%q';", new_publication_year, isbn.c_str());
	rc = sqlite3_exec(db, sql, callback, 0, &error_message);
	if (rc != SQLITE_OK) {
		fprintf(stderr, "SQL errow: %s\n", error_message);
		sqlite3_free(error_message);
		//
	}
	else {
		cout << "Publication Year changed Successfully\n";
	}
	return new_publication_year;
}

//
string change_isbn(sqlite3* db, string isbn) {
	string new_isbn;
	cout << "Enter new ISBN: ";
	getline(cin, new_isbn);
	char* error_message = 0;
	int rc;
	char* sql = sqlite3_mprintf("UPDATE BOOKS SET isbn ='%q' WHERE isbn='%q';", new_isbn.c_str(), isbn.c_str());
	rc = sqlite3_exec(db, sql, callback, 0, &error_message);
	if (rc != SQLITE_OK) {
		fprintf(stderr, "SQL errow: %s\n", error_message);
		sqlite3_free(error_message);
		//
	}
	else {
		cout << "Publication Year changed Successfully\n";
	}
	return new_isbn;
}

//
bool delete_book(sqlite3* db, string isbn) {
	string sql = "DELETE FROM BOOKS WHERE isbn = ?;";
	sqlite3_stmt* stmt;
	sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, NULL);
	sqlite3_bind_text(stmt, 1, isbn.c_str(), -1, SQLITE_STATIC);
	int result = sqlite3_step(stmt);
	sqlite3_finalize(stmt);
	if (result == SQLITE_DONE) {
		cout << "Book Deleted.\n";
		return true;
	}
	else {
		cout << "Error occured during deletion.\n";
		return false;
	}
}

//
void print_table(sqlite3* db) {
	string sql = "SELECT * FROM BOOKS;";
	char* error_message = NULL;
	int result = sqlite3_exec(db, sql.c_str(), print_callback, 0, &error_message);
	if (result != SQLITE_OK) {
		cerr << "Error executing SELECT statement: " << error_message << endl;
		sqlite3_free(error_message);
	}
}

//
int count_callback(void* data, int argc, char** argv, char** colName) {
	int* count = static_cast<int*>(data);
	*count = stoi(argv[0]);
	return 0;
}

//
void count_books(sqlite3* db) {
	int count = 0, rc;
	string sql = "SELECT COUNT(*) FROM BOOKS;";
	char* errmsg;
	rc = sqlite3_exec(db, sql.c_str(), count_callback, &count, &errmsg);

	if (rc != SQLITE_OK) {
		cerr << "SQL error: " << errmsg << endl;
		sqlite3_free(errmsg);
	}
	else {
		cout << "Number of books in database: " << count << endl;
	}
}

//
void search_by_title(sqlite3* db) {
	int count = 0;
	string keyword;
	cout << "Enter keyword: ";
	getline(cin, keyword);
	string sql = "SELECT title,author,publication,availability, isbn FROM BOOKS WHERE title LIKE ?";
	sqlite3_stmt* stmt;
	sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, NULL);
	string search_term = "%" + keyword + "%";
	sqlite3_bind_text(stmt, 1, search_term.c_str(), -1, SQLITE_STATIC);
	int result = sqlite3_step(stmt);

	while (result == SQLITE_ROW) {
		cout << "Title: " << reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0)) << endl;
		cout << "Author(s): " << reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1)) << endl;
		cout << "Publication Year: " << sqlite3_column_int(stmt, 2) << endl;
		cout << "Availability: " << reinterpret_cast<const char*>(sqlite3_column_text(stmt, 3)) << endl;
		cout << "ISBN: " << reinterpret_cast<const char*>(sqlite3_column_text(stmt, 4)) << endl;
		cout << "------------------------------------------------------------------------------\n";
		result = sqlite3_step(stmt);
		count++;
	}
	if (result != SQLITE_DONE) {
		cout << "Error searching for book.\n";
	}
	if (count == 0) {
		cout << "Book does not exist in our database\n.";
	}
	sqlite3_finalize(stmt);
}

//
void search_by_author(sqlite3* db) {
	int count = 0;
	string keyword;
	cout << "Enter keyword: ";
	getline(cin, keyword);
	string sql = "SELECT title,author,publication,availability, isbn FROM BOOKS WHERE author LIKE ?";
	sqlite3_stmt* stmt;
	sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, NULL);
	string search_term = "%" + keyword + "%";
	sqlite3_bind_text(stmt, 1, search_term.c_str(), -1, SQLITE_STATIC);
	int result = sqlite3_step(stmt);

	while (result == SQLITE_ROW) {
		cout << "Title: " << reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0)) << endl;
		cout << "Author(s): " << reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1)) << endl;
		cout << "Publication Year: " << sqlite3_column_int(stmt, 2) << endl;
		cout << "Availability: " << reinterpret_cast<const char*>(sqlite3_column_text(stmt, 3)) << endl;
		cout << "ISBN: " << reinterpret_cast<const char*>(sqlite3_column_text(stmt, 4)) << endl;
		cout << "------------------------------------------------------------------------------\n";
		result = sqlite3_step(stmt);
		count++;
	}
	if (result != SQLITE_DONE) {
		cout << "Error searching for book.\n";
	}
	if (count == 0) {
		cout << "Book does not exist in our database\n.";
	}
	sqlite3_finalize(stmt);
}

//
void check_availability(sqlite3* db) {
	int count = 0;
	string sql = "SELECT title,author,publication,availability, isbn FROM BOOKS WHERE availability = 'Available'";
	sqlite3_stmt* stmt;
	sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, NULL);
	int result = sqlite3_step(stmt);
	while (result == SQLITE_ROW) {
		cout << "Title: " << reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0)) << endl;
		cout << "Author(s): " << reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1)) << endl;
		cout << "Publication Year: " << sqlite3_column_int(stmt, 2) << endl;
		cout << "Availability: " << reinterpret_cast<const char*>(sqlite3_column_text(stmt, 3)) << endl;
		cout << "ISBN: " << reinterpret_cast<const char*>(sqlite3_column_text(stmt, 4)) << endl;
		cout << "------------------------------------------------------------------------------\n";
		result = sqlite3_step(stmt);
		count++;
	}
	if (result != SQLITE_DONE) {
		cout << "Error searching for book.\n";
	}
	if (count == 0) {
		cout << "No book is available for borrow now. Try again later\n";
	}
	
	sqlite3_finalize(stmt);
}

//
void search_by_year(sqlite3* db) {
	int count = 0, year;
	cout << "Enter publication year: ";
	cin >> year;
	cin.ignore();
	string sql = "SELECT title,author,publication,availability, isbn FROM BOOKS WHERE publication = ?";
	sqlite3_stmt* stmt;
	sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, NULL);
	sqlite3_bind_int(stmt, 1, year);
	int result = sqlite3_step(stmt);

	while (result == SQLITE_ROW) {
		cout << "Title: " << reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0)) << endl;
		cout << "Author(s): " << reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1)) << endl;
		cout << "Publication Year: " << sqlite3_column_int(stmt, 2) << endl;
		cout << "Availability: " << reinterpret_cast<const char*>(sqlite3_column_text(stmt, 3)) << endl;
		cout << "ISBN: " << reinterpret_cast<const char*>(sqlite3_column_text(stmt, 4)) << endl;
		cout << "------------------------------------------------------------------------------\n";
		result = sqlite3_step(stmt);
		count ++;
	}
	if (result != SQLITE_DONE) {
		cout << "Error searching for book.\n";
	}
	if (count == 0) {
		cout << "Book does not exist in our database\n.";
	}

	sqlite3_finalize(stmt);
}

//
void change_availability(sqlite3* db, string isbn) {
	string available[] = { "Available","Not Available" };
	int option;
	cout << "Please choose availability:\n";
	cout << "1. Availbale\n";
	cout << "2. Not Available\n";
	cin >> option;
	cin.ignore();
	char* error_message = 0;
	int rc;
	char* sql = sqlite3_mprintf("UPDATE BOOKS SET availability='%q' WHERE isbn ='%q';", available[option-1].c_str(), isbn.c_str());
	rc = sqlite3_exec(db, sql, callback, 0, &error_message);
	if (rc != SQLITE_OK) {
		fprintf(stderr, "SQL error: %s\n", error_message);
		sqlite3_free(error_message);
		//
	}
	else {
		cout << "Availability Status changed successfully\n";
	}
}