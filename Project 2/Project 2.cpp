// Name: Uche Joseph Ugochukwu
// Library Management System
 

#include <iostream>
#include <cstring>
using namespace std;
const int len = 50;
struct Bookdetails {
	char Book_ISBN[len];
	char Book_title[len];
	char author_full_name[len];
	int publication_year;
	char availability[1];
};
void addbook(Bookdetails* book, int position) {// function to add book to the library
	char availableforborrow[2] = { 'y','n' };
	cin.ignore();
	cout << "Enter book details." << endl;
	cout << "Isbn: ";
	cin.getline(book[position].Book_ISBN, len);
	cout << "Book title: ";
	cin.getline(book[position].Book_title, len);
	cout << "Book author: ";
	cin.getline(book[position].author_full_name, len);
	cout << "Book year: ";
	cin >> book[position].publication_year;
	book[position].availability[0] = availableforborrow[rand() % 2];
	cout << "Available for Borrow: ";
	cout << book[position].availability[0] << endl;
}
void searchbook(int searchopt, int num, Bookdetails books[]) {// function to search for a book
	cin.ignore();
	char searchbytitle[len];
	char searchbyauthor[len];
	int searchbyyear;
	int book_position = 0, pos1 = 0;
	int marker1 = 0, marker2 = 0;
	if (searchopt == 1) {// search using the tittle of the book
		cout << "Enter key word for title of the book to search for: " << endl;
		cin.getline(searchbytitle, len);
		while (book_position < num) {
			int j = 0;
			int count1 = 0;
			while (j < strlen(books[book_position].Book_title) && pos1 < strlen(searchbytitle)) {
				if (books[book_position].Book_title[j] == searchbytitle[pos1]) {
					pos1++;
					count1 += 1;
				}
				else {
					if (count1 != strlen(searchbytitle)) {
						pos1 = 0;
						count1 = 0;
					}
				}
				j++;
			}
			if (count1 >= strlen(searchbytitle)) {
				marker1 += 1;
				cout << books[book_position].author_full_name << ", " << books[book_position].Book_title << " ," << books[book_position].publication_year << ", " << books[book_position].Book_ISBN << "." << endl;
				cout << "\n";
			}
			book_position++;
		}
		if (marker1 == 0) {
			cout << "Book Not Found" << endl;
			cout << "\n";
		}
	}
	else if (searchopt == 2) {// Search using the authors name
		cout << "Enter authors' name: " << endl;
		cin.getline(searchbyauthor, len);
		while (book_position < num) {
			int pos2 = 0;
			int count2 = 0;
			int q = 0;
			while (pos2 < strlen(searchbyauthor) && q < strlen(books[book_position].author_full_name)) {
				if (books[book_position].author_full_name[q] == searchbyauthor[pos2]) {
					count2 += 1;
					pos2++;
				}
				else {
					if (count2 != strlen(searchbyauthor)) {
						count2 = 0;
						pos2 = 0;
					}
				}
				q++;
			}
			if (count2 >= strlen(searchbyauthor)) {
				marker2 += 1;
				cout << books[book_position].Book_title << ", " << books[book_position].publication_year << ", " << books[book_position].Book_ISBN << "." << endl;
				cout << "\n";
			}
			book_position++;
		}
		if (marker2 == 0) {
			cout << "Book written by " << searchbyauthor << " not found." << endl;
			cout << "\n";
		}
	}
	else if (searchopt == 3) {// search using the publication year of the book
		int marker3 = 0;
		cout << "Enter the publication year of the book: " << endl;
		cin >> searchbyyear;
		while (book_position < num) {
			if (searchbyyear == books[book_position].publication_year) {
				marker3 += 1;
				cout << books[book_position].author_full_name << " ," << books[book_position].Book_title << " ," << books[book_position].publication_year << ", " << books[book_position].Book_ISBN << "." << endl;
				cout << "\n";
			}
			book_position++;
		}
		if (marker3 == 0) {
			cout << "No book Published in " << searchbyyear << " was found." << endl;
			cout << "\n";
		}
	}
	else if (searchopt == 4) {// checking the availability of the book
		int count3 = 0;
		while (book_position < num) {
			if (books[book_position].availability[0] == 'y') {
				count3 += 1;
				cout << books[book_position].author_full_name << " ," << books[book_position].Book_title << " ," << books[book_position].publication_year << " ," << books[book_position].Book_ISBN << "        " << books[book_position].availability[0] << endl;
				cout << "\n";
			}
			book_position++;
		}
		if (count3 == 0) {
			cout << "No books Available for Borrow." << endl;
		}
	}
}
int print(Bookdetails bookl[], int number, int pos3) {// Recursive function to Print out the books in the library
	if (pos3 == number) {
		return 0;
	}
	else {
		cout << bookl[pos3].author_full_name << "       " << bookl[pos3].Book_title << "           ";
		cout << bookl[pos3].publication_year << "          " << bookl[pos3].Book_ISBN << "               " << bookl[pos3].availability[0] << endl;
		cout << "\n";
		print(bookl, number, pos3 + 1);
	}
}

int main() {
	Bookdetails booklog[len];// Array of structures
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
			cout << "There are " << number + 1 << " in the library." << endl;
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
