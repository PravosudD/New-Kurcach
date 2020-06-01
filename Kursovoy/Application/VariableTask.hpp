#ifndef VARIABLETASK_HPP
#define VARIABLETASK_HPP 

//For OsWrapper::Thread
#include "thread.hpp" //For definition of class Thread
#include "Vlaznost.hpp" //For definition of class Variale
#include "Filter.hpp"//For definition of class Filter
#include <iostream>

using namespace::OsWrapper ;

template <typename myADC>

class VariableTask : public OsWrapper::Thread<512>
{
private:
  
 // inline static float value;
  Filter filter;
  Vlaznost myVlaznost; 
  
public:
  void Execute() override
  {
    myADC::SetChannel(0); //podkluchaem kanali
    myADC::dmaConfig(); //podkluchaem DMA 
    myADC::adcConfig(Resolution::Bits12, tSampleRate::Cycles480, tSampleRate::Cycles480);
  
    for( ; ;)
    {
        myADC::On(); //vkluchaen adc
        myADC::Start();
        myVlaznost.Calculation(myADC::GetCode());
        filter.Update(myVlaznost.GetValue());
        Sleep(100ms);
    } 
  }
  float GetFilterValue ()
  {
    return filter.GetOldFilterValue();
  }
};

#endif 