//====================================================
// McKenna Gameros
// 9 December 2016
// Programming Assignment #7
// Description: Address Book
//====================================================

#include <iostream>
#include <string>
#include <fstream>

using namespace std;

struct person
{
	// firstName: first name of person
	// lastName: last name of person
	// phoneNumber: phone number of person
	// email: email address of person
	string firstName;
	string lastName;
	string phoneNumber;
	string email;
};

char menu(person book[], int &size);
int read(person book[]);
void add(person book[], int &size);
void remove(person book[], int &size);
void find(person book[], int size);
void list(person book[], int size);
void save(person book[], int size);
void swap(person book[], int size);
string toLower(string name);
int found(person book[], int size);

int main()
{
	// book: the address book array
	// count: the number of people in book
	// choice: the choice made by the user
	person book[100];
	int count;
	char choice;

	// read the number of names in the book
	count = read(book);

	// initialize application
	do
	{

		choice = menu(book, count);
		cout << endl;

	} while (choice != 'e');
	
	return 0;
}

//======================================================
// read: read the names from book.txt
// parameters: 
//    book: the array of structs representing people
// return type: int (the number of people in book)
//======================================================
int read(person book[])
{
	// addressIn: input from book.txt
	// count: counter for loop
	ifstream addressIn;
	int count = 0;

	addressIn.open("book.txt");

	while (getline(addressIn, book[count].firstName, '\n'))
	{
		getline(addressIn, book[count].lastName, '\n');
		getline(addressIn, book[count].phoneNumber, '\n');
		addressIn >> book[count].email;
		addressIn.ignore();
		count++;
	}

	return count;
}

//======================================================
// menu: display menu and initialize choices
// parameters: 
//    book: the array of structs representing people
//    size: the number of people in the array
// return type: char (to get out of the main loop)
//======================================================
char menu(person book[], int &size)
{
	// choice: input for menu options
	char choice;

	// display main menu
	cout << "\tMain Menu" << endl;
	cout << "A - Add Person" << endl;
	cout << "D - Delete Person" << endl;
	cout << "F - Find and Display Person" << endl;
	cout << "L - List All People" << endl;
	cout << "S - Save List" << endl;
	cout << "E - Exit" << endl;

	// make choice lowercase to make the input case-
	// insensitive
	cin >> choice;
	choice = tolower(choice);

	// validate input
	while (choice != 'a' && choice != 'd' &&
		choice != 'f' && choice != 'l' &&
		choice != 's' && choice != 'e')
	{
		cout << "You did not enter an available choice. ";
		cout << "Try again: ";
		cin >> choice;
		choice = tolower(choice);
	}

	// initialize choice
	if (choice == 'a')
	{
		add(book, size);
	}

	else if (choice == 'd')
	{
		remove(book, size);
	}

	else if (choice == 'f')
	{
		find(book, size);
	}

	else if (choice == 'l')
	{
		list(book, size);
	}

	else if (choice == 's')
	{
		save(book, size);
	}

	return choice;
}

//======================================================
// add: add a person to the array
// parameters: 
//    book: the array of structs representing people
//    size: the number of people in the array
// return type: none
//======================================================
void add(person book[], int &size)
{
	// count: counter for loops
	// foundAt: location of @ in email
	// foundDot: location of dot in email
	int count;
	int foundAt = 0;
	int foundDot = 0;

	// prompt for person's information
	cout << "Enter the person's first name: ";
	cin.ignore();
	getline(cin, book[size].firstName, '\n');
	cout << "Enter the person's last name: ";
	getline(cin, book[size].lastName, '\n');
	cout << "Enter the person's phone number: ";
	getline(cin, book[size].phoneNumber, '\n');
	cout << "Enter the person's email address: ";
	cin >> book[size].email;

	// find the @
	for (count = 0; count < book[size].email.length()
		&& foundAt == 0; count++)
	{
		if (book[size].email[count] == '@')
		{
			foundAt = count;
		}
	}
	
	// validate email address
	while (foundAt == 0)
	{
		cout << "Invalid email address. Try again: ";
		cin >> book[size].email;

		for (count = 0; count < book[size].email.length() 
			&& foundAt == 0; count++)
		{
			if (book[size].email[count] == '@')
			{
				foundAt = count;
			}
		}
	}

	// find the dot
	for (count = foundAt; count < book[size].email.length() 
		&& foundDot == 0; count++)
	{
		if (book[size].email[count] == '.')
		{
			foundDot = count;
		}
	}

	// re-validate email address
	while (foundDot == 0)
	{
		cout << "Invalid email address. Try again: ";
			cin >> book[size].email;

		for (count = foundAt; count < book[size].email.length() 
			&& foundDot == 0; count++)
		{
			if (book[size].email[count] == '.')
			{
				foundDot = count;
			}
		}
	}

	size++;
}

