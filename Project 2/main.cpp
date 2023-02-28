// Library Management System

#include "Book_info.h"

// main function
int main() {

	Bookdetails booklog[len];  // Array of structures
	int option, number = 0, searchoption, yesorno;
	cout << "Select an option from menu 1-4" << endl;
	cout << "1: Add a book" << endl;
	cout << "2: Search for a book" << endl;
	cout << "3: Print and Output the total number of books" << endl;
	cout << "4: Exit" << endl;
	cin >> option;

	while (option != 4) {

		if (option == 1) {

			while (number < len) {

				addbook(booklog, number);
				cout << "Do you want to add another book? " << endl;
				cout << "1:Yes" << endl << "2:No" << endl;
				cin >> yesorno;

				if (yesorno == 1) {

					number++;

				}
				else if (yesorno == 2) {

					break;

				}
			}
		}
		else if (option == 2) {

			cout << "Search for a book:" << endl;
			cout << "Enter option for seaching by: " << endl;
			cout << "1: The title" << endl;
			cout << "2: Author " << endl;
			cout << "3: Year" << endl;
			cout << "4: Availability for borrow" << endl;
			cin >> searchoption;

			searchbook(searchoption, number + 1, booklog);
		}
		else if (option == 3) {

			cout << "Book Author       Book Title           Publication Year         ISBN             Availability for borrow" << endl;
			cout << "\n";
			int booknumber = 0;

			print(booklog, number + 1, booknumber);

			cout << "\n";
		}

		cout << "Select an option from menu 1-4" << endl << "1: Add a book" << endl << "2: Search for a book" << endl << "3: Print and Output the total number of books" << endl << "4: Exit" << endl;
		cin >> option;

		while (option == 1) {

			number = number + 1;

			while (number < len) {

				addbook(booklog, number);
				cout << "Do you want to add another book? " << endl;
				cout << "1:Yes" << endl << "2:No" << endl;
				cin >> yesorno;

				if (yesorno == 1) {

					number++;

				}
				else if (yesorno == 2) {

					break;

				}
			}

			cout << "Select an option from menu 1-4" << endl << "1: Add a book" << endl << "2: Search for a book" << endl << "3: Print and Output the total number of books" << endl << "4: Exit" << endl;
			cin >> option;
		}
	}
	if (option == 4) {

		cout << "Bye Bye" << endl;
	}
}
