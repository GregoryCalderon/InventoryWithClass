#include "Inventory.h"
#include "Car.h"
#include "StringFunc.h"
#include <string>
#include <iostream>
#include <iomanip>
#include <fstream>
using namespace std;

Inventory::Inventory(int n_size){
  Size = n_size;
  if(Size > 40) Size = 40;
};


// add a car into inventory 
void Inventory::AddCar(int index,  string id, string model, int qty, double price){
    carInventory[index].SetRecords(id, model, qty, price); 
    ptrArr[index] = &carInventory[index];
}

// retrieve car from inventory 
Car Inventory::GetCar(int index) const{
  return carInventory[index];
}

// retrievve size of inventory 
int Inventory::GetSize() const {
  return Size;
}

// sort chosen attribute
void Inventory::Sort(int key, int count) {
  for(int i = 0; i < count-1; i++)
    {
      for(int j = 0; j < count-i-1; j++)
        {
          bool isGreater = false;
          switch(key) {
            case 1:
              isGreater = ptrArr[j]->GetID() > ptrArr[j+1]->GetID();
              break;
            case 2: 
              isGreater = ptrArr[j]->GetModel() > ptrArr[j+1]->GetModel();
              break;
            case 3:
              isGreater = ptrArr[j]->GetQuantity() > ptrArr[j+1]->GetQuantity();
              break;
            case 4:
              isGreater = ptrArr[j]->GetPrice() > ptrArr[j+1]->GetPrice();
              break;
          }if(isGreater) {
            Car* temp = ptrArr[j];
            ptrArr[j] = ptrArr[j + 1];
            ptrArr[j + 1] = temp;
          }
      }
    }
}


// search record by id or model
void Inventory::SearchRecordByString(int count) {
	string userSrchTerm;
	string foundRecords = "";
	int foundCounter = 0;
	cout << "Enter car ID or Model: ";

	cin >> userSrchTerm;
	cin.clear();
	cin.ignore(numeric_limits<streamsize>::max(), '\n');

	// transform all data to uppercase
	userSrchTerm = TransformToUpper(userSrchTerm);

	// check user search term using partial search against toupper(car.ID)
	for (int i = 0; i < count; i++) {
		int posID = carInventory[i].GetID().find(userSrchTerm);
		int posModel = carInventory[i].GetModel().find(userSrchTerm);

		// if search term found, save to found results
		if (posID != string::npos || posModel != string::npos) {
			foundRecords += carInventory[i].ToString();
      foundCounter++;
		}
	}
	if (foundCounter > 0) {
    cout << SetHeader("Found Records") << foundRecords;
	} else {
		cout << "\nRECORD NOT FOUND. PLEASE TRY AGAIN.";
	}
}


// search record by price
void Inventory::SearchRecordByPrice(int count) {
 	int foundCounter = 0;
 	double searchPrice = -1;
 	double range = -1;
  string foundRecords = "";

 	// get price and range from user
 	searchPrice = AskSearchPrice();
 	range = AskSearchRange();

 	double inRangeLow = searchPrice - (searchPrice * (range / 100));
 	double inRangeHigh = searchPrice + (searchPrice * (range / 100));

 	for (int i = 0; i < count; i++){
 		if (carInventory[i].GetPrice() >= inRangeLow &&
 			carInventory[i].GetPrice() <= inRangeHigh) {
 			foundRecords += carInventory[i].ToString();
 			foundCounter++;
 		}
  }
 	if (foundCounter > 0) {
    cout << SetHeader("Records Found") << foundRecords;
 	} else {
 		cout << "\nRECORD NOT FOUND. PLEASE TRY AGAIN.";
 	}
}

// user search price 
double Inventory::AskSearchPrice() {
 	double searchPrice = -1;
 	do {
 		cout << "Enter Price (larger than 0): ";
 		cin >> searchPrice;
 		cin.clear();
 		cin.ignore(numeric_limits<streamsize>::max(), '\n');
 		if (searchPrice <= 0) {
 			cout << "\nERROR: INVALID PRICE (MUST BE GREATER THAN 0)\n\n"
 				 << endl;
 		}
 	} while (searchPrice <= 0);

 	return searchPrice;
 }

// user search range
double Inventory::AskSearchRange() {
 	double range = -1;
 	do {
 		cout << "Enter price range to search (percent. i.e: 30) Greater or "
 				"Equal to 0: ";
 		cin >> range;
 		cin.clear();
 		cin.ignore(numeric_limits<streamsize>::max(), '\n');
 		if (range < 0) {
 			cout << "\nERROR: INVALID RANGE (MUST BE GREATER THAN OR EQUAL TO "
					"0)\n\n"
 				 << endl;
 		}
 	} while (range < 0);

 	return range;
 }

// set inventory header for print output
string Inventory::SetHeader(string header) {
  stringstream headStr;
  headStr << "\n***" << header << "***\n"
		 << setfill('-') << setw(52) << "-" << setfill(' ') << "\n"
		 << left << setw(11) << "ID"
		 << " |" << left << setw(10) << "Model"
		 << " | " << right << setw(13) << "Qty"
		 << "| " << right << setw(11) << "Price"
		 << "\n"
		 << setfill('-') << setw(52) << "-" << setfill(' ') << endl;
  return headStr.str();
}



// print inventory errors
void Inventory::PrintErrors(int errorCount) {
	int i;
	cout << "\n***Errors***\n"
		 << setfill('-') << setw(70) << "-" << setfill(' ') << endl;

	string errorString;
	ifstream errorInput("errorOutput.txt");
	if (!errorInput.is_open()) {
		cout << "ERROR. Could not open Error file." << endl;
		exit(EXIT_FAILURE);
	}
	if (errorInput.peek() == EOF) {
		cout << "ERROR. OUTPUT FILE IS EMPTY." << endl;
		exit(EXIT_FAILURE);
	}

	while (!errorInput.eof()) {
		getline(errorInput, errorString);
		cout << errorString << endl;
	}

	errorInput.close();
}

// print inventory records
void Inventory::Print(int count, string header) {
 cout << SetHeader(header);
	for (int i = 0; i < count; i++) {
      //cout << GetCar(i).ToString();
      cout << ptrArr[i]->ToString();
    }
}





