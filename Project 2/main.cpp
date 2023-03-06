/** \file main.cpp
* \brief The part of the whole project that users will be able to interact with.
* \details The user will be able the functions that are in other parts of the project through this file. In this file a connection 
* to the datase is created and the table is created or if it already exists this file accesses it.
* <BR>
* \author Joseph Uche
* \version 0.1
* \date 06-03-2023
*/

#include "Book_info.h"

int main() {
	sqlite3* database;
	char* error_message = 0;
	int rc,option;
	const char* sql;
	const char* data = "Callback function called.";

	// Opening Connection to database
	rc = sqlite3_open("Library.db", &database);
	
	if (rc) {
		cerr << "Can't open database: " << sqlite3_errmsg(database) << endl;
		sqlite3_close(database);
		return 1;
	}
	else {
		cout << "Connection successful\n";
	}

	//Creating Table in Databse
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

	// User Interaction
	cout << "Welcome to the library Management System.\n";
	cout << "1. Add a book\n";
	cout << "2. Search for a book\n";
	cout << "3. print and count the total number of books.\n";
	cout << "4. Edit book details\n";
	cout << "5. Exit\n";
	cin >> option;
	while (option != 5) {
		cin.ignore();
		Book books;
		if (option == 1) {
			books.read_details(database);
			books.save_details(database);
		}

		else if (option == 2) {
			cout << "1. Search by Publication Year\n";
			cout << "2. Search by Author\n";
			cout << "3. Search by Title\n";
			cout << "4. See available books\n";
			cout << "5. Back\n";
			cin >> option;
			while (option != 5) {
				cin.ignore();
				if (option == 1) {
					search_by_year(database);
				}
				else if (option == 2) {
					search_by_author(database);
				}
				else if (option == 3) {
					search_by_title(database);
				}
				else if (option == 4) {
					check_availability(database);
				}
				else {
					cout << "Invalid Input\n";
				}
				cout << "1. Search by Year\n";
				cout << "2. Search by Author\n";
				cout << "3. Search by Title\n";
				cout << "4. See available books\n";
				cout << "5. Back\n";
				cin >> option;
			}
		}
		else if (option == 3) {
			print_table(database);
			count_books(database);
		}
		else if (option == 4) {
			cout << "1. Change Author's name\n";
			cout << "2. Change Publication Year\n";
			cout << "3. Change Book Title\n";
			cout << "4. Change ISBN\n";
			cout << "5. Change Availability Status\n";
			cout << "6. Delete Book\n";
			cout << "7. Back\n";
			cin >> option;
			
			while (option != 7) {
				cin.ignore();
				string isbn;
				cout << "Enter the ISBN of the book that you want to change\\delete: ";
				getline(cin, isbn);
				if (option == 1) {
					change_authors_name(database, isbn);
				}
				else if (option == 2) {
					change_publication_year(database, isbn);
				}
				else if (option == 3) {
					change_title(database, isbn);
				}
				else if (option == 4) {
					change_isbn(database, isbn);
				}
				else if (option == 5) {
					change_availability(database, isbn);
				}
				else if (option == 6) {
					delete_book(database, isbn);
				}
				else {
					cout << "Invalid Input\n";
				}
				cout << "1. Change Author's name\n";
				cout << "2. Change Publication Year\n";
				cout << "3. Change Book Title\n";
				cout << "4. Change ISBN\n";
				cout << "5. Chnage Availability Status\n";
				cout << "6. Delete Book\n";
				cout << "7. Back\n";
				cin >> option;
				
			}
		}
		else {
			cout << "Invalid Input\n";
		}
		cout << "1. Add a book\n";
		cout << "2. Search for a book\n";
		cout << "3. print and count the total number of books.\n";
		cout << "4. Edit book details\n";
		cout << "5. Exit\n";
		cin >> option;
	}
}