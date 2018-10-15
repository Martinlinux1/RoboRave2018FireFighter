#include "include.h"

class Fan {
private:
  int *fanPins;
public:
  Fan(short *fanPins);
  void turnFan(bool on, short sensor);
};
