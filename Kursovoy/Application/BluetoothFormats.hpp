#pragma once

#include "susudefs.hpp" // for SusuString

class BluetoothFormats 
{
  public:

  char* Getbluetoothformat (float filtervlaznost)
  {
    static char str[40];
    sprintf(str, "%s%.3f %s\n", "Vlaznost: ", filtervlaznost, " %");
    return (str);
  }
};