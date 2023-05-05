//Calderon, Gregory

/******** Instructor's Feedback Do NOT DELETE

check feedback.md

*********/
#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>
#include <algorithm>
#include "Inventory.h"
#include "Car.h"
#include "StringFunc.h"

// function declarations
void GetData(Inventory&, int&, int&);
void ShowMenu(Inventory&, int&, int&);
void SearchMenu(Inventory&, int&);
void SortMenu(Inventory&, int&);
void isFileOpen(ifstream&, ofstream&);
bool isDataValid(string, string, int, double, string &);


bool isAllowedAlpha(char);
bool isValidID(string, string &);
bool isIdLength(string, string &);
bool isValidModel(string, string &);
bool isValidQuantity(int, string &);
bool isValidPrice(double, string &);

// main menu options
enum MenuOption {
	VALID = 1,
	INVALID = 2,
	GET_RECORDS = 3,
  SORT = 4,
	QUIT = 5,
};

// search menu options
enum SearchOption {
	SEARCH_ID_MODEL = 1,
	SEARCH_PRICE = 2,
	MENU_MAIN = 3,
};

// sort menu options
enum SortOption {
	SORT_ID = 1,
  SORT_MODEL = 2,
  SORT_QUANTITY = 3,
	SORT_PRICE = 4,
	MAIN = 5,
};

const string ERRORS[] = {
	" Invalid ID format.",
	" Invalid Id Length.",
	" Invalid Model Format.",
	" Invalid Quantity.",
	" Invalid Price.",
};

int main() {
	Inventory CarInventory(20);
	int inventoryCount = 0;
	int errorCount = 0;

	// validate data and store valids, output invalids
	GetData(CarInventory, inventoryCount, errorCount);
	// show main menu to user
	ShowMenu(CarInventory, inventoryCount, errorCount);
	return 0;
}

void isFileOpen(ifstream& inData, ofstream& errorData)
{
	// open files and check if open and check if it opened
	inData.open("carInventory.txt");
	errorData.open("errorOutput.txt");

	if (!inData.is_open()) {
		cout << "ERROR. COULD NOT OPEN INPUT FILE." << endl;
		exit(EXIT_FAILURE);
	}

	if (!errorData.is_open()) {
		cout << "ERROR. COULD NOT OPEN ERROR FILE." << endl;
		inData.close();
		exit(EXIT_FAILURE);
	}

	// format error file
	errorData << fixed << showpoint << setprecision(2);

	// peek to see if file is empty
	if (inData.peek() == EOF) {
		cout << "ERROR. FILE INPUT FILE IS EMPTY." << endl;
		exit(EXIT_FAILURE);
	}
}

// GetData() reads data from the file
void GetData(Inventory& CarInventory, int &inventoryCount, int &errorCount) {
  ifstream inData;
	ofstream errorData;
  isFileOpen(inData, errorData);
 
  string id, model, errMess;
  int qty;

  double price;
  int const MAX =CarInventory.GetSize();
	// if not end of file or out-of-bounds then process record
	while (!inData.eof() && inventoryCount < MAX) {
		inData >> id >> model >> qty >> price;
		bool validData = true;
		validData = isDataValid(id, model, qty, price, errMess);

		// if the data is valid save it into our inventory else save it to error
		if (validData) {
			CarInventory.AddCar(inventoryCount, TransformToUpper(id), TransformToUpper(model), qty, price);
			inventoryCount++;
		} else {
			errorData << id << " " << model << " " << qty << " " << price << " " << errMess << "\n"
					  << endl;

			errMess = "";
			errorCount++;
		}
	}
	if (inventoryCount >= MAX) {
		cout << "\n***WARNING: STORAGE CAPACITY REACHED. SOME RECORDS WERE NOT PROCESSED.***\n"
			 << endl;
	} else if (!inData.eof()) {
		cout << "\n***WARNING: UNPROCESSED RECORDS REMAIN.\n" << endl;
	}
	inData.close();
	errorData.close();
}


void ShowMenu(Inventory& CarInventory, int& inventoryCount, int& errorCount) {
  int option = -1;
	string header = "INVENTORY";
	// do-while loop to display menu until user quits
	do {
		cout << "\n\n***MENU***\n\n"
				"1. Inventory\n"
				"2. Errors\n"
				"3. Search\n"
        "4. Sort\n"
				"5. Quit\n\n"
				"Enter Choice: ";

		cin >> option;
		switch (option) {
		case VALID:
			CarInventory.Print(inventoryCount, "Inventory");
			break;
		case INVALID:
			CarInventory.PrintErrors(errorCount);
			break;
		case GET_RECORDS:
      SearchMenu(CarInventory, inventoryCount);
			break;
    case SORT:
      SortMenu(CarInventory, inventoryCount);
      break;
		case QUIT:
			cout << "\nProgram Terminated" << endl;
			break;
		default:
			cout << "\nInvalid selection. Please choose again.\n" << endl;
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			break;
		}
	} while (option != QUIT);
}

