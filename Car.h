#ifndef CAR_H
#define CAR_H

#include <string>

using namespace std;

class Car
{
public:
  explicit Car(string = " ", string = " ", int=-1, double=0.0);

  void SetRecords(string, string, int, double);
  void SetID(string);
  void SetModel(string);
  void SetQuantity(int);
  void SetPrice(double);

  string GetID() const;
  string GetModel() const;
  int GetQuantity() const;
  double GetPrice() const;
  string ToString() const;
  friend class Inventory;

protected:
  string ID;
  string Model;
  int Quantity;
  double Price;
};

#endif