#include "Car.h"
#include <iostream>
#include <iomanip>
#include "StringFunc.h"
using namespace std;


Car::Car(string n_id, string n_model, int n_qty, double n_price){
  SetRecords(n_id, n_model, n_qty, n_price);
}

void Car::SetRecords(string n_id, string n_model, int n_qty, double n_price){
    ID = n_id;
    Model = n_model;
    Quantity = n_qty;
    Price = n_price;
}

void Car::SetID(string n_id) {
 SetRecords(n_id, Model, Quantity, Price);
}

void Car::SetModel(string n_model) {
  SetRecords(ID, n_model, Quantity, Price);
}

void Car::SetQuantity(int n_qty) {
  SetRecords(ID, Model, n_qty, Price);
}

void Car::SetPrice(double n_price) {
  SetRecords(ID, Model, Quantity, n_price);
}

string Car::GetID() const {
  return ID;
}

string Car::GetModel() const {
  return Model;
}

int Car::GetQuantity() const {
  return Quantity;
}

double Car::GetPrice() const {
  return Price;
}

string Car::ToString() const {
  stringstream recordString;
  recordString << left << setw(11) << GetID() << " |" << left
			 << setw(10) << GetModel() << " | " << right << setw(13)
			 << GetQuantity() << "| " << right << setw(11) << fixed
			 << setprecision(2) << GetPrice() << "\n" << setfill('-') 
       << setw(52) << "-" << setfill(' ') << endl;
  return recordString.str(); 
}
