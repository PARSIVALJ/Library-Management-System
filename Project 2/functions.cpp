#include "Book_info.h"

void addbook(Bookdetails* book, int position) {  // function to add book to the library
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

void searchbook(int searchopt, int num, Bookdetails books[]) { // function to search for a book
	cin.ignore();
	char searchbytitle[len];
	char searchbyauthor[len];
	int searchbyyear;
	int book_position = 0, pos1 = 0;
	int marker1 = 0, marker2 = 0;
	if (searchopt == 1) {  // search using the title of the book
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
	else if (searchopt == 2) {  // Search using the authors name
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
	else if (searchopt == 3) {  // search using the publication year of the book
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
	else if (searchopt == 4) {  // checking the availability of the book
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

void  print(Bookdetails bookl[], int number, int position) {  // Recursive function to Print out the books in the library
	if (position == number) {
		cout << "There are " << number << " books in the library." << endl;
	}
	else {
		cout << bookl[position].author_full_name << "       " << bookl[position].Book_title << "           ";
		cout << bookl[position].publication_year << "          " << bookl[position].Book_ISBN << "               " << bookl[position].availability[0] << endl;
		cout << "\n";
		print(bookl, number, position + 1);
	}
}