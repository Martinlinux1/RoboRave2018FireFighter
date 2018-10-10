#include "include.h"

class Fan {
private:
  short *fanPins;
public:
  Fan(short *fanPins);
  void turnFan(bool on, short sensor);
};