// show search menu
void SearchMenu(Inventory& CarInventory, int& count) {
   	int option = -1;
	do {
		cout << "\n\n***SEARCH MENU***\n\n"
        "Select a Search Option:\n"
				"1. ID or Model\n"
				"2. Price\n"
				"3. Main Menu\n\n"
				"Enter Choice: ";

		cin >> option;
		switch (option) {
		case SEARCH_ID_MODEL:
      CarInventory.SearchRecordByString(count);
      break;
		case SEARCH_PRICE:
			CarInventory.SearchRecordByPrice(count);
			break;
		case MENU_MAIN:
			break;
		default:
			cout << "\nINVALID SELECTION. PLEASE TRY AGAIN.\n" << endl;
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			break;
		}
	} while (option != MENU_MAIN);
}


// show sort menu 
void SortMenu(Inventory& CarInventory, int& count) {
  int option = -1;
	do {
		cout << "\n\n***SORT MENU***\n\n"
        "Select a Sort Option:\n"
				"1. ID\n"
        "2. Model\n"
        "3. Quantity\n"
				"4. Price\n"
				"5. Main Menu\n\n"
				"Enter Choice: ";

		cin >> option;
    
		switch (option) {
    case SORT_ID: 
		case SORT_MODEL:
    case SORT_QUANTITY:
		case SORT_PRICE:
      CarInventory.Sort(option, count);
      CarInventory.Print(count, "Sorted");
		case MAIN:
			break;
		default:
			cout << "\nINVALID SELECTION. PLEASE TRY AGAIN.\n" << endl;
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			break;
		}
	} while (option != MAIN);
}

// validate the data BEFORE passing it to CarInventory[]
bool isDataValid(string id, string model, int quantity, double price, string &errMess) {
	isValidID(id, errMess);
	isValidModel(model, errMess);
	isValidQuantity(quantity, errMess);
	isValidPrice(price, errMess);

	return errMess == "";
}

// check if ID is valid format
bool isValidID(string id, string &errMess) {
	bool isValid = isIdLength(id, errMess);
	int errorMessIndex = 0;
	string firstTwo;
	string middleFour;
	string lastThree;
	firstTwo = Parse(id, 0, 2);
	middleFour = Parse(id, 2, 4);
	lastThree = Parse(id, 4, 6);

	if (isValid) {
		// capitalize for uniformity
		for (int i = 0; i < middleFour.length(); i++) {
			middleFour[i] = toupper(middleFour[i]);
		}

		// check first two elements of ID
		if (!isdigit(firstTwo[0]) || !isdigit(firstTwo[1])) {
			isValid = false;
			// check middle four elements of ID
		} else if (
			!isAllowedAlpha(middleFour[0]) || !isAllowedAlpha(middleFour[1]) ||
			!isAllowedAlpha(middleFour[2]) || !isAllowedAlpha(middleFour[3])) {
			isValid = false;
			// check last three elements of ID
		} else if (
			!isalnum(lastThree[0]) || !isalnum(lastThree[1]) ||
			!isalnum(lastThree[2])) {
			isValid = false;
		}
	}
	if (isValid == false) {
		errMess += ERRORS[errorMessIndex];
	}

	return errMess == "";
}

// check that id is of accepted length
bool isIdLength(string id, string &errMess) {
	const int LENGTH = 9;
	int errorMessIndex = 1;
	if (id.length() != LENGTH) {
		errMess += ERRORS[errorMessIndex];
	}
	return errMess == "";
}

// function that checks ID has valid alpha characters
bool isAllowedAlpha(char a) {
	bool passedAlpha = true;
	if (a > 'S' || a == 'O' || a < 'A') {
		passedAlpha = false;
	}

	return passedAlpha;
}

// function that checks car model is correct format
bool isValidModel(string model, string &errMess) {
	bool modelValid = true;
	int errorMessIndex = 2;
	string firstLetter;
	firstLetter = Parse(model, 0, 1);
  int length = model.length();

	if (!isalpha(firstLetter[0])) {
		modelValid = false;
	}
	for (int i = 0; i < length && modelValid; i++) {
		if (!isalnum(model[i]) && model[i] != '_') {
			modelValid = false;
		}
	}
	if (!modelValid) {
		errMess += ERRORS[errorMessIndex];
	}

	return errMess == "";
}

