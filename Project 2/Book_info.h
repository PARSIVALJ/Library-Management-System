#include <iostream>
#include <cstring>
using namespace std;

const int len = 50;

//used to store book information
struct Bookdetails {

	char Book_ISBN[len];
	char Book_title[len];
	char author_full_name[len];
	int publication_year;
	char availability[1];

};

//prototype 
void addbook(Bookdetails* book, int position);

void searchbook(int searchopt, int num, Bookdetails books[]);

void  print(Bookdetails bookl[], int number, int position);


