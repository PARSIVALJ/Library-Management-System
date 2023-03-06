#include "Book_info.h"

int main() {
	sqlite3* database;
	char* error_message = 0;
	int rc,option;
	const char* sql;
	const char* data = "Callback function called.";

	//
	rc = sqlite3_open("Library.db", &database);
	
	if (rc) {
		cerr << "Can't open database: " << sqlite3_errmsg(database) << endl;
		sqlite3_close(database);
		return 1;
	}
	else {
		cout << "Connection successful\n";
	}
	sql = "CREATE TABLE IF NOT EXISTS BOOKS ("\
		"title TEXT NOT NULL,"\
		"author TEXT NOT NULL,"\
		"publication INT NOT NULL,"\
		"availability TEXT NOT NULL,"\
		"isbn TEXT NOT NULL);";

	rc = sqlite3_exec(database, sql, callback, (void*)data, &error_message);
	if (rc != SQLITE_OK) {
		cerr << "SQL erroe: " << error_message << endl;
		sqlite3_free(error_message);
	}
	else {
		cout << "Connection Successful.\n";
	}

	cout << "Welcome to the library Management System.\n";
	cout << "1. Add a book\n";
	cout << "2. Search for a book\n";
	cout << "3. print and count the total number of books.\n";
	cout << "4. Exit\n";
	cin >> option;
	while (option != 4) {
		cin.ignore();
		Book books;
		if (option == 1) {
			books.read_details(database);
			books.save_details(database);
		}
	}
}