// Check if quantity is greater than 0
bool isValidQuantity(int quantity, string &errMess) {
	int errorMessIndex = 3;
	if (quantity <= 0) {
		errMess += ERRORS[errorMessIndex];
	}

	return errMess == "";
}

// Check if price is greater than 0
bool isValidPrice(double price, string &errMess) {
	bool priceValid = true;
	int errorMessIndex = 4;
	if (price <= 0) {
		priceValid = false;
		errMess += ERRORS[errorMessIndex];
	}
	return errMess == "";
}

// parse strings for validation
string Parse(string toParse, int pos, int num)
{
  return toParse.substr(pos, num);
}

// transform to uppercase 
string TransformToUpper(string& term) {
  	transform(
 		term.begin(),
 		term.end(),
 		term.begin(),
 		::toupper);
  return term;
}

/*  TEST CASES

***MENU***

1. Inventory
2. Errors
3. Search
4. Sort
5. Quit

Enter Choice: 4

***SORT MENU***

Select a Sort Option:
1. ID
2. Model
3. Quantity
4. Price
5. Main Menu

Enter Choice: 6

INVALID SELECTION. PLEASE TRY AGAIN.


***SORT MENU***

Select a Sort Option:
1. ID
2. Model
3. Quantity
4. Price
5. Main Menu

Enter Choice: 0

INVALID SELECTION. PLEASE TRY AGAIN.

***SORT MENU***

Select a Sort Option:
1. ID
2. Model
3. Quantity
4. Price
5. Main Menu

Enter Choice: 1

***Sorted Array***
----------------------------------------------------
ID          |Model      |           Qty|       Price
----------------------------------------------------
13HGCD456   |MERCEDES   |            12|    55000.00
----------------------------------------------------
16ABCE345   |CHEVY      |           711|    39598.00
----------------------------------------------------
55HEEP245   |FORD       |            44|    89324.22
----------------------------------------------------
82HEFN696   |CHEVY      |            30|    66898.93
----------------------------------------------------
97REED333   |CADILLAC   |             9|    78999.98
----------------------------------------------------


***SORT MENU***

Select a Sort Option:
1. ID
2. Model
3. Quantity
4. Price
5. Main Menu

Enter Choice: 2

***Sorted Array***
----------------------------------------------------
ID          |Model      |           Qty|       Price
----------------------------------------------------
97REED333   |CADILLAC   |             9|    78999.98
----------------------------------------------------
16ABCE345   |CHEVY      |           711|    39598.00
----------------------------------------------------
82HEFN696   |CHEVY      |            30|    66898.93
----------------------------------------------------
55HEEP245   |FORD       |            44|    89324.22
----------------------------------------------------
13HGCD456   |MERCEDES   |            12|    55000.00
----------------------------------------------------


***SORT MENU***

Select a Sort Option:
1. ID
2. Model
3. Quantity
4. Price
5. Main Menu

Enter Choice: 3

***Sorted Array***
----------------------------------------------------
ID          |Model      |           Qty|       Price
----------------------------------------------------
97REED333   |CADILLAC   |             9|    78999.98
----------------------------------------------------
13HGCD456   |MERCEDES   |            12|    55000.00
----------------------------------------------------
82HEFN696   |CHEVY      |            30|    66898.93
----------------------------------------------------
55HEEP245   |FORD       |            44|    89324.22
----------------------------------------------------
16ABCE345   |CHEVY      |           711|    39598.00
----------------------------------------------------

***SORT MENU***

Select a Sort Option:
1. ID
2. Model
3. Quantity
4. Price
5. Main Menu

Enter Choice: 4

***Sorted Array***
----------------------------------------------------
ID          |Model      |           Qty|       Price
----------------------------------------------------
16ABCE345   |CHEVY      |           711|    39598.00
----------------------------------------------------
13HGCD456   |MERCEDES   |            12|    55000.00
----------------------------------------------------
82HEFN696   |CHEVY      |            30|    66898.93
----------------------------------------------------
97REED333   |CADILLAC   |             9|    78999.98
----------------------------------------------------
55HEEP245   |FORD       |            44|    89324.22
----------------------------------------------------


***SORT MENU***

Select a Sort Option:
1. ID
2. Model
3. Quantity
4. Price
5. Main Menu

Enter Choice: 5


***MENU***

1. Inventory
2. Errors
3. Search
4. Sort
5. Quit

Enter Choice: 5

Program Terminated

*/