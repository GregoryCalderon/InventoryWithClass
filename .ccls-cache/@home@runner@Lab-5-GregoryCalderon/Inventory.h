#ifndef INVENTORY
#define INVENTORY
#include "Car.h"
#include <string>
using namespace std;


class Inventory{
  public:
    explicit Inventory(int=40);

    void AddCar(int, string, string, int, double);
    Car GetCar(int) const;
    int GetSize() const;

    void SearchRecordByString(int);
    void SearchRecordByPrice(int);
    double AskSearchPrice();
    double AskSearchRange();
    void Sort(int, int);

    string SetHeader(string);
    void Print(int, string);
    void PrintErrors(int);
 


  private:
   
    int Size;
    Car carInventory[40];
    Car* ptrArr[40]={nullptr};
    
};

#endif