//======================================================
// remove: remove a person from the array
// parameters: 
//    book: the array of structs representing people
//    size: the number of people in the array
// return type: none
//======================================================
void remove(person book[], int &size)
{
	// location: location of person to remove
	int location;

	// find location
	location = found(book, size);

	// delete person
	if (location != -1)
	{
		book[location] = book[size - 1];
		size--;
	}

	// validate input
	else
	{
		cout << "Person not found." << endl;
	}

}

//======================================================
// find: find a person by inputted last name and display
//		the entry
// parameters: 
//    book: the array of structs representing people
//    size: the number of people in the array
// return type: none
//======================================================
void find(person book[], int size)
{
	// location: location of person
	int location;

	// find location
	location = found(book, size);

	// display person
	if (location != -1)
	{
		cout << "Name: " << book[location].firstName << " " 
			<< book[location].lastName << endl;
		cout << "Phone Number: " << book[location].phoneNumber << endl;
		cout << "Email address: " << book[location].email << "\n" << endl;
	}

	// validate input
	else
	{
		cout << "Person not found." << endl;
	}
}

//======================================================
// list: display the array, sorted by last name
// parameters: 
//    book: the array of structs representing people
//    size: the number of people in the array
// return type: none
//======================================================
void list(person book[], int size)
{
	// count: counter for loop
	int count;

	// sort names
	swap(book, size);

	// display names
	for (count = 0; count < size; count++)
	{
		cout << "Name: " << book[count].firstName << " " 
			<< book[count].lastName << endl;
		cout << "Phone Number: " << book[count].phoneNumber << endl;
		cout << "Email address: " << book[count].email << "\n" << endl;
	}
}

//======================================================
// save: save the array to book.txt
// parameters: 
//    book: the array of structs representing people
//    size: the number of people in the array
// return type: none
//======================================================
void save(person book[], int size)
{
	// addressOut: output to book.txt
	// count: counter for loop
	ofstream addressOut;
	addressOut.open("book.txt");
	int count;

	for (count = 0; count < size; count++)
	{
		addressOut << book[count].firstName << endl;
		addressOut << book[count].lastName << endl;
		addressOut << book[count].phoneNumber << endl;
		addressOut << book[count].email << endl;
	}

	cout << "The address book has been saved." << endl;

}

//======================================================
// swap: sort the array
// parameters: 
//    book: the array of structs representing people
//    size: the number of people in the array
// return type: none
//======================================================
void swap(person book[], int size)
{
	// swap: whether or not the array has been sorted
	// temp: placeholder for swapping
	// count: counter for loop
	bool swap;
	person temp;
	int count;

	do
	{
		// set swap to false; it will end the loop if
		// no swaps were made
		swap = false;
		for (count = 0; count < (size - 1); count++)
		{
			// check to see if the names need to be swapped
			if (book[count].lastName > book[count + 1].lastName)
			{
				// swap the data
				temp = book[count];
				book[count] = book[count + 1];
				book[count + 1] = temp;

				// set swap to true to re-run the loop
				swap = true;
			}
		}
	} while (swap);
}

//======================================================
// toLower: make a string all lowercase
// parameters: 
//    name: the string that needs converting
// return type: string (the lowercase string made)
//======================================================
string toLower(string name)
{
	// lc: empty string to return lowercase name
	string lc = " ";

	// add lowercase values to string
	for (int i = 0; i < name.length(); i++)
	{
		lc += tolower(name[i]);
	}

	return lc;
}

//======================================================
// found: find a person by last name in the array
// parameters: 
//    book: the array of structs representing people
//    size: the number of people in the array
// return type: int (the location of the person)
//======================================================
int found(person book[], int size)
{
	// find: name to find
	// temp: temporary name copied from array so the array
	//		won't be altered
	// first: left bound of array to search
	// last: right bound of array to search
	// middle: middle value to search
	// spot: location of name
	// found: whether or not name has been found
	string find, temp;
	int first = 0;
	int last = size;
	int middle, spot;
	bool found = false;

	// prompt for name to be found
	cout << "Person's last name: ";
	cin >> find;
	find = toLower(find);

	// sort names
	swap(book, size);

	// find name
	while (!found && first <= last)
	{
		middle = (first + last) / 2;
		temp = book[middle].lastName;
		temp = toLower(temp);

		if (temp == find)
		{
			found = true;
			spot = middle;
		}

		else if (temp > find)
		{
			last = middle - 1;
		}

		else
		{
			first = middle + 1;
		}
	}

	// validate input
	if (!found)
	{
		spot = -1;
	}

	return spot;
}