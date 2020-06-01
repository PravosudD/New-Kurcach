#pragma once
//For OsWrapper::Thread
#include "thread.hpp" //For definition of class Thread
#include "VariableTask.hpp"
#include "BluetoothFormats.hpp"
#include "USART.hpp"
#include <cstring> //For strlen

using namespace::OsWrapper ;

template <typename myUSART, auto& myVariableTask>

class BluetoothTask : public OsWrapper::Thread<512>
{
  private:

  BluetoothFormats bluetoothformat;  
  char* rezault;
  
  public:
    
  void Execute() override
  {
    UsartConfig USART2Config ;
    USART2Config.speed = Speed::Speed9600 ;
    USART2Config.stopbits = StopBits::OneBit ;
    USART2Config.bitssize = BitsSize::Bits8 ;
    USART2Config.parity = Parity::None ;
    USART2Config.samplingmode = SamplingMode::Mode8 ;
    myUSART::Config(USART2Config);
    myUSART::On();

    for( ; ;)
    {
      Sleep(1000ms);
      rezault = bluetoothformat.Getbluetoothformat(myVariableTask.GetFilterValue());
      myUSART::SendData(rezault, strlen(rezault));
    }
  }